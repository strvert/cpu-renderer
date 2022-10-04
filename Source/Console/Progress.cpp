#include "Console/Progress.h"
#include <future>
#include <iostream>
#include <thread>

namespace Raytracer {

Progress::Progress(const std::uint32_t Total, const std::uint32_t BarLength)
    : Total(Total)
    , Current(0)
    , BarLength(BarLength)
{
    WakePrintTask();
}

void Progress::WakePrintTask()
{
    std::future<void> ENotify = EndNotify.get_future();
    Keeper = TaskEnded.get_future().share();

    std::thread PrintTask([&](const std::future<void> Notify, std::promise<void> Ended) {
        std::cout << "\e[?25l" << std::flush;
        while (true) {
            {
                std::unique_lock<std::mutex> Lock(PrintMtx);
                PrintCond.wait(Lock);
                PrintProgress();
            }

            if (Notify.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                PrintProgress();
                std::cout << "\e[?25h" << std::flush;
                std::cout << std::endl;
                break;
            }
        }
        Ended.set_value();
    },
        std::move(ENotify), std::move(TaskEnded));

    PrintTask.detach();
}

void Progress::Increment(const std::uint32_t Value) 
{
    Current += Value;
    PrintCond.notify_all();
}

void Progress::PrintProgress()
{
    const float P = static_cast<float>(Current) / static_cast<float>(Total);
    std::uint32_t Filled = BarLength * P;

    std::cout << "|";
    for (std::uint32_t Idx = 0; Idx < Filled; Idx++) {
        std::cout << "█";
    }
    for (std::uint32_t Idx = 0; Idx < BarLength - Filled; Idx++) {
        std::cout << " ";
    }
    std::cout << "| ";

    std::cout << static_cast<unsigned>((100.0f * static_cast<float>(Current)) / static_cast<float>(Total)) << "%\e[1G";
}

void Progress::Update(const std::uint32_t Value)
{
    Current = Value;
    PrintCond.notify_all();
}

void Progress::End()
{
    EndNotify.set_value();
    PrintCond.notify_all();
    Keeper.wait();
}

}
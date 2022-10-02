#include "Console/Progress.h"
#include <future>
#include <iostream>
#include <thread>

namespace Raytracer {

Progress::Progress(const std::uint32_t Total)
    : Total(Total)
    , Current(0)
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
                PrintProgress(20);
            }

            if (Notify.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                // std::cout << Total << " / " << Total << "\e[1G" << std::endl;
                PrintProgress(20);
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

void Progress::PrintProgress(const std::uint32_t Length)
{
    const float P = static_cast<float>(Current) / static_cast<float>(Total);
    std::uint32_t Filled = Length * P;

    std::cout << "|";
    for (std::uint32_t Idx = 0; Idx < Filled; Idx++) {
        std::cout << "█";
    }
    for (std::uint32_t Idx = 0; Idx < Length - Filled; Idx++) {
        std::cout << " ";
    }
    std::cout << "|";

    std::cout << " ( " << Current << " / " << Total << " )\e[1G";
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
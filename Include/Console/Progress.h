#pragma once

#include <cstdint>
#include <condition_variable>
#include <future>
#include <chrono>

namespace Raytracer {

class Progress {
public:
    Progress(const std::uint32_t Total, const std::uint32_t BarLength = 20);

    void Increment(const std::uint32_t Value);
    void Update(const std::uint32_t Value);
    void End();

private:
    void WakePrintTask();
    void PrintProgress();

    std::uint32_t Total;
    std::uint32_t Current;

    std::uint32_t BarLength;

    std::condition_variable PrintCond;
    std::mutex PrintMtx;

    std::promise<void> EndNotify;
    std::promise<void> TaskEnded;
    std::shared_future<void> Keeper;

    std::chrono::system_clock::time_point StartTimePoint;
};

}

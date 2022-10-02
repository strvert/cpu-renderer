#pragma once

#include <cstdint>
#include <condition_variable>
#include <future>

namespace Raytracer {

class Progress {
public:
    Progress(const std::uint32_t Total);

    void Update(const std::uint32_t Value);
    void End();

private:
    void WakePrintTask();
    void PrintProgress(const std::uint32_t Length);

    std::uint32_t Total;
    std::uint32_t Current;

    std::condition_variable PrintCond;
    std::mutex PrintMtx;

    std::promise<void> EndNotify;
    std::promise<void> TaskEnded;
    std::shared_future<void> Keeper;
};

}
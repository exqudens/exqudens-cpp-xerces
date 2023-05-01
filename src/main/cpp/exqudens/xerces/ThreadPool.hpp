#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <type_traits>

#include "exqudens/xerces/export.hpp"
#include "exqudens/xerces/macros.hpp"

namespace exqudens::xerces {

  class EXQUDENS_XERCES_EXPORT ThreadPool {

    private:

      size_t queueSize;
      std::queue<std::function<void()>> queue;
      std::vector<std::thread> threads;
      std::mutex mutex;
      std::condition_variable condition;
      bool stop;

    public:

      ThreadPool();

      explicit ThreadPool(size_t queueSize);

      ThreadPool(size_t queueSize,size_t threadSize);

      template<class F, class... ARGS>
      auto submit(F&& f, ARGS&&... args) -> std::future<typename std::invoke_result<F, ARGS...>::type>;

      ~ThreadPool();
  };

  template<class F, class... ARGS>
  auto ThreadPool::submit(F&& f, ARGS&&... args) -> std::future<typename std::invoke_result<F, ARGS...>::type> {
    try {
      if (queue.size() >= queueSize) {
        throw std::runtime_error(CALL_INFO() + ": queue overflow");
      }
      using return_type = typename std::invoke_result<F, ARGS...>::type;
      auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<ARGS>(args)...));
      std::future<return_type> res = task->get_future();
      {
        std::unique_lock<std::mutex> lock(mutex);
        if(stop) {
          throw std::runtime_error(CALL_INFO() + ": submitted on stopped 'ThreadPool'");
        }
        queue.emplace([task] { (*task)(); });
      }
      condition.notify_one();
      return res;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

}

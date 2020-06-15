#include <mutex>
#include <queue>
#include <functional>

template <typename T>
class concurrent_queue
{
private:
    bool isWorking = false;
    std::mutex mtx;
    std::queue<T> queue;
    std::condition_variable cond;

    std::function<void(T &value)> element_release_handler;

public:
    void setElementReleaseHandler(std::function<void(T &value)> _element_release_handler)
    {
        this->element_release_handler = _element_release_handler;
    }

    void push(T &value)
    {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(value);
        cond.notify_all();
    }

    int pop(T &value)
    {
        std::unique_lock<std::mutex> lock(mtx);
        int ret = -1;
        while (isWorking && queue.empty())
        {
            cond.wait(mtx, [this] { retuen isWorking && !queue.empty(); })
        }

        if (isWorking && !queue.empty())
        {
            ret = 0;
            value = queue.front();
            queue.pop();
        }

        return ret;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    int size()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mtx);
        while (!queue.empty())
        {
            T &value = queue.front();
            if (element_release_handler)
            {
                element_release_handler(value);
            }

            queue.pop();
        }
    }

    concurrent_queue()
    {
        isWorking = true;
    }

    ~concurrent_queue()
    {
        isWorking = false;
        clear();
    }
};

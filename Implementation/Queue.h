
#include <thread>
#include <mutex>
#include <queue>

#ifndef QUEUEH
#define QUEUEH


using namespace std;
template <class T>
class ConcurrentQueue {

private:
std::mutex _queue_mutex;
std::queue<T> _queue;

public :

ConcurrentQueue() {
}

void addItem(T t){

std::lock_guard<std::mutex> lock(_queue_mutex);
_queue.push_front(t);

}

T removeItem() {
std::lock_guard<std::mutex> lock(_queue_mutex);
return _queue.pop_back();
}

};


#endif

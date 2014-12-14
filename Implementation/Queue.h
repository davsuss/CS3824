#ifndef QUEUEH
#define QUEUEH

#include <thread>
#include <mutex>
#include <queue>
#include "Helper.h"
using namespace std;

class ConcurrentQueue {

private:
std::mutex _queue_mutex;
std::queue<motifResults*> _queue;

public:
ConcurrentQueue() {
}

void addItem(motifResults* t){

std::lock_guard<std::mutex> lock(_queue_mutex);
_queue.push(t);

}

motifResults* removeItem() {
std::lock_guard<std::mutex> lock(_queue_mutex);

motifResults* results =_queue.front();
_queue.pop();
return results;
}

};


#endif

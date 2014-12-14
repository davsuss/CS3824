#include "Queue.h"

void ConcurrentQueue::addItem(motifResults* t){
cerr << "HI";
std::lock_guard<std::mutex> lock(_queue_mutex);
cerr << "BYE";
_queue.push(t);

}
motifResults* ConcurrentQueue::removeItem() {

std::lock_guard<std::mutex> lock(_queue_mutex);
motifResults* result = _queue.front();
_queue.pop();
return result;
}

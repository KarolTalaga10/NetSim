// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#include "package.hpp"
#include "storage_types.hpp"

Package& PackageQueue::pop() {
    if(get_queue_type()==PackageQueueType::FIFO)
    {
        Package& pck = mQueue.front();
        mQueue.pop_front();

        return pck;
    }
    else
    {
        Package& pck = mQueue.back();
        mQueue.pop_back();

        return pck;
    }

    /*
   Package& pck();
   switch(get_queue_type())
   {
       case PackageQueueType::FIFO :
       {
           pck = mQueue.front();
           mQueue.pop_front();
       }
       break;
       case PackageQueueType::LIFO :
       {
           pck = mQueue.back();
           mQueue.pop_back();
       }
       break;
   }
   return pck;
   */
}

void PackageQueue::push(Package &&pck) {
    mQueue.push_back(std::move(pck));
}

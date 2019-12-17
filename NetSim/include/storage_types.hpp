
// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include <cstddef>
#include "package.hpp"
#include <string>
#include <list>
#include <deque>


enum class PackageQueueType{
    FIFO, LIFO
};


class IPackageStockpile{
public:
    using iterator = std::deque<Package>::const_iterator;

    virtual void push(Package&& pck) = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
    virtual iterator cbegin() const = 0;
    virtual iterator cend() const = 0;

};


class IPackageQueue: public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue: public IPackageQueue{
private:
    PackageQueueType mQueueType;
    std::deque<Package> mQueue;
    std::list<Package> mList;
public:
    PackageQueue(PackageQueueType queueType) : mQueueType(queueType) {}
    PackageQueueType get_queue_type() const override { return mQueueType; }

    Package pop() override;
    void push(Package&& pck) override;
    bool empty() const override     { return mQueue.empty();  }
    size_t size() const override    { return mQueue.size();   }
    iterator begin() const override { return mQueue.begin();  }
    iterator end() const override   { return mQueue.end();    }
    iterator cbegin()const override { return mQueue.cbegin(); }
    iterator cend() const override  { return mQueue.cend();   }
};

#endif //NETSIM_STORAGE_TYPES_HPP


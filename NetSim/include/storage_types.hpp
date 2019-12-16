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

};


class IPackageQueue: IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue: IPackageQueue{
public:
    virtual void push(Package&& pck) = 0;
    virtual bool empty() = 0;
    virtual size_t size() = 0;
};

#endif //NETSIM_STORAGE_TYPES_HPP

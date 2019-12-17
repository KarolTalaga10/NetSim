
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
    using const_iterator = std::deque<Package>::const_iterator;
    using iterator = std::deque<Package>::iterator;

    virtual void push(Package&& pck) = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

};


class IPackageQueue: IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue: IPackageQueue{
public:
    using const_iterator = std::deque<Package>::const_iterator;
    using iterator = std::deque<Package>::iterator;

    PackageQueue(PackageQueueType QueueType) : mQueueType(QueueType) {}
    Package pop() override;
    void push(Package&& pck) override;
    bool empty() const override;
    size_t size() const override;
    iterator begin() const override;
    iterator end() const override;
    const_iterator cbegin()const override;
    const_iterator cend() const override;

private:
    PackageQueueType mQueueType;
    std::list<Package> package_list;
};

#endif //NETSIM_STORAGE_TYPES_HPP


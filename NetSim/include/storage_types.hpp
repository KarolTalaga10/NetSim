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

};


class IPackageQueue: IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue: IPackageQueue{
public:
    PackageQueue(PackageQueueType _mQueueType) : mQueueType(_mQueueType) {}

    void puch(Package&& pck) override;

    Package pop() const override;

    bool empty() const override;

    size_t size() const override;

    iterator begin() override;

    iterator end() override;

    const_iterator cbegin() override;

    const_iterator begin() override;

private:
    PackageQueueType mQueueType;
    std::list<Package> package_list;
};

#endif //NETSIM_STORAGE_TYPES_HPP

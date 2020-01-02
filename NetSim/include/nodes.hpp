#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include <optional>
#include <memory>
#include <map>
#include "package.hpp"
#include "storage_types.hpp"
#include <functional>
#include "helpers.hpp"

class IPackageReceiver
{
    using iterator = std::list<Package>::const_iterator;
public:
    virtual void receive_package(Package&& pck) = 0;
    virtual void get_ID(ElementID id) = 0;

    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
    virtual iterator cbegin() const = 0;
    virtual iterator cend() const = 0;
};

class ReceiverPreferences
{
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;
private:
    preferences_t mPreferences;
    void rebuild_pref();
    std::function<double(void)> mRng;
public:
    ReceiverPreferences(std::function<double(void)> rng = get_random) : mRng(std::move(rng)) {}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();

    iterator begin()              { return mPreferences.begin();  }
    iterator end()                { return mPreferences.end();    }
    const_iterator cbegin() const { return mPreferences.cbegin(); }
    const_iterator cend()   const { return mPreferences.cend();   }
};

class PackageSender
{
private:
    std::optional<Package> mBuffer;
public:
    ReceiverPreferences mReceiverPreferences;
    void send_package();
    std::optional<Package> get_sending_buffer();
protected:
    void push_package(Package&& pck);
};

class Ramp : PackageSender
{
private:
    TimeOffset mOffset;
    ElementID mID;
public:
    Ramp(ElementID id, TimeOffset offset) : mOffset(offset), mID(id) {}
    void deliver_goods(Time time);
    TimeOffset get_delivery_interval() const;
    ElementID get_ID() const;
};

class Worker : PackageSender, IPackageReceiver
{
private:
    Time mTime;
    TimeOffset mOffset;
    ElementID mID;
    std::optional<Package> mWorkerBuffer;
public:
    Worker(ElementID id, TimeOffset offset, std::unique_ptr<PackageQueue> queue_ptr);
    void do_work(Time time);
    TimeOffset get_processing_duration() const;
    Time get_package_processing_start_time() const { return mTime; }
};

class Storehouse : IPackageReceiver
{
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> queue_ptr);
};


#endif //NETSIM_NODES_HPP

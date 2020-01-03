#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include <optional>
#include <memory>
#include <map>
#include "package.hpp"
#include "storage_types.hpp"
#include <functional>
#include "helpers.hpp"

enum class NodeIdentity{
    RAMP, WORKER, STOREHOUSE
};

class IPackageReceiver
{
public:
    using iterator = std::list<Package>::const_iterator;
    virtual void receive_package(Package&& pck) = 0;
    virtual ElementID get_ID() = 0;

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
    ProbabilityGenerator mRng;
public:
    ReceiverPreferences(ProbabilityGenerator rng = get_random) : mRng(std::move(rng)) {}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver(); //TODO troche nie wiem jak zaimplementowac ta dystrybuantę

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
    std::optional<Package> get_sending_buffer() {return std::move(mBuffer);}; //TODO chuj wie jak to działa
protected:
    void push_package(Package&& pck);
};

class Ramp : public PackageSender
{
private:
    TimeOffset mOffset;
    ElementID mID;
public:
    Ramp(ElementID id, TimeOffset di) : mOffset(di), mID(id) {}
    void deliver_goods(Time time);
    TimeOffset get_delivery_interval()  const {return mOffset; }
    ElementID get_ID()                  const { return mID;    }
};

class Worker : public PackageSender, public IPackageReceiver
{
private:
    Time mTime = 0;
    TimeOffset mOffset;
    ElementID mID;
    std::optional<Package> mWorkerBuffer;
    std::unique_ptr<PackageQueue> mUniquePtr;
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> queue_ptr);
    void do_work(Time time);
    TimeOffset get_processing_duration()     const { return mOffset; }
    Time get_package_processing_start_time() const { return mTime;   }
};

class Storehouse : public IPackageReceiver
{
private:
    std::unique_ptr<IPackageStockpile> mUniquePtr;
    ElementID mID;
    std::list<Package> mStorage;

public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> stockpile_ptr);
    std::list<Package> get_storage() {return mStorage;}
    void receive_package(Package&& pck) override;
    ElementID get_ID() override;
    std::list<Package> check_storage();

    iterator begin() const override { return mStorage.begin();  }
    iterator end() const override   { return mStorage.end();    }
    iterator cbegin()const override { return mStorage.cbegin(); }
    iterator cend() const override  { return mStorage.cend();   }
};


#endif //NETSIM_NODES_HPP

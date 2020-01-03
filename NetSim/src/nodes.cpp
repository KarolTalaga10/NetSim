#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver* r)
{
    mPreferences.emplace(std::make_pair(r,0.0)); // get_random()
    rebuild_pref();
}
void ReceiverPreferences::remove_receiver(IPackageReceiver* r)
{
    mPreferences.erase(r);
    rebuild_pref();
}
IPackageReceiver* ReceiverPreferences::choose_receiver()
{
    double number = mRng();
    double sum = 0;
    for (const auto &item: mPreferences)
    {
        sum = sum + item.second;
        if(number <= sum)
            return item.first;
    }
    return mPreferences.end()->first;
}
void ReceiverPreferences::rebuild_pref()
{
    double sum = 0;
    for(auto& item : mPreferences)
    {
        sum+= item.second;
    }

    for(auto& item : mPreferences)
    {
        item.second /= sum;
    }
}
void PackageSender::send_package()
{
    if(mBuffer)
    {
        mReceiverPreferences.choose_receiver()->receive_package(std::move(*mBuffer));
        std::cout<< (*mBuffer).get_id()<<std::endl;
        mBuffer.reset();
    }
}
void PackageSender::push_package(Package&& pck)
{
    mBuffer.emplace(std::move(pck));
}
void Ramp::deliver_goods(Time time)
{
    if(time % mOffset == 0)
    {
        Package pkc;
        push_package(std::move(pkc));
        send_package();
    }
}
Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> queue_ptr)
{
    mID = id; mOffset = pd;
    mUniquePtr = std::move(queue_ptr);
}
void Worker::do_work(Time time)
{
    if((time-mTime)% mOffset == 0)
    {
        if(mWorkerBuffer)
        {
            push_package(std::move(*mWorkerBuffer));
            mWorkerBuffer.reset();
        }
        mWorkerBuffer.emplace(mUniquePtr->pop());
        send_package();
    }
   
    mTime = time;
}
Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> stockpile_ptr)
{
    mID = id;
    mUniquePtr = std::move(stockpile_ptr);
}

void Storehouse::receive_package(Package&& pck)
{
    mStorage.push_back(std::move(pck));
}


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
}/*
IPackageReceiver* ReceiverPreferences::choose_receiver()
{

}*/
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

}
void PackageSender::push_package(Package&& pck)
{
    mBuffer.emplace(std::move(pck));
}/*
void Ramp::deliver_goods(Time time)
{

}*/
Worker::Worker(ElementID id, TimeOffset offset, std::unique_ptr<PackageQueue> queue_ptr)
{
    mID = id; mOffset = offset;
    mWorkerBuffer.emplace(queue_ptr->pop());
}
void Worker::do_work(Time time)
{
    mTime = time;
}/*
Storehouse::Storehouse(ElementID id, std::unique_ptr<PackageQueue> queue_ptr)
{

}
*/
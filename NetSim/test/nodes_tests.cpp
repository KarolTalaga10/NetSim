#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nodes.hpp"

TEST(StorehouseTest, CorrectReceivingTest) {
    PackageQueue q(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(q);
    Storehouse s(1, std::move(ptr));
    Ramp r(1,2);
    r.mReceiverPreferences.add_receiver(&s);
    r.deliver_goods(0);
    r.deliver_goods(1);
    r.deliver_goods(2);
    EXPECT_EQ(2, s.cend()->get_id());
}
/*
TEST(ReceiverPreferences, ProbabilityScalingTest) {
    std::function<double(void)> rng = your_num;
    ReceiverPreferences pref(rng);
    IPackageReceiver* r1;
    IPackageReceiver* r2;
    pref.add_receiver(r1);
    pref.add_receiver(r2);
    EXPECT_EQ(0.5, pref.get_probability(r1));
}
*/
TEST(WorkerBuffer, PackageReceivedInBuffer) {
    PackageQueue q(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(q);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.mReceiverPreferences.add_receiver(&w);
    w.mReceiverPreferences.add_receiver(&s);
    r.deliver_goods(0);
    w.do_work(0);
    r.deliver_goods(1);
    w.do_work(1);
    r.deliver_goods(2);
    w.do_work(2);
    EXPECT_EQ(1, w.get_ID_from_buffer());
}

TEST(WorkerTime, CorrectTimeProcessingPackage) {
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(q2);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.mReceiverPreferences.add_receiver(&w);
    w.mReceiverPreferences.add_receiver(&s);
    r.deliver_goods(0);
    w.do_work(0);
    r.deliver_goods(1);
    w.do_work(1);
    r.deliver_goods(2);
    w.do_work(2);

    EXPECT_EQ(1, s.cbegin()->get_id());
}





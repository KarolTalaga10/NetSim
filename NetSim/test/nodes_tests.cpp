#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nodes.hpp"
/*
---------------- TEST EXAMPLE ----------------
2 Workers: w1(FIFO), w2(LIFO)
2 Ramps: r1, r2
2 Storehouses: s1(FIFO), s2(LIFO)

TEST(FunctionalityName, TestingCase) {
    PackageQueue q1(PackageQueueType::FIFO);
	PackageQueue q2(PackageQueueType::LIFO);
	PackageQueue q3(PackageQueueType::FIFO);
	PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
	Storehouse s1(1, std::move(ptr3));
	Storehouse s2(2, std::move(ptr4));
	Ramp r1(1, 1);
	Ramp r2(2, 2);
	Worker w1(1, 1, std::move(ptr1));
	Worker w2(2, 2, std::move(ptr2));
    //-----------------------------------------------
    // make your own preferences
    //e.x. r1.mReceiverPreferences.add_receiver(&w1);
    //-----------------------------------------------
    // test logic

    EXPECT_EQ(WhatWeExpect, FunctionCall);
}
 */



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





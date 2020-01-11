#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nodes.hpp"
/*
---------------- TEST EXAMPLE ----------------
2 Workers: w1(FIFO), w2(LIFO)
2 Ramps: r1, r2
2 Storehouses: s1(FIFO), s2(LIFO)

TEST(FunctionalityNameTest, TestingCase) {
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

TEST(PackageSenderTest, EmptyBufferTest) { //wysyłanie półproduktu: czy po wysłaniu bufor jest pusty?
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    //-----------------------------------------------
    // make your own preferences
    //e.x. r1.mReceiverPreferences.add_receiver(&w1);
    r1.receiver_preferences_.add_receiver(&w1);
    //-----------------------------------------------
    // test logic
    r1.deliver_goods(0);
    r1.send_package();

    EXPECT_EQ(std::nullopt, r1.get_sending_buffer());
}

TEST(RampTest, DeliveryTest) { //dostawa: czy dostawa odbywa się we właściwej turze? czy półprodukt trafia od razu do bufora?
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    //-----------------------------------------------
    // make your own preferences
    //e.x. r1.mReceiverPreferences.add_receiver(&w1);
    r2.receiver_preferences_.add_receiver(&w1);
    r2.deliver_goods(0);
    r2.send_package();
    r2.deliver_goods(1);
    r2.send_package();
    r2.deliver_goods(2);
    //-----------------------------------------------
    // test logic
    EXPECT_EQ(1, r2.get_sending_buffer().has_value());
}

TEST(RampTest, NotDeliveryTest) { //dostawa: czy dostawa odbywa się we właściwej turze? czy półprodukt trafia od razu do bufora?
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    //-----------------------------------------------
    // make your own preferences
    //e.x. r1.mReceiverPreferences.add_receiver(&w1);
    r2.receiver_preferences_.add_receiver(&w1);
    r2.deliver_goods(0);
    r2.send_package();
    r2.deliver_goods(1);

    //-----------------------------------------------
    // test logic
    EXPECT_EQ(0, r2.get_sending_buffer().has_value());
}

TEST(StorehouseTest, CorrectReceivingTest) {
    std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    Storehouse s(1, std::move(ptr));
    Ramp r(1,2);
    r.receiver_preferences_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    r.deliver_goods(1);
    r.send_package();
    r.deliver_goods(2);
    r.send_package();
    EXPECT_EQ(2, s.cend()->get_id());
}

TEST(ReceiverPreferencesTest, CorectReceiver) {
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
    std::function<double(void)> rng = your_num;
    ReceiverPreferences pref(rng);

    IPackageReceiver* rec1;
    IPackageReceiver* rec2;

    rec1 = &w1;
    rec2 = &w2;

    pref.add_receiver(&w1);
    pref.add_receiver(&w2);
    // test logic

    EXPECT_EQ(__min(rec1, rec2), pref.choose_receiver());
}


TEST(ReceiverPreferences, ProbabilityScalingTest) {
    std::function<double(void)> rng = your_num;
    ReceiverPreferences pref(rng);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    IPackageReceiver* r1;
    IPackageReceiver* r2;
    r1 = &w1;
    r2 = &w2;
    pref.add_receiver(r1);
    pref.add_receiver(r2);
    EXPECT_EQ(0.5, pref.get_probability(r2));
}

TEST(WorkerBuffer, PackageReceivedInBuffer) {
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.receiver_preferences_.add_receiver(&w);
    w.receiver_preferences_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    w.do_work(0);
    w.send_package();
    r.deliver_goods(1);
    r.send_package();
    w.do_work(1);
    w.send_package();
    r.deliver_goods(2);
    r.send_package();
    w.do_work(2);
    w.send_package();
    EXPECT_EQ(1, w.get_ID_from_buffer());
}

TEST(WorkerTime, CorrectTimeProcessingPackage) { //wykonywanie pracy: czy robotnik przetwarza półprodukt odpowiednią liczbę tur? czy przekazuje dalej odpowiedni półprodukt?
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.receiver_preferences_.add_receiver(&w);
    w.receiver_preferences_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    w.do_work(0);
    w.send_package();
    r.deliver_goods(1);
    r.send_package();
    w.do_work(1);
    w.send_package();
    r.deliver_goods(2);
    r.send_package();
    w.do_work(2);
    w.send_package();

    EXPECT_EQ(1, s.cbegin()->get_id());
}





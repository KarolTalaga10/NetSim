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

TEST(ReceiverPreferences, ProbabilityScalingTest) {
    std::function<double(void)> rng = your_num;
    ReceiverPreferences pref(rng);
    IPackageReceiver* r1;
    IPackageReceiver* r2;
    pref.add_receiver(r1);
    pref.add_receiver(r2);
    EXPECT_EQ(0.5, pref.get_probability(r1));
}


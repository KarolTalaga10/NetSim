#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nodes.hpp"
TEST(StorageFIFOTest, FirstLastProduct) {
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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "package.hpp"
/*
TEST(PackageInitTest, firstPackageID) {
    Package pack1;

    EXPECT_EQ(1, pack1.get_id());
}

TEST(PackageAssignTest, secondPackageID) {
    Package pack1;
    Package pack2;

    EXPECT_EQ(2, pack2.get_id());
}


TEST(PackageCopyTest, changePackageID) {
    Package pack1;
    Package pack2(static_cast<Package&&>(pack1));

    EXPECT_EQ(1, pack2.get_id());
}

TEST(PackageOperatorTest, changingPackageID) {
    Package pack1;
    Package pack2;

    pack2.operator=(static_cast<Package&&>(pack1));

    EXPECT_EQ(1, pack2.get_id());
}

TEST(PackageidTest, changePackageID){
    Package pack1;
    Package pack2;

    EXPECT_TRUE(pack1.get_id() != pack2.get_id());
}
*/
#include "storage_types.hpp"


TEST(PackageQueueInitIsEmptyLIFOTest, IsEmptyTest) {
    PackageQueue packageQueue(PackageQueueType::LIFO);

    EXPECT_EQ(true, packageQueue.empty());
}


TEST(PackageQueueInitIsEmptyFIFOTest, IsEmptyTest) {
    PackageQueue packageQueue(PackageQueueType::FIFO);

    EXPECT_EQ(true, packageQueue.empty());
}

TEST(PackageQueueInitSizeLIFOTest, SizeTest) {
    PackageQueue packageQueue(PackageQueueType::LIFO);

    EXPECT_EQ(0, packageQueue.size());
}


TEST(PackageQueueInitSizeFIFOTest, SizeTest) {
    PackageQueue packageQueue(PackageQueueType::FIFO);

    EXPECT_EQ(0, packageQueue.size());
}


TEST(PackageQueueLIFOGetQueueTypeTest, GetQueueTest) {
    PackageQueue packageQueue(PackageQueueType::LIFO);

    EXPECT_EQ(PackageQueueType::LIFO, packageQueue.get_queue_type());
}


TEST(PackageQueueFIFOGetQueueTypeTest, GetQueueTest) {
    PackageQueue packageQueue(PackageQueueType::FIFO);

    EXPECT_EQ(PackageQueueType::FIFO, packageQueue.get_queue_type());
}


TEST(PackageQueuePushSizeTest, PackagePushSizeTest) {
    Package pack;

    PackageQueue packageQueue(PackageQueueType::LIFO);
    packageQueue.push(static_cast<Package &&>(pack));

    EXPECT_EQ(1, packageQueue.size());
}


TEST(PackageQueuePushIsEmptyTest, PackageQueuePushIsEmptyTest) {
    Package pack;

    PackageQueue packageQueue(PackageQueueType::LIFO);
    packageQueue.push(static_cast<Package &&>(pack));

    EXPECT_EQ(false, packageQueue.empty());
}


TEST(PackageQueuePopLIFOTest, PackageQueuePopTest) {
    Package pack1;
    Package pack2;

    PackageQueue packageQueue(PackageQueueType::LIFO);
    packageQueue.push(static_cast<Package &&>(pack1));
    packageQueue.push(static_cast<Package &&>(pack2));

    packageQueue.pop();

    EXPECT_EQ(1, packageQueue.size());
}


TEST(PackageQueuePopFIFOTest, PackageQueuePopTest) {
    Package pack1;
    Package pack2;

    PackageQueue packageQueue(PackageQueueType::FIFO);
    packageQueue.push(static_cast<Package &&>(pack1));
    packageQueue.push(static_cast<Package &&>(pack2));

    packageQueue.pop();

    EXPECT_EQ(1, packageQueue.size());
}
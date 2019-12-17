#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "package.hpp"

TEST(PackageInitTest, firstPackageID) {
Package pack1;

EXPECT_EQ(1, pack1.get_id());
}

TEST(PackageAssignTest, secondPackageID) {
Package pack1;
Package pack2;

EXPECT_EQ(2, pack2.get_id());
}
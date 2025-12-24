#include <gtest/gtest.h>

TEST(BasicTest, MathWorks) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(StrategyTest, InitialBalance) {
    double initial_cash = 1000.0;
    EXPECT_GT(initial_cash, 0.0);
}
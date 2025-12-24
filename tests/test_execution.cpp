#include <gtest/gtest.h>
#include "backtester/SimulatedExecutionHandler.hpp"

TEST(ExecutionHandlerTest, ExecutesOrderCorrectly) {
    SimulatedExecutionHandler handler(0.0);

    Tick marketTick{1000, 50000.0, 1.0, Side::Sell, false};
    Order order{1000, "BTCUSDT", Side::Buy, 0.5};

    auto execOpt = handler.onOrder(order, marketTick);

    ASSERT_TRUE(execOpt.has_value());
    const Execution& exec = execOpt.value();

    EXPECT_EQ(exec.price, 50000.0);
    EXPECT_EQ(exec.quantity, 0.5);
    EXPECT_DOUBLE_EQ(exec.fee, 0.0);
    EXPECT_EQ(exec.side, Side::Buy);
}

TEST(ExecutionHandlerTest, CalculatesFeesCorrectly) {
    SimulatedExecutionHandler handler(0.001);

    Tick marketTick{2000, 100.0, 1.0, Side::Sell, false}; 
    Order order{2000, "TEST", Side::Buy, 10.0}; 

    auto execOpt = handler.onOrder(order, marketTick);
    
    ASSERT_TRUE(execOpt.has_value());
    const Execution& exec = execOpt.value();

    EXPECT_DOUBLE_EQ(exec.fee, 1.0);
    EXPECT_EQ(handler.getExecutions().size(), 1);
}
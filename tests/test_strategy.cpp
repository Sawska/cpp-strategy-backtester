#include <gtest/gtest.h>
#include "backtester/MeanReversionStrategy.hpp"

class StrategyTest : public ::testing::Test {};

TEST_F(StrategyTest, ReturnsUnknownWhenNotEnoughData) {
    MeanReversionStrategy strategy(5, 2.0);
    Tick t{0, 100.0, 1.0, Side::Unknown, false};

    for(int i=0; i<4; ++i) {
        EXPECT_EQ(strategy.onTick(t), Side::Unknown);
    }
}

TEST_F(StrategyTest, TriggersSellOnSpikeUp) {
    MeanReversionStrategy strategy(5, 1.5);

    Tick stableTick{0, 100.0, 1.0, Side::Unknown, false};
    for(int i=0; i<5; ++i) {
        strategy.onTick(stableTick);
    }

    Tick spikeTick{0, 110.0, 1.0, Side::Buy, false};
    
    Side signal = strategy.onTick(spikeTick);
    EXPECT_EQ(signal, Side::Sell);
}

TEST_F(StrategyTest, TriggersBuyOnDrop) {
    MeanReversionStrategy strategy(5, 1.5);

    Tick stableTick{0, 100.0, 1.0, Side::Unknown, false};
    for(int i=0; i<5; ++i) {
        strategy.onTick(stableTick);
    }

    Tick dropTick{0, 90.0, 1.0, Side::Sell, false};
    
    Side signal = strategy.onTick(dropTick);
    EXPECT_EQ(signal, Side::Buy);
}

TEST_F(StrategyTest, StaysQuietWithinBands) {
    MeanReversionStrategy strategy(10, 2.0);

    for(int i=0; i<20; ++i) {
        Tick t{0, 100.0 + (i%2 == 0 ? 1.0 : -1.0), 1.0, Side::Unknown, false}; 
        strategy.onTick(t);
    }
}
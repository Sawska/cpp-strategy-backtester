#include <gtest/gtest.h>
#include "backtester/portfolio/PortfolioHandler.hpp"

TEST(PortfolioTest, InitialBalanceIsCorrect) {
    PortfolioHandler portfolio(10000.0);
    EXPECT_DOUBLE_EQ(portfolio.getCash(), 10000.0);
    EXPECT_DOUBLE_EQ(portfolio.getPosition("BTC"), 0.0);
}

TEST(PortfolioTest, UpdatesOnBuy) {
    PortfolioHandler portfolio(10000.0);
    
    Execution exec{0, "BTC", Side::Buy, 5000.0, 1.0, 10.0, "id1"};
    portfolio.onExecution(exec);

    EXPECT_DOUBLE_EQ(portfolio.getCash(), 4990.0);
    EXPECT_DOUBLE_EQ(portfolio.getPosition("BTC"), 1.0);
}

TEST(PortfolioTest, UpdatesOnSell) {
    PortfolioHandler portfolio(0.0); 
    
    Execution exec{0, "BTC", Side::Sell, 6000.0, 0.5, 5.0, "id2"};
    portfolio.onExecution(exec);

    EXPECT_DOUBLE_EQ(portfolio.getCash(), 2995.0);
    EXPECT_DOUBLE_EQ(portfolio.getPosition("BTC"), -0.5); // Short position
}

TEST(PortfolioTest, CalculatesTotalValue) {
    PortfolioHandler portfolio(1000.0);

    Execution exec{0, "COIN", Side::Buy, 10.0, 10.0, 0.0, "id1"};
    portfolio.onExecution(exec);


    std::map<std::string, double> marketPrices;
    marketPrices["COIN"] = 20.0;

    EXPECT_DOUBLE_EQ(portfolio.getTotalValue(marketPrices), 1100.0);
}
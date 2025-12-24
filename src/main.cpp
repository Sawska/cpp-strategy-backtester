#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include "backtester/data/CsvTickLoader.hpp"
#include "backtester/strategy/MeanReversionStrategy.hpp"
#include "backtester/execution/SimulatedExecutionHandler.hpp"
#include "backtester/portfolio/PortfolioHandler.hpp"

int main() {
    std::string filename = "data/market_data.csv"; 
    
    std::cout << "Loading data from: " << filename << std::endl;

    CsvTickLoader loader(filename);

    MeanReversionStrategy strategy(20, 2.0);

    SimulatedExecutionHandler executionHandler(0.001);

    PortfolioHandler portfolio(10000.0);

    std::cout << "Starting Backtest..." << std::endl;
    std::cout << "Initial Balance: " << portfolio.getCash() << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    int tickCount = 0;
    double lastPrice = 0.0; 

    while (true) {
        auto tickOpt = loader.next();
        if (!tickOpt.has_value()) break;
        
        const Tick& tick = tickOpt.value();
        lastPrice = tick.price;
        tickCount++;

        
        Side signal = strategy.onTick(tick);

        if (signal != Side::Unknown) {
            Order order;
            order.timestamp = tick.timestamp;
            order.symbol = "BTCUSDT";
            order.side = signal;
            order.quantity = 1.0; 

            auto execOpt = executionHandler.onOrder(order, tick);

            if (execOpt.has_value()) {
                const Execution& exec = execOpt.value();
                
                portfolio.onExecution(exec);

                std::cout << "Tick #" << tickCount 
                          << " | " << (exec.side == Side::Buy ? "BUY " : "SELL")
                          << " | Price: " << std::fixed << std::setprecision(2) << exec.price
                          << " | Fee: " << exec.fee
                          << " | Cash Left: " << portfolio.getCash() 
                          << std::endl;
            }
        }
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "BACKTEST RESULTS" << std::endl;
    
    std::map<std::string, double> finalPrices;
    finalPrices["BTCUSDT"] = lastPrice;
    
    double startValue = 10000.0;
    double endValue = portfolio.getTotalValue(finalPrices);
    double pnl = endValue - startValue;
    double returnPct = (pnl / startValue) * 100.0;

    std::cout << "Final Price: " << lastPrice << std::endl;
    std::cout << "Final Cash: " << portfolio.getCash() << std::endl;
    std::cout << "Final Holdings: " << portfolio.getPosition("BTCUSDT") << " BTC" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Total Portfolio Value: " << endValue << std::endl;
    std::cout << "Net Profit (PnL): " << (pnl >= 0 ? "+" : "") << pnl << " (" << returnPct << "%)" << std::endl;

    return 0;
}
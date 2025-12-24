#pragma once
#include "Strategy.hpp"
#include <deque>
#include <vector>

class MeanReversionStrategy : public IStrategy {
public:
    /**
     * @param windowSize (N) - Number of ticks to calculate statistics
     * @param stdDevMultiplier (k) - Width of the bands
     */
    MeanReversionStrategy(int windowSize, double stdDevMultiplier);

    Side onTick(const Tick& tick) override;
    std::string getName() const override;

private:
    int _windowSize;
    double _stdDevMultiplier;
    std::deque<double> _prices;

    double calculateMean() const;
    double calculateStdDev(double mean) const;
};
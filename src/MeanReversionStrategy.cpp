#include "backtester/MeanReversionStrategy.hpp"
#include <numeric> 
#include <cmath>   

MeanReversionStrategy::MeanReversionStrategy(int windowSize, double stdDevMultiplier)
    : _windowSize(windowSize), _stdDevMultiplier(stdDevMultiplier) {
}

std::string MeanReversionStrategy::getName() const {
    return "MeanReversion_Bollinger";
}

Side MeanReversionStrategy::onTick(const Tick& tick) {
    _prices.push_back(tick.price);

    if (_prices.size() > static_cast<size_t>(_windowSize)) {
        _prices.pop_front();
    }

    if (_prices.size() < static_cast<size_t>(_windowSize)) {
        return Side::Unknown;
    }

    double mean = calculateMean();
    double stdDev = calculateStdDev(mean);

    double upperBand = mean + (_stdDevMultiplier * stdDev);
    double lowerBand = mean - (_stdDevMultiplier * stdDev);

    if (tick.price > upperBand) {
        return Side::Sell;
    }

    else if (tick.price < lowerBand) {
        return Side::Buy;
    }

    return Side::Unknown;
}

double MeanReversionStrategy::calculateMean() const {
    double sum = std::accumulate(_prices.begin(), _prices.end(), 0.0);
    return sum / _prices.size();
}

double MeanReversionStrategy::calculateStdDev(double mean) const {
    double sumSqDiff = 0.0;
    

    for (double price : _prices) {
        double diff = price - mean;
        sumSqDiff += diff * diff;
    }

    double variance = sumSqDiff / _prices.size();
    return std::sqrt(variance);
}
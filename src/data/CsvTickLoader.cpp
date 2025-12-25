#include "backtester/data/CsvTickLoader.hpp"
#include <sstream>
#include <iostream>
#include <algorithm> 

CsvTickLoader::CsvTickLoader(const std::string& filePath) {
    _file.open(filePath);
    
    if (!_file.is_open()) {
        std::cerr << "[Error] Failed to open file: " << filePath << std::endl;
        return;
    }

    if (_file.good()) {
        std::string header;
        std::getline(_file, header);
    }
}

std::optional<Tick> CsvTickLoader::next() {
    if (!_file.is_open() || _file.eof()) {
        return std::nullopt;
    }

    std::string line;
    if (!std::getline(_file, line)) {
        return std::nullopt;
    }

    if (line.empty()) {
        return std::nullopt;
    }

    return parseLine(line);
}

std::optional<Tick> CsvTickLoader::parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string segment;
    Tick tick;

    try {
        if (!std::getline(ss, segment, ',')) return std::nullopt;
        tick.timestamp = std::stoll(segment);

        if (!std::getline(ss, segment, ',')) return std::nullopt;
        tick.price = std::stod(segment);

        if (!std::getline(ss, segment, ',')) return std::nullopt;
        tick.quantity = std::stod(segment);

        if (!std::getline(ss, segment, ',')) return std::nullopt;
        
        std::string sideStr = segment;
        std::transform(sideStr.begin(), sideStr.end(), sideStr.begin(), ::tolower);

        if (sideStr == "buy" || sideStr == "b" || sideStr == "1") {
            tick.side = Side::Buy;
        } else if (sideStr == "sell" || sideStr == "s" || sideStr == "0") {
            tick.side = Side::Sell;
        } else {
            tick.side = Side::Unknown;
        }


    } catch (const std::exception& e) {
        return std::nullopt;
    }

    return tick;
}
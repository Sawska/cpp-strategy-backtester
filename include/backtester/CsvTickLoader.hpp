#pragma once
#include "DataSource.hpp"
#include <fstream>
#include <string>
#include <vector>

class CsvTickLoader : public IDataSource {
public:
    explicit CsvTickLoader(const std::string& filePath);

    ~CsvTickLoader() = default;

    std::optional<Tick> next() override;

private:
    std::ifstream _file;
    
    std::optional<Tick> parseLine(const std::string& line);
};
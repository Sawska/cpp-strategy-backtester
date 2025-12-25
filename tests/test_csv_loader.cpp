#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "backtester/data/CsvTickLoader.hpp"

#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "backtester/data/CsvTickLoader.hpp"

class CsvLoaderTest : public ::testing::Test {
protected:
    std::string test_filename = "test_market_data.csv";

    void SetUp() override {
        std::ofstream out(test_filename);
        // Header updated
        out << "timestamp,price,quantity,side\n";

        // Data updated (removed ",true" and ",false")
        out << "1600000001,100.50,10.0,Buy\n";  
        out << "1600000002,101.00,5.0,Sell\n"; 
        out << "1600000003,100.75,2.5,Unknown\n";  
        out.close();
    }

    void TearDown() override {
        std::remove(test_filename.c_str());
    }
};

TEST_F(CsvLoaderTest, ReadsTicksCorrectly) {
    CsvTickLoader loader(test_filename);

    auto tick1 = loader.next();
    ASSERT_TRUE(tick1.has_value()); 
    EXPECT_EQ(tick1->timestamp, 1600000001);
    EXPECT_DOUBLE_EQ(tick1->price, 100.50);
    EXPECT_EQ(tick1->side, Side::Buy);

    auto tick2 = loader.next();
    ASSERT_TRUE(tick2.has_value());
    EXPECT_EQ(tick2->timestamp, 1600000002);
    EXPECT_EQ(tick2->side, Side::Sell);

    auto tick3 = loader.next();
    ASSERT_TRUE(tick3.has_value());
    EXPECT_EQ(tick3->side, Side::Unknown);

    auto tickEnd = loader.next();
    EXPECT_FALSE(tickEnd.has_value());
}

TEST(CsvLoaderManualTest, HandlesMissingFile) {
    CsvTickLoader loader("non_existent_file.csv");
    auto result = loader.next();
    EXPECT_FALSE(result.has_value()); 
}

TEST(CsvLoaderManualTest, HandlesMissingFile) {
    CsvTickLoader loader("non_existent_file.csv");
    auto result = loader.next();
    EXPECT_FALSE(result.has_value()); 
}




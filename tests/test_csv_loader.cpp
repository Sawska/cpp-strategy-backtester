#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "backtester/CsvTickLoader.hpp"

class CsvLoaderTest : public ::testing::Test {
protected:
    std::string test_filename = "test_market_data.csv";


    void SetUp() override {
        std::ofstream out(test_filename);

        out << "timestamp,price,quantity,side,is_market_maker\n";

        out << "1600000001,100.50,10.0,Buy,true\n";  
        out << "1600000002,101.00,5.0,Sell,false\n"; 
        out << "1600000003,100.75,2.5,Unknown,0\n";  
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
    EXPECT_TRUE(tick1->is_market_maker);

    auto tick2 = loader.next();
    ASSERT_TRUE(tick2.has_value());
    EXPECT_EQ(tick2->timestamp, 1600000002);
    EXPECT_EQ(tick2->side, Side::Sell);
    EXPECT_FALSE(tick2->is_market_maker);

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




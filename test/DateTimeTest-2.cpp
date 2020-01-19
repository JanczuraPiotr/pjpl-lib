//
// Created by piotr@janczura.pl on 2019.12.03
//

#include "DateTimeTest.h"

TEST_F(DateTimeTest, transformFromYmD)
{
    {
        std::string inDate = "11-11-2011";
        std::string outDate = "2011-11-11";
        EXPECT_EQ(DateTime::transformFromYmD(inDate), outDate);
    }
    {
        std::string inDate = "11.11.2011";
        std::string outDate = "2011-11-11";
        EXPECT_EQ(DateTime::transformFromYmD(inDate), outDate);
    }
}
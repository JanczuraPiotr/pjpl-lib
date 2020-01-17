//
// Created by piotr@janczura.pl on 2020.01.17
//

#include "DateTime.h"

namespace test {

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


}
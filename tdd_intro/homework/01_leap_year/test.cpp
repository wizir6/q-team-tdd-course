/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
except every year that is evenly divisible by 100
unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>

bool is_leap_year(int year)
{
    bool return_value = false;

    if (year % 400 == 0)
    {
        return_value = true;
    }

    else if (year % 4 == 0 && year % 100 != 0)
    {
        return_value = true;
    }

    return return_value;
}

TEST(LeapYear, divisible_by_4)
{
    EXPECT_TRUE(is_leap_year(1996));
}

TEST(LeapYear, not_divisible_by_4)
{
    EXPECT_FALSE(is_leap_year(1997));
}

TEST(LeapYear, divisible_by_4_and_100)
{
    EXPECT_FALSE(is_leap_year(900));
}

TEST(LeapYear, divisible_by_400)
{
    EXPECT_TRUE(is_leap_year(2000));
}

/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[g_linesInDigit];
};

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[g_linesInDigit];
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };//6
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };//2
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };//5
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };//5
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };//4
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };//5
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };//6
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };//3
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };//7
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };//6

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

short calc_specific_symbol(const std::string& line, char symbol)
{
    short number_of_symbols = 0;

    for (size_t i = 0; i < line.size(); ++i)
    {
        if (line[i] == symbol)
        {
            ++number_of_symbols;
        }
    }

    return number_of_symbols;
}

short get_digit_from_struct(Digit digit)
{
    return 0;
}


TEST(test_calc_specific_symbol, two_non_spaces)
{
    EXPECT_EQ(2, calc_specific_symbol(" _ ", ' '));
}

TEST(test_calc_specific_symbol, one_underline)
{
    EXPECT_EQ(1, calc_specific_symbol(" _ ", '_'));
}

TEST(test_calc_specific_symbol, three_spaces)
{
    EXPECT_EQ(3, calc_specific_symbol("   ", ' '));
}

TEST(test_calc_specific_symbol, none_search_symbols)
{
    EXPECT_EQ(0, calc_specific_symbol("   ", '|'));
}

TEST(test_get_digit_from_struct, digit_one)
{
    EXPECT_EQ(1, get_digit_from_struct(s_digit1));
}

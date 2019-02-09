/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

#include <gtest/gtest.h>
#include <iostream>
#include <string>

std::vector<std::string> get_words(const std::string& phrase)
{
    std::vector<std::string> words;
    std::stringstream stream(phrase);
    std::string word;
    while (std::getline(stream, word, ' '))
    {
        words.push_back(word);
    }

    return words;
}

TEST(word_count, get_words_test)
{
    std::vector<std::string> words = {"olly", "olly", "in", "come", "free", "please", "please", "let", "it", "be", "in", "such", "manner", "olly"};

    EXPECT_EQ(words, get_words("olly olly in come free please please let it be in such manner olly"));
}

TEST(word_count, get_words_check_empty_strig)
{
    std::vector<std::string> words = {};

    EXPECT_EQ(words, get_words(""));
}

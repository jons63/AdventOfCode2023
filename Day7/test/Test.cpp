#include <gtest/gtest.h>
#include <map>
#include <vector>
#include "Day7.h"
#include <cmath>

using namespace Day7;

TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
};

TEST(HelloTest, EmptyMapIncrement) {
    std::map<char, int> tmp;

    tmp['A']++;

    EXPECT_EQ(tmp['A'], 1);
    EXPECT_EQ(tmp.size(), 1);
};


TEST(HelloTest, HandScore)
{
    std::map<char, int> cards{{'A', 5}};

    auto score = ScoreOfHand(cards);
    EXPECT_EQ(score, exp10(5));

    cards = std::map<char, int>{{'A', 4}, {'K', 1}};
    score = ScoreOfHand(cards);
    EXPECT_EQ(score, exp10(4)+10);

    cards = std::map<char, int>{{'A', 3}, {'K', 2}};
    score = ScoreOfHand(cards);
    EXPECT_EQ(score, exp10(3)+exp10(2));

    cards = std::map<char, int>{{'A', 3}, {'K', 1}, {'D', 1}};
    score = ScoreOfHand(cards);
    EXPECT_EQ(score, exp10(3)+10+10);

    cards = std::map<char, int>{{'A', 2}, {'K', 2},{'D', 1}};
    score = ScoreOfHand(cards);
    EXPECT_EQ(score, exp10(2)+exp10(2)+10);

    cards = std::map<char, int>{{'A', 2}, {'K', 1},{'D', 1},{'T', 1}};
    score = ScoreOfHand(cards);
    EXPECT_EQ(score, exp10(2)+10+10+10);

    cards = std::map<char, int>{{'A', 1}, {'K', 1},{'D', 1},{'T', 1},{'9', 1}};
    score = ScoreOfHand(cards);
    EXPECT_EQ(score, 10+10+10+10+10);
};

TEST(HelloTest, FindBestHand)
{
    std::map<char, int> cards = std::map<char, int>{{'A', 4}, {'1', 1}};
    auto score = FindBestHand(cards);
    EXPECT_EQ(score, exp10(5));

    cards = std::map<char, int>{{'5', 3}, {'1', 1}, {'A', 1}};
    score = FindBestHand(cards);
    EXPECT_EQ(score, exp10(4) + exp10(1));

    cards = std::map<char, int>{{'A', 2}, {'1', 1}, {'D', 2}};
    score = FindBestHand(cards);
    EXPECT_EQ(score, exp10(3) + exp10(2));

    cards = std::map<char, int>{{'A', 1}, {'1', 1}, {'D', 1}, {'K', 1}, {'9', 1}};
    score = FindBestHand(cards);
    EXPECT_EQ(score, exp10(2) + 10 + 10 + 10);
};
#include "solver.h"
#include <gtest/gtest.h>
int testsolve(std::string first, std::string second){
    return solveTask(first, second);
}

TEST(all_tests, all_tests) {
    EXPECT_EQ(testsolve("aa.", "aa"), 2);
    EXPECT_EQ(testsolve("ab+c.aba.*.bac.+.+*", "abacb"), 5);
    EXPECT_EQ(testsolve("acb..bab.c.*.ab.ba.+.+*a.", "acbac"), 5);
    EXPECT_EQ(testsolve("aba.b..", "aba"), 3);
    EXPECT_EQ(testsolve("aa.", "aa"), 2);
    EXPECT_EQ(testsolve("ab+c.aba.*.bac.+.+*", "abacb"), 5);
    EXPECT_EQ(testsolve("acb..bab.c.*.ab.ba.+.+*a.", "acbac"), 5);
    EXPECT_EQ(testsolve("aba.b..", "aba"), 3);
    EXPECT_EQ(testsolve("a1+bc+.a*.", "abcab"), 2);
    EXPECT_EQ(testsolve("ab.*ab.c.+ac+bc+.+bc..", "abcbcaaaabcbc"), 5);
    EXPECT_EQ(testsolve("a1+b1+c1+..*ab..", "abccabbbbcba"), 12);
}

TEST(error_tests, error_tests) {
    EXPECT_EQ(testsolve("aa..", "aa"), -1);
    EXPECT_EQ(testsolve("aa..", "aa"), -1);
    EXPECT_EQ(testsolve("a1+bc+a*", "acbbbacab"), -1);
}


//
// Created by Omer on 18/01/2018.
//

#include "testMacros.h"
#include "Group.h"
#include "exceptions.h"

using namespace mtm;

bool testConstructor1() {
    ASSERT_EXCEPTION(Group("", "clan", 5, 5, 3, 1, 80), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", 0, 0, 3, 1, 80), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", -1, 5, 3, 1, 80), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", 5, -1, 3, 1, 80), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", 5, 5, -1, 1, 80), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", 5, 5, 3, -1, 80), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", 5, 5, 3, 1, -1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", "clan", 5, 5, 3, 1, 101), GroupInvalidArgs);

    ASSERT_NO_EXCEPTION(Group("aaa", "", 5, 5, 3, 1, 80));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 0, 5, 3, 1, 80));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 0, 3, 1, 80));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 5, 0, 0, 80));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 5, 3, 0, 80));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 5, 0, 1, 80));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 5, 3, 1, 0));
    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 5, 3, 1, 100))

    ASSERT_NO_EXCEPTION(Group("aaa", "clan", 5, 5, 3, 1, 80));

    return true;
}

bool testConstructor2() {
    ASSERT_EXCEPTION(Group("", 5, 5), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", 0, 0), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", -1, 5), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("aaa", 5, -1), GroupInvalidArgs);

    ASSERT_NO_EXCEPTION(Group("aaa", 5, 0));
    ASSERT_NO_EXCEPTION(Group("aaa", 0, 5));

    ASSERT_NO_EXCEPTION(Group("aaa", 5, 5));

    return true;
}

bool testGetName() {
    Group group("aaa", 5, 5);
    ASSERT_TRUE(group.getName() == "aaa");
    ASSERT_FALSE(group.getName() == "alpa");
    ASSERT_FALSE(group.getName().empty());

    return true;
}

bool testGetSize() {
    Group group1("aaa", 5, 5);
    ASSERT_TRUE(group1.getSize() == 10);
    ASSERT_FALSE(group1.getSize() == 0);

    Group group2("bbb", 0, 1);
    ASSERT_TRUE(group2.getSize() == 1);
    ASSERT_FALSE(group2.getSize() == 0);

    Group group3("ccc", 0, 1);
    ASSERT_TRUE(group3.getSize() == 1);
    ASSERT_FALSE(group3.getSize() == 0);

    return true;
}

bool testGetClan() {
    Group group1("aaa", 5, 5);
    ASSERT_TRUE(group1.getClan().empty());

    Group group2("bbb", "", 1, 2, 3, 3, 80);
    ASSERT_TRUE(group2.getClan().empty());

    Group group3("ccc", "clan", 1, 2, 3, 3, 80);
    ASSERT_TRUE(group3.getClan() == "clan");

    return true;
}

bool testChangeClan() {
    Group group1("aaa", 5, 5);

    group1.changeClan("");
    ASSERT_TRUE(group1.getClan().empty());
    // morale should be 70
    cout << group1 <<endl;

    group1.changeClan("aaa");
    ASSERT_TRUE(group1.getClan() == "aaa");
    // morale should be 77
    cout << group1 <<endl;

    group1.changeClan("");
    ASSERT_TRUE(group1.getClan().empty());
    // morale should be 69
    cout << group1 <<endl;

    Group group2("bbb", "", 1, 2, 3, 3, 95);
    group2.changeClan("clan");
    ASSERT_TRUE(group2.getClan() == "clan");
    // morale should be 100
    cout << group2 <<endl;

    Group group3("ccc", "clan", 1, 2, 3, 3, 0);
    group3.changeClan("");
    ASSERT_TRUE(group3.getClan().empty());
    // morale should be 0
    cout << group3 <<endl;

    Group group4("ddd", "clan", 1, 2, 3, 3, 1);
    group4.changeClan("");
    ASSERT_TRUE(group4.getClan().empty());
    // morale should be 0
    cout << group4 <<endl;

    Group group5("eee", "clan", 1, 2, 3, 3, 50);
    group5.changeClan("clan");
    ASSERT_TRUE(group5.getClan() == "clan");
    // morale should be 50
    cout << group5 <<endl;

    return true;
}

bool testLessOperator() {
    Group group1("Alpha", "Beta", 1, 2, 3, 4, 5);
    Group group2("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_FALSE(group1 < group2);
    Group group3("alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group1 < group3);
    ASSERT_FALSE(group3 < group1);
    Group group5("Alpha", "Beta", 1, 2, 3, 4, 100);
    ASSERT_FALSE(group5 < group3);
    return true;
}

bool testEqualOperator() {
    Group group1("Alpha", "Beta", 1, 2, 3, 4, 5);
    Group group2("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group1 == group2);
    Group group3("Alph4", "Beta", 1, 2, 3, 4, 5);
    ASSERT_FALSE(group1 == group3);
    Group group4("Alpha", "Beta", 1, 3, 3, 4, 5);
    ASSERT_FALSE(group1 == group4);
    return true;
}

bool testUnEqualOperator() {
    Group group1("Alpha", "Beta", 1, 2, 3, 4, 5);
    Group group2("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_FALSE(group1 != group2);
    Group group3("Alph4", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group1 != group3);
    Group group4("Alpha", "Beta", 1, 3, 3, 4, 5);
    ASSERT_TRUE(group1 != group4);
    return true;
}

bool testBiggerOperator() {
    Group group1("Alpha", "Beta", 1, 2, 3, 4, 5);
    Group group2("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_FALSE(group1 > group2);
    Group group3("Alpha", "Beta", 1, 2, 3, 4, 100);
    ASSERT_FALSE(group1 > group3);
    ASSERT_TRUE(group1 < group3);
    ASSERT_TRUE(group3 > group2);
    Group group5("zbi", "Beta", 1, 2, 3, 4, 100);
    ASSERT_TRUE(group5 > group3);
    return true;
}

bool testBiggerEqual() {
    Group group1("Alpha", "Beta", 1, 2, 3, 4, 5);
    Group group2("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group1 >= group2);
    Group group3("Alpha", "Beta", 1, 2, 3, 4, 100);
    ASSERT_FALSE(group1 > group3);
    ASSERT_TRUE(group1 < group3);
    ASSERT_TRUE(group3 >= group2);
    Group group5("zbi", "Beta", 1, 2, 3, 4, 100);
    ASSERT_TRUE(group5 >= group3);
    return true;
}

bool testLessEqual() {
    Group group1("Alpha", "Beta", 5, 5, 5, 5, 5);
    Group group2("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group1 >= group2);
    Group group3("zbw", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group1 > group3);
    Group group5("zbi", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group5 <= group3);
    Group group6("Alpha", "Beta", 1, 2, 3, 4, 5);
    ASSERT_TRUE(group6 <= group2);
    return true;
}

bool testUnite() {
    Group group1("A", "Alpha", 1, 2, 3, 4, 71);
    Group group2("B", "Alpha", 4, 3, 2, 1, 72);
    ASSERT_TRUE(group1.unite(group2, 25));
    Group group3("A", "Alpha", 1, 2, 3, 4, 71);
    Group group4("A", "Alpha", 1, 2, 3, 4, 71);
    ASSERT_FALSE(group3.unite(group4, 10));
    Group group5("B", "Alpha", 1, 2, 3, 4, 69);
    Group group6("A", "Alpha", 1, 2, 3, 4, 71);
    ASSERT_FALSE(group5.unite(group6, 12));
    Group group7("B", "Alpha", 1, 2, 3, 4, 80);
    Group group8("A", "Alpha", 1, 2, 3, 4, 71);
    ASSERT_FALSE(group7.unite(group8, 2));

    return true;
}

bool testDivide() {
    Group group1("A", "Alpha", 1, 2, 3, 4, 5);
    ASSERT_NO_EXCEPTION(group1.divide("fibi"));
    Group group3("A", "Alpha", 1, 1, 1, 4, 5);
    ASSERT_EXCEPTION(group3.divide("will not work"), GroupCantDivide);
    Group group5("A", "Alpha", 1, 3, 2, 4, 5);
    ASSERT_EXCEPTION(group5.divide(""), GroupInvalidArgs);
    return true;
}

bool testFight() {
    Group group1("Z", "Alpha", 5, 5, 5, 5, 5);
    Group group2("A", "Alpha", 1, 1, 2, 1, 3);
    ASSERT_NO_EXCEPTION(group1.fight(group2));
    ASSERT_EXCEPTION(group2.fight(group1), GroupCantFightEmptyGroup);
    Group group3("A", "Alpha", 5, 5, 5, 5, 5);
    ASSERT_EXCEPTION(group3.fight(group2), GroupCantFightWithItself);
    Group group5("A", "Alpha", 5, 5, 6, 6, 12);
    Group group6("Z", "Getta", 10, 15, 3, 22, 10);
    ASSERT_NO_EXCEPTION(group5.fight(group6));
    ASSERT_NO_EXCEPTION(group6.fight(group5));
    return true;
}

bool testTrade() {
    Group group1("Z", "Alpha", 5, 5, 100, 2, 5);
    Group group2("A", "Alpha", 1, 1, 2, 10, 3);
    ASSERT_TRUE(group1.trade(group2));
    ASSERT_EXCEPTION(group1.trade(group1), GroupCantTradeWithItself);
    Group group3("B", "Alpha", 5, 5, 5, 5, 5);
    ASSERT_FALSE(group1.trade(group3));
    Group group4("Z", "Alpha", 5, 5, 4, 1, 5);
    Group group5("A", "Alpha", 1, 1, 1, 2, 3);
    ASSERT_TRUE(group4.trade(group5)); //group4: tools-2,foor-3;group5-tools-3,food-0
    return true;
}

bool testPrint(){
    Group group1("a", "Alpha", 5, 5, 6, 2, 90);
    Group group2("b", "Alpha", 5, 5, 7, 2, 80);
    ASSERT_NO_EXCEPTION(group1.unite(group2,20));
    ASSERT_NO_EXCEPTION(cout << group1 <<endl);
    return true;
}

int main() {
    //TODO: make test for evrey case.
    RUN_TEST(testConstructor1);
    RUN_TEST(testConstructor2);
    RUN_TEST(testGetName);
    RUN_TEST(testGetSize);
    RUN_TEST(testGetClan);
    RUN_TEST(testChangeClan);
    RUN_TEST(testLessOperator);
    RUN_TEST(testEqualOperator);
    RUN_TEST(testUnEqualOperator);
    RUN_TEST(testBiggerOperator);
    RUN_TEST(testLessEqual);
    RUN_TEST(testUnite);
    RUN_TEST(testDivide);
    RUN_TEST(testFight);
    RUN_TEST(testTrade);
    RUN_TEST(testPrint);
    return 0;
}
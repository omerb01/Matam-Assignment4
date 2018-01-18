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
    // TODO: print for morale check

    group1.changeClan("aaa");
    ASSERT_TRUE(group1.getClan() == "aaa");
    // morale should be 77
    // TODO: print for morale check

    group1.changeClan("");
    ASSERT_TRUE(group1.getClan().empty());
    // morale should be 69
    // TODO: print for morale check

    Group group2("bbb", "", 1, 2, 3, 3, 95);
    group2.changeClan("clan");
    ASSERT_TRUE(group2.getClan() == "clan");
    // morale should be 100
    // TODO: print for morale check

    Group group3("ccc", "clan", 1, 2, 3, 3, 0);
    group3.changeClan("");
    ASSERT_TRUE(group3.getClan().empty());
    // morale should be 0
    // TODO: print for morale check

    Group group4("ddd", "clan", 1, 2, 3, 3, 1);
    group4.changeClan("");
    ASSERT_TRUE(group4.getClan().empty());
    // morale should be 0
    // TODO: print for morale check

    Group group5("eee", "clan", 1, 2, 3, 3, 50);
    group5.changeClan("clan");
    ASSERT_TRUE(group5.getClan().empty());
    // morale should be 50
    // TODO: print for morale check

    return true;
}

int main() {
    RUN_TEST(testConstructor1);
    RUN_TEST(testConstructor2);
    RUN_TEST(testGetName);
    RUN_TEST(testGetSize);
    RUN_TEST(testGetClan);
    RUN_TEST(testChangeClan);
    return 0;
}
//
// Created by Ilya on 1/19/2018.
//
#include "testMacros.h"
#include "Clan.h"
#include "exceptions.h"

using namespace mtm;

bool testClanConstructor() {
    ASSERT_NO_EXCEPTION(Clan clan("blala"));
    ASSERT_EXCEPTION(Clan clan(""), ClanEmptyName);
    return true;
}

bool testAddGroup() {
    Clan new_clan("Alpha");
    Group group1("Zero", "Alpha", 3, 2, 3, 4, 5);
    ASSERT_NO_EXCEPTION(new_clan.addGroup(group1));
    Group group2("One", "Alpha", 1, 1, 2, 1, 3);
    group2.fight(group1);
    ASSERT_EXCEPTION(new_clan.addGroup(group2), ClanGroupIsEmpty);
    Group group3("Zero", "Alpha", 1, 2, 2, 1, 3);
    ASSERT_EXCEPTION(new_clan.addGroup(group3), ClanGroupNameAlreadyTaken);
    Group group4("Two", "Alpha", 2, 3, 4, 5, 6);
    Group group5("Three", "Alpha", 7, 8, 9, 10, 11);
    ASSERT_NO_EXCEPTION(new_clan.addGroup(group4));
    ASSERT_NO_EXCEPTION(new_clan.addGroup(group5));
    return true;
}

bool testDoesContain() {
    Clan new_clan("Alpha");
    Group group1("Zero", "Alpha", 3, 2, 3, 4, 5);
    Group group2("One", "Alpha", 1, 1, 2, 1, 3);
    Group group4("Two", "Alpha", 2, 3, 4, 5, 6);
    Group group5("Three", "Alpha", 7, 8, 9, 10, 11);
    new_clan.addGroup(group1);
    new_clan.addGroup(group2);
    new_clan.addGroup(group4);
    new_clan.addGroup(group5);
    ASSERT_TRUE(new_clan.doesContain("Two"));
    ASSERT_FALSE(new_clan.doesContain("Eight"));
    return true;
}

bool testGetSize() {
    Clan new_clan("Alpha");
    Group group1("Zero", "Alpha", 3, 2, 3, 4, 5);
    Group group2("One", "Alpha", 1, 1, 2, 1, 3);
    Group group4("Two", "Alpha", 2, 3, 4, 5, 6);
    Group group5("Three", "Alpha", 7, 8, 9, 10, 11);
    new_clan.addGroup(group1);
    new_clan.addGroup(group2);
    new_clan.addGroup(group4);
    new_clan.addGroup(group5);
    ASSERT_TRUE(new_clan.getSize() == (12 + 7 + 8));
    Clan new_clan2("beta");
    ASSERT_TRUE(new_clan2.getSize() == 0);
    return true;
}

bool testUnite() {
    //TODO: check with friends unite
    Clan clan1("Alpha");
    Group group1("Zero", "Alpha", 3, 2, 3, 4, 5);
    Group group2("One", "Alpha", 1, 1, 2, 1, 3);
    Group group4("Two", "Alpha", 2, 3, 4, 5, 6);
    Group group5("Three", "Alpha", 7, 8, 9, 10, 11);
    clan1.addGroup(group1);
    clan1.addGroup(group2);
    clan1.addGroup(group4);
    clan1.addGroup(group5);
    Clan clan2("Beta");
    Group group11("1", "Beta", 3, 2, 3, 4, 24);
    Group group12("2", "Beta", 1, 1, 2, 1, 23);
    Group group14("3", "Beta", 2, 3, 4, 5, 22);
    Group group15("4", "Beta", 7, 8, 9, 10, 21);
    clan2.addGroup(group11);
    clan2.addGroup(group12);
    clan2.addGroup(group14);
    clan2.addGroup(group15);
    ASSERT_NO_EXCEPTION(clan1.unite(clan2, "Alpha"));
    //cout<<clan1<<endl;
    return true;
}

bool testPrint() {
    Clan clan1("Alpha");
    Group group1("Zero", "Alpha", 3, 2, 3, 4, 5);
    Group group2("One", "Alpha", 1, 1, 2, 1, 3);
    Group group4("Two", "Alpha", 2, 3, 4, 5, 6);
    Group group5("Three", "Alpha", 7, 8, 9, 10, 11);
    clan1.addGroup(group1);
    clan1.addGroup(group2);
    clan1.addGroup(group4);
    clan1.addGroup(group5);
    Clan clan2("Alpha");
    Group group66("Three", "Alpha", 7, 8, 9, 10, 11);
    cout << clan2 << endl;
    ASSERT_NO_EXCEPTION(clan2.addGroup(group66));
    cout << clan2 << endl;
    cout << clan1 << endl;
    return true;
}

bool testMakeFriend() {
    Clan clan1("Alpha");
    Clan clan2("Alpha");
    ASSERT_NO_EXCEPTION(clan1.makeFriend(clan2));
    ASSERT_TRUE(clan1.isFriend(clan2));
    clan1.makeFriend(clan2);
    Clan clan3("Beta");
    ASSERT_NO_EXCEPTION(clan1.makeFriend(clan3));
    ASSERT_TRUE(clan1.isFriend(clan3));
    return true;
}

bool testIsFriend() {
    Clan clan1("Alpha");
    Clan clan2("Alpha");
    ASSERT_NO_EXCEPTION(clan1.makeFriend(clan2));
    clan1.isFriend(clan2);
    Clan clan3("Beta");
    clan1.makeFriend(clan3);
    ASSERT_TRUE(clan1.isFriend(clan3));
    Clan clan4("Beta");
    ASSERT_TRUE(clan1.isFriend(clan4));
    return true;
}

int main() {
    RUN_TEST(testClanConstructor);
    RUN_TEST(testAddGroup);
    RUN_TEST(testDoesContain);
    RUN_TEST(testGetSize);
    RUN_TEST(testUnite);
    RUN_TEST(testPrint);
    RUN_TEST(testMakeFriend);
    RUN_TEST(testIsFriend);
}
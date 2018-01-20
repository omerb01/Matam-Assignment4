//
// Created by Ilya on 1/19/2018.
//
#include "testMacros.h"
#include "Clan.h"
#include "exceptions.h"

using namespace mtm;

bool testClanConstructor(){
    ASSERT_NO_EXCEPTION(Clan clan("blala"));
    ASSERT_EXCEPTION(Clan clan(""),ClanEmptyName);
    return true;
}
bool testAddGroup(){
    Clan new_clan("Alpha");
    Group group1("Zero","Alpha",3,2,3,4,5);
    ASSERT_NO_EXCEPTION(new_clan.addGroup(group1));
    Group group2("One","Alpha",1,1,2,1,3);
    group2.fight(group1);
    ASSERT_EXCEPTION(new_clan.addGroup(group2),ClanGroupIsEmpty);
    Group group3("Zero","Alpha",1,2,2,1,3);
    ASSERT_EXCEPTION(new_clan.addGroup(group3),ClanGroupNameAlreadyTaken);
    Group group4("Two","Alpha",2,3,4,5,6);
    Group group5("Three", "Alpha", 7,8,9,10,11);
    ASSERT_NO_EXCEPTION(new_clan.addGroup(group4));
    ASSERT_NO_EXCEPTION(new_clan.addGroup(group5));
    return true;
}

int main(){
    RUN_TEST(testClanConstructor);
    RUN_TEST(testAddGroup);
}
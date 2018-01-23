//
// Created by Ilya on 1/21/2018.
//

#include "../testMacros.h"
#include "../Mountain.h"

using namespace mtm;

bool testConstructor() {
    Mountain mount1("Hermon");
    Mountain mount2("Meiron");
    ASSERT_EXCEPTION(Mountain mount3(""), AreaInvalidArguments);
    return true;
}

bool testGroupArrive() {
    Mountain mount1("Hermon");
    Clan clan1("Blue");
    clan1.addGroup(Group("Blue1", "Blue", 1, 2, 3, 4, 5));
    clan1.addGroup(Group("Blue2", "Blue", 5, 4, 3, 2, 1));
    Clan clan2("Red");
    clan2.addGroup(Group("Red1", "Red", 5, 6, 7, 8, 9));
    clan2.addGroup(Group("Red2", "Red", 9, 8, 7, 6, 5));
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<string, Clan>("clan1", clan1));
    clan_map.insert(std::pair<string, Clan>("clan2", clan2));
    Clan test = clan_map.at("clan1");
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Blue1", "clan1", clan_map));
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Red2", "clan2", clan_map));
    MtmSet<std::string> group_names = mount1.getGroupsNames();
    ASSERT_TRUE(group_names.size()==2);
    ASSERT_EXCEPTION(mount1.groupArrive("Red2", "clan2", clan_map),
                     AreaGroupAlreadyIn);
    ASSERT_EXCEPTION(mount1.groupArrive("Blue1", "none", clan_map),
                     AreaClanNotFoundInMap);
    ASSERT_EXCEPTION(mount1.groupArrive("none", "clan1", clan_map),
                     AreaGroupNotInClan);
    ASSERT_TRUE(group_names.size()==2);
    return true;
}


bool testGroupLeave() {
    Mountain mount1("Hermon");
    Clan clan1("clan1");
    clan1.addGroup(Group("Blue1", "clan1", 1, 2, 3, 4, 5));
    clan1.addGroup(Group("Blue2", "clan1", 5, 4, 3, 2, 1));
    clan1.addGroup(Group("Blue3", "clan1", 5, 4, 2, 1, 1));
    Clan clan2("clan2");
    clan2.addGroup(Group("Red1", "clan2", 5, 6, 7, 4, 3));
    clan2.addGroup(Group("Red2", "clan2", 9, 8, 7, 6, 5));
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<string, Clan>("clan1", clan1));
    clan_map.insert(std::pair<string, Clan>("clan2", clan2));
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Blue1","clan1",clan_map));
    ASSERT_NO_EXCEPTION(mount1.groupLeave("Blue1"));
    MtmSet<std::string> group_names = mount1.getGroupsNames();
    ASSERT_TRUE(group_names.empty());
    ASSERT_EXCEPTION(mount1.groupLeave("Blue1"),AreaGroupNotFound);
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Red1","clan2",clan_map));
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Red2","clan2",clan_map));
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Blue2","clan1",clan_map));
    ASSERT_TRUE(mount1.getGroupsNames().size() == 3);
    //Red2 should be dominating so far
    ASSERT_NO_EXCEPTION(mount1.groupLeave("Red2"));
    //Red1 should continue dominating
    ASSERT_NO_EXCEPTION(mount1.groupArrive("Blue1","clan1",clan_map));
    ASSERT_NO_EXCEPTION(mount1.groupLeave("Red1"));
    //Blue2 should be dominating
    return true;
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testGroupArrive);
    RUN_TEST(testGroupLeave);
}
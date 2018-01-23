//
// Created by Omer on 20/01/2018.
//
#include "../testMacros.h"
#include "../Area.h"
#include "../exceptions.h"

using namespace mtm;

bool testConstructor() {

    ASSERT_EXCEPTION(Area area(""), AreaInvalidArguments);
    ASSERT_NO_EXCEPTION(Area area("a"));
    ASSERT_NO_EXCEPTION(Area area("a"));

    return true;
}

bool testAddReachableArea() {
    Area area("area_name");

    ASSERT_NO_EXCEPTION(area.addReachableArea(""));
    ASSERT_NO_EXCEPTION(area.addReachableArea("test"));

    return true;
}

bool testIsReachable() {
    Area area("area_name");

    ASSERT_FALSE(area.isReachable(""));
    ASSERT_FALSE(area.isReachable("test"));

    area.addReachableArea("test1");
    ASSERT_FALSE(area.isReachable(""));
    ASSERT_TRUE(area.isReachable("test1"));

    area.addReachableArea("test1");
    area.addReachableArea("test2");
    area.addReachableArea("test3");
    ASSERT_FALSE(area.isReachable(""));
    ASSERT_TRUE(area.isReachable("test1"));
    ASSERT_TRUE(area.isReachable("test2"));
    ASSERT_TRUE(area.isReachable("test3"));

    return true;
}

bool testGroupArrive() {
    Area area("area_name");
    std::map<string, Clan> clan_map;

    ASSERT_EXCEPTION(area.groupArrive("group1", "clan1", clan_map),
                     AreaClanNotFoundInMap);

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));
    ASSERT_EXCEPTION(area.groupArrive("group1", "clan2", clan_map),
                     AreaGroupNotInClan);

    clan_map.at("clan1").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 1, 1));

    ASSERT_NO_EXCEPTION(area.groupArrive("group2", "clan2", clan_map));
    ASSERT_EXCEPTION(area.groupArrive("group2", "clan2", clan_map),
                     AreaGroupAlreadyIn);
    ASSERT_NO_EXCEPTION(area.groupArrive("group1", "clan1", clan_map));

    return true;
}

bool testGroupLeave() {
    Area area("area_name");
    std::map<string, Clan> clan_map;
    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));
    clan_map.at("clan1").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 1, 1));

    ASSERT_EXCEPTION(area.groupLeave("group1"), AreaGroupNotFound);

    area.groupArrive("group1", "clan1", clan_map);
    ASSERT_EXCEPTION(area.groupLeave("group2"), AreaGroupNotFound);
    ASSERT_NO_EXCEPTION(area.groupLeave("group1"));

    area.groupArrive("group2", "clan2", clan_map);
    ASSERT_EXCEPTION(area.groupLeave("group0"), AreaGroupNotFound);
    ASSERT_NO_EXCEPTION(area.groupLeave("group2"));

    return true;
}

bool testGetGroupsNames() {
    Area area("area_name");
    std::map<string, Clan> clan_map;
    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));
    clan_map.at("clan1").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 1, 1));

    MtmSet<string> set1 = area.getGroupsNames();
    ASSERT_TRUE(set1.empty());

    area.groupArrive("group1", "clan1", clan_map);
    MtmSet<string> set2 = area.getGroupsNames();
    ASSERT_TRUE(set2.size() == 1);
    ASSERT_TRUE(*set2.begin() == "group1");

    area.groupArrive("group2", "clan2", clan_map);
    MtmSet<string> set3 = area.getGroupsNames();
    ASSERT_TRUE(set3.size() == 2);
    ASSERT_TRUE(set3.contains("group1"));
    ASSERT_TRUE(set3.contains("group2"));

    return true;
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testAddReachableArea);
    RUN_TEST(testIsReachable);
    RUN_TEST(testGroupArrive);
    RUN_TEST(testGroupLeave);
    RUN_TEST(testGetGroupsNames);
    return 0;
}
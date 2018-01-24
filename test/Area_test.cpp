//
// Created by Omer on 20/01/2018.
//
#include "../testMacros.h"
#include "../Plain.h"
#include "../River.h"
#include "../Mountain.h"
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

bool testPlainExceptions() {
    Plain area("area_name");
    std::map<string, Clan> clan_map;

    ASSERT_EXCEPTION(area.groupArrive("group", "clan", clan_map),
                     AreaClanNotFoundInMap);

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    ASSERT_EXCEPTION(area.groupArrive("group", "clan2", clan_map),
                     AreaGroupNotInClan);

    clan_map.at("clan2").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 10, 10));

    ASSERT_NO_EXCEPTION(area.groupArrive("group1", "clan2", clan_map));
    ASSERT_EXCEPTION(area.groupArrive("group1", "clan2", clan_map),
                     AreaGroupAlreadyIn);

    return true;
}

bool testPlainUnite() {
    Plain area("area_name");
    std::map<string, Clan> clan_map;

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    clan_map.at("clan2").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 1, 1));
    clan_map.at("clan2").addGroup(Group("group3", 10, 10));

    ASSERT_NO_EXCEPTION(area.groupArrive("group2", "clan2", clan_map));
    ASSERT_NO_EXCEPTION(area.groupArrive("group1", "clan2", clan_map));
    ASSERT_FALSE(clan_map.at("clan2").doesContain("group1"));
    ASSERT_TRUE(clan_map.at("clan2").doesContain("group2"));
    ASSERT_TRUE(clan_map.at("clan2").getGroup("group2")->getSize() == 4);

    MtmSet<string> set = area.getGroupsNames();
    ASSERT_TRUE(set.size() == 1);
    ASSERT_TRUE(set.contains("group2"));

    return true;
}

bool testPlainDivide() {
    Plain area("area_name");
    std::map<string, Clan> clan_map;

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    clan_map.at("clan2").addGroup(Group("group_5", 1, 1));
    clan_map.at("clan2").addGroup(Group("group_2", 1, 1));
    clan_map.at("clan2").addGroup(Group("group_3", 1, 1));
    clan_map.at("clan2").addGroup(Group("group_4", 1, 1));
    clan_map.at("clan2").addGroup(Group("group", 10, 10));

    ASSERT_NO_EXCEPTION(area.groupArrive("group", "clan2", clan_map));
    ASSERT_TRUE(clan_map.at("clan2").doesContain("group"));
    ASSERT_TRUE(clan_map.at("clan2").doesContain("group_6"));

    MtmSet<string> set = area.getGroupsNames();
    ASSERT_TRUE(set.size() == 2);
    ASSERT_TRUE(set.contains("group"));
    ASSERT_TRUE(set.contains("group_6"));

    return true;
}

bool testPlainNormalGroupArrive() {
    Plain area("area_name");
    std::map<string, Clan> clan_map;

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    clan_map.at("clan1").addGroup(Group("1/3_group1", 1, 1));
    clan_map.at("clan1").addGroup(Group("1/3_group2", 1, 1));
    clan_map.at("clan1").addGroup(Group("1/3_group3", 1, 1));

    ASSERT_NO_EXCEPTION(area.groupArrive("1/3_group1", "clan1", clan_map));
    ASSERT_NO_EXCEPTION(area.groupArrive("1/3_group2", "clan1", clan_map));
    ASSERT_NO_EXCEPTION(area.groupArrive("1/3_group3", "clan1", clan_map));

    MtmSet<string> set = area.getGroupsNames();
    ASSERT_TRUE(set.size() == 3);
    ASSERT_TRUE(set.contains("1/3_group1"));
    ASSERT_TRUE(set.contains("1/3_group2"));
    ASSERT_TRUE(set.contains("1/3_group3"));

    return true;
}

bool testMountainConstructor() {
    Mountain mount1("Hermon");
    Mountain mount2("Meiron");
    ASSERT_EXCEPTION(Mountain mount3(""), AreaInvalidArguments);
    return true;
}

bool testMountainGroupArrive() {
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


bool testMountainGroupLeave() {
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

bool testRiverExceptions() {
    River area("area_name");
    std::map<string, Clan> clan_map;

    ASSERT_EXCEPTION(area.groupArrive("group", "clan", clan_map),
                     AreaClanNotFoundInMap);

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    ASSERT_EXCEPTION(area.groupArrive("group", "clan2", clan_map),
                     AreaGroupNotInClan);

    clan_map.at("clan2").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 10, 10));

    ASSERT_NO_EXCEPTION(area.groupArrive("group1", "clan2", clan_map));
    ASSERT_EXCEPTION(area.groupArrive("group1", "clan2", clan_map),
                     AreaGroupAlreadyIn);

    return true;
}

bool testRiverTrade() {
    River area("area_name");
    std::map<string, Clan> clan_map;

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    clan_map.at("clan2").addGroup(Group("group1", "", 10, 10, 3, 1, 70));
    clan_map.at("clan2").addGroup(Group("group2", "", 10, 10, 5, 10, 70));
    clan_map.at("clan2").addGroup(Group("group3", "", 10, 10, 2, 1, 70));
    clan_map.at("clan2").addGroup(Group("group4", "", 10, 10, 2, 1, 70));
    clan_map.at("clan2").addGroup(Group("group5", "", 10, 10, 2, 1, 70));

    ASSERT_NO_EXCEPTION(area.groupArrive("group1", "clan2", clan_map));
    ASSERT_NO_EXCEPTION(area.groupArrive("group2", "clan2", clan_map));
    ASSERT_NO_EXCEPTION(area.groupArrive("group3", "clan2", clan_map));

    return true;
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testAddReachableArea);
    RUN_TEST(testIsReachable);
    RUN_TEST(testGroupArrive);
    RUN_TEST(testGroupLeave);
    RUN_TEST(testGetGroupsNames);

    RUN_TEST(testPlainExceptions);
    RUN_TEST(testPlainUnite);
    RUN_TEST(testPlainDivide);
    RUN_TEST(testPlainNormalGroupArrive);

    RUN_TEST(testMountainConstructor);
    RUN_TEST(testMountainGroupArrive);
    RUN_TEST(testMountainGroupLeave);

    RUN_TEST(testRiverExceptions);
    RUN_TEST(testRiverTrade);
    return 0;
}
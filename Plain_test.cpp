//
// Created by Omer on 21/01/2018.
//
#include "testMacros.h"
#include "Plain.h"

using namespace mtm;

bool testExceptions() {
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

bool testUnite() {
    /*Plain area("area_name");
    std::map<string, Clan> clan_map;

    clan_map.insert(std::pair<string, Clan>("clan1", Clan("clan1")));
    clan_map.insert(std::pair<string, Clan>("clan2", Clan("clan2")));
    clan_map.insert(std::pair<string, Clan>("clan3", Clan("clan3")));

    clan_map.at("clan2").addGroup(Group("group1", 1, 1));
    clan_map.at("clan2").addGroup(Group("group2", 1, 1));
    clan_map.at("clan2").addGroup(Group("group3", 10, 10));

    ASSERT_NO_EXCEPTION(area.groupArrive("group1", "clan2", clan_map));
    ASSERT_NO_EXCEPTION(area.groupArrive("group2", "clan2", clan_map));
    ASSERT_FALSE(clan_map.at("clan2").doesContain("group2"));
    ASSERT_TRUE(clan_map.at("clan2").doesContain("group1"));
    ASSERT_TRUE(clan_map.at("clan2").getGroup("group1")->getSize() == 4);

    MtmSet<string> set = area.getGroupsNames();
    ASSERT_TRUE(set.size() == 1);
    ASSERT_TRUE(set.contains("group1"));*/

    return true;
}

bool testDivide() {
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

bool testNormalGroupArrive() {
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

int main() {
    RUN_TEST(testExceptions);
    RUN_TEST(testUnite);
    RUN_TEST(testDivide);
    RUN_TEST(testNormalGroupArrive);
    return 0;
}
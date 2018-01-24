//
// Created by Omer on 22/01/2018.
//
#include "../testMacros.h"
#include "../River.h"

using namespace mtm;

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
    RUN_TEST(testRiverExceptions)
    RUN_TEST(testRiverTrade)
    return 0;
}
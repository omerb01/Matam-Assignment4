#include "testMacros.h"
#include "Group.h"
#include "Clan.h"
#include "Area.h"
#include "Plain.h"
#include "River.h"
#include "Mountain.h"
#include "exceptions.h"

using namespace mtm;


std::map<std::string, Clan> makeClanMap(){
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<std::string, Clan>("Tea", Clan("Tea")));
    clan_map.insert(std::pair<std::string, Clan>("Tree", Clan("Tree")));
    clan_map.insert(std::pair<std::string, Clan>("Mealy", Clan("Mealy")));
    clan_map.at("Tea").addGroup(Group("Nana", "Tea", 10, 10, 41, 51, 90));
    clan_map.at("Tea").addGroup(Group("Luiza", "Tea", 0, 5, 40, 50, 80));
    clan_map.at("Tree").addGroup(Group("Shiba", "Tree", 10, 10, 40, 40, 60));
    clan_map.at("Tree").addGroup(Group("Nana_2", "Tree", 10, 30, 61, 51, 90));
    clan_map.at("Mealy").addGroup(Group("Diva", "Mealy", 1,1,20,10,10));
    return clan_map;
}
bool examplePlain(){
    Area* tel_aviv(new Plain("Tel-Aviv"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_EXCEPTION(tel_aviv->groupArrive("Nana", "Beta", clan_map),
                     AreaClanNotFoundInMap);
    ASSERT_EXCEPTION(tel_aviv->groupArrive("Shiba", "Tea", clan_map),
                     AreaGroupNotInClan);
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Nana", "Tea", clan_map));//divide
    ASSERT_EXCEPTION(tel_aviv->groupArrive("Nana", "Tea", clan_map),
                     AreaGroupAlreadyIn);
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Nana_3"));
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Luiza", "Tea", clan_map));
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Luiza"));
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Diva", "Mealy", clan_map));
    //divide
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Shiba", "Tree", clan_map));
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Nana_3"));
    ASSERT_FALSE(tel_aviv->getGroupsNames().contains("Diva_2"));
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Diva"));
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Shiba"));
delete tel_aviv;
    return true;
}

bool exampleMountain(){
    Area* carmel(new Mountain("Carmel"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_EXCEPTION(carmel->groupArrive("Nana", "Beta", clan_map),
                     AreaClanNotFoundInMap);
   ASSERT_EXCEPTION(carmel->groupArrive("Shiba", "Tea", clan_map), AreaGroupNotInClan);
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Nana", "Tea", clan_map));
    ASSERT_EXCEPTION(carmel->groupArrive("Nana", "Tea", clan_map),
                     AreaGroupAlreadyIn);
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Nana_2", "Tree", clan_map));
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Diva", "Mealy", clan_map));
    ASSERT_FALSE(carmel->getGroupsNames().contains("Diva"));
    ASSERT_NO_EXCEPTION(carmel->groupLeave("Nana"));
    ASSERT_FALSE(carmel->getGroupsNames().contains("Nana"));
    delete carmel;
    return true;
}

bool exampleRiver(){
    Area* jordan(new River("Jordan"));
    std::map<std::string, Clan> clan_map = makeClanMap();
   clan_map.at("Tea").makeFriend(clan_map.at("Mealy"));
    ASSERT_EXCEPTION(jordan->groupArrive("Nana", "Beta", clan_map),
                     AreaClanNotFoundInMap);
    ASSERT_EXCEPTION(jordan->groupArrive("Shiba", "Tea", clan_map),
                     AreaGroupNotInClan);
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Nana", "Tea", clan_map));
    ASSERT_EXCEPTION(jordan->groupArrive("Nana", "Tea", clan_map),
                     AreaGroupAlreadyIn);
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Luiza", "Tea", clan_map));
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Shiba", "Tree", clan_map));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << *clan_map.at("Tea").getGroup("Nana")<<*clan_map
            .at("Tea").getGroup("Luiza")<<*clan_map.at("Tree").getGroup
            ("Shiba"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 41\n"
            "Group's food: 51\n"
            "Group's morale: 90\n"
            "Group's name: Luiza\n"
            "Group's clan: Tea\n"
            "Group's children: 0\n"
            "Group's adults: 5\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 80\n"
            "Group's name: Shiba\n"
            "Group's clan: Tree\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 40\n"
            "Group's morale: 60\n"
    ));

    ASSERT_NO_EXCEPTION(jordan->groupArrive("Diva", "Mealy", clan_map));
    ASSERT_NO_EXCEPTION(os << *clan_map.at("Tea").getGroup("Nana")<<*clan_map
            .at("Mealy").getGroup("Diva"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 46\n"
            "Group's food: 46\n"
            "Group's morale: 90\n"
            "Group's name: Diva\n"
            "Group's clan: Mealy\n"
            "Group's children: 1\n"
            "Group's adults: 1\n"
            "Group's tools: 15\n"
            "Group's food: 15\n"
            "Group's morale: 10\n"
    ));
    delete jordan;
    return true;
}

int main(){
    RUN_TEST(examplePlain);
   RUN_TEST(exampleRiver);
   RUN_TEST(exampleMountain);
    return 0;
}

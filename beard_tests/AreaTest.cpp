#include <iostream>
#include "../Plain.h"
#include "../River.h"
#include "../testMacros.h"
#include "../Area.h"
#include "../exceptions.h"
#include "../Mountain.h"
#include "../World.h"
using namespace mtm;

std::map<std::string, Clan> makeClanMap(){
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<std::string, Clan>("Marvel", Clan("Marvel")));
    clan_map.insert(std::pair<std::string, Clan>("DC", Clan("DC")));
    clan_map.insert(std::pair<std::string, Clan>("GOT", Clan("GOT")));

    clan_map.at("Marvel").addGroup(Group("Avengers", 2, 2));
    clan_map.at("Marvel").addGroup(Group("X-Men","", 10, 7, 100, 100, 80));
    clan_map.at("Marvel").addGroup(Group("Deadpool","", 0, 1, 1000, 1000, 100));
    clan_map.at("Marvel").addGroup(Group("Weak","", 0, 1, 1, 1, 10));
    clan_map.at("Marvel").addGroup(Group("Traders","", 1, 1, 1100, 500, 10));
    clan_map.at("DC").addGroup(Group("Justice League_1", 1, 1));
    clan_map.at("DC").addGroup(Group("Justice League_2", 1, 1));
    clan_map.at("DC").addGroup(Group("Justice League_3", 5, 5));
    clan_map.at("DC").addGroup(Group("Justice League_4","", 10, 6,97,100,80));
    clan_map.at("GOT").addGroup(Group("Stark","", 15, 5,30,47,70));
    clan_map.at("GOT").addGroup(Group("Lannister","",5,7, 100,97,50));
    clan_map.at("GOT").addGroup(Group("Baratheon","",5,5, 5,5,85));
    clan_map.at("GOT").addGroup(Group("Targeryan","",21,20, 100,100,85));
    clan_map.at("GOT").addGroup(Group("Targeryan_2","",1,0, 1000,1000,85));
    clan_map.at("GOT").addGroup(Group("Targeryan_3","",1,0, 1,1,85));
    return clan_map;
}

bool testPlain(){
    AreaPtr winterfell(new Plain("Winterfell"));
    AreaPtr kingslanding(new Plain("Kingslanding"));
    ASSERT_EXCEPTION(Plain(""),AreaInvalidArguments);
    ASSERT_NO_EXCEPTION(winterfell->addReachableArea("Kingslanding"));
    ASSERT_TRUE(winterfell->isReachable("Kingslanding"));
    ASSERT_FALSE(winterfell->isReachable("Kingsland"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(winterfell->groupArrive("Stark", "GOT", clan_map));
    ASSERT_TRUE(winterfell->getGroupsNames().contains("Stark"));
    ASSERT_FALSE(winterfell->getGroupsNames().contains("Lannister"));
    ASSERT_NO_EXCEPTION(winterfell->groupArrive("Lannister", "GOT", clan_map));
    ASSERT_TRUE(winterfell->getGroupsNames().contains("Lannister"));
    ASSERT_NO_EXCEPTION(winterfell->groupArrive("Baratheon", "GOT", clan_map));
    ASSERT_TRUE(winterfell->getGroupsNames().contains("Baratheon"));
    ASSERT_NO_EXCEPTION(winterfell->groupArrive("Targeryan", "GOT", clan_map));
    ASSERT_TRUE(winterfell->getGroupsNames().contains("Targeryan"));
    ASSERT_TRUE(winterfell->getGroupsNames().contains("Targeryan_4"));
    ASSERT_NO_EXCEPTION(winterfell->groupArrive("Targeryan_2","GOT", clan_map));
    ASSERT_FALSE(winterfell->getGroupsNames().contains("Targeryan_2"));
    ASSERT_EXCEPTION(winterfell->groupLeave("Targeryan_2"),AreaGroupNotFound);
    ASSERT_NO_EXCEPTION(winterfell->groupLeave("Stark"));
    ASSERT_NO_EXCEPTION(winterfell->groupLeave("Lannister"));
    ASSERT_NO_EXCEPTION(winterfell->groupLeave("Baratheon"));
    ASSERT_FALSE(winterfell->getGroupsNames().contains("Baratheon"));
    ASSERT_FALSE(winterfell->getGroupsNames().contains("Lannister"));
    ASSERT_FALSE(winterfell->getGroupsNames().contains("Stark"));
    ASSERT_EXCEPTION(winterfell->groupLeave(""),AreaGroupNotFound);
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << clan_map.at("GOT"));
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: GOT\n"
            "Clan's groups:\n"
            "Targeryan\n"
            "Targeryan_4\n"
            "Lannister\n"
            "Stark\n"
            "Baratheon\n"
            "Targeryan_3\n"));
    return true;
}

bool testMountain() {
    AreaPtr m1(new Mountain("Casterly Rock"));
    AreaPtr m2(new Mountain("The Eyrie"));
    ASSERT_EXCEPTION(Mountain(""), AreaInvalidArguments);
    ASSERT_NO_EXCEPTION(m1->addReachableArea("The Eyrie"));
    ASSERT_TRUE(m1->isReachable("The Eyrie"));
    ASSERT_FALSE(m1->isReachable("TheEyrie"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(m1->groupArrive("Avengers", "Marvel", clan_map));
    ASSERT_TRUE(m1->getGroupsNames().contains("Avengers"));
    ASSERT_NO_EXCEPTION(m1->groupArrive("Justice League_1", "DC", clan_map));
    ASSERT_TRUE(m1->getGroupsNames().contains("Avengers"));
    ASSERT_FALSE(m1->getGroupsNames().contains("Justice League_1"));//died
    ASSERT_NO_EXCEPTION(m1->groupArrive("X-Men", "Marvel", clan_map));//ruler
    ASSERT_NO_EXCEPTION(m1->groupArrive("Justice League_2", "DC", clan_map));
    ASSERT_TRUE(m1->getGroupsNames().contains("Avengers"));
    ASSERT_TRUE(m1->getGroupsNames().contains("X-Men"));
    ASSERT_FALSE(m1->getGroupsNames().contains("Justice League_2"));//died
    ASSERT_NO_EXCEPTION(m1->groupLeave("X-Men"));//Avengers will rule now.
    ASSERT_NO_EXCEPTION(
            m1->groupArrive("Justice League_3", "DC", clan_map));//won
    ASSERT_TRUE(m1->getGroupsNames().contains("Justice League_3"));
    ASSERT_TRUE(m1->getGroupsNames().contains("Avengers"));
    ASSERT_NO_EXCEPTION(m1->groupLeave("Justice League_3"));//Avengers rule.
    ASSERT_NO_EXCEPTION(
            m1->groupArrive("Justice League_3", "DC", clan_map));//won
    ASSERT_TRUE(m1->getGroupsNames().contains("Justice League_3"));
    ASSERT_FALSE(m1->getGroupsNames().contains("Avengers"));//died
    ASSERT_NO_EXCEPTION(m1->groupArrive("Justice League_4", "DC", clan_map));
    ASSERT_NO_EXCEPTION(m1->groupArrive("X-Men", "Marvel", clan_map));//lost
    ASSERT_TRUE(m1->getGroupsNames().contains("Justice League_3"));
    ASSERT_TRUE(m1->getGroupsNames().contains("Justice League_4"));
    ASSERT_TRUE(m1->getGroupsNames().contains("X-Men"));
    ASSERT_NO_EXCEPTION(m1->groupLeave("Justice League_4"));//JL3 rule.
    ASSERT_NO_EXCEPTION(m1->groupArrive("Deadpool", "Marvel", clan_map));//won
    ASSERT_NO_EXCEPTION(m1->groupLeave("Deadpool"));//X-Men rule.
    //would lose if X-Men didn't rule .
    ASSERT_NO_EXCEPTION(m1->groupArrive("Weak", "Marvel", clan_map));
    ASSERT_TRUE(m1->getGroupsNames().contains("Weak"));
    ASSERT_TRUE(m1->getGroupsNames().contains("Justice League_3"));
    ASSERT_EXCEPTION(m1->groupLeave(""),AreaGroupNotFound);
    ASSERT_EXCEPTION(m1->groupLeave("Deadpool"),AreaGroupNotFound);
    return true;
}

bool testRiver () {
    AreaPtr r1(new River("Bravos"));
    AreaPtr r2(new River("Riverrun"));
    ASSERT_EXCEPTION(River(""), AreaInvalidArguments);
    ASSERT_NO_EXCEPTION(r1->addReachableArea("Riverrun"));
    ASSERT_TRUE(r1->isReachable("Riverrun"));
    ASSERT_FALSE(r1->isReachable("riverrun"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(r1->groupArrive("Stark", "GOT", clan_map));
    ASSERT_TRUE(r1->getGroupsNames().contains("Stark"));
    ASSERT_FALSE(r1->getGroupsNames().contains("Lannister"));
    ASSERT_NO_EXCEPTION(r1->groupArrive("Lannister", "GOT", clan_map));
    ASSERT_TRUE(r1->getGroupsNames().contains("Lannister"));
    ASSERT_NO_EXCEPTION(r1->groupArrive("X-Men", "Marvel", clan_map));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << *(clan_map.at("GOT").getGroup("Lannister")));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Lannister\n"
                        "Group's clan: GOT\n"
                        "Group's children: 5\n"
                        "Group's adults: 7\n"
                        "Group's tools: 94\n"
                        "Group's food: 103\n"
                        "Group's morale: 55\n"));
    ASSERT_NO_EXCEPTION(r1->groupArrive("Justice League_4", "DC", clan_map));
    ASSERT_NO_EXCEPTION(os << *(clan_map.at("GOT").getGroup("Lannister")));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Lannister\n"
            "Group's clan: GOT\n"
            "Group's children: 5\n"
            "Group's adults: 7\n"
            "Group's tools: 94\n"
            "Group's food: 103\n"
            "Group's morale: 55\n"));
    clan_map.at("GOT").makeFriend(clan_map.at("Marvel"));
    // will trade with Lannister beacuse they are strongest and friend clan.
    ASSERT_NO_EXCEPTION(r1->groupArrive("Traders", "Marvel", clan_map));
    ASSERT_NO_EXCEPTION(os << *(clan_map.at("GOT").getGroup("Lannister")));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Lannister\n"
            "Group's clan: GOT\n"
            "Group's children: 5\n"
            "Group's adults: 7\n"
            "Group's tools: 197\n"
            "Group's food: 0\n"
            "Group's morale: 55\n"));
    ASSERT_NO_EXCEPTION(r1->groupLeave("Traders"));
    ASSERT_EXCEPTION(r1->groupLeave("Traders"),AreaGroupNotFound);
    ASSERT_NO_EXCEPTION(r1->groupArrive("Traders", "Marvel", clan_map));
    return true ;
}

int main(){
    RUN_TEST(testPlain);
    RUN_TEST(testMountain);
    RUN_TEST(testRiver);
    return 0;
}

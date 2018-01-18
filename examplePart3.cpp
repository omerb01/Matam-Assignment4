#include "testMacros.h"
#include "Group.h"
#include "Clan.h"
#include "Area.h"
#include "Plain.h"
#include "Mountain.h"
#include "River.h"
#include "World.h"
#include "exceptions.h"

using namespace mtm;

bool exampleClan(){
    Clan beta("Beta");
    ASSERT_NO_EXCEPTION(beta.addGroup(Group("Alpha1", 10, 10)));
    ASSERT_NO_EXCEPTION(beta.addGroup(Group("Alpha2", 5, 5)));
    ASSERT_NO_EXCEPTION(beta.addGroup(Group("Alpha3", 15, 15)));
    ASSERT_NO_EXCEPTION(beta.getGroup("Alpha1")->getClan() == "Beta");
    ASSERT_TRUE(beta.doesContain("Alpha2"));
    ASSERT_TRUE(beta.getSize() == 60);
    Clan beta2("Beta2");
    ASSERT_NO_EXCEPTION(beta2.addGroup(Group("Alpha4", 20, 20)));
    ASSERT_NO_EXCEPTION(beta.unite(beta2, "Beta3"));
    ostringstream os;
    ASSERT_TRUE(beta2.getSize() == 0);
    ASSERT_NO_EXCEPTION(os << beta);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Beta3\n"
        "Clan's groups:\n"
        "Alpha4\n"
        "Alpha3\n"
        "Alpha1\n"
        "Alpha2\n"));
    Clan gamma1("Gamma 1");
    Clan gamma2("Gamma 2");
    ASSERT_NO_EXCEPTION(gamma1.makeFriend(gamma2));
    ASSERT_TRUE(gamma1.isFriend(gamma2));
    return true;
}

std::map<std::string, Clan> makeClanMap(){
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<std::string, Clan>("Beta", Clan("Beta")));
    clan_map.insert(std::pair<std::string, Clan>("Gamma", Clan("Gamma")));
    clan_map.at("Beta").addGroup(Group("Alpha1", 10, 10));
    clan_map.at("Beta").addGroup(Group("Alpha2","", 10, 10, 40, 0, 70));
    clan_map.at("Gamma").addGroup(Group("Lambda1", 10, 10));
    clan_map.at("Gamma").addGroup(Group("Lambda2", 5, 5));
    clan_map.at("Gamma").addGroup(Group("Lambda3", 100, 100));
    return clan_map;
}

bool examplePlain(){
    AreaPtr tel_aviv(new Plain("Tel-Aviv"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Alpha1", "Beta", clan_map));
    // divide
    ASSERT_TRUE(tel_aviv->getGroupsNames().contains("Alpha1_2"));
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Lambda1", "Gamma", clan_map));
    ASSERT_NO_EXCEPTION(tel_aviv->groupArrive("Lambda2", "Gamma", clan_map));
    //unite with lambda1
    
    ASSERT_FALSE(tel_aviv->getGroupsNames().contains("Lambda2"));
    
    return true;
}

bool exampleMountain(){
    AreaPtr carmel(new Mountain("Carmel"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Alpha1", "Beta", clan_map));
    ASSERT_NO_EXCEPTION(carmel->groupArrive("Lambda2", "Gamma", clan_map));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << *clan_map.at("Gamma").getGroup("Lambda2"));
    ASSERT_TRUE(VerifyOutput(os ,"Group's name: Lambda2\n"
        "Group's clan: Gamma\n"
        "Group's children: 3\n"
        "Group's adults: 3\n"
        "Group's tools: 10\n"
        "Group's food: 12\n"
        "Group's morale: 61\n"));
    return true;
}

bool exampleRiver(){
    AreaPtr jordan(new River("Jordan"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Alpha1", "Beta", clan_map));
    ASSERT_NO_EXCEPTION(jordan->groupArrive("Alpha2", "Beta", clan_map));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << *clan_map.at("Beta").getGroup("Alpha1"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha1\n"
        "Group's clan: Beta\n"
        "Group's children: 10\n"
        "Group's adults: 10\n"
        "Group's tools: 53\n"
        "Group's food: 37\n"
        "Group's morale: 77\n"));
    return true;
}

bool exampleWorld(){
    World w;
    ASSERT_NO_EXCEPTION(w.addClan("Beta"));
    ASSERT_NO_EXCEPTION(w.addArea("Tel-Aviv", PLAIN));
    ASSERT_NO_EXCEPTION(w.addArea("Carmel", MOUNTAIN));
    ASSERT_NO_EXCEPTION(w.makeReachable("Carmel", "Tel-Aviv"));
    ASSERT_NO_EXCEPTION(w.addGroup("Alpha","Beta", 10, 10, "Carmel"));
    ASSERT_NO_EXCEPTION(w.moveGroup("Alpha", "Tel-Aviv")); //divides
    ostringstream os;
    ASSERT_NO_EXCEPTION(w.printGroup(os, "Alpha"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Beta\n"
        "Group's children: 5\n"
        "Group's adults: 5\n"
        "Group's tools: 20\n"
        "Group's food: 25\n"
        "Group's morale: 77\n"
        "Group's current area: Tel-Aviv\n"));
    return true;
}

int main(){
    RUN_TEST(exampleClan);
    RUN_TEST(examplePlain);
    RUN_TEST(exampleMountain);
    RUN_TEST(exampleRiver);
    RUN_TEST(exampleWorld);
    return 0;
}

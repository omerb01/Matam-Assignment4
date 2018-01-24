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

bool addClanWorld(){
    World w;
    ASSERT_EXCEPTION(w.addClan(""),WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(w.addClan("Tea"));
    ASSERT_EXCEPTION(w.addClan("Tea"),WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(w.addClan("Poli"));
    ASSERT_NO_EXCEPTION(w.addClan("Mini"));
    ASSERT_NO_EXCEPTION(w.addClan("Eli"));
    ASSERT_NO_EXCEPTION(w.addClan("Cohen"));
    ASSERT_EXCEPTION(w.addArea("",PLAIN),WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(w.addArea("Tel-Aviv",PLAIN));
    ASSERT_EXCEPTION(w.addArea("Tel-Aviv",PLAIN),WorldAreaNameIsTaken);
    ASSERT_NO_EXCEPTION(w.addArea("Haifa",MOUNTAIN));
    ASSERT_NO_EXCEPTION(w.addArea("Eilat",RIVER));
    ASSERT_EXCEPTION(w.addGroup("","Tea", 10, 10, "Haifa"),WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(w.addGroup("Alpha","Tea", 10, 10, "Haifa"));
    ASSERT_EXCEPTION(w.addGroup("Alpha","Tea", 10, 10, "Haifa"),WorldGroupNameIsTaken);
    ASSERT_EXCEPTION(w.addGroup("jo","FFA", 10, 10, "Haifa"),WorldClanNotFound);
    ASSERT_EXCEPTION(w.addGroup("lo","Tea", 10, 10, "ffa"),WorldAreaNotFound);
    ostringstream os;
    ASSERT_NO_EXCEPTION(w.printGroup(os, "Alpha"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 77\n"
            "Group's current area: Haifa\n"));
    ASSERT_NO_EXCEPTION(w.addGroup("Mila","Tea", 20, 20, "Eilat"));
    ASSERT_EXCEPTION(w.makeReachable("Haifa","ff"),WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(w.makeFriends("Tea","Poli"));
    ASSERT_NO_EXCEPTION(w.makeFriends("Poli","Eli"));
    ASSERT_NO_EXCEPTION(w.addGroup("Sima","Poli", 20, 20, "Haifa"));
    ASSERT_NO_EXCEPTION(w.printGroup(os, "Sima"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Sima\n"
            "Group's clan: Poli\n"
            "Group's children: 20\n"
            "Group's adults: 15\n"
            "Group's tools: 60\n"
            "Group's food: 112\n"
            "Group's morale: 93\n"
            "Group's current area: Haifa\n"));
    ASSERT_NO_EXCEPTION(w.printGroup(os, "Alpha"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
            "Group's clan: Tea\n"
            "Group's children: 6\n"
            "Group's adults: 6\n"
            "Group's tools: 20\n"
            "Group's food: 25\n"
            "Group's morale: 61\n"
            "Group's current area: Haifa\n"));
    ASSERT_NO_EXCEPTION(w.makeReachable("Haifa","Eilat"));
    ASSERT_NO_EXCEPTION(w.makeReachable("Tel-Aviv","Eilat"));
    ASSERT_NO_EXCEPTION(w.moveGroup("Alpha", "Eilat")); //no trade
    ASSERT_NO_EXCEPTION(w.printGroup(os, "Alpha"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
            "Group's clan: Tea\n"
            "Group's children: 6\n"
            "Group's adults: 6\n"
            "Group's tools: 20\n"
            "Group's food: 25\n"
            "Group's morale: 61\n"
            "Group's current area: Eilat\n"));
    ASSERT_NO_EXCEPTION(w.addGroup("Rahel","Tea", 40, 10, "Tel-Aviv"));//divide
    ASSERT_NO_EXCEPTION(w.printGroup(os, "Rahel_2"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Rahel_2\n"
            "Group's clan: Tea\n"
            "Group's children: 20\n"
            "Group's adults: 5\n"
            "Group's tools: 20\n"
            "Group's food: 55\n"
            "Group's morale: 77\n"
            "Group's current area: Tel-Aviv\n"));
    ASSERT_EXCEPTION(w.uniteClans("Tea","Poli",""),WorldInvalidArgument);
    ASSERT_EXCEPTION(w.uniteClans("Tea","Poli","Eli"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(w.uniteClans("Tea","LLL","jojo"),WorldClanNotFound);
    ASSERT_EXCEPTION(w.uniteClans("Tea","Tea","kkk"),WorldInvalidArgument);
    ASSERT_EXCEPTION(w.uniteClans("Tea","Tea","kook"),WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(w.uniteClans("Tea","Poli","New_clan"));
    ASSERT_NO_EXCEPTION(w.printClan(os, "New_clan"));
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: New_clan\n"
            "Clan's groups:\n"
            "Mila\n"
            "Sima\n"
            "Rahel\n"
            "Rahel_2\n"
            "Alpha\n"));
    return true;
}


int main(){

    RUN_TEST(addClanWorld);
    return 0;
}

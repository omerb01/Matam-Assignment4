//
// Created by Omer on 23/01/2018.
//

#include "../exceptions.h"
#include "../World.h"
#include "../testMacros.h"

using namespace mtm;

bool testAddClan() {
    World world;

    ASSERT_EXCEPTION(world.addClan(""), WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addClan("CLAN"));
    ASSERT_EXCEPTION(world.addClan("CLAN"), WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addClan("ANOTHER CLAN"));

    ostringstream os;
    world.printClan(os, "CLAN");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: CLAN\n"
            "Clan's groups:\n"));
    world.printClan(os, "ANOTHER CLAN");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: ANOTHER CLAN\n"
            "Clan's groups:\n"));

    return true;
}

bool testAddArea() {
    World world;

    ASSERT_EXCEPTION(world.addArea("", PLAIN), WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addArea("PLAIN", PLAIN));
    ASSERT_EXCEPTION(world.addArea("PLAIN", PLAIN), WorldAreaNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addArea("MOUNTAIN", MOUNTAIN));
    ASSERT_EXCEPTION(world.addArea("MOUNTAIN", RIVER),
                     WorldAreaNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addArea("RIVER", RIVER));

    return true;
}

bool testAddGroup() {
    World world;
    world.addClan("CLAN");
    world.addArea("PLAIN", PLAIN);

    ASSERT_EXCEPTION(world.addGroup("", "CLAN", 1, 1, "PLAIN"),
                     WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("GROUP", "CLAN", -1, 1, "PLAIN"),
                     WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("GROUP", "CLAN", 1, -1, "PLAIN"),
                     WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup("GROUP", "CLAN", 0, 0, "PLAIN"),
                     WorldInvalidArgument);

    ASSERT_NO_EXCEPTION(world.addGroup("GROUP", "CLAN", 0, 1, "PLAIN"));

    ASSERT_EXCEPTION(world.addGroup("GROUP", "CLAN1", 0, 1, "PLAIN1"),
                     WorldGroupNameIsTaken);
    ASSERT_EXCEPTION(world.addGroup("GROUP1", "CLAN1", 0, 1, "PLAIN1"),
                     WorldClanNotFound);
    ASSERT_EXCEPTION(world.addGroup("GROUP1", "CLAN", 0, 1, "PLAIN1"),
                     WorldAreaNotFound);

    ostringstream os;
    world.printClan(os, "CLAN");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: CLAN\n"
            "Clan's groups:\n"
            "GROUP\n"));
    world.printGroup(os, "GROUP");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: GROUP\n"
            "Group's clan: CLAN\n"
            "Group's children: 0\n"
            "Group's adults: 1\n"
            "Group's tools: 4\n"
            "Group's food: 3\n"
            "Group's morale: 77\n"
            "Group's current area: PLAIN\n"));

    return true;
}

bool testUniteClans() {
    World world;
    world.addClan("TEST_CLAN1");
    world.addClan("TEST_CLAN2");

    ASSERT_EXCEPTION(world.uniteClans("CLAN1", "CLAN2", ""),
                     WorldInvalidArgument);
    ASSERT_EXCEPTION(world.uniteClans("CLAN1", "CLAN2", "TEST_CLAN1"),
                     WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.uniteClans("CLAN1", "CLAN2", "CLAN1"),
                     WorldClanNotFound);
    ASSERT_EXCEPTION(world.uniteClans("TEST_CLAN1", "CLAN2", "CLAN1"),
                     WorldClanNotFound);
    ASSERT_EXCEPTION(world.uniteClans("CLAN1", "TEST_CLAN1", "CLAN1"),
                     WorldClanNotFound);

    ASSERT_NO_EXCEPTION(world.uniteClans("TEST_CLAN1", "TEST_CLAN2", "CLAN1"));
    ASSERT_NO_EXCEPTION(world.addClan("NEW_CLAN1"));
    ASSERT_NO_EXCEPTION(world.addClan("NEW_CLAN2"));
    ASSERT_EXCEPTION(world.uniteClans("TEST1", "TEST2", "CLAN1"),
                     WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(world.uniteClans("NEW_CLAN1", "NEW_CLAN2", "CLAN2"));

    world.addArea("PLAIN", PLAIN);
    world.addGroup("GROUP1", "CLAN1", 0, 1, "PLAIN");
    world.addGroup("GROUP2", "CLAN2", 2, 2, "PLAIN");

    ASSERT_NO_EXCEPTION(world.uniteClans("CLAN1", "CLAN2", "TEAM_NAME"));

    ostringstream os;
    world.printClan(os, "TEAM_NAME");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: TEAM_NAME\n"
            "Clan's groups:\n"
            "GROUP2\n"
            "GROUP1\n"));

    return true;
}

bool testMakeFriends() {
    World world;

    ASSERT_EXCEPTION(world.makeFriends("", ""), WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends("CLAN1", ""), WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends("", "CLAN2"), WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends("CLAN1", "CLAN2"), WorldClanNotFound);

    world.addClan("CLAN1");

    ASSERT_EXCEPTION(world.makeFriends("CLAN1", "CLAN2"), WorldClanNotFound);

    world.addClan("CLAN2");

    ASSERT_NO_EXCEPTION(world.makeFriends("CLAN1", "CLAN2"));
    ASSERT_NO_EXCEPTION(world.makeFriends("CLAN1", "CLAN2"));

    return true;
}

bool testReachable(){
    World world;
    ASSERT_NO_EXCEPTION(world.addArea("Haifa",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Morodor", MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.makeReachable("Haifa", "Morodor"));
    ASSERT_EXCEPTION(world.makeReachable("Haifa","M0rodor"),WorldAreaNotFound);
    return true;
}

bool testMoveGroup(){
    World world;
    ASSERT_NO_EXCEPTION(world.addArea("Haifa",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Morodor", MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addClan("clan1"));
    ASSERT_NO_EXCEPTION(world.addGroup("Blue","clan1",1,2,"Haifa"));
    ASSERT_EXCEPTION(world.moveGroup("Blue","Morodor"), WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(world.makeReachable("Haifa","Morodor"));
    ASSERT_NO_EXCEPTION(world.moveGroup("Blue","Morodor"));
    ASSERT_EXCEPTION(world.moveGroup("Blue","Morodor"),WorldGroupAlreadyInArea);
    ASSERT_EXCEPTION(world.moveGroup("blue","Morodor"), WorldGroupNotFound);
    ASSERT_EXCEPTION(world.moveGroup("Blue","Morodor"),WorldGroupAlreadyInArea);
    ASSERT_EXCEPTION(world.moveGroup("Blue","faifa"),WorldAreaNotFound);
    return true;
}

bool testUsedNames() {
    World world;
    world.addClan("CLAN1");
    world.addClan("CLAN2");

    ASSERT_NO_EXCEPTION(world.uniteClans("CLAN1", "CLAN2", "NEW CLAN1"));
    ASSERT_EXCEPTION(world.addClan("CLAN1"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("CLAN2"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("NEW CLAN1"),WorldClanNameIsTaken);

    ASSERT_NO_EXCEPTION(world.addClan("NEW CLAN2"));
    ASSERT_NO_EXCEPTION(world.uniteClans("NEW CLAN1", "NEW CLAN2", "TEST1"));
    ASSERT_EXCEPTION(world.addClan("NEW CLAN1"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("NEW CLAN2"),WorldClanNameIsTaken);

    ASSERT_NO_EXCEPTION(world.addClan("TEST2"));
    ASSERT_EXCEPTION(world.uniteClans("TEST1", "TEST2", "NEW CLAN1"),
                     WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(world.uniteClans("TEST1", "TEST2", "TEST1"));

    return true;
}

int main() {
    RUN_TEST(testReachable);
    RUN_TEST(testMoveGroup);
    RUN_TEST(testAddClan);
    RUN_TEST(testAddArea);
    RUN_TEST(testAddGroup);
    RUN_TEST(testUniteClans);
    RUN_TEST(testMakeFriends);
    RUN_TEST(testUsedNames);
    return 0;
}
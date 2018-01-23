//
// Created by Omer on 23/01/2018.
//

#include "exceptions.h"
#include "World.h"
#include "testMacros.h"

using namespace mtm;

bool testAddClan() {
    World world;

    ASSERT_EXCEPTION(world.addClan(""), WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addClan("CLAN"));
    ASSERT_EXCEPTION(world.addClan("CLAN"), WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(world.addClan("ANOTHER CLAN"));

    world.printClan(cout, "CLAN");
    world.printClan(cout, "ANOTHER CLAN");

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

    world.printClan(cout, "CLAN");
    world.printGroup(cout, "GROUP");

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
    ASSERT_NO_EXCEPTION(world.addClan("TEST_CLAN1"));
    ASSERT_NO_EXCEPTION(world.addClan("TEST_CLAN2"));
    ASSERT_EXCEPTION(world.uniteClans("TEST1", "TEST2", "CLAN1"),
                     WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(world.uniteClans("TEST_CLAN1", "TEST_CLAN2", "CLAN2"));

    world.addArea("PLAIN", PLAIN);
    world.addGroup("GROUP1", "CLAN1", 0, 1, "PLAIN");
    world.addGroup("GROUP2", "CLAN2", 2, 2, "PLAIN");

    ASSERT_NO_EXCEPTION(world.uniteClans("CLAN1", "CLAN2", "TEAM_NAME"));

    world.printClan(cout, "TEAM_NAME");

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
    ASSERT_EXCEPTION(world.makeReachable("Haifa","M0rodor"),WorldClanNotFound);
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
int main() {
    RUN_TEST(testReachable);
    RUN_TEST(testMoveGroup);
    RUN_TEST(testAddClan);
    RUN_TEST(testAddArea);
    RUN_TEST(testAddGroup);
    RUN_TEST(testUniteClans);
    RUN_TEST(testMakeFriends);
    return 0;
}
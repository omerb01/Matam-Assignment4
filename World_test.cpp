//
// Created by Omer on 23/01/2018.
//

#include "exceptions.h"
#include "testMacros.h"
#include "World.h"

using namespace mtm;

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
    //RUN_TEST(testReachable);
    RUN_TEST(testMoveGroup);
}
#include <iostream>
#include "../testMacros.h"
#include "../exceptions.h"
#include "../World.h"
using namespace mtm;

bool testWorldConstractor(){
    ASSERT_NO_EXCEPTION(World());
    return true;
}

bool testWorldAddClan() {
    World w ;
    ASSERT_NO_EXCEPTION(w.addClan("GameOfThrones"));
    ASSERT_EXCEPTION(w.addClan(""),WorldInvalidArgument);
    ASSERT_EXCEPTION(w.addClan("GameOfThrones"),WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(w.addClan("DC"));
    ASSERT_NO_EXCEPTION(w.addClan("Marvel"));
    return true;
}

bool testWorldAddArea() {
    World w ;
    ASSERT_NO_EXCEPTION(w.addArea("Winterfell",PLAIN));
    ASSERT_EXCEPTION(w.addArea("",PLAIN),WorldInvalidArgument);
    ASSERT_EXCEPTION(w.addArea("Winterfell",PLAIN),WorldAreaNameIsTaken);
    ASSERT_NO_EXCEPTION(w.addArea("Bravos",RIVER));
    ASSERT_NO_EXCEPTION(w.addArea("The Eyire",MOUNTAIN));
    return true ;
}

bool testAddGroup() {
    World w ;
    w.addClan("GOT");
    w.addArea("Winterfell",PLAIN);
    w.addArea("NewYork",PLAIN);
    w.addClan("Marvel");
    ASSERT_NO_EXCEPTION(w.addGroup("Stark","GOT",10,10,"Winterfell"));
    ASSERT_EXCEPTION(w.addGroup("","GOT",10,10,"Winterfell")
    ,WorldInvalidArgument);
    ASSERT_EXCEPTION(w.addGroup("Stark","GOT",-1,10,"Winterfell")
    ,WorldInvalidArgument);
    ASSERT_EXCEPTION(w.addGroup("Stark","GOT",10,-1,"")
    ,WorldInvalidArgument);
    ASSERT_EXCEPTION(w.addGroup("Stark","GOT",0,0,"Winterfell")
    ,WorldInvalidArgument);
    ASSERT_EXCEPTION(w.addGroup("Stark","",10,10,"Winterfell")
    ,WorldGroupNameIsTaken);
    ASSERT_EXCEPTION(w.addGroup("Baratheon","",10,10,"Winterfell")
    ,WorldClanNotFound);
    ASSERT_EXCEPTION(w.addGroup("Baratheon","DC",10,10,"Winterfell")
    ,WorldClanNotFound);
    ASSERT_EXCEPTION(w.addGroup("Baratheon","",10,10,"")
    ,WorldClanNotFound);
    ASSERT_EXCEPTION(w.addGroup("Baratheon","GOT",10,10,"")
    ,WorldAreaNotFound);
    ASSERT_EXCEPTION(w.addGroup("Baratheon","GOT",10,10,"KingsLanding")
    ,WorldAreaNotFound);
    w.addArea("KingsLanding",PLAIN);
    ASSERT_NO_EXCEPTION(w.addGroup("Baratheon","GOT",2,2,"KingsLanding"));
    ASSERT_EXCEPTION(w.addGroup("Stark","Marvel",10,10,"NewYork")
    ,WorldGroupNameIsTaken);
    ASSERT_NO_EXCEPTION(w.addGroup("Tony Stark","Marvel",2,2,"NewYork"));
    return true ;
}

bool testWorldMakeReachable() {
    World w ;
    w.addClan("GOT");
    w.addArea("Winterfell",PLAIN);
    w.addArea("Kingslanding",PLAIN) ;
    w.addArea("CasterlyRock",MOUNTAIN);
    w.addArea("Bravos",RIVER) ;
    w.addArea("TheWall",MOUNTAIN);
    w.makeReachable("Winterfell" , "TheWall") ;
    ASSERT_EXCEPTION(w.makeReachable("",""),WorldAreaNotFound);
    ASSERT_EXCEPTION(w.makeReachable("Winterfell",""),WorldAreaNotFound);
    ASSERT_EXCEPTION(w.makeReachable("","Kingslanding"),WorldAreaNotFound);
    ASSERT_EXCEPTION(w.makeReachable("XXX","Kingslanding"),WorldAreaNotFound);
    ASSERT_EXCEPTION(w.makeReachable("Kingslanding","XXX"),WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(w.makeReachable("Kingslanding","TheWall"));
    ASSERT_NO_EXCEPTION(w.makeReachable("TheWall","Kingslanding"));
    ASSERT_NO_EXCEPTION(w.makeReachable("CasterlyRock","Bravos"));
    ASSERT_NO_EXCEPTION(w.makeReachable("TheWall","Kingslanding"));
    ASSERT_NO_EXCEPTION(w.makeReachable("Kingslanding","CasterlyRock"));
    return true;
}

bool testWorldMoveGroup() {
    World w ;
    w.addClan("TheNorth");
    w.addClan("TheSouth");
    w.addArea("Winterfell",PLAIN);
    w.addArea("Kingslanding",PLAIN) ;
    w.addArea("CasterlyRock",MOUNTAIN);
    w.addArea("Bravos",RIVER) ;
    w.addArea("TheWall",MOUNTAIN);
    w.makeReachable("Winterfell" , "TheWall") ;
    w.makeReachable("TheWall", "Winterfell") ;
    w.makeReachable("Winterfell","Kingslanding");
    w.makeReachable("CasterlyRock","Winterfell");
    w.makeReachable("Winterfell","CasterlyRock");
    w.makeReachable("CasterlyRock","Kingslanding");
    w.makeReachable("Kingslanding","Bravos");
    w.makeReachable("Bravos","Kingslanding");

    w.addGroup("Stark","TheNorth",1,1,"Winterfell");
    w.addGroup("NightsWatch","TheNorth",10,10,"TheWall");
    w.addGroup("Bolton","TheNorth",100,100,"Winterfell");

    w.addGroup("Lannister","TheSouth",10,10,"CasterlyRock");
    w.addGroup("Baratheon","TheSouth",1,0,"Kingslanding");
    w.addGroup("Tyrel","TheSouth",20,60,"Bravos");


    ASSERT_EXCEPTION(w.moveGroup("",""),WorldGroupNotFound);
    ASSERT_EXCEPTION(w.moveGroup("","Winterfell"),WorldGroupNotFound);
    ASSERT_EXCEPTION(w.moveGroup("Stark",""),WorldAreaNotFound);
    ASSERT_EXCEPTION(w.moveGroup("","Winterfell"),WorldGroupNotFound);
    ASSERT_EXCEPTION(w.moveGroup("Stark","Winterfell"),WorldGroupAlreadyInArea);
    ASSERT_EXCEPTION(w.moveGroup("Stark","Bravos"),WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(w.moveGroup("Bolton_2","TheWall"));//bolton_2 rule
    ASSERT_EXCEPTION(w.moveGroup("Lannister","TheWall"),WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(w.moveGroup("Lannister","Winterfell"));
    ASSERT_NO_EXCEPTION(w.moveGroup("Lannister","TheWall"));//lannister lost
    ASSERT_NO_EXCEPTION(w.moveGroup("Stark","CasterlyRock"));
    ASSERT_EXCEPTION(w.moveGroup("Stark","CasterlyRock")
                       ,WorldGroupAlreadyInArea);
    ASSERT_NO_EXCEPTION(w.moveGroup("Lannister","Winterfell"));
    ASSERT_NO_EXCEPTION(w.moveGroup("Lannister","CasterlyRock"));//stark died
    ASSERT_EXCEPTION(w.moveGroup("Stark","CasterlyRock")
                      ,WorldGroupNotFound);
    ASSERT_NO_EXCEPTION(w.moveGroup("Lannister","Kingslanding"));//rule
    ASSERT_EXCEPTION(w.moveGroup("Lannister","CasterlyRock")
                     ,WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(w.moveGroup("Lannister","Bravos"));
    ASSERT_NO_EXCEPTION(w.moveGroup("Tyrel","Kingslanding"));
    return true ;
}

bool testWorldMakeFriends() {
    World w ;
    w.addClan("GOT");
    w.addArea("Winterfell",PLAIN);
    w.addArea("NewYork",PLAIN) ;
    w.addClan("Marvel") ;
    w.addClan("DC") ;
    w.addGroup("Stark","GOT",10,10,"Winterfell");
    w.addGroup("TonyStark","Marvel",10,10,"NewYork");
    w.addGroup("SuperMan","DC",10,10,"NewYork");
    ASSERT_EXCEPTION(w.makeFriends("","GOT"),WorldClanNotFound);
    ASSERT_EXCEPTION(w.makeFriends("GOT",""),WorldClanNotFound);
    ASSERT_EXCEPTION(w.makeFriends("",""),WorldClanNotFound);
    ASSERT_EXCEPTION(w.makeFriends("GOT","Marbel"),WorldClanNotFound);
    ASSERT_NO_EXCEPTION(w.makeFriends("GOT","GOT"));
    ASSERT_NO_EXCEPTION(w.makeFriends("GOT","Marvel"));
    ASSERT_NO_EXCEPTION(w.makeFriends("DC","Marvel"));
    return true ;
}

bool testWorldUniteClans () {
    World w ;
    w.addClan("TheNorth");
    w.addClan("TheSouth") ;
    w.addClan("TheEast") ;
    w.addArea("Westeros",PLAIN);
    w.addGroup("Stark","TheNorth",1,1,"Westeros");
    w.addGroup("NightsWatch","TheNorth",10,10,"Westeros");
    w.addGroup("Bolton","TheNorth",100,100,"Westeros");
    w.addGroup("Lannister","TheSouth",10,10,"Westeros");
    w.addGroup("Baratheon","TheSouth",1,0,"Westeros");
    w.addGroup("Tyrel","TheSouth",20,60,"Westeros");
    w.addGroup("Targeryan","TheEast",10,10,"Westeros");
    w.addGroup("Unsullied","TheEast",1,0,"Westeros");
    ASSERT_EXCEPTION(w.uniteClans("","",""),WorldInvalidArgument);
    ASSERT_EXCEPTION(w.uniteClans("TheNorth","",""),WorldInvalidArgument);
    ASSERT_EXCEPTION(w.uniteClans("","TheSouth","PeaceClan")
                                              ,WorldClanNotFound);
    ASSERT_EXCEPTION(w.uniteClans("TheNorth","","PeaceClan")
                                              ,WorldClanNotFound);
    ASSERT_EXCEPTION(w.uniteClans("","TheSouth","TheEast")
                                              ,WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(w.uniteClans("TheNorth","TheSouth","PeaceClan"));
    ASSERT_EXCEPTION(w.addClan("PeaceClan"),WorldClanNameIsTaken);
    ASSERT_NO_EXCEPTION(w.addClan("TheNorth"));
    ASSERT_NO_EXCEPTION(w.uniteClans("PeaceClan","TheEast","TheSouth"));
    ASSERT_NO_EXCEPTION(w.uniteClans("TheSouth","TheNorth","PeaceClan"));
    return true;
}

bool testWorldPrintGroup() {
    World w ;
    w.addClan("TheNorth");
    w.addClan("TheSouth");
    w.addArea("Winterfell",PLAIN);
    w.addArea("CasterlyRock",MOUNTAIN);
    w.addArea("Bravos",RIVER) ;
    w.makeReachable("Winterfell","CasterlyRock");
    w.makeReachable("CasterlyRock","Winterfell");
    w.makeReachable("CasterlyRock","Bravos");
    w.makeReachable("Bravos","CasterlyRock");
    w.addGroup("Stark","TheNorth",20,20,"Winterfell");//group will split.
    std::ostringstream os;
    ASSERT_EXCEPTION(w.printGroup(os,""),WorldGroupNotFound);
    ASSERT_EXCEPTION(w.printGroup(os,"Baratheon"),WorldGroupNotFound);
    w.printGroup(os,"Stark");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Stark\n"
                        "Group's clan: TheNorth\n"
                        "Group's children: 10\n"
                        "Group's adults: 10\n"
                        "Group's tools: 40\n"
                        "Group's food: 50\n"
                        "Group's morale: 77\n"
                        "Group's current area: Winterfell\n"));
    w.addGroup("Lannister","TheSouth",100,100,"CasterlyRock");
    w.printGroup(os,"Lannister");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Lannister\n"
            "Group's clan: TheSouth\n"
            "Group's children: 100\n"
            "Group's adults: 100\n"
            "Group's tools: 400\n"
            "Group's food: 500\n"
            "Group's morale: 77\n"
            "Group's current area: CasterlyRock\n")) ;
    w.moveGroup("Stark","CasterlyRock"); //stark lost fight.
    w.printGroup(os,"Stark");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Stark\n"
            "Group's clan: TheNorth\n"
            "Group's children: 6\n"
            "Group's adults: 6\n"
            "Group's tools: 20\n"
            "Group's food: 25\n"
            "Group's morale: 61\n"
            "Group's current area: CasterlyRock\n"));
    w.addGroup("Tyrel","TheSouth",0,100,"Bravos");
    w.moveGroup("Stark","Bravos"); //clans not friend no trade.
    w.printGroup(os,"Stark");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Stark\n"
            "Group's clan: TheNorth\n"
            "Group's children: 6\n"
            "Group's adults: 6\n"
            "Group's tools: 20\n"
            "Group's food: 25\n"
            "Group's morale: 61\n"
            "Group's current area: Bravos\n"));
    w.makeFriends("TheNorth","TheSouth");
    w.moveGroup("Lannister","Winterfell");
    w.moveGroup("Stark","CasterlyRock"); // stark rule
    w.moveGroup("Stark","Bravos"); // no trade will happen.
    w.printGroup(os,"Stark");
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Stark\n"
            "Group's clan: TheNorth\n"
            "Group's children: 6\n"
            "Group's adults: 6\n"
            "Group's tools: 45\n"
            "Group's food: 0\n"
            "Group's morale: 61\n"
            "Group's current area: Bravos\n"));
    return true ;
}

bool testWorldPrintClan(){

    World w ;
    w.addClan("TheNorth");
    w.addClan("TheSouth");
    w.addArea("Winterfell",PLAIN);
    w.addArea("Kingslanding",PLAIN) ;
    w.addArea("CasterlyRock",MOUNTAIN);
    w.addArea("Bravos",RIVER) ;
    w.addGroup("Stark","TheNorth",4,4,"Winterfell");
    w.addGroup("NightsWatch_2","TheSouth",5,5,"Bravos");
    w.addGroup("NightsWatch","TheNorth",20,20,"Winterfell");//split
    w.addGroup("Bolton","TheNorth",1,1,"Winterfell");//join stark
    w.addGroup("Lannister","TheSouth",10,10,"CasterlyRock");
    w.addGroup("Baratheon","TheSouth",1,0,"Kingslanding");
    w.addGroup("Tyrel","TheSouth",100,100,"Bravos");
    std::ostringstream os;
    ASSERT_EXCEPTION(w.printClan(os,""),WorldClanNotFound);
    ASSERT_EXCEPTION(w.printClan(os,"Targeryan"),WorldClanNotFound);
    w.printClan(os,"TheNorth");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: TheNorth\n"
            "Clan's groups:\n"
            "NightsWatch_3\n"
            "NightsWatch\n"
            "Stark\n"));
    w.printClan(os,"TheSouth");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: TheSouth\n"
            "Clan's groups:\n"
            "Tyrel\n"
            "Lannister\n"
            "NightsWatch_2\n"
            "Baratheon\n"));
    return true ;
}

int main() {
    RUN_TEST(testWorldConstractor);
    RUN_TEST(testWorldAddClan);
    RUN_TEST(testWorldAddArea);
    RUN_TEST(testAddGroup);
    RUN_TEST(testWorldMakeReachable);
    RUN_TEST(testWorldMoveGroup);
    RUN_TEST(testWorldMakeFriends);
    RUN_TEST(testWorldUniteClans);
    RUN_TEST(testWorldPrintGroup);
    RUN_TEST(testWorldPrintClan);
    return 0;
}
#include "../testMacros.h"
#include "../Group.h"
#include "../Clan.h"
#include "../exceptions.h"

using namespace mtm;

bool testClanConstractor(){
    ASSERT_EXCEPTION(Clan(""),ClanEmptyName);
    ASSERT_NO_EXCEPTION(Clan("GameOfThrones"));
    return true;
}

bool testClanAddGroup(){
    Clan game_of_thrones("GameOfThrones");
    Group g1("Stark", "Marvel", 4, 5, 50, 50, 80);
    Group g2("Stark", "", 1, 0, 1000, 1000, 100);
    Group g3("X-Men", "Marvel", 4, 5, 50, 50, 80);
    Group g4("Tarly", 4, 5);
    ASSERT_NO_EXCEPTION(game_of_thrones.addGroup(g1));
    ASSERT_TRUE(g1.getClan()=="Marvel");
    ASSERT_EXCEPTION(game_of_thrones.addGroup(g2),ClanGroupNameAlreadyTaken);
    ASSERT_NO_EXCEPTION(game_of_thrones.addGroup(g3));
    g1.unite(g3,50);
    ASSERT_EXCEPTION(game_of_thrones.addGroup(g3),ClanGroupIsEmpty);
    ASSERT_EXCEPTION(game_of_thrones.addGroup(g1),ClanGroupNameAlreadyTaken);
    ASSERT_NO_EXCEPTION(game_of_thrones.addGroup(g4));
    return true;
}

bool testClanGetGroup(){
    Clan game_of_thrones("GameOfThrones");
    Group g1("Stark", "Marvel", 4, 5, 50, 50, 80);
    Group g2("X-Men", "Marvel", 4, 5, 50, 50, 80);
    Group g3("Tarly", 4, 5);
    ASSERT_EXCEPTION(game_of_thrones.getGroup(""),ClanGroupNotFound);
    game_of_thrones.addGroup(g1);
    game_of_thrones.addGroup(g2);
    game_of_thrones.addGroup(g3);
    ASSERT_EXCEPTION(game_of_thrones.getGroup("Tarlyy"),ClanGroupNotFound);
    ASSERT_NO_EXCEPTION(game_of_thrones.getGroup("Stark"));
    GroupPointer got_ptr = game_of_thrones.getGroup("Tarly");
    ASSERT_TRUE((*got_ptr).getName()=="Tarly");
    ASSERT_TRUE((*got_ptr).getClan()=="GameOfThrones");
    ASSERT_TRUE((*got_ptr).getSize()==9);
    got_ptr = game_of_thrones.getGroup("Stark");
    ASSERT_TRUE((*got_ptr).getName()=="Stark");
    ASSERT_TRUE((*got_ptr).getClan()=="GameOfThrones");
    ASSERT_TRUE((*got_ptr).getSize()==9);
    return true;
}

bool testClanDoesContain(){
    Clan game_of_thrones("GameOfThrones");
    Group g1("Stark", "Marvel", 4, 5, 50, 50, 80);
    Group g2("X-Men", "Marvel", 4, 5, 50, 50, 80);
    Group g3("Tarly", 4, 5);
    ASSERT_FALSE(game_of_thrones.doesContain("Stark"));
    game_of_thrones.addGroup(g1);
    game_of_thrones.addGroup(g2);
    game_of_thrones.addGroup(g3);
    ASSERT_TRUE(game_of_thrones.doesContain("Stark"));
    ASSERT_TRUE(game_of_thrones.doesContain("X-Men"));
    ASSERT_TRUE(game_of_thrones.doesContain("Tarly"));
    ASSERT_FALSE(game_of_thrones.doesContain(""));
    ASSERT_FALSE(game_of_thrones.doesContain("Starki"));
    return true;
}

bool testClanGetSize() {
    Clan game_of_thrones("GameOfThrones");
    Group g1("Stark", "Marvel", 4, 5, 50, 50, 80);
    Group g2("X-Men", "Marvel", 4, 5, 50, 50, 80);
    Group g3("Tarly", 4, 5);
    ASSERT_TRUE(game_of_thrones.getSize()==0);
    game_of_thrones.addGroup(g1);
    game_of_thrones.addGroup(g2);
    game_of_thrones.addGroup(g3);
    ASSERT_TRUE(game_of_thrones.getSize()==27);
    return true;
}

bool testClanUnite(){
    Clan got("GameOfThrones");
    Group g1("Stark", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g2("Baratheon", "Marvel", 4, 5, 50, 50, 80);
    Group g3("Tarly", 4, 5);
    got.addGroup(g1);
    got.addGroup(g2);
    got.addGroup(g3);
    Clan marvel("Marvel");
    Group g4("X-Men", "Marvel", 4, 5, 50, 50, 80);
    Group g5("Deadpool", "Marvel", 1, 0, 100, 100, 100);
    Group g6("Avengers", 4, 5);
    Group g7("Stark",1,0);
    marvel.addGroup(g4);
    marvel.addGroup(g5);
    marvel.addGroup(g6);
    Clan got2("GameOfThrones");
    got2.addGroup(g4);
    got2.addGroup(g3);
    got2.addGroup(g7);
    Clan empty("Nothing");
    ASSERT_EXCEPTION(got.unite(marvel,""),ClanEmptyName);
    ASSERT_EXCEPTION(got.unite(got2,""),ClanEmptyName);
    ASSERT_EXCEPTION(got.unite(got2,"ERROR"),ClanCantUnite);
    ASSERT_NO_EXCEPTION(empty.unite(got2,"X-Men"));
    ASSERT_TRUE(empty.getSize()==19);
    ASSERT_TRUE(got2.getSize()==0);
    ASSERT_NO_EXCEPTION(marvel.unite(got,"Family"));
    ASSERT_TRUE(marvel.getSize()==46);
    ASSERT_TRUE(got.getSize()==0);
    GroupPointer group_check = marvel.getGroup("Stark");
    ASSERT_TRUE((*group_check).getName()=="Stark");
    ASSERT_TRUE((*group_check).getClan()=="Family");
    ASSERT_TRUE((*group_check).getSize()==9);
    ASSERT_EXCEPTION(empty.unite(marvel,"ERROR"),ClanCantUnite);
    return true;
}

bool testClanIsFriend(){
    Clan got("GameOfThrones");
    Clan marvel("Marvel");
    Clan dc("DC");
    Clan bb("BreakingBad");
    Clan bs("BlakSails");
    ASSERT_TRUE(got.isFriend(got));
    ASSERT_FALSE(got.isFriend(marvel));
    ASSERT_FALSE(marvel.isFriend(got));
    ASSERT_NO_EXCEPTION(got.makeFriend(marvel));
    ASSERT_TRUE(got.isFriend(marvel));
    ASSERT_TRUE(marvel.isFriend(got));
    ASSERT_NO_EXCEPTION(got.makeFriend(dc));
    ASSERT_NO_EXCEPTION(marvel.makeFriend(bs));
    ASSERT_NO_EXCEPTION(dc.makeFriend(bb));
    ASSERT_FALSE(marvel.isFriend(dc));
    marvel.unite(got,"NewShow");
    ASSERT_TRUE(marvel.isFriend(dc));
    ASSERT_FALSE(marvel.isFriend(bb));
    ASSERT_TRUE(marvel.isFriend(bs));
    return true ;
}

bool testClanPrint() {
    Clan got("Game Of Thrones");
    Group g1("Stark", "Marvel", 10,10, 50, 50, 80);
    Group g2("Baratheon", "Marvel", 8, 8, 50, 50, 80);
    Group g3("Tarly", 3, 3);
    Group g4("Lannister", "Marvel", 30, 30, 50, 50, 80);
    Group g5("Targaryen", "Marvel", 50, 50, 50, 50, 80);
    Clan empty_clan("Empty");
    got.addGroup(g1);
    got.addGroup(g2);
    got.addGroup(g3);
    got.addGroup(g4);
    got.addGroup(g5);
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << got);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Game Of Thrones\n"
            "Clan's groups:\n"
            "Targaryen\n"
            "Lannister\n"
            "Stark\n"
            "Baratheon\n"
            "Tarly\n"));
    ASSERT_NO_EXCEPTION(os << empty_clan);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Empty\n"
            "Clan's groups:\n"));
    return true ;
}

int main(){
    RUN_TEST(testClanConstractor);
    RUN_TEST(testClanAddGroup);
    RUN_TEST(testClanGetGroup);
    RUN_TEST(testClanDoesContain);
    RUN_TEST(testClanGetSize);
    RUN_TEST(testClanUnite);
    RUN_TEST(testClanIsFriend);
    RUN_TEST(testClanPrint);
    return 0;
}

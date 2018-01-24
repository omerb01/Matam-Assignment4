#include "../testMacros.h"
#include "../Group.h"
#include "../exceptions.h"

using namespace mtm;

bool testGroupConstractor() {
    ASSERT_EXCEPTION(Group("", 1, 1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", -1, 1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", 1, -1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", 0, 0), GroupInvalidArgs);
    ASSERT_NO_EXCEPTION(Group("Stark",0,10));
    ASSERT_NO_EXCEPTION(Group("Stark",100,0));
    ASSERT_EXCEPTION(Group("", "GameOfThrones", 1, 1, 1, 1, 1),
                     GroupInvalidArgs);
    ASSERT_NO_EXCEPTION(Group("Stark", "", 1, 1, 1, 1, 1));
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", -1, 1, 1, 1, 1),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", 1, -1, 1, 1, 1),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", 1, 1, -1, 1, 1),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", 1, 1, 1, -1, 1),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", 1, 1, 1, 1, -1),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", 1, 1, 1, 1, 101),
                     GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Stark", "GameOfThrones", 0, 0, 1, 1, 1),
                     GroupInvalidArgs);
    ASSERT_NO_EXCEPTION(Group("Stark","GameOfThrones",100,0,21,0,1));
    ASSERT_NO_EXCEPTION(Group("Stark","GameOfThrones",0,10,0,11,0));
    ASSERT_NO_EXCEPTION(Group("Stark","GameOfThrones",100,0,0,0,100));
    return true;
}

bool testGroupGetName() {
    Group g1("Stark", "GameOfThrones", 10, 10, 40, 50, 80);
    Group g2("Lannister", "GameOfThrones", 5, 5, 20, 10, 90);
    Group g3("Tarly", 5, 6);
    Group g4("Sand", 50, 80);
    ASSERT_TRUE(g1.getName() == "Stark");
    ASSERT_TRUE(g2.getName() == "Lannister");
    ASSERT_TRUE(g3.getName() == "Tarly");
    ASSERT_TRUE(g4.getName() == "Sand");
    return true;
}

bool testGroupGetSize(){
    Group g1("Stark", "GameOfThrones", 10, 10, 40, 50, 80);
    Group g2("Lannister", "GameOfThrones", 5, 5, 20, 10, 90);
    Group g3("Tarly", 0, 6);
    Group g4("Sand", 50, 0);
    ASSERT_TRUE(g1.getSize() == 20);
    ASSERT_TRUE(g2.getSize() == 10);
    ASSERT_TRUE(g3.getSize() == 6);
    ASSERT_TRUE(g4.getSize() == 50);
    return true;
}

bool testGroupGetClan(){
    Group g1("Stark", "GameOfThrones", 10, 10, 40, 50, 80);
    Group g2("Lannister", "GameOfThrones", 5, 5, 20, 10, 90);
    Group g3("Tarly", 0, 6);
    Group g4("Sand", 50, 0);
    ASSERT_TRUE(g1.getClan() == "GameOfThrones");
    ASSERT_TRUE(g2.getClan() == "GameOfThrones");
    ASSERT_TRUE(g3.getClan() == "");
    ASSERT_TRUE(g4.getClan() == "");
    return true;
}

bool testGroupChangeClan(){
    Group g1("Stark", "GameOfThrones", 10, 10, 40, 50, 61);
    g1.changeClan("GameOfThrones");
    ASSERT_TRUE(g1.getClan() == "GameOfThrones");
    g1.changeClan("");
    ASSERT_TRUE(g1.getClan() == "");
    g1.changeClan("Baratheon");
    ASSERT_TRUE(g1.getClan() == "Baratheon");
    return true;
}

bool testGroupOperators(){
    Group g1("Stark", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g2("Stark", "IronMan", 1, 0, 1000, 1000, 100);
    Group g3("Stark", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g4("Starki", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g5("A", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g6("Z", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g7("Stark", "GameOfThrones", 4, 5, 50, 51, 80);
    ASSERT_TRUE(g1<g2);
    ASSERT_FALSE(g1>g2);
    ASSERT_TRUE(g1<g6);
    ASSERT_FALSE(g1>g6);
    ASSERT_TRUE(g1>g5);
    ASSERT_FALSE(g1<g5);
    ASSERT_TRUE(g2>g1);
    ASSERT_FALSE(g2<g1);
    ASSERT_TRUE(g1<=g2);
    ASSERT_FALSE(g1>=g2);
    ASSERT_TRUE(g1<=g6);
    ASSERT_FALSE(g1>=g6);
    ASSERT_TRUE(g1>=g5);
    ASSERT_FALSE(g1<=g5);
    ASSERT_TRUE(g2>=g1);
    ASSERT_FALSE(g2<=g1);
    ASSERT_TRUE(g2>=g3);
    ASSERT_FALSE(g1>=g4);
    ASSERT_TRUE(g1<=g4);
    ASSERT_FALSE(g1==g4);
    ASSERT_TRUE(g1==g3);
    ASSERT_TRUE(g1!=g4);
    ASSERT_FALSE(g1!=g3);
    ASSERT_TRUE(g7>=g1);
    ASSERT_TRUE(g7!=g1);
    return true;
}

bool testGroupUnite() {
    Group g1("Stark", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g2("Stark", "IronMan", 1, 0, 1000, 1000, 100);
    Group g3("Baratheon", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g4("Tarly",2,2);
    Group g5("Stark", "GameOfThrones", 4, 5, 50, 50, 80);
    Group g6("Snow", "GameOfThrones", 1, 1, 50, 50, 69);
    ASSERT_FALSE(g1.unite(g2,100));
    ASSERT_FALSE(g1.unite(g1,100));
    ASSERT_TRUE(g1.unite(g5,100));
    ASSERT_FALSE(g1.unite(g6,100));
    ASSERT_FALSE(g6.unite(g1,100));
    ASSERT_FALSE(g4.unite(g1,100));
    ASSERT_FALSE(g1.unite(g4,100));
    ASSERT_FALSE(g1.unite(g3,26));
    ASSERT_TRUE(g3.unite(g1,27));
    ASSERT_TRUE(g1.getSize()==0);
    ASSERT_TRUE(g3.getSize()==27);
    ASSERT_TRUE(g3.getName()=="Stark");
    return true;
}

bool testGroupDivide () {
    Group g1("Stark", "GameOfThrones", 1, 0, 50, 50, 80);
    Group g2("Stark", "GameOfThrones", 0, 1, 50, 50, 80);
    Group g3("Stark", "GameOfThrones", 1, 1, 50, 50, 80);
    Group g4("Stark", "GameOfThrones", 1, 1, 50, 50, 80);
    Group g5("Baratheon", "GameOfThrones", 9, 10, 50, 50, 80);
    g1.unite(g5,20); // now has 10 adults and 10 childrens
    ASSERT_EXCEPTION(g5.divide(""),GroupInvalidArgs);
    ASSERT_EXCEPTION(g5.divide("new_group"),GroupCantDivide);
    ASSERT_EXCEPTION(g2.divide("new_group"),GroupCantDivide);
    ASSERT_EXCEPTION(g3.divide("new_group"),GroupCantDivide);
    ASSERT_NO_EXCEPTION(g1.divide("new_group"));//now g1 has 5 adults&children
    Group g6=g1.divide("Baratheon");
    ASSERT_TRUE(g6.getName()=="Baratheon");
    ASSERT_TRUE(g6.getClan()=="GameOfThrones");
    ASSERT_TRUE(g6.getSize()==4);
    return true ;
}

bool testGroupFight() {
    Group g1("Stark", "GameOfThrones", 50, 50, 50, 50, 82);
    Group g2("Stark", "GameOfThrones", 50, 50, 50, 50, 82);
    Group g3("Tarly", "GameOfThrones", 1, 1, 50, 50, 82);
    Group g4("Frey", "GameOfThrones", 7, 9, 50, 50, 1);
    Group g5("Stark", "IronMan2", 50, 29, 30, 64, 100);
    ASSERT_EXCEPTION(g1.fight(g1),GroupCantFightWithItself);
    ASSERT_TRUE(g1.fight(g3)==WON);
    ASSERT_EXCEPTION(g1.fight(g3),GroupCantFightEmptyGroup);
    ASSERT_EXCEPTION(g3.fight(g1),GroupCantFightEmptyGroup);
    ASSERT_EXCEPTION(g3.fight(g3),GroupCantFightWithItself);
    ASSERT_TRUE(g4.fight(g1)==LOST);
    ASSERT_TRUE(g5.fight(g1)==DRAW);
    ASSERT_TRUE(g1.fight(g5)==DRAW);
    return true ;
}

bool testGroupTrade() {
    Group g1("MoreTools", "Traders", 50, 50, 100, 2, 82);
    Group g2("MoreTools", "Traders", 1, 1, 152, 13, 82);
    Group g3("MoreFood", "Traders", 7, 9, 2, 10, 1);
    Group g4("MoreFood", "Traders", 50, 29, 34, 35, 100);
    Group g5("Stark", "IronMan2", 50, 29, 20, 20, 100);
    ASSERT_EXCEPTION(g1.trade(g1),GroupCantTradeWithItself);
    ASSERT_FALSE(g1.trade(g2));
    ASSERT_FALSE(g3.trade(g4));
    ASSERT_FALSE(g2.trade(g5));
    ASSERT_FALSE(g5.trade(g2));
    ASSERT_TRUE(g1.trade(g3));
    ASSERT_TRUE(g4.trade(g2));
    return true ;
}

bool testGroupPrint() {
    Group starks("Stark", "GameOfThrones", 5, 5, 50, 50, 90);
    Group lannisters("Lannister", "GameOfThrones", 20, 20, 100, 100, 90);
    Group targaryen("Targaryen","GameOfThrones",100,100,100,100,90);
    std::ostringstream os;
    os << starks << lannisters ;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Stark\n"
            "Group's clan: GameOfThrones\n"
            "Group's children: 5\n"
            "Group's adults: 5\n"
            "Group's tools: 50\n"
            "Group's food: 50\n"
            "Group's morale: 90\n"
            "Group's name: Lannister\n"
            "Group's clan: GameOfThrones\n"
            "Group's children: 20\n"
            "Group's adults: 20\n"
            "Group's tools: 100\n"
            "Group's food: 100\n"
            "Group's morale: 90\n"));
    lannisters.fight(starks);
    os << starks << lannisters ;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Stark\n"
            "Group's clan: GameOfThrones\n"
            "Group's children: 3\n"
            "Group's adults: 3\n"
            "Group's tools: 25\n"
            "Group's food: 25\n"
            "Group's morale: 72\n"
            "Group's name: Lannister\n"
            "Group's clan: GameOfThrones\n"
            "Group's children: 20\n"
            "Group's adults: 15\n"
            "Group's tools: 75\n"
            "Group's food: 112\n"
            "Group's morale: 100\n"));
    starks.unite(targaryen,250);
    os << targaryen << starks ;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: \n"
            "Group's clan: \n"
            "Group's children: 0\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 0\n"
            "Group's morale: 0\n"
            "Group's name: Targaryen\n"
            "Group's clan: GameOfThrones\n"
            "Group's children: 103\n"
            "Group's adults: 103\n"
            "Group's tools: 125\n"
            "Group's food: 125\n"
            "Group's morale: 89\n"));
    return true;
}

int main(){
    RUN_TEST(testGroupConstractor);
    RUN_TEST(testGroupGetName);
    RUN_TEST(testGroupGetSize);
    RUN_TEST(testGroupGetClan);
    RUN_TEST(testGroupChangeClan);
    RUN_TEST(testGroupOperators);
    RUN_TEST(testGroupUnite);
    RUN_TEST(testGroupDivide);
    RUN_TEST(testGroupFight);
    RUN_TEST(testGroupTrade);
    RUN_TEST(testGroupPrint);
    return 0;
}

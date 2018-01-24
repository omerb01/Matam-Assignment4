#include "..\Group.h"
#include "..\testMacros.h"
#include "..\exceptions.h"

using namespace mtm;

bool ConstractorGroup(){
    ASSERT_EXCEPTION(Group("", 1, 1), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("","",10,40,70, 1,300), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Invalid","",10,40,70, 1,300), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Invalid","",-20,40,70, 1,20), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Invalid","",10,-50,70, 1,20), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Invalid","",10,50,-2, 1,20), GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Invalid","",10,50,70, -80,20), GroupInvalidArgs);
    ASSERT_NO_EXCEPTION(Group("valid","",10,50,70, 80,20));
    ASSERT_NO_EXCEPTION(Group("valid", 1, 1));
    Group alpha("Alpha", "Beta", 10, 10, 40, 50, 80);
    Group gamma("Gamma", "Lambda" ,5 , 5, 20, 10 , 90);
    return true;
}

bool GetsGroup() {
    Group Nana("Nana", "Tea", 10, 10, 40, 50, 80);
    Group Luiza("Luiza", "Tea" ,5 , 5, 20, 10 , 90);
    ASSERT_TRUE(Nana.getName() == "Nana");
    ASSERT_TRUE(Luiza.getName() == "Luiza");
    ASSERT_TRUE(Nana.getClan()=="Tea");
    ASSERT_TRUE(Luiza.getClan()=="Tea");
    ASSERT_TRUE(Luiza.getClan()==Nana.getClan());
    ASSERT_TRUE(Nana.getSize()==20);
    ASSERT_TRUE(Luiza.getSize()==10);
    ASSERT_NO_EXCEPTION(Nana.changeClan("Tree"));
    ASSERT_TRUE(Nana.getClan() == "Tree");
    ASSERT_NO_EXCEPTION(Luiza.changeClan("Tutim"));
    ASSERT_TRUE(Luiza.getClan() == "Tutim");
    return true;
}
bool OperatorsGroup(){
    Group Nana("Nana", "Tea", 10, 10, 40, 50, 80);
    Group Copy("Nana", "Tea" ,10 , 10, 40, 50 , 80);
    Group Luiza("Luiza", "Tea" ,10 , 10, 40, 50 , 80);
    Group Luizar("Luizar", "Tea" ,10 , 10, 40, 50 , 80);
    Group Jasmin("Jasmin", "Tea" ,4 , 3, 10, 5 , 40);
    ASSERT_TRUE(Luiza > Nana);
    ASSERT_TRUE(Luiza > Luizar);
    ASSERT_TRUE(Luiza >= Nana);
    ASSERT_TRUE(Nana < Luiza);
    ASSERT_TRUE(Nana <= Luiza);
    ASSERT_TRUE(Luiza > Jasmin);
    ASSERT_TRUE(Nana == Copy);
    ASSERT_TRUE(Nana >= Copy);
    ASSERT_TRUE(Nana <= Copy);
    ASSERT_TRUE(Nana != Jasmin);
    ASSERT_FALSE(Nana == Luiza);
    return true;
}
bool ChangeClanGroup(){
    Group Nana("Nana", "Tea", 10, 10, 40, 50, 80);
    Group Luiza("Luiza", "" ,10 , 10, 40, 50 , 30);
    Nana.changeClan("Tea");
    Luiza.changeClan("");
    std::ostringstream os;
    os << Nana << Luiza;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 80\n"
            "Group's name: Luiza\n"
            "Group's clan: \n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 30\n"));
    Nana.changeClan("Tea2");
    Luiza.changeClan("Tea");
    os << Nana <<Luiza;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea2\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 72\n"
            "Group's name: Luiza\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 33\n"));
    return true;
}
bool UnitGroup(){
    Group Nana("Nana", "", 10, 10, 40, 50, 80);
    Group Shiba("Shiba", "" ,10 , 10, 40, 50 , 60);
    Group Luiza("Luiza", "" ,10 , 10, 40, 50 , 80);
    ASSERT_FALSE(Nana.unite(Luiza,150));
    ASSERT_FALSE(Nana.unite(Shiba,150));
    Nana.changeClan("Tea");
    Luiza.changeClan("Tea");
    ASSERT_FALSE(Nana.unite(Luiza,30));
    ASSERT_TRUE(Nana.unite(Luiza,40));
    std::ostringstream os;
    os << Nana <<Luiza;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Luiza\n"
            "Group's clan: Tea\n"
            "Group's children: 20\n"
            "Group's adults: 20\n"
            "Group's tools: 80\n"
            "Group's food: 100\n"
            "Group's morale: 88\n"
            "Group's name: \n"
            "Group's clan: \n"
            "Group's children: 0\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 0\n"
            "Group's morale: 0\n"));

    return true;
}
bool DivideGroup(){
    Group Nana("Nana", "Tea",2 , 1, 41, 51, 80);
    ASSERT_EXCEPTION(Nana.divide(""),GroupInvalidArgs);
    Group Luiza("Luiza", "Tea" ,1 , 1, 40, 50 , 80);
    ASSERT_EXCEPTION(Luiza.divide("Shiba"),GroupCantDivide);
    Group Shiba=Nana.divide("Shiba");
    std::ostringstream os;
    os << Nana <<Shiba;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 1\n"
            "Group's adults: 1\n"
            "Group's tools: 21\n"
            "Group's food: 26\n"
            "Group's morale: 80\n"
            "Group's name: Shiba\n"
            "Group's clan: Tea\n"
            "Group's children: 1\n"
            "Group's adults: 0\n"
            "Group's tools: 20\n"
            "Group's food: 25\n"
            "Group's morale: 80\n"));
    return true;
}
bool FightGroup(){
    Group Nana("Nana", "Tea",10 , 9, 41, 51, 90);
    Group Copy("Nana", "Tea",10 , 9, 41, 51, 90);
    Group Luiza("Luiza", "Tea" ,0 , 0, 40, 50 , 80);
    Group Shiba("Shiba", "Tea" ,1 , 1, 40, 50 , 60);
    Group Ginger("Ginger", "Tea" ,10 , 11, 73, 61 , 90);
    ASSERT_EXCEPTION(Nana.fight(Nana),GroupCantFightWithItself);
    ASSERT_EXCEPTION(Nana.fight(Luiza),GroupCantFightEmptyGroup);
    ASSERT_TRUE(Nana.fight(Copy)==DRAW);
    ASSERT_TRUE(Nana.fight(Shiba)==WON);
    std::ostringstream os;
    os << Nana <<Shiba;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 7\n"
            "Group's tools: 31\n"
            "Group's food: 63\n"
            "Group's morale: 100\n"
            "Group's name: \n"
            "Group's clan: \n"
            "Group's children: 0\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 0\n"
            "Group's morale: 0\n"));
    ASSERT_TRUE(Nana.fight(Ginger)==LOST);
    os << Nana <<Ginger;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 6\n"
            "Group's adults: 4\n"
            "Group's tools: 15\n"
            "Group's food: 31\n"
            "Group's morale: 80\n"
            "Group's name: Ginger\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 9\n"
            "Group's tools: 55\n"
            "Group's food: 76\n"
            "Group's morale: 100\n"));

    return true;
}
bool TradeGroup(){
    Group Nana("Nana", "Tea",10 , 9, 41, 51, 90);
    Group Copy("Nana", "Tea",10 , 9, 41, 51, 90);
    Group Luiza("Luiza", "Tea" ,0 , 0, 40, 50 , 80);
    Group Shiba("Shiba", "Tea" ,1 , 1, 40, 40 , 60);
    Group Ginger("Ginger", "Tea" ,10 , 30, 61, 51 , 90);
    ASSERT_EXCEPTION(Nana.trade(Nana),GroupCantTradeWithItself);
    ASSERT_TRUE(Luiza.trade(Nana)== false);
    ASSERT_TRUE(Nana.trade(Shiba)== false);
    ASSERT_TRUE(Nana.trade(Ginger)== true);
    std::ostringstream os;
    os << Nana <<Ginger;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Nana\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 9\n"
            "Group's tools: 46\n"
            "Group's food: 46\n"
            "Group's morale: 90\n"
            "Group's name: Ginger\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 30\n"
            "Group's tools: 56\n"
            "Group's food: 56\n"
            "Group's morale: 90\n"));
    return true;
}
int main(){
    RUN_TEST(ConstractorGroup);
    RUN_TEST(GetsGroup);
    RUN_TEST(OperatorsGroup);
    RUN_TEST(ChangeClanGroup);
    RUN_TEST(UnitGroup);
    RUN_TEST(DivideGroup);
    RUN_TEST(FightGroup);
    RUN_TEST(TradeGroup);
    return 0;
}



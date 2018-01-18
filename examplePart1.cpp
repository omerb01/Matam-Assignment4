#include "testMacros.h"
#include "Group.h"
#include "exceptions.h"

using namespace mtm;

bool exampleGroup(){
    ASSERT_EXCEPTION(Group("", 1, 1), GroupInvalidArgs);
    Group alpha("Alpha", "Beta", 10, 10, 40, 50, 80);
    Group gamma("Gamma", "Lambda" ,5 , 5, 20, 10 , 90);
    ASSERT_TRUE(alpha.getName() == "Alpha");
    ASSERT_TRUE(alpha.getSize() == 20);
    ASSERT_TRUE(alpha.getClan() == "Beta");
    ASSERT_NO_EXCEPTION(alpha.changeClan("Lambda"));
    ASSERT_TRUE(alpha.getClan() == "Lambda");
    ASSERT_TRUE(alpha > gamma);
    ASSERT_FALSE(alpha == gamma);
    
    ASSERT_TRUE(alpha.trade(gamma));
    
    std::ostringstream os;
    
    os << alpha << gamma;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Lambda\n"
        "Group's children: 10\n"
        "Group's adults: 10\n"
        "Group's tools: 45\n"
        "Group's food: 45\n"
        "Group's morale: 72\n"
        "Group's name: Gamma\n"
        "Group's clan: Lambda\n"
        "Group's children: 5\n"
        "Group's adults: 5\n"
        "Group's tools: 15\n"
        "Group's food: 15\n"
        "Group's morale: 90\n"));
    
    
    ASSERT_TRUE(alpha.unite(gamma, 40));
    
    
    os << alpha << gamma;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Lambda\n"
        "Group's children: 15\n"
        "Group's adults: 15\n"
        "Group's tools: 60\n"
        "Group's food: 60\n"
        "Group's morale: 78\n"
        "Group's name: \n" // notice the space!!!!!
        "Group's clan: \n" //notice the space!!!!!
        "Group's children: 0\n"
        "Group's adults: 0\n"
        "Group's tools: 0\n"
        "Group's food: 0\n"
        "Group's morale: 0\n"));
    
    Group alpha2 = alpha.divide("Alpha 2");
    ASSERT_TRUE(alpha.fight(alpha2) == WON);
    
    os << alpha << alpha2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Alpha\n"
        "Group's clan: Lambda\n"
        "Group's children: 8\n"
        "Group's adults: 6\n"
        "Group's tools: 23\n"
        "Group's food: 37\n"
        "Group's morale: 94\n"
        "Group's name: Alpha 2\n"
        "Group's clan: Lambda\n"
        "Group's children: 4\n"
        "Group's adults: 4\n"
        "Group's tools: 15\n"
        "Group's food: 15\n"
        "Group's morale: 62\n"));
    
    return true;
}

int main(){
    RUN_TEST(exampleGroup);
    return 0;
}

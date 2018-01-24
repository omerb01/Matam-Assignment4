#include "testMacros.h"
#include "Group.h"
#include "Clan.h"
#include "exceptions.h"

using namespace mtm;

bool constractorClan() {
    Clan beta("Beta");
    ASSERT_EXCEPTION(Clan(""), ClanEmptyName);
    Clan copy(beta);
    ASSERT_TRUE(copy.isFriend(copy));
    ASSERT_TRUE(copy.getSize() == 0);
    return 1;
}

bool addGetGroupClan() {
    Group Nana("Nana", "Tea", 0, 0, 40, 50, 80);
    Group Luiza("Luiza", "Tea", 10, 5, 20, 10, 90);
    Group Shiba("Shiba", "", 10, 10, 40, 50, 60);
    Group copy_luiza("Luiza", "Tea", 10, 5, 20, 10, 90);
    Clan Tea("Tea");
    ASSERT_EXCEPTION(Tea.addGroup(Nana), ClanGroupIsEmpty);
    ASSERT_NO_EXCEPTION(Tea.addGroup(Luiza));
    ASSERT_NO_EXCEPTION(Tea.addGroup(Shiba));
    ASSERT_EXCEPTION(Tea.addGroup(copy_luiza), ClanGroupNameAlreadyTaken);
    ASSERT_TRUE(Tea.getGroup("Shiba")->getClan() == "Tea");
    ASSERT_TRUE(Tea.getSize() == 35);
    ostringstream os;
    os << *(Tea.getGroup(Luiza.getName())) << *(Tea.getGroup(Shiba.getName()));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Luiza\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 5\n"
            "Group's tools: 20\n"
            "Group's food: 10\n"
            "Group's morale: 90\n"
            "Group's name: Shiba\n"
            "Group's clan: Tea\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 66\n"));
    return true;
}

bool GetSizeClan() {
    Group Luiza("Luiza", "Tea", 10, 90, 20, 10, 90);
    Group Shiba("Shiba", "", 10, 10, 40, 50, 60);
    Clan Tea("Tea");
    ASSERT_TRUE(Tea.getSize() == 0);
    ASSERT_NO_EXCEPTION(Tea.addGroup(Luiza));
    ASSERT_TRUE(Tea.getSize() == 100);
    ASSERT_NO_EXCEPTION(Tea.addGroup(Shiba));
    ASSERT_TRUE(Tea.getSize() == 120);
    return true;
}

bool IsMakeFriendClan() {
    Group Luiza("Luiza", "Tea", 10, 90, 20, 10, 90);
    Group Shiba("Shiba", "", 10, 10, 40, 50, 60);
    Clan Tea("Tea");
    ASSERT_TRUE(Tea.isFriend(Tea));
    ASSERT_NO_EXCEPTION(Tea.addGroup(Luiza));
    ASSERT_NO_EXCEPTION(Tea.addGroup(Shiba));
    Clan Tree("Tree");
    ASSERT_NO_EXCEPTION(Tea.makeFriend(Tree));
    ASSERT_TRUE(Tea.isFriend(Tree));
    return 1;
}

bool UnitClan() {
    Group Nana("Nana", "Tea", 10, 10, 41, 51, 90);
    Group Copy("Nana", "Tea", 10, 10, 41, 51, 90);
    Group Luiza("Luiza", "Tea", 80, 20, 40, 50, 80);
    Group Shiba("Shiba", "Tea", 10, 10, 40, 40, 60);
    Group Ginger("Ginger", "Tea", 10, 30, 61, 51, 90);
    Clan Tea("Tea");
    ASSERT_NO_EXCEPTION(Tea.addGroup(Nana));
    ASSERT_NO_EXCEPTION(Tea.addGroup(Luiza));
    ASSERT_NO_EXCEPTION(Tea.addGroup(Shiba));
    Clan Tree("Tree");
    ASSERT_NO_EXCEPTION(Tree.addGroup(Shiba));
    ASSERT_NO_EXCEPTION(Tree.addGroup(Ginger));
    Clan Apple("Apple");
    ASSERT_NO_EXCEPTION(Apple.addGroup(Ginger));
    ASSERT_NO_EXCEPTION(Apple.makeFriend(Tree));
    ASSERT_EXCEPTION(Tea.unite(Tree,"new"),ClanCantUnite);
    ASSERT_EXCEPTION(Tea.unite(Apple,""),ClanEmptyName);
    ASSERT_NO_EXCEPTION(Tea.unite(Apple,"Banana"));
    ASSERT_TRUE(Tea.getSize()==180);
    ASSERT_TRUE(Apple.getSize()==0);
    ASSERT_TRUE(Tea.getGroup("Ginger")->getClan() == "Banana");
    ASSERT_TRUE(Tea.doesContain("Ginger"));
    ASSERT_TRUE(Tea.isFriend(Tree));
    ASSERT_FALSE(Tea.isFriend(Apple));
    ASSERT_TRUE(Tea.isFriend(Tea));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << Tea);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Banana\n"
            "Clan's groups:\n"
            "Ginger\n"
            "Luiza\n"
            "Nana\n"
            "Shiba\n"));

    return true;
}




int main() {
    RUN_TEST(constractorClan);
    RUN_TEST(addGetGroupClan);
    RUN_TEST(GetSizeClan);
    RUN_TEST(IsMakeFriendClan);
    RUN_TEST(UnitClan);

    return 0;
}


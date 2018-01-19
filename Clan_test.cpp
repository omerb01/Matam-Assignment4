//
// Created by Ilya on 1/19/2018.
//
#include "testMacros.h"
#include "Clan.h"
#include "exceptions.h"

using namespace mtm;

bool testClanConstructor(){
    ASSERT_NO_EXCEPTION(Clan clan("blala"));
    ASSERT_EXCEPTION(Clan clan(""),ClanEmptyName);
    return true;
}

int main(){
    RUN_TEST(testClanConstructor);
}
//
// Created by Ilya on 1/21/2018.
//

#include "testMacros.h"
#include "Mountain.h"

using namespace mtm;
bool testConstructor(){
    Mountain mount1("Hermon");
    Mountain mount2("Meiron");
    ASSERT_EXCEPTION(Mountain mount3(""), AreaInvalidArguments);
    return true;
}

int main(){
    RUN_TEST(testConstructor);
}
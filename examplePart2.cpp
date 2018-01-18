#include "testMacros.h"
#include "MtmSet.h"
#include "exceptions.h"

using namespace mtm;

bool isEven(int n){
    return !(n%2);
}

bool exampleSet(){
    MtmSet<int> set;
    ASSERT_NO_EXCEPTION(set.insert(1));
    ASSERT_NO_EXCEPTION(set.insert(2));
    MtmSet<int> set2(set);
    ASSERT_TRUE(set.contains(1));
    ASSERT_NO_EXCEPTION(set.erase(1));
    ASSERT_FALSE(set.contains(1));
    ASSERT_TRUE(set.size() == 1);
    ASSERT_FALSE(set.empty());
    MtmSet<int>::iterator it = set.begin();
    ASSERT_TRUE(*(it++) == 2);
    ASSERT_TRUE(it == set.end());
    ASSERT_TRUE(set.begin() == set.find(2));
    ASSERT_TRUE(set2.isSuperSetOf(set));
    ASSERT_TRUE(set2 != set);
    ASSERT_NO_EXCEPTION(set.unite(set2));
    ASSERT_TRUE(set == set2);
    MtmSet<int> set3;
    ASSERT_NO_EXCEPTION(set.intersect(set3));
    ASSERT_TRUE(set.empty());
    ASSERT_NO_EXCEPTION(set2.clear());
    ASSERT_TRUE(set2.empty());
    ASSERT_NO_EXCEPTION(set.insert(1));
    ASSERT_NO_EXCEPTION(set.insert(2));
    ASSERT_NO_EXCEPTION(set.insert(3));
    ASSERT_TRUE(set.getSubSet(isEven).size() == 1);
    return true;
}

int main(){
    RUN_TEST(exampleSet);
    return 0;
}

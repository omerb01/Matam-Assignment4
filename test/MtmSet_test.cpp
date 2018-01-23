//
// Created by Omer on 18/01/2018.
//

#include "../MtmSet.h"
#include "../testMacros.h"

using namespace mtm;

bool testIteratorDereference() {
    MtmSet<int> set;
    MtmSet<int>::iterator i;

    ASSERT_EXCEPTION((*i == 2), NodeIsEndException);

    i = set.insert(2);
    ASSERT_TRUE(*i == 2);

    // TODO: check Derefrence with "->"

    return true;
}

bool testIteratorIncrement() {
    MtmSet<int> set;
    MtmSet<int>::iterator i;

    ASSERT_EXCEPTION(i++, NodeIsEndException);
    ASSERT_EXCEPTION(++i, NodeIsEndException);

    i = set.insert(1);
    set.insert(2);
    set.insert(3);

    ASSERT_TRUE(*(++i) == 2);
    ASSERT_TRUE(*(i++) == 2);

    return true;
}

bool testIteratorComparison() {
    MtmSet<int> set;
    MtmSet<int>::iterator a1 = set.insert(1);
    MtmSet<int>::iterator a2 = set.insert(2);
    set.insert(3);
    set.insert(4);
    MtmSet<int>::iterator a3 = set.insert(2);
    ASSERT_TRUE(a2 == a3);
    ASSERT_FALSE(a2 == a1);
    ASSERT_TRUE(a1 != a2);
    ASSERT_FALSE(a2 != a3);

    MtmSet<int> set2;
    MtmSet<int>::iterator b2 = set2.insert(2);
    ASSERT_FALSE(a2 == b2);
    ASSERT_TRUE(a2 != b2);

    return true;
}

bool testCopyConstructor() {
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);

    MtmSet<int> set_copy(set);

    MtmSet<int>::iterator i;
    MtmSet<int>::iterator j;
    for (i = set.begin(), j = set_copy.begin(); i != set.end(); i++, j++) {
        ASSERT_TRUE(*i == *j);
        ASSERT_TRUE(i != j);
    }

    set.erase(2);
    ASSERT_TRUE(set_copy.contains(2));

    return true;
}

bool testInsert() {
    MtmSet<int> set;
    set.insert(1);
    MtmSet<int>::iterator i1 = set.insert(2);
    set.insert(3);
    set.insert(4);
    MtmSet<int>::iterator i2 = set.insert(2);

    ASSERT_TRUE(i1 == i2);

    int index = 0;
    for (MtmSet<int>::iterator i = set.begin(); i != set.end(); i++) {
        index++;
        ASSERT_TRUE(index == *i);
    }

    return true;
}

bool testErase() {
    MtmSet<int> set;
    set.erase(2);
    ASSERT_TRUE(set.empty());

    set.insert(1);
    set.insert(2);
    set.erase(1);
    ASSERT_TRUE(set.size() == 1);
    ASSERT_TRUE(*set.begin() == 2);

    set.erase(2);
    ASSERT_TRUE(set.empty());

    MtmSet<int>::iterator i = set.insert(1);
    set.insert(2);
    set.erase(2);
    ASSERT_TRUE(set.size() == 1);
    ASSERT_TRUE(*set.begin() == 1);

    set.erase(i);
    ASSERT_TRUE(set.empty());
    set.erase(set.end());
    ASSERT_TRUE(set.empty());

    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.erase(2);
    ASSERT_TRUE(set.size() == 2);
    i = set.begin();
    ASSERT_TRUE(*i == 1);
    ASSERT_TRUE(*(++i) == 3);

    return true;
}

bool testClear() {
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);

    set.clear();
    ASSERT_TRUE(set.empty());

    return true;
}

bool testContains() {
    MtmSet<int> set;

    ASSERT_TRUE(!set.contains(1));
    set.insert(1);
    ASSERT_TRUE(set.contains(1));

    set.insert(2);
    set.insert(3);
    set.insert(4);

    ASSERT_TRUE(set.contains(3));
    ASSERT_TRUE(!set.contains(5));
    return true;
}

bool testIsSuperSetOf() {
    MtmSet<int> set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.insert(4);

    ASSERT_TRUE(set1.isSuperSetOf(set1));

    MtmSet<int> set2;
    ASSERT_TRUE(set1.isSuperSetOf(set2));
    ASSERT_FALSE(set2.isSuperSetOf(set1));

    ASSERT_TRUE(set2.isSuperSetOf(set2));

    MtmSet<int> set3(set1);
    set3.insert(5);
    set3.insert(6);
    ASSERT_TRUE(set3.isSuperSetOf(set1));
    ASSERT_FALSE(set1.isSuperSetOf(set3));

    set3.erase(2);
    ASSERT_FALSE(set1.isSuperSetOf(set3));
    ASSERT_FALSE(set3.isSuperSetOf(set1));

    return true;
}

bool testComparison() {
    MtmSet<int> set1;
    MtmSet<int> set2;
    ASSERT_TRUE(set1 == set2);
    ASSERT_FALSE(set1 != set2);

    ASSERT_TRUE(set1 == set1);
    ASSERT_FALSE(set1 != set1);

    set1.insert(0);
    ASSERT_FALSE(set1 == set2);
    ASSERT_TRUE(set1 != set2);

    ASSERT_TRUE(set1 == set1);
    ASSERT_FALSE(set1 != set1);

    set2.insert(0);
    ASSERT_TRUE(set1 == set2);
    ASSERT_FALSE(set1 != set2);

    set1.insert(1);
    set2.insert(2);
    ASSERT_FALSE(set1 == set2);
    ASSERT_TRUE(set1 != set2);

    ASSERT_TRUE(set1 == set1);
    ASSERT_FALSE(set1 != set1);

    return true;
}

bool testUnite() {
    MtmSet<int> set1;
    MtmSet<int> set2;

    set1.unite(set1);
    ASSERT_TRUE(set1.empty());

    set1.unite(set2);
    ASSERT_TRUE(set1.empty());

    set2.insert(0);
    set1.unite(set2);
    ASSERT_TRUE(*set1.begin() == 0);
    ASSERT_TRUE(set1.size() == 1);

    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(2);
    set2.insert(3);
    set2.insert(4);
    set1.unite(set2);

    ASSERT_TRUE(set1.size() == 5);
    for (int i = 0; i <= 4; i++) {
        ASSERT_TRUE(set1.contains(i));
    }

    const MtmSet<int> set3(set2);
    const MtmSet<int> set4 = set3.unite(set2);
    ASSERT_TRUE(set4 == set3);

    return true;
}

bool testIntersect() {
    MtmSet<int> set1;
    MtmSet<int> set2;

    set2.intersect(set2);
    ASSERT_TRUE(set2.empty());
    set1.intersect(set2);
    ASSERT_TRUE(set1.empty());

    set1.insert(0);
    set1.intersect(set2);
    ASSERT_TRUE(set1.empty());

    set2.insert(0);
    set1.intersect(set2);
    ASSERT_TRUE(set1.empty());

    set1.insert(-2);
    set1.insert(-1);
    set1.insert(0);
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(1);
    set2.insert(2);
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    const MtmSet<int> set3 = set1.intersect(set2);
    set3.intersect(set3);

    ASSERT_TRUE(set3.size() == 4);
    for (int i = 0; i <= 3; i++) {
        ASSERT_TRUE(set3.contains(i));
    }

    return true;
}

bool getEvenNums(int num) {
    return num % 2 == 0;
}

bool testGetSubSet() {
    MtmSet<int> set;

    set.getSubSet(getEvenNums);
    ASSERT_TRUE(set.empty());

    set.insert(0);
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    const MtmSet<int> sub_set = set.getSubSet(getEvenNums);

    ASSERT_TRUE(sub_set.size() == 3);
    ASSERT_TRUE(sub_set.contains(0));
    ASSERT_TRUE(sub_set.contains(2));
    ASSERT_TRUE(sub_set.contains(4));

    return true;
}

int main() {
    RUN_TEST(testIteratorDereference);
    RUN_TEST(testIteratorIncrement);
    RUN_TEST(testIteratorComparison);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testInsert);
    RUN_TEST(testErase);
    RUN_TEST(testClear);
    RUN_TEST(testContains);
    RUN_TEST(testIsSuperSetOf);
    RUN_TEST(testComparison);
    RUN_TEST(testUnite);
    RUN_TEST(testIntersect);
    RUN_TEST(testGetSubSet);
    return 0;
}
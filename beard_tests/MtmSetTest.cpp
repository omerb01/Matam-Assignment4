#include "../testMacros.h"
#include "../Group.h"
#include "../MtmSet.h"
#include "../exceptions.h"

using namespace mtm;

bool isEven(int n){
    return !(n%2);
}

bool testMTMSet(){
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

bool testSetConstructor(){
    MtmSet<int> set1;
    ASSERT_TRUE(set1.empty());
    set1.insert(4);
    set1.insert(3);
    MtmSet<int> set2(set1);
    ASSERT_TRUE(set1 == set2);
    return true;
}

bool testSetInsert(){
    MtmSet<int> set;
    ASSERT_NO_EXCEPTION(set.insert(1));
    ASSERT_TRUE(set.size() == 1);
    ASSERT_NO_EXCEPTION(set.insert(2));
    ASSERT_TRUE(set.contains(2));
    MtmSet<int>::iterator it = set.insert(3);
    ASSERT_TRUE(*it == 3);
    return true;
}

bool testSetErase(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    MtmSet<int>::iterator it = set.begin();
    ASSERT_NO_EXCEPTION(set.erase(1));
    ASSERT_FALSE(set.contains(1));
    ASSERT_NO_EXCEPTION(set.erase(it));
    ASSERT_TRUE(set.empty());
    return true;
}

bool testSetSize(){
    MtmSet<int> set;
    ASSERT_TRUE(set.size() == 0);
    set.insert(1);
    ASSERT_TRUE(set.size() == 1);
    set.erase(1);
    ASSERT_TRUE(set.size() == 0);
    return true;
}

bool testSetEmpty(){
    MtmSet<int> set;
    ASSERT_TRUE(set.empty());
    set.insert(1);
    ASSERT_FALSE(set.empty());
    set.erase(1);
    ASSERT_TRUE(set.empty());
    return true;
}

bool testSetClean(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    ASSERT_NO_EXCEPTION(set.clear());
    ASSERT_TRUE(set.empty());
    return true;
}

bool testSetBegin(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);                      //set: head-> (2) -> (1)
    MtmSet<int>::iterator it;
    ASSERT_NO_EXCEPTION(it = set.begin());
    ASSERT_TRUE(*it == 2);
    const MtmSet<int> set_const(set);   //set_const: head -> (1) -> (2)
    MtmSet<int>::const_iterator c_it;
    ASSERT_NO_EXCEPTION(c_it = set_const.begin());
    ASSERT_TRUE(*c_it == 1);
    c_it++;
    ASSERT_TRUE(*c_it == *it);
    ASSERT_FALSE(c_it == it);
    return true;
}

bool testSetEnd(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    MtmSet<int>::iterator it;
    ASSERT_NO_EXCEPTION(it = set.end());
    MtmSet<int>::iterator it_end(NULL);
    ASSERT_TRUE(it == it_end);
    const MtmSet<int> set_const(set);
    MtmSet<int>::const_iterator c_it;
    ASSERT_NO_EXCEPTION(c_it = set_const.end());
    ASSERT_TRUE(c_it == it_end);
    ASSERT_TRUE(c_it == it);
    return true;
}

bool testSetFind(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    MtmSet<int>::iterator it;
    ASSERT_NO_EXCEPTION(it = set.find(2));
    ASSERT_TRUE(*it == 2);
    const MtmSet<int> set_const(set);
    MtmSet<int>::const_iterator c_it;
    ASSERT_NO_EXCEPTION(c_it = set_const.find(2));
    ASSERT_TRUE(*c_it == 2);
    ASSERT_FALSE(c_it == it);
    return true;
}

bool testSetContains(){
    MtmSet<int> set;
    ASSERT_FALSE(set.contains(1));
    set.insert(1);
    set.insert(2);
    ASSERT_TRUE(set.contains(1));
    ASSERT_TRUE(set.contains(2));
    ASSERT_FALSE(set.contains(3));
    return true;
}

bool testSetIsSuperSetOf(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    MtmSet<int> superSet;
    ASSERT_FALSE(superSet.isSuperSetOf(set));
    superSet.insert(1);
    ASSERT_FALSE(superSet.isSuperSetOf(set));
    superSet.unite(set);
    ASSERT_TRUE(superSet.isSuperSetOf(set));
    superSet.insert(3);
    ASSERT_TRUE(superSet.isSuperSetOf(set));
    return true;
}

bool testSetComparisons(){
    MtmSet<int> set1;
    MtmSet<int> set2;
    ASSERT_TRUE(set1 == set2);
    ASSERT_FALSE(set1 != set2);
    set1.insert(1);
    ASSERT_TRUE(set1 != set2);
    ASSERT_FALSE(set1 == set2);
    set2.insert(2);
    ASSERT_TRUE(set1 != set2);
    ASSERT_FALSE(set1 == set2);
    return true;
}

bool testSetUnite(){
    MtmSet<int> set1;
    set1.insert(1);
    set1.insert(2);
    MtmSet<int> set2;
    set2.insert(1);
    set2.insert(3);
    const MtmSet<int> set_const(set2);
    ASSERT_NO_EXCEPTION(set2.unite(set1));
    ASSERT_TRUE(set2.contains(2));
    MtmSet<int> unite = set_const.unite(set1);
    ASSERT_TRUE(unite.contains(2));
    ASSERT_TRUE(unite.contains(3));
    return true;
}

bool testSetIntersect(){
    MtmSet<int> set1;
    set1.insert(1);
    set1.insert(2);
    MtmSet<int> set2;
    set2.insert(1);
    set2.insert(3);
    const MtmSet<int> set_const(set2);
    ASSERT_NO_EXCEPTION(set2.intersect(set1));
    ASSERT_TRUE(set2.contains(1));
    ASSERT_FALSE(set2.contains(2));
    ASSERT_FALSE(set2.contains(3));
    MtmSet<int> intersect = set_const.intersect(set1);
    ASSERT_TRUE(intersect.contains(1));
    ASSERT_FALSE(intersect.contains(2));
    ASSERT_FALSE(intersect.contains(3));
    return true;
}

bool testSetGetSubSet(){
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    const MtmSet<int> set_const(set);
    ASSERT_NO_EXCEPTION(set.getSubSet(isEven));
    ASSERT_TRUE(set.contains(2));
    ASSERT_FALSE(set.contains(1));
    MtmSet<int> subSet = set_const.getSubSet(isEven);
    ASSERT_TRUE(subSet.contains(2));
    ASSERT_FALSE(subSet.contains(1));
    return true;
}

bool testIteratorConstructor(){
    ASSERT_NO_EXCEPTION(MtmSet<int>::iterator it);
    ASSERT_NO_EXCEPTION(MtmSet<int>::const_iterator c_it);
    MtmSet<int> set;
    set.insert(1);
    ASSERT_NO_EXCEPTION(MtmSet<int>::iterator it(set.begin()));
    ASSERT_NO_EXCEPTION(MtmSet<int>::const_iterator c_it(set.begin()));
    MtmSet<int>::iterator it_orig = set.begin();
    MtmSet<int>::iterator c_it_orig = set.begin();
    ASSERT_NO_EXCEPTION(MtmSet<int>::iterator it(it_orig));
    ASSERT_NO_EXCEPTION(MtmSet<int>::const_iterator c_it(it_orig));
    ASSERT_NO_EXCEPTION(MtmSet<int>::const_iterator c_it(c_it_orig));
    return true;
}

bool testIteratorAssignment(){
    MtmSet<int> set;
    set.insert(1);
    MtmSet<int>::iterator it1 = set.begin();
    MtmSet<int>::iterator it2;
    MtmSet<int>::const_iterator c_it1;
    MtmSet<int>::const_iterator c_it2;
    ASSERT_NO_EXCEPTION(it2 = it1);
    ASSERT_NO_EXCEPTION(c_it1 = it1);
    ASSERT_NO_EXCEPTION(c_it2 = it1);
    ASSERT_TRUE(it1 == it2);
    ASSERT_TRUE(it1 == c_it1);
    ASSERT_TRUE(it1 == c_it2);
    it1 = set.end();
    c_it1 = it2 = it1;
    ASSERT_TRUE(c_it1 == set.end());
    ASSERT_TRUE(it2 == set.end());
    return true;
}

bool testIteratorAsterisk(){
    MtmSet<int> set;
    set.insert(1);
    MtmSet<int>::iterator it = set.begin();
    ASSERT_TRUE(*it == 1);
    MtmSet<int>::const_iterator c_it = set.begin();
    ASSERT_TRUE(*c_it == 1);
    return true;
}

bool testIteratorArrow(){
    MtmSet<Group> set;
    Group g1("Stark", "GameOfThrones", 4, 5, 50, 50, 80);
    set.insert(g1);
    MtmSet<Group>::iterator it = set.begin();
    ASSERT_TRUE(it.operator->() == &(*it));
    ASSERT_TRUE(it.operator->()->getName() == g1.getName());
    ASSERT_TRUE(it->getName() == g1.getName());
    return true;
}

bool testIteratorIncrement(){
    MtmSet<int> set;
    set.insert(3);
    set.insert(2);
    set.insert(1);      //set: head -> (1) -> (2) -> (3) -> NULL
    MtmSet<int>::iterator it = set.begin();
    MtmSet<int>::const_iterator c_it = set.begin();
    ASSERT_TRUE(*(it++) == 1);
    ASSERT_TRUE(*it == 2);
    ASSERT_TRUE(*(++it) == 3);
    ASSERT_TRUE(*(c_it++) == 1);
    ASSERT_TRUE(*c_it == 2);
    ASSERT_TRUE(*(++c_it) == 3);
    return true;
}

bool testIteratorComparisons(){
    MtmSet<int>::iterator it1, it2;
    MtmSet<int>::const_iterator c_it1, c_it2;
    ASSERT_TRUE(it1 == it2);
    ASSERT_TRUE(c_it1 == c_it2);
    ASSERT_TRUE(it1 == c_it1);
    MtmSet<int> set;
    set.insert(1);
    set.insert(2);
    c_it1 = it1 = set.begin();
    ASSERT_TRUE(it1 != c_it2);
    ASSERT_TRUE(it1 != it2);
    ASSERT_TRUE(c_it1 != c_it2);
    ASSERT_TRUE(it1 == c_it1);
    c_it2 = it2 = it1++;
    ASSERT_FALSE(c_it2 != c_it1);
    ASSERT_FALSE(it2 == it1);
    ASSERT_FALSE(c_it1 == it1);
    return true;
}

int main(){
    RUN_TEST(testMTMSet);           //a generic test from examples
    RUN_TEST(testSetBegin);
    RUN_TEST(testSetClean);
    RUN_TEST(testSetComparisons);
    RUN_TEST(testSetConstructor);
    RUN_TEST(testSetContains);
    RUN_TEST(testSetEmpty);
    RUN_TEST(testSetEnd);
    RUN_TEST(testSetErase);
    RUN_TEST(testSetFind);
    RUN_TEST(testSetGetSubSet);
    RUN_TEST(testSetInsert);
    RUN_TEST(testSetIntersect);
    RUN_TEST(testSetIsSuperSetOf);
    RUN_TEST(testSetSize);
    RUN_TEST(testSetUnite);

    RUN_TEST(testIteratorConstructor);
    RUN_TEST(testIteratorAssignment);
    RUN_TEST(testIteratorAsterisk);
    RUN_TEST(testIteratorArrow);
    RUN_TEST(testIteratorIncrement);
    RUN_TEST(testIteratorComparisons);
    return 0;
}

#include "../testMacros.h"
#include "../MtmSet.h"
#include "../exceptions.h"

using namespace mtm;

bool checkString(const std::string& str){
    return(str == "kaa" || str=="abcd");
}

bool setTest(){
    MtmSet<std::string> set1, set2;
    ASSERT_NO_EXCEPTION(set1.insert("abc"));
    ASSERT_NO_EXCEPTION(set1.insert("cba"));
    ASSERT_NO_EXCEPTION(set1.insert("abcd"));
    ASSERT_NO_EXCEPTION(set1.insert("abc"));
    ASSERT_NO_EXCEPTION(set2.insert("abc"));
    ASSERT_NO_EXCEPTION(set2.insert("cba"));
    ASSERT_TRUE(set1.size()==3);
    ASSERT_TRUE(set1.isSuperSetOf(set2));
    ASSERT_FALSE(set2.isSuperSetOf(set1));
    ASSERT_TRUE(set1.contains("abcd"));
    ASSERT_FALSE(set2.contains("abcd"));
    ASSERT_TRUE(set1!=set2);
    ASSERT_FALSE(set1==set2);
    ASSERT_NO_EXCEPTION(set2.insert("kaa"));
    MtmSet<std::string> set3(set1);
    ASSERT_NO_EXCEPTION(set3.unite(set2));
    ASSERT_TRUE(set1.size()==3);
    ASSERT_TRUE(set2.size()==3);
    ASSERT_TRUE(set3.size()==4);
    ASSERT_NO_EXCEPTION(set1.intersect(set2));
    ASSERT_TRUE(set1.size()==2);
    ASSERT_FALSE(set1.contains("abcd"));
    ASSERT_NO_EXCEPTION(set1.getSubSet(checkString));
    ASSERT_NO_EXCEPTION(set3.getSubSet(checkString));
    ASSERT_TRUE(set1.size()==0);
    ASSERT_TRUE(set1.empty());
    ASSERT_TRUE(set3.size()==2);
    ASSERT_FALSE(set3.empty());
    ASSERT_NO_EXCEPTION(set3.clear());
    ASSERT_TRUE(set3.empty());
    ASSERT_NO_EXCEPTION(set2.erase("kaa"));
    return true;
}

bool iteratorTest()
{
    MtmSet<std::string> set1, set2;
    ASSERT_NO_EXCEPTION(set1.insert("abc"));
    ASSERT_NO_EXCEPTION(set1.insert("cba"));
    ASSERT_NO_EXCEPTION(set2.insert("abc"));
    ASSERT_NO_EXCEPTION(set2.insert("cba"));
    ASSERT_TRUE(set1==set2);
    MtmSet<std::string>::iterator it1 = set1.find("abc");
    MtmSet<std::string>::iterator it2 = set2.find("abc");
    ASSERT_TRUE(*it1 == "abc");
    ASSERT_TRUE(*it2 == "abc");
    ASSERT_FALSE(it1==it2);
    ASSERT_TRUE(it1!=it2);
    ASSERT_TRUE(*it1 == *it2);
    ASSERT_NO_EXCEPTION(set1.erase(it1));
    ASSERT_TRUE(set1.size()==1);
    ASSERT_NO_EXCEPTION(it1 = set1.begin());
    ASSERT_TRUE(*it1=="cba");
    ASSERT_TRUE(*(it1++)=="cba");
    ASSERT_NO_EXCEPTION(it1 = set1.begin());
    ASSERT_TRUE(++it1==set1.end());
    return true;
}

bool constIteratorTest()
{
    MtmSet<std::string> set1, set2, set3;
    ASSERT_NO_EXCEPTION(set1.insert("abc"));
    ASSERT_NO_EXCEPTION(set1.insert("cba"));
    ASSERT_NO_EXCEPTION(set2.insert("abc"));
    ASSERT_NO_EXCEPTION(set2.insert("cba"));
    ASSERT_NO_EXCEPTION(set3.insert("cba"));
    ASSERT_TRUE(set1==set2);
    MtmSet<std::string>::const_iterator cit1 = set1.find("abc");
    MtmSet<std::string>::const_iterator cit2 = set2.find("abc"), cit3;
    ASSERT_TRUE(*cit1 == "abc");
    ASSERT_TRUE(*cit2 == "abc");
    ASSERT_FALSE(cit1==cit2);
    ASSERT_TRUE(cit1!=cit2);
    ASSERT_TRUE(*cit1 == *cit2);
    ASSERT_NO_EXCEPTION(cit3 = set3.begin());
    ASSERT_TRUE(*cit3=="cba");
    ASSERT_TRUE(*(cit3++)=="cba");
    ASSERT_NO_EXCEPTION(cit3 = set3.begin());
    ASSERT_TRUE(++cit3==set3.end());
    return true;
}

int main(){
    RUN_TEST(setTest);
    RUN_TEST(iteratorTest);
    RUN_TEST(constIteratorTest);
    return 0;
}

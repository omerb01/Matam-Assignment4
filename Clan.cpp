//
// Created by Ilya on 1/19/2018.
//

#include "Clan.h"
#include "exceptions.h"

using namespace std;

using namespace mtm;

Clan::Clan(const string &name) {
    if (name.empty()) {
        throw ClanEmptyName();
    }
    this->name = name;
    groups = MtmSet<GroupPointer>();
    friend_groups = MtmSet<std::string>();
}

Clan::Clan(const Clan& other) = default;

Clan::~Clan() = default;


bool Clan::isInSet(const std::string& group_name){
    MtmSet<GroupPointer>::const_iterator it;
    GroupPointer temp;
    for(it = groups.begin();it!=groups.end();it++){
        temp = *it;
        if((*temp).getName() == group_name){
            return true;
        }
    }
    return false;
}

void Clan::addGroup(const Group &group) {
    if (group.getSize() == 0) {
        throw ClanGroupIsEmpty();
    }
    if(isInSet(group.getName())){
        throw ClanGroupNameAlreadyTaken();

    }
    Group new_group = group;
    new_group.changeClan(name);
    const GroupPointer new_pointer = GroupPointer(new Group(new_group));
    groups.insert(new_pointer);
}

const GroupPointer& Clan::getGroup(const std::string& group_name) const{
    //TODO: shouldn't we check if group_name==""?
    MtmSet<GroupPointer>::const_iterator it;
    GroupPointer temp;
    for(it = groups.begin();it!=groups.end();it++){
        temp = *it;
        if((*temp).getName() == group_name){
            return *it;
        }
    }
    throw ClanGroupNotFound();
}

/*bool Clan::doesContain(const std::string& group_name) const{

}*/


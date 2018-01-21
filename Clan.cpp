//
// Created by Ilya on 1/19/2018.
//

#include "Clan.h"

using namespace std;

namespace mtm {

    Clan::Clan(const string &name) {
        if (name.empty()) {
            throw ClanEmptyName();
        }
        this->name = name;
        groups = MtmSet<GroupPointer>();
        friend_groups = MtmSet<std::string>();
    }

    Clan::Clan(const Clan &other) = default;

    Clan::~Clan() = default;

    void Clan::addGroup(const Group &group) {
        if (group.getSize() == 0) {
            throw ClanGroupIsEmpty();
        }
        if (doesContain(group.getName())) {
            throw ClanGroupNameAlreadyTaken();

        }
        Group new_group = group;
        new_group.changeClan(name);
        const GroupPointer new_pointer = GroupPointer(new Group(new_group));
        groups.insert(new_pointer);
    }

    const GroupPointer &Clan::getGroup(const std::string &group_name) const {
        //TODO: shouldn't we check if group_name==""?
        MtmSet<GroupPointer>::const_iterator it;
        GroupPointer temp;
        for (it = groups.begin(); it != groups.end(); it++) {
            temp = *it;
            if ((*temp).getName() == group_name) {
                return *it;
            }
        }
        throw ClanGroupNotFound();
    }

    bool Clan::doesContain(const std::string &group_name) const {
        MtmSet<GroupPointer>::const_iterator it;
        GroupPointer temp;
        for (it = groups.begin(); it != groups.end(); it++) {
            temp = *it;
            if ((*temp).getName() == group_name) {
                return true;
            }
        }
        return false;
    }

    int Clan::getSize() const {
        int people_amount = 0;
        MtmSet<GroupPointer>::const_iterator it;
        for (it = groups.begin(); it != groups.end(); it++) {
            people_amount += (*(*it)).getSize();
        }
        return people_amount;
    }

    void Clan::ChangeClan(Clan &clan, const std::string &new_name) {
        clan.name = new_name;
        for (auto it = clan.groups.begin(); it != clan.groups.end(); it++) {
            (*(*it)).changeClan(new_name);
        }
    }

    Clan &Clan::unite(Clan &other, const std::string &new_name) {
        if (new_name.empty()) throw ClanEmptyName();
        if (other.name == name) throw ClanCantUnite();
        for (auto it = other.groups.begin(); it != other.groups.end(); it++) {
            if (this->doesContain((*(*it)).getName())) {
                throw ClanCantUnite();
            }
        }
        friend_groups.unite(other.friend_groups);
        if (new_name == name) {
            ChangeClan(other, new_name);
        } else if (new_name == other.name) {
            ChangeClan(*this, new_name);
        } else {
            ChangeClan(*this, new_name);
            ChangeClan(other, new_name);
        }
        GroupPointer temp= nullptr;
        for (auto it = other.groups.begin(); it != other.groups.end(); it++) {
            other.groups.erase(temp);
            temp=*it;
            groups.insert(*(it));
        }
        return *this;
    }



    /*std::ostream &operator<<(std::ostream &os, const Clan &clan) {
        MtmSet<mtm::GroupPointer> filtered_set = clan.groups;
        MtmSet<GroupPointer>::iterator it2;
        os << "Clan's name: " << clan.name << "\nClan's groups: \n";
        GroupPointer temp2 = nullptr;
        for (auto it = filtered_set.begin(); it != filtered_set.end(); it++) {
            Group temp = (*(*it));
            // build max function. if current element func's max == current, print it and remove.
            os << temp.getName() << "\n";
            filtered_set.erase(temp2);
            it = filtered_set.begin();
            it2 = filtered_set.begin();
        }
        return os;
    }*/
}
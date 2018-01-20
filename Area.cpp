//
// Created by Omer on 20/01/2018.
//

#include "Area.h"
#include "exceptions.h"

using namespace mtm;

Area::Area(const std::string &name) : name(name) {}

Area::~Area() = default;

void Area::addReachableArea(const std::string &area_name) {
    reachable_areas.insert(area_name);
}

bool Area::isReachable(const std::string &area_name) const {
    if (area_name == this->name) return true;
    return reachable_areas.contains(area_name);
}

void Area::groupArrive(const string &group_name, const string &clan,
                       map<string, Clan> &clan_map) {
    auto iterator = clan_map.find(clan);
    if (iterator == clan_map.end()) throw AreaClanNotFoundInMap();

    GroupPointer group_ptr;
    try {
        group_ptr = iterator->second.getGroup(group_name);
    }
    catch (ClanGroupNotFound &e) {
        throw AreaGroupNotInClan();
    }

    for(auto i = groups.begin(); i != groups.end(); i++) {
        if(*i == group_ptr) throw AreaGroupAlreadyIn();
    }

    groups.push_back(group_ptr);
}

void Area::groupLeave(const std::string &group_name) {
    for(auto i = groups.begin(); i != groups.end(); i++) {
        if((*i)->getName() == group_name) {
            groups.erase(i);
            return;
        }
    }
    throw AreaGroupNotFound();
}

MtmSet<std::string> Area::getGroupsNames() const {
    MtmSet<string> groups_names;
    for(auto i = groups.begin(); i != groups.end(); i++) {
        groups_names.insert((*i)->getName());
    }
    return MtmSet<string>(groups_names);
}
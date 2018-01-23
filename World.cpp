//
// Created by Omer on 23/01/2018.
//

#include <assert.h>
#include "exceptions.h"
#include "World.h"
#include "Plain.h"
#include "River.h"
#include "Mountain.h"

using namespace mtm;
using std::pair;

World::World() = default;

World::~World() = default;

void World::addClan(const string &clan_name) {
    if (clan_name.empty()) throw WorldInvalidArgument();

    auto iterator = clan_map.find(clan_name);
    if (iterator != clan_map.end()) throw WorldClanNameIsTaken();

    clan_map.insert(pair<string, Clan>(clan_name, Clan(clan_name)));
}

void World::addArea(const string &area_name, AreaType type) {
    if (area_name.empty()) throw WorldInvalidArgument();

    auto iterator = clan_map.find(area_name);
    if (iterator != clan_map.end()) throw WorldAreaNameIsTaken();

    if (type == PLAIN) {
        AreaPtr area_ptr(new Plain(area_name));
        area_map.insert(pair<string, AreaPtr>(area_name, area_ptr));
    } else if (type == MOUNTAIN) {
        AreaPtr area_ptr(new Mountain(area_name));
        area_map.insert(pair<string, AreaPtr>(area_name, area_ptr));
    } else if (type == RIVER) {
        AreaPtr area_ptr(new River(area_name));
        area_map.insert(pair<string, AreaPtr>(area_name, area_ptr));
    } else {
        assert(false);
    }
}

static bool isGroupAlreadyExists(const map<string, Clan> &clan_map,
                                 const string &group_name) {
    for (auto i = clan_map.begin(); i != clan_map.end(); i++) {
        if(i->second.doesContain(group_name)) return false;
    }
    return true;
}

void World::addGroup(const string &group_name, const string &clan_name,
                     int num_children, int num_adults,
                     const string &area_name) {
    try {
        Group new_group(group_name, num_children, num_adults);
        if(isGroupAlreadyExists(clan_map, group_name)) {
            throw WorldGroupNameIsTaken();
        }

        auto clan_it = clan_map.find(clan_name);
        if(clan_it == clan_map.end()) throw WorldClanNotFound();
        auto area_it = area_map.find(area_name);
        if(area_it == area_map.end()) throw WorldAreaNotFound();

        clan_it->second.addGroup(new_group);
        area_it->second->groupArrive(group_name, clan_name, clan_map);
    }
    catch (GroupInvalidArgs &e) {
        throw WorldInvalidArgument();
    }
}

void World::makeReachable(const string& from, const string& to){
    if(area_map.find(from) == area_map.end() || area_map.find(to) == area_map.end()){
        throw WorldClanNotFound();
    }
    for (const auto &area_pair: area_map){
        if((area_pair.first) == from){
            (*area_pair.second).addReachableArea(to);
        }
        if((area_pair.first) == to){
            (*area_pair.second).addReachableArea(from);
        }
    }
}

void World::moveGroup(const string& group_name, const string& destination){
    AreaPtr group_current_area= nullptr;
    GroupPointer group_object = nullptr;
    std::string group_clan="";
    for (const auto &clan_pair: clan_map){
        if(clan_pair.second.doesContain(group_name)){
            group_object = clan_pair.second.getGroup(group_name);
            group_clan = clan_pair.first;
        }
    }
    if(clan_map.find(group_name) == clan_map.end()){
        throw WorldClanNotFound();
    }
    if(area_map.find(destination) != area_map.find(destination)){
        throw WorldGroupNotFound();
    }
    for (const auto &area_pair: area_map){
        auto it = area_pair.second->getGroupsNames().find(group_name);
        if(it != area_pair.second->getGroupsNames().end()){
            group_current_area = area_pair.second;
        }
    }
    for (const auto &area_pair: area_map){
        auto it = area_pair.second->getGroupsNames().find(group_name);
        if(it == area_pair.second->getGroupsNames().end() && area_pair.first == destination){
            if(group_current_area->isReachable(destination)){
                area_pair.second->groupArrive(group_name,group_clan,clan_map);
            }else if(group_current_area->isReachable(destination)){
                throw WorldAreaNotReachable();
            }
        }else if(it != area_pair.second->getGroupsNames().end() && area_pair.first == destination){
            throw WorldGroupAlreadyInArea();
        }
    }
}
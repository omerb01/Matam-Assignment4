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
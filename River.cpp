//
// Created by Omer on 22/01/2018.
//

#include "River.h"

using namespace mtm;

River::River(const std::string &name) : Area(name) {}

River::~River() = default;

static std::vector<GroupPointer>::const_iterator getStrongestGroup
        (const std::vector<GroupPointer> &groups) {
    auto strongest_group = groups.begin();

    for (auto i = groups.begin(); i != groups.end(); i++) {
        if (*i > *strongest_group) strongest_group = i;
    }

    return strongest_group;
}

static bool tradeWithStrongestGroup(std::vector<GroupPointer> groups,
                                    std::map<string, Clan> &clan_map,
                                    const string &clan_name,
                                    const GroupPointer &new_group) {
    while (!groups.empty()) {
        auto strongest_group = getStrongestGroup(groups);
        const Clan &strongest_group_clan =
                clan_map.at((*strongest_group)->getClan());

        if ((*strongest_group)->getClan() == clan_name ||
            strongest_group_clan.isFriend(clan_map.at(clan_name))) {
            if ((*strongest_group)->trade(*new_group)) return true;
        }

        groups.erase(strongest_group);
    }

    return false;
}

static void checkGroupsArriveExceptions(const string &group_name,
                                        const string &clan_name,
                                        const map<string, Clan> &clan_map,
                                        const std::vector<GroupPointer> &groups) {
    auto clan_it = clan_map.find(clan_name);

    if (clan_it == clan_map.end()) {
        throw AreaClanNotFoundInMap();
    }

    if (!clan_it->second.doesContain(group_name)) {
        throw AreaGroupNotInClan();
    }
    GroupPointer group_ptr = clan_it->second.getGroup(group_name);

    for (auto i = groups.begin(); i != groups.end(); i++) {
        if (*i == group_ptr) throw AreaGroupAlreadyIn();
    }
}

void River::groupArrive(const string &group_name, const string &clan_name,
                        map<string, Clan> &clan_map) {
    checkGroupsArriveExceptions(group_name, clan_name, clan_map, groups);

    Clan &clan = clan_map.at(clan_name);
    const GroupPointer &new_group_ptr = clan.getGroup(group_name);

    tradeWithStrongestGroup(groups, clan_map, clan_name, new_group_ptr);

    groups.push_back(new_group_ptr);
}
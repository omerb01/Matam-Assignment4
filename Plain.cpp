//
// Created by Omer on 21/01/2018.
//

#include "Plain.h"

using namespace mtm;

Plain::Plain(const std::string &name) : Area(name) {}

Plain::~Plain() = default;

static std::vector<GroupPointer>::const_iterator getStrongestGroup
        (const std::vector<GroupPointer> &groups) {
    auto strongest_group = groups.begin();

    for (auto i = groups.begin(); i != groups.end(); i++) {
        if (*i > *strongest_group) strongest_group = i;
    }

    return strongest_group;
}

static bool uniteWithStrongestGroup(std::vector<GroupPointer> groups,
                                    const GroupPointer &new_group, int
                                    clan_size) {
    while (!groups.empty()) {
        auto strongest_group = getStrongestGroup(groups);

        if ((double) (*strongest_group)->getSize() +
            (double) new_group->getSize()
            < (double) clan_size / 3) {
            if ((*strongest_group)->unite(*new_group, clan_size)) return true;
        }

        groups.erase(strongest_group);
    }

    return false;
}

static string getDividedGroupName(map<string, Clan> &clan_map,
                                  const string &group_name) {
    int index = 2;
    string new_name = group_name + "_" + std::to_string(index);

    bool is_clan_contains;
    while (true) {
        is_clan_contains = false;

        for (auto i = clan_map.begin(); i != clan_map.end(); i++) {
            if (i->second.doesContain(new_name)) is_clan_contains = true;
        }

        if(!is_clan_contains) return new_name;
        index++;
        new_name = group_name + "_" + std::to_string(index);
    }

    return new_name;
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

void Plain::groupArrive(const string &group_name, const string &clan_name,
                        map<string, Clan> &clan_map) {
    checkGroupsArriveExceptions(group_name, clan_name, clan_map, groups);

    Clan& clan = clan_map.at(clan_name);
    GroupPointer new_group_ptr = clan.getGroup(group_name);

    if ((double) new_group_ptr->getSize() < (double) clan.getSize() / 3) {
        if(uniteWithStrongestGroup(groups, new_group_ptr, clan.getSize())) {
            return;
        }
    }

    if ((double) new_group_ptr->getSize() > (double) clan.getSize() / 3) {
        if (new_group_ptr->getSize() >= 10) {
            string new_name = getDividedGroupName(clan_map, group_name);
            Group divided_group(new_group_ptr->divide(new_name));

            clan.addGroup(divided_group);
            GroupPointer divided_group_ptr = clan.getGroup(new_name);

            groups.push_back(new_group_ptr);
            groups.push_back(divided_group_ptr);
            return;
        }
    }

    groups.push_back(new_group_ptr);
}
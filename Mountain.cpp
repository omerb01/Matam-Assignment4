//
// Created by Ilya on 1/21/2018.
//

#include <sstream>
#include "Mountain.h"


namespace mtm {

    Mountain::Mountain(const std::string &name) : Area(name) {
        this->dominating_group = "";
    }

    Mountain::~Mountain() = default;

    void Mountain::groupArrive(const string &group_name, const string &clan,
                               map<string, Clan> &clan_map) {
        //TODO: fix function length
        auto it = clan_map.find(clan);
        if (it == clan_map.end()) {
            throw AreaClanNotFoundInMap();
        }
        if (!((it->second).doesContain(group_name))) {
            throw AreaGroupNotInClan();
        }
        //Group arriving = *(it->second.getGroup(group_name));
        GroupPointer current_dominating_group = getDomintaingGroupObject(clan_map);
        GroupPointer arriving_group_p = (it->second.getGroup(group_name));
        if (dominating_group.empty()) {
            dominating_group = group_name;
            groups.push_back(arriving_group_p);
            current_dominating_group = getDomintaingGroupObject(clan_map);
        } else {

            if (arriving_group_p->getName() == current_dominating_group->getName()) {
                throw AreaGroupAlreadyIn();
            }
            if (*arriving_group_p > *current_dominating_group && arriving_group_p->getClan() ==
                                                                 current_dominating_group->getClan()) {
                dominating_group = arriving_group_p->getName();
            } else if (arriving_group_p->getClan() !=
                       current_dominating_group->getClan()) {
                FIGHT_RESULT result = arriving_group_p->fight(*current_dominating_group);
                if (result == WON) {
                    dominating_group = arriving_group_p->getName();
                }
            }
            groups.push_back(arriving_group_p);
        }
    }

    /*Group*/GroupPointer Mountain::getDomintaingGroupObject(map<string, Clan> &clan_map) {

        //Group current_dominating_group("dummy", 1, 1);
        GroupPointer current_dominating_group=nullptr;
        for (const auto &clan_pair: clan_map) {

            if ((clan_pair.second).doesContain(dominating_group)) {
                current_dominating_group = ((clan_pair).second.getGroup(
                        dominating_group));
            }
        }
        if(current_dominating_group != nullptr) {
            dominating_clan = current_dominating_group->getClan();
        }
        return current_dominating_group;
    }

    const std::string Mountain::getMaximumGroupMount(const std::string &group_name) {
        if(groups.size() != 0) {
            GroupPointer maximum = *(groups.begin());
            for (size_t i = 0; i < groups.size(); i++) {
                if (groups[i] > maximum &&
                    (*(groups[i])).getName() != group_name)
                    maximum = groups[i];
            }
            return maximum->getName();
        }else{
            return "";
        }
    }

    const std::string Mountain::getMaximumGroupClan(const std::string &group_name) {
        if(groups.size()!=0) {
            GroupPointer maximum = *(groups.begin());
            for (size_t i = 0; i < groups.size(); i++) {
                if ((*(groups[i])).getName() == dominating_clan &&
                    (*(groups[i])).getName() != group_name) {
                    maximum = *maximum > (*(groups[i])) ? maximum : groups[i];
                }
            }
            if((*maximum).getClan() == dominating_clan) {
                return maximum->getName();
            }else{
                return "";
            }
        }
        else{
            return "";
        }


    }


    void Mountain::groupLeave(const std::string &group_name) {
        if (group_name.empty()) {
            throw AreaGroupNotFound();
        }
        for (auto i = groups.begin(); i != groups.end(); i++) {
            if ((*i)->getName() == group_name) {
                groups.erase(i);
                break;
            }
        }
        if (dominating_group == group_name) {
            std::string dominating_group_from_clan = getMaximumGroupClan(group_name);
            std::string dominating_group_overall = getMaximumGroupMount(group_name);
            if (!(dominating_group_from_clan.empty())) {
                dominating_group = dominating_group_from_clan;
            } else if (!(dominating_group_overall.empty())) {
                dominating_group = dominating_group_overall;
            } else {
                dominating_group = "";
                dominating_clan ="";
            }
        }else{
            throw AreaGroupNotFound();
        }
    }


}

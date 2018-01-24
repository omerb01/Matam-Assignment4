//
// Created by Ilya on 1/21/2018.
//

#ifndef ASSIGNMENT4_MOUNTAIN_H
#define ASSIGNMENT4_MOUNTAIN_H

#include "Area.h"

namespace mtm {
    class Mountain : public Area {
        // The current dominating group in the mountain. Empty if such a group doesn't exist
        std::string dominating_group;
        std::string dominating_clan;
        GroupPointer getDomintaingGroupObject(map<string, Clan> &clan_map);
        const std::string getMaximumGroupMount(const std::string &group_name);
        const std::string getMaximumGroupClan(const std::string &group_name);
    public:
        // Mountain c'tor. Receives the name of the mountain. Inherits properties from Area.h
        Mountain(const string &name);

        ~Mountain();

        Mountain(const Mountain &) = delete;

        Mountain &operator=(const Mountain &) = delete;

        void groupArrive(const string &group_name, const string &clan,
                         map<string, Clan> &clan_map) override;

        void groupLeave(const std::string &group_name);
    };
}

#endif //ASSIGNMENT4_MOUNTAIN_H

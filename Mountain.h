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

    public:
        // Mountain c'tor. Receives the name of the mountain. Inherits properties from Area.h
        Mountain(const string &name);
        ~Mountain();
        //TODO: make sure it's fine:
        Mountain(Mountain mount) = delete;
        Mountain &operator=(const Mountain &) = delete;

        void groupArrive(const string& group_name, const string& clan,
                         map<string, Clan>& clan_map) override;

    };
}

#endif //ASSIGNMENT4_MOUNTAIN_H

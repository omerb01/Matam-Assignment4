//
// Created by Ilya on 1/21/2018.
//

#include "Mountain.h"

namespace mtm {

    Mountain::Mountain(const std::string &name) : Area(name) {
        this->dominating_group = "";
    }

    ~Mountain() = default;

    void Mountain::groupArrive(const string &group_name, const string &clan,
                               map<string, Clan> &clan_map) {

    }

}

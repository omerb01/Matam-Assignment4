//
// Created by Ilya on 1/19/2018.
//

#include "Clan.h"
#include "exceptions.h"

using namespace std;

namespace mtm{
    Clan::Clan(const string& name){
        if(name.empty()){
            throw ClanEmptyName();
        }
        this->name = name;
    }
    Group::Group(const Group &other) = default;
    Group::~Group() = default;

}

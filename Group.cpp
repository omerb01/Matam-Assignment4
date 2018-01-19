//
// Created by Omer on 18/01/2018.
//

#include "Group.h"
#include "exceptions.h"
#include <cmath>


using namespace mtm;

Group::Group(const std::string &name, const std::string &clan, int children,
             int adults, int tools, int food, int morale) {
    if (name.empty()) throw GroupInvalidArgs();
    if (adults == 0 && children == 0) throw GroupInvalidArgs();
    if (adults < 0 || children < 0 || tools < 0 || food < 0) {
        throw GroupInvalidArgs();
    }
    if (morale < 0 || morale > 100) throw GroupInvalidArgs();

    this->name = name;
    this->clan = clan;
    this->children = children;
    this->adults = adults;
    this->tools = tools;
    this->food = food;
    this->morale = morale;
}

Group::Group(const std::string &name, int children, int adults) {
    if (name.empty()) throw GroupInvalidArgs();
    if (adults == 0 && children == 0) throw GroupInvalidArgs();
    if (adults < 0 || children < 0) throw GroupInvalidArgs();

    this->name = name;
    this->clan = "";
    this->children = children;
    this->adults = adults;
    this->tools = 4 * adults;
    this->food = 3 * adults + 2 * children;
    this->morale = 70;
}

Group::Group(const Group &other) = default;

Group::~Group() = default;

const std::string &Group::getName() const {
    return name;
}

int Group::getSize() const {
    return adults + children;
}

const std::string &Group::getClan() const {
    return clan;
}

void Group::changeClan(const std::string &new_clan) {
    if (clan == new_clan) return;

    double temp;
    if (clan.empty()) {
        if (new_clan.empty()) return;
        clan = new_clan;
        temp = morale + morale * 0.1;

    } else {
        clan = new_clan;
        temp = morale - morale * 0.1;
    }

    if (temp > 100) temp = 100.0;
    morale = (int) temp;
}

int Group::calcPower(const Group &rhs) const {
    return int(floor(((10 * rhs.adults + 3 * rhs.children) *
                      (10 * rhs.tools + rhs.food) * (rhs.morale)) / 100));
}

bool Group::operator<(const Group &rhs) const {
    int rhs_power, this_power;
    rhs_power = calcPower(rhs);
    this_power = calcPower(*this);
    if (this_power < rhs_power) {
        return true;
    } else if (this_power > rhs_power) {
        return false;
    } else {
        if (name < rhs.name) {
            return true;
        } else {
            return false;
        }
    }
}

bool Group::operator==(const Group &rhs) const {
    int rhs_power, this_power;
    rhs_power = calcPower(rhs);
    this_power = calcPower(*this);
    //TODO: ask a tutorial
    if ((rhs_power == this_power) && (rhs.name == name)) {
        return true;
    } else {
        return false;
    }
}

bool Group::operator!=(const Group &rhs) const {
    if (!(*this == rhs)) {
        return true;
    } else {
        return false;
    }
}

bool Group::operator>(const Group &rhs) const {
    if (!(*this < rhs) && (*this != rhs)) {
        return true;
    } else {
        return false;
    }
}


bool Group::operator>=(const Group &rhs) const {
    if ((*this > rhs) || (*this == rhs)) {
        return true;
    } else {
        return false;
    }
}

bool Group::operator<=(const Group &rhs) const {
    if ((*this < rhs) || (*this == rhs)) {
        return true;
    } else {
        return false;
    }
}

void Group::uniteClan(Group &source, Group &destination) {
    int total_adults = source.adults + destination.adults;
    int total_children = source.children + destination.children;
    int total_food = source.food + destination.food;
    int total_tools = source.tools + destination.tools;
    int morale = int(
            floor((((source.morale * (source.children + source.adults)) *
                    (destination.morale *
                     (destination.children + destination.adults))) /
                   ((double) total_adults + (double) total_children))));
    morale = morale >= 100 ? 100 : morale;
    destination.adults = total_adults;
    destination.children = total_children;
    destination.food = total_food;
    destination.tools = total_tools;
    destination.morale = morale;
    source.tools = 0;
    source.children = 0;
    source.food = 0;
    source.adults = 0;
    source.clan = "";
    source.name = "";
    source.morale = 0;
}

bool Group::unite(Group &other, int max_amount) {
    int total_people = children + adults + other.children + other.adults;
    if (this->name != other.name && this->clan == other.clan &&
        total_people <= max_amount &&
        other.morale >= 70 && morale >= 70) {
        if (*this > other) {
            uniteClan(other, *this);
        } else {
            uniteClan(*this, other);
        }
        return true;
    } else {
        return false;
    }
}

Group Group::divide(const std::string &name) {
    if (this->adults <= 1 && this->children <= 1) throw GroupCantDivide();
    if (name.empty() == true) throw GroupInvalidArgs();
    int new_children = int(floor(children / 2.0));
    int new_adults = int(floor(adults / 2.0));
    int new_tools = int(floor(tools / 2.0));
    int new_food = int(floor(food / 2.0));
    Group new_group(name, clan, new_children, new_adults, new_tools, new_food,
                    morale);
    this->children = children - new_children;
    this->adults = adults - new_adults;
    this->food = food - new_food;
    this->tools = tools - new_tools;
    return new_group;
}

void Group::postFightUpdate(Group &lost, Group &won) {
    int lost_food = int(ceil((1.0 / 2.0) * (lost.food)));
    lost.adults -= int(ceil((1.0 / 3.0) * (lost.adults)));
    lost.children -= int(ceil((1.0 / 3.0) * (lost.children)));
    lost.food -= lost_food;
    lost.tools -= int(ceil((1.0 / 2.0) * (lost.tools)));
    lost.morale -= int(ceil((0.2) * (lost.morale)));

    won.adults -= int(floor((1.0 / 4.0) * (won.adults)));
    won.food += int(floor((1.0 / 2.0) * lost_food));
    won.tools -= int(floor((1.0 / 4.0) * (won.tools)));
    won.morale += int(ceil((0.2) * (won.morale)));
    if (won.morale > 100) {
        won.morale = 100;
    }
}

FIGHT_RESULT Group::fight(Group &opponent) {
    if (opponent.name == name && opponent.clan == clan) {
        throw GroupCantFightWithItself();
    }
    if ((adults == 0 && children == 0) ||
        (opponent.children == 0 && opponent.adults == 0)) {
        throw GroupCantFightEmptyGroup();
    }
    if (*this > opponent) {
        postFightUpdate(opponent, *this);
        return WON;
    } else if (*this == opponent) {
        return DRAW;
    } else {
        postFightUpdate(*this, opponent);
        return LOST;
    }
}

int Group::max(int a, int b) {
    return a > b ? a : b;
}

int Group::min(int a, int b) {
    return a < b ? a : b;
}

void Group::makeTrade(Group &group1, Group &group2, int average_trade) {
    int new_average;
    if (max(group1.food, group1.tools) < average_trade ||
        max(group2.food, group2.tools) < average_trade) {
        new_average = min(max(group2.food, group2.tools),
                          max(group1.food, group1.tools));
    } else {
        new_average = average_trade;
    }
    if (group1.food > group1.tools) {
        group1.food -= new_average;
        group1.tools += new_average;
        group2.food += new_average;
        group2.tools -= new_average;
    } else {
        group1.tools -= new_average;
        group1.food += new_average;
        group2.tools += new_average;
        group2.food -= new_average;
    }
}

bool Group::trade(Group &other) {
    if (other.name == name && other.clan == clan) {
        throw GroupCantTradeWithItself();
    }
    if ((food == tools || other.tools == other.food) ||
        (tools > food && other.tools > other.food) ||
        (food > tools && other.food > other.tools)) {
        return false;
    } else {
        int group1_trade, group2_trade, average_trade;
        group1_trade = int(ceil(abs(tools - food) / 2.0));
        group2_trade = int(ceil(abs(other.tools - other.food) / 2.0));
        average_trade = int(ceil(abs(group1_trade + group2_trade) / 2.0));
        makeTrade(*this, other, average_trade);
    }
    return true;
}
namespace mtm{
std::ostream &operator<<(std::ostream &os, const Group &group) {
    os << "Group's name: " << group.name << "\n" << "Group's clan: "
       << group.clan << "\n" << "Group's children: " << group.children
       << "\n" << "Group's adults: " << group.adults << "\n"
       << "Group's tools: " << group.tools << "\n"<< "Group's food: "
       << group.food <<"\n"<< "Group's morale: " << group.morale;
    return os;
}
}
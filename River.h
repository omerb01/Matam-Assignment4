//
// Created by Omer on 22/01/2018.
//

#ifndef ASSIGNMENT4_RIVER_H
#define ASSIGNMENT4_RIVER_H

#include "Area.h"

namespace mtm {
    class River : public Area {
    public:

        /**
         * Constructor
         * @param name The name of the area
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit River(const std::string &name);

        /**
         * Disable copy constructor
         */
        River(const River &) = delete;

        /**
         * Disable assignment operator
         */
        River &operator=(const River &) = delete;

        /**
         * Destructor
         */
        ~River() override;

        /**
         * overrides from Area
         */
        void groupArrive(const string &group_name, const string &clan_name,
                         map<string, Clan> &clan_map) override;

    };
}

#endif //ASSIGNMENT4_RIVER_H

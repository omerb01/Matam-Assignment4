//
// Created by Omer on 21/01/2018.
//

#ifndef ASSIGNMENT4_PLAIN_H
#define ASSIGNMENT4_PLAIN_H

#include "Area.h"

using std::vector;

namespace mtm {
    class Plain : public Area {
    public:

        /**
         * Constructor
         * @param name The name of the area
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit Plain(const std::string &name);

        /**
         * Disable copy constructor
         */
        Plain(const Plain &) = delete;

        /**
         * Disable assignment operator
         */
        Plain &operator=(const Plain &) = delete;

        /**
         * Destructor
         */
        ~Plain() override;

        /**
         * overrides from Area
         */
        void groupArrive(const string &group_name, const string &clan_name,
                         map<string, Clan> &clan_map) override;

    };
}

#endif //ASSIGNMENT4_PLAIN_H

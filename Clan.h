#ifndef MTM4_CLAN_H
#define MTM4_CLAN_H

#include <string>
#include "Group.h"
#include <ostream>
#include <memory>

namespace mtm{
    
    typedef std::shared_ptr<Group> GroupPointer;
    /**
     * A clan of multiple groups. Groups can join a clan, and clans can be
     * friends to other clans.
     * Groups with no people can't join a clan, and a group that had
     * lost all of its people, will be removed from the clan.
     */
    class Clan{
    
    public:
        /**
         * Constructor
         * @param name The name of the new clan, can't be empty
         * @throws ClanEmptyName if name is empty.
         */
        explicit Clan(const std::string& name);
        
        /**
         * Copy constructor.
         */
        Clan(const Clan& other);

        /**
         * Disable assignment operator
         */
        Clan &operator=(const Clan &) = delete;
        
        /**
         * Destructor
         */
        ~Clan();
        
        /**
         * Add a group (copy of it) to the clan
         * @param group The group to add to the clan
         * @throws ClanGroupIsEmpty if the group has no people (empty)
         * @throws ClanGroupNameAlreadyTaken if there is already a group
         * with the same name in the clan.
         */
        void addGroup(const Group& group);
        
        /**
         * Get a group from the clan, with a given name
         * @param group_name The name of the group the return
         * @return A reference to the group with the given name
         * @throws ClanGroupNotFound if there is no group in the clan with the
         * given name.
         */
        const GroupPointer& getGroup(const std::string& group_name) const;
        
        bool doesContain(const std::string& group_name) const;
        
        /**
         * The function returns the amount of people in the clan.
         * A person belongs to the clan, if he belongs to a group, that
         * belongs to the clan.
         * @return The amount of people in the clan.
         */
        int getSize() const;
        
        /**
         * Make two clans unite, to form a new clan, with a new name. All the
         * groups of each clan will change their clan.
         * The friends of the new clan are all the friends of either one of
         * the old 2 clans.
         * The new clan will replace this clan, and the other clan (received
         * by an argument) will become empty (i.e no groups).
         *
         * If One of the exception is thrown, both clan shouldn't change.
         * @param other The clan to unite with
         * @param new_name The name of the new clan. If the name is of one of
         *  the uniting clans (assume to clan A), that means the other clan,
         *  joined clan A, and the groups of the clan A, don't change their
         *  clan.
         * @return A reference to the new clan (this).
         * @throws ClanEmptyName new_name is empty.
         * @throws ClanCantUnite If other is the same clan as this or if
         *  there is a group in one of the clans, that has the same name as a
         *  group in the other clan.
         */
        Clan& unite(Clan& other, const std::string& new_name);
        
        /**
         * Make this clan, and a given clan, friends. If the two clans already
         * were friends, does nothing.
         * Assume that every clan has a unique name. (In copied clans, you
         * can assume one of the copies will not be used again).
         * @param other The clan to become a friend with.
         */
        void makeFriend(Clan& other);
        
        /**
         * Check if a given clan is a friend of this clan.
         * Every clan is a friend of itself.
         * @param other The clan to check if is a friend.
         * @return true, if the given clan is a friend of this clan, false
         *  otherwise.
         */
        bool isFriend(const Clan& other) const;
        
        /**
         * Print The clan name, and it groups, sorted by groups comparison
         * operators, from strongest to weakest. In the next Format:
         *
         * Clan's name: [name]
         *     [1'st group name]
         *     [2'nd group name]
         *     [3'rd group name]
         *             *
         *             *
         *             *
         *
         * @param os The output stream
         * @param clan The clan to print
         * @return A reference to the output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Clan& clan);
    };
} // namespace mtm

#endif //MTM4_CLAN_H

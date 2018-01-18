#ifndef MTM4_AREA_H
#define MTM4_AREA_H

#include <string>
#include <map>
#include "Clan.h"
#include "Group.h"
#include <vector>
#include <memory>

using std::string;
using std::shared_ptr;
using std::map;

namespace mtm{
    
    /**
     * An abstract call of an area in the world.
     * Assume every name is unique.
     * Groups that become empty, should be removed from the area.
     */
    class Area{
        
    protected:

        std::vector<GroupPointer> groups;

    public:
        /**
         * Constructor
         * @param name The name of the area
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit Area(const std::string& name);
        
        /**
         * Disable copy constructor
         */
        Area(const Area&) = delete;

        /**
         * Disable assignment operator
         */
        Area &operator=(const Area &) = delete;

        /**
         * Destructor
         */
        virtual ~Area();
        
        /**
         * Add an area, that can be reachable from this area.
         * Doesn't mean that this area is reachable from the area with the
         * given name.
         * @param area_name The name of the area that can be reachable from
         *  this are.
         */
        void addReachableArea(const std::string& area_name);
        
        /**
         * Check if an area is reachable from this area.
         * An area is always reachable from itself.
         * @param area_name The name of the area to check if it's reachable.
         * @return True if the area with the given name is reachable from
         * this area, and false otherwise.
         */
        bool isReachable(const std::string& area_name) const;
        
        /**
         * Get a group into the area.
         * @param group_name The name of the group that get into the area.
         * @param clan The name of the clan that the group belongs to.
         * @param clan_map The map of clans that contains the clan of the group
         * @throws AreaClanNotFoundInMap If there is no clan with the given
         * name in the map.
         * @throws AreaGroupNotInClan If there is no group with the given name
         * in the clan with the given name in the map.
         * @throws AreaGroupAlreadyIn If group with same name already in the
         *  area.
         *
         * Assert that the map does contain the clan that the group belongs to.
         */
        virtual void groupArrive(const string& group_name, const string& clan,
                                 map<string, Clan>& clan_map);
        
        /**
         * Get a group out of the area.
         * @param group_name The name of the leaving group.
         * @throws AreaGroupNotFound If there is no group in the area with the
         *  same name;
         */
        virtual void groupLeave(const std::string& group_name);
        
        /**
         * Get a set of the names of all the groups in the area.
         * @return A set that contains the names of all the groups in the area.
         */
        MtmSet<std::string> getGroupsNames() const;
    };
} //namespace mtm

#endif //MTM4_AREA_H

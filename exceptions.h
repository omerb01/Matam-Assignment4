#ifndef MTM4_EXCEPTIONS_H
#define MTM4_EXCEPTIONS_H

#include <exception>

#define NEW_EXCEPTION(exp, from) \
    class exp : public from{\
    public: \
        virtual const char* what() const throw(){\
            return #exp;\
    }}

namespace mtm{
    
    NEW_EXCEPTION(GroupException, std::exception);
    NEW_EXCEPTION(GroupInvalidArgs, GroupException);
    NEW_EXCEPTION(GroupCantFightWithItself, GroupException);
    NEW_EXCEPTION(GroupCantFightEmptyGroup, GroupException);
    NEW_EXCEPTION(GroupCantTradeWithItself, GroupException);
    NEW_EXCEPTION(GroupCantDivide, GroupException);
    
    NEW_EXCEPTION(ClanException, std::exception);
    NEW_EXCEPTION(ClanEmptyName, ClanException);
    NEW_EXCEPTION(ClanGroupNameAlreadyTaken, ClanException);
    NEW_EXCEPTION(ClanGroupNotFound, ClanException);
    NEW_EXCEPTION(ClanCantUnite, ClanException);
    NEW_EXCEPTION(ClanGroupIsEmpty, ClanException);
    
    NEW_EXCEPTION(AreaException, std::exception);
    NEW_EXCEPTION(AreaInvalidArguments, AreaException);
    NEW_EXCEPTION(AreaClanNotFoundInMap, AreaException);
    NEW_EXCEPTION(AreaGroupNotInClan, AreaException);
    NEW_EXCEPTION(AreaGroupAlreadyIn, AreaException);
    NEW_EXCEPTION(AreaGroupNotFound, AreaException);
    
    NEW_EXCEPTION(WorldException, std::exception);
    NEW_EXCEPTION(WorldInvalidArgument, WorldException);
    NEW_EXCEPTION(WorldGroupNameIsTaken, WorldException);
    NEW_EXCEPTION(WorldClanNameIsTaken, WorldException);
    NEW_EXCEPTION(WorldAreaNameIsTaken, WorldException);
    NEW_EXCEPTION(WorldGroupNotFound, WorldException);
    NEW_EXCEPTION(WorldClanNotFound, WorldException);
    NEW_EXCEPTION(WorldAreaNotFound, WorldException);
    NEW_EXCEPTION(WorldGroupAlreadyInArea, WorldException);
    NEW_EXCEPTION(WorldAreaNotReachable, WorldException);
    
    
    NEW_EXCEPTION(MTMSetException, std::exception);
    NEW_EXCEPTION(MTMSetNodeException, MTMSetException);
    NEW_EXCEPTION(NodeIsEndException, MTMSetNodeException);
}
#endif //MTM4_EXCEPTIONS_H

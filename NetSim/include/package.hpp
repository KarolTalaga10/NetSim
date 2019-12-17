// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include <iostream>
#include <set>
#include "types.hpp"

static std::set<ElementID>assigned_IDs;
static std::set<ElementID>freed_IDs;

class Package{
private:
    ElementID mID;
    bool is_ID_assigned(const ElementID &id_to_assign);
    ElementID give_id();
public:
    Package() {mID = give_id(); assigned_IDs.insert(get_id());};
    ~Package() {assigned_IDs.erase(mID); freed_IDs.insert(mID);}
    Package(const Package&& pcg):mID(std::move(pcg.mID)) {};
    Package& operator = (const Package&& pcg);
    ElementID get_id() const { return mID; }

};

#endif //NETSIM_PACKAGE_HPP

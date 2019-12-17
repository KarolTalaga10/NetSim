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

public:
    Package();
    Package(const Package&& pcg);
    Package& operator= (Package&& pcg) {
        freed_IDs.emplace(mID);
        mID = std::move(pcg.mID);
        return *this;
    }
    ElementID get_id() const { return mID; }
};

#endif //NETSIM_PACKAGE_HPP

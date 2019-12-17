// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#include <package.hpp>
#include <iostream>

std::set<ElementID>Package::assigned_IDs = {};
std::set<ElementID>Package::freed_IDs = {};

bool Package::is_ID_assigned(const ElementID &id_to_assign)
{
    bool is_in = assigned_IDs.find(id_to_assign) != assigned_IDs.end();
    return is_in;
}

ElementID Package::give_id()
{
    ElementID id_to_be_given = 1;
    if(is_ID_assigned(id_to_be_given))
    {
        id_to_be_given = *freed_IDs.begin();
    }
    ElementID given_id = id_to_be_given;
    freed_IDs.erase(given_id);
    assigned_IDs.emplace(given_id);
    freed_IDs.emplace(given_id+1);
    return given_id;
}

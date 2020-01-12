// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP
#include <set>

#include "types.hpp"

/**
 * Ponieważ w myśl założeń projektowych w systemie nie mogą istnieć dwa
 * półprodukty o tym samym ID, konstruktor kopiujący oraz operator przypisania
 * zostały oznaczone jako usunięte.
 *
 * Ponieważ konstruktor przenoszący oraz przenoszący operator przypisania
 * sprawiają, że obiekt przekazany jako odpowiednio argument lub operand
 * przestaje być "poprawny" (nie powinniśmy się do niego odnosić później
 * w programie), możemy ten obiekt zmodyfikować - oznaczyć jako "niepoprawny"
 * poprzez przypisanie mu pewnego szczególnego ID spoza dopuszczalnego zakresu
 * (dla przypomnienia: dopuszczalne ID to liczby całkowite DODATNIE).
 */
class Package {
public:
    Package();

    explicit Package(ElementID id);

    Package(const Package&) = delete;
    Package(Package&&) noexcept;

    Package& operator=(Package&) = delete;
    Package& operator=(Package&&) noexcept;

    ~Package();

    ElementID get_id() const { return id_; }

private:
    static const ElementID BLANK_ID = -1;

    /*
     * Począwszy od C++17 pola statyczne mogą być oznaczane jako `inline`,
     * dzięki czemu moża je inicjalizować wewnątrz definicji klasy (a nie
     * w osobnym pliku źródłowym).
     */

    // Pula identyfikatorów aktualnie przyporządkowanych półproduktom.
    inline static std::set<ElementID> assigned_ids_{0};

    // Pula identyfikatorów, które zostały zwolnione w wyniku usuwania półproduktów.
    inline static std::set<ElementID> freed_ids_;

    ElementID id_ = BLANK_ID;
};

/*
#include <iostream>
#include <set>
#include "types.hpp"

class Package{
private:
    ElementID mID;
    bool is_ID_assigned(const ElementID &id_to_assign);
    ElementID give_id();
    static std::set<ElementID>assigned_IDs;
    static std::set<ElementID>freed_IDs;
public:
    Package() {mID = give_id(); assigned_IDs.insert(get_id());};
    ~Package() {assigned_IDs.erase(mID); freed_IDs.insert(mID);}
    Package(const Package& pcg) = default;
    Package(const Package&& pcg):mID(std::move(pcg.mID)) {};
    Package& operator = (Package&& pcg) {
        freed_IDs.emplace(mID);
        mID = std::move(pcg.mID);
        return *this;
    }
    ElementID get_id() const { return mID; }
};
*/
#endif //NETSIM_PACKAGE_HPP


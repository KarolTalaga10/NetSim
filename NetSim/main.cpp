#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "nodes.hpp"

int main() {
    //std::cout << "Hello, World!" << std::endl;
    //std::cout << get_random() << std::endl;

    PackageQueue q(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(q);
    Storehouse s(1, std::move(ptr));
    Ramp r(1,2);
    r.mReceiverPreferences.add_receiver(&s);
    r.deliver_goods(0);
    std::cout<< "1 z kontenera: " <<s.cbegin()->get_id()<< std::endl;
    r.deliver_goods(1);
    std::cout<< "1 z kontenera: " <<s.cbegin()->get_id()<< std::endl;
    r.deliver_goods(2);
    std::cout<< "1 z kontenera: " <<s.cbegin()->get_id()<< std::endl;

    return 0;
}
// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#include <factory.hpp>

template <typename Node>
void NodeCollection<Node>::remove_by_id(ElementID id_)
{
    auto it = find_by_id(id_);
    if(it != mContainer.end())
    {
        mContainer.erase(it);
    }
}

// TO DO: te dwie funkcje ponizej sa do zrobienia, chodzi glownie o sprawdzenie czy kazdy package docelowo trafia do magazynu, trzeba uzyc przeszukiwania wglab i wykorzystac pseudokod

/*
bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors)
{

}

bool Factory::is_consistent()
{

}
*/


// W konspekcie te funckje mialy byc zrobione z uzyciem std::for_each ale nie wychodzi mi wiec for wjezdza na salony
void Factory::do_deliveries(Time time)
{
    //std::for_each(Ramps.begin(),Ramps.end(),[](auto &ramps){ramps.deliver_goods(time);});
    for(auto& ramps: Ramps)
    {
        ramps.deliver_goods(time);
    }
}

void Factory::do_package_passing()
{
    for(auto& ramp: Ramps)
    {
        if(ramp.get_sending_buffer().has_value())
        {
            ramp.send_package();
        }
    }
    for(auto& worker: Workers)
    {
        if(worker.get_sending_buffer().has_value())
        {
            worker.send_package();
        }
    }
}

void Factory::do_work(Time time)
{
    for(auto& worker: Workers)
    {
        worker.do_work(time);
    }
}

// Ta funkcja ma odpowiadac za usuwanie polaczen miedzy dostawcami

template <typename Node>
void Factory::remove_receiver(NodeCollection<Node>& collection, ElementID id)
{
    std::for_each(Ramps.begin(), Ramps.end(), [id](Ramp &ramp){
        auto ramp_receivers = ramp.receiver_preferences_.get_preferences();

        for(auto receiver = ramp_receivers.begin(); receiver != ramp_receivers.end(); receiver++) {
            ramp.receiver_preferences_.remove_receiver(receiver->first);
        }
    });

    std::for_each(Workers.begin(), Workers.end(), [id](Worker &worker){
        auto worker_receivers = worker.receiver_preferences_.get_preferences();

        for(auto receiver = worker_receivers.begin(); receiver != worker_receivers.end(); receiver++) {
            worker.receiver_preferences_.remove_receiver(receiver->first);
        }
    });
    collection.remove_by_id(id);

    /*
    auto ramp_list = std::find_if(Ramps.begin(), Ramps.end(), [id](auto& elem) {
        return id == elem.receiver_preferences_.get_preferences()->first;
    });

    for (auto& ramp: ramp_list) {
        ramp.receiver_preferences_.remove_receiver(&collection.find_ramp_by_id(id));
    }
    auto worker_list = std::find_if(Workers.begin(), Workers.end(), [id](auto& elem) {
        return id == elem.receiver_preferences_.get_preferences()->first;
    });

    for (auto& worker: worker_list) {
        worker.receiver_preferences_.remove_receiver(&collection.find_worker_by_id(id));
    }
     */
}

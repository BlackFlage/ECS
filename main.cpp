#include <iostream>
#include "EntityManager.hpp"
#include "ComponentArray.hpp"

int main()
{
    EntityManager manager;

    std::array<Entity, 5> my_entities{};

    for(int i = 0; i < 5; i++)
    {
        my_entities[i] = manager.create_entity();
    }



    return 0;
}

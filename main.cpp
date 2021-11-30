#include <iostream>
#include "EntityManager.hpp"

int main()
{
    EntityManager manager;

    for(int i = 0; i < 10; i++)
    {
        Entity e = manager.create_entity();
    }

    return 0;
}

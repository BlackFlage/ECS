#include <iostream>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include <random>

struct Position
{
    float x;
    float y;
    float z;
};

void print_position(ComponentManager& manager, const Entity& entity)
{
    auto pos = manager.get_component<Position>(entity);
    std::printf("Entity ID: %d, x: %f y: %f z: %f\n", entity, pos.x, pos.y, pos.z);
}

int main()
{
    EntityManager entity_manager;
    ComponentManager component_manager;

    component_manager.register_component<Position>();

    std::array<Entity, 5> my_entities{};
    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);

    for(int i = 0; i < 5; i++)
    {
        my_entities[i] = entity_manager.create_entity();
        component_manager.add_component<Position>(my_entities[i], Position{
            .x = randPosition(generator),
            .y = randPosition(generator),
            .z = randPosition(generator)
        });
    }

    for(int i = 0; i < 5; i++)
    {
        print_position(component_manager, my_entities[i]);
    }

    return 0;
}

#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "MainManager.hpp"
#include "Types.hpp"

struct Position
{
    float x;
    float y;
    float z;
};

struct Color
{
    float x;
    float y;
    float z;
    float a;
};

struct RigidBody
{
    float velocity_x;
    float velocity_y;
};

MainManager manager;

using namespace std::chrono_literals;

class PhysicsSystem : public System
{
public:
    void on_update(float a_delta_time)
    {
        for(auto& entity : m_entities)
        {
            auto& pos = manager.get_component<Position>(entity);
            const auto& vel = manager.get_component<RigidBody>(entity);

            pos.x += vel.velocity_x * a_delta_time;
            pos.y += vel.velocity_y * a_delta_time;
        }
    }
};

class ColorSystem : public System
{
public:
    void on_update()
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_real_distribution<float> randColor( 0.0f, 1.0f);

        for(auto& entity : m_entities)
        {
            auto& color = manager.get_component<Color>(entity);
            color.x = randColor(generator);
            color.y = randColor(generator);
            color.z = randColor(generator);
        }
    }
};

void print(const Entity& entity)
{
    const auto& pos = manager.get_component<Position>(entity);
    const auto& vel = manager.get_component<RigidBody>(entity);
    const auto& color = manager.get_component<Color>(entity);

    std::printf("Entity ID: %d, pos(x, y, z): (%f, %f, %f), vel(x, y): (%f, %f), col(x, y, z, a): (%f, %f, %f, %f)\n",
                entity, pos.x, pos.y, pos.z, vel.velocity_x, vel.velocity_y, color.x, color.y, color.z, color.a);
}

int main()
{
    std::array<Entity, 4> my_entities{};
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);

    manager.register_component<Position>();
    manager.register_component<RigidBody>();
    manager.register_component<Color>();

    auto physicsSystem = manager.register_system<PhysicsSystem>();

    Signature physSignature;
    physSignature.set(manager.get_component_type<Position>(), true);
    physSignature.set(manager.get_component_type<RigidBody>(), true);
    manager.set_system_signature<PhysicsSystem>(physSignature);

    auto colorSystem = manager.register_system<ColorSystem>();

    Signature colorSignature;
    colorSignature.set(manager.get_component_type<Color>(), true);
    manager.set_system_signature<ColorSystem>(colorSignature);

    for(int i = 0; i < 3; i++)
    {
        my_entities[i] = manager.create_entity();

        manager.add_component(my_entities[i],
                              Position{
                                    .x = randPosition(generator),
                                    .y = randPosition(generator),
                                    .z = randPosition(generator)
                                    });

        manager.add_component(my_entities[i],
                              Color{
                                    .x = 1.0f,
                                    .y = 1.0f,
                                    .z = 1.0f,
                                    .a = 1.0f
                                });

        manager.add_component(my_entities[i],
                              RigidBody{
                                    .velocity_x = 1.0f,
                                    .velocity_y = 1.0f
                                });
    }

    my_entities[3] = manager.create_entity();
    manager.add_component(my_entities[3], Color{1.0f, 1.0f, 1.0f, 1.0f});

    float delta_time = 0.0f;

    while(true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < 3; i++)
        {
            print(my_entities[i]);
        }

        const auto& col = manager.get_component<Color>(my_entities[3]);
        printf("ID: %d, col(x, y, z, a): (%f, %f, %f, %f)\n", my_entities[3], col.x, col.y, col.z, col.y);

        physicsSystem->on_update(delta_time);
        colorSystem->on_update();

        std::printf("\n\n\n");

        auto stopTime = std::chrono::high_resolution_clock::now();

        delta_time = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
        std::this_thread::sleep_for(5s);
    }

    return 0;
}

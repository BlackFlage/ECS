//
// Created by BlackFlage on 30.11.2021.
//

#ifndef ECS_COMPONENTARRAY_HPP
#define ECS_COMPONENTARRAY_HPP

#include <unordered_map>
#include "EntityManager.hpp"

template<typename T>
class ComponentArray
{
public:
    ComponentArray();

    void insert_data(const Entity& a_entity, T a_component);
    void remove_data(const Entity& a_entity);

    T& get_data(const Entity& a_entity);

    void on_entity_destroyed(const Entity& a_entity);
private:
    std::array<T, MAX_ENTITIES> m_component_array;
    std::unordered_map<Entity, size_t> m_entity_to_index;
    std::unordered_map<size_t, Entity> m_index_to_entity;

    size_t m_current_size;
};

#endif //ECS_COMPONENTARRAY_HPP

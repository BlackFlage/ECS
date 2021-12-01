//
// Created by BlackFlage on 30.11.2021.
//

#ifndef ECS_COMPONENTARRAY_HPP
#define ECS_COMPONENTARRAY_HPP

#include <unordered_map>
#include "EntityManager.hpp"
#include <cassert>

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void on_entity_destroyed(const Entity& a_entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    ComponentArray()
    {
        m_current_size = 0;
    }

    void insert_data(const Entity& a_entity, T a_component)
    {
        assert(m_entity_to_index.find(a_entity) == m_entity_to_index.end());

        size_t new_index = m_current_size;
        m_entity_to_index[a_entity] = new_index;
        m_index_to_entity[new_index] = a_entity;
        m_component_array[new_index] = a_component;
        m_current_size++;
    }
    void remove_data(const Entity& a_entity)
    {
        assert(m_entity_to_index.find(a_entity) != m_entity_to_index.end());

        size_t index_of_removed_entity = m_entity_to_index[a_entity];

        m_component_array[index_of_removed_entity] = m_component_array[m_current_size - 1];

        m_entity_to_index[m_current_size - 1] = index_of_removed_entity;
        m_index_to_entity[index_of_removed_entity] = m_current_size - 1;

        m_entity_to_index.erase(a_entity);
        m_index_to_entity.erase(m_current_size - 1);

        --m_current_size;
    }

    T& get_data(const Entity& a_entity)
    {
        assert(m_entity_to_index.find(a_entity) != m_entity_to_index.end());

        size_t index_of_component = m_entity_to_index[a_entity];

        return m_component_array[index_of_component];
    }

    void on_entity_destroyed(const Entity& a_entity) override
    {
        if(m_entity_to_index.find(a_entity) != m_entity_to_index.end())
        {
            remove_data(a_entity);
        }
    }
private:
    std::array<T, MAX_ENTITIES> m_component_array;
    std::unordered_map<Entity, size_t> m_entity_to_index;
    std::unordered_map<size_t, Entity> m_index_to_entity;

    size_t m_current_size;
};

#endif //ECS_COMPONENTARRAY_HPP

//
// Created by BlackFlage on 30.11.2021.
//

#include "ComponentArray.hpp"
#include <cassert>

template<typename T>
ComponentArray<T>::ComponentArray()
{
    m_current_size = 0;
}

template<typename T>
void ComponentArray<T>::insert_data(const Entity &a_entity, T a_component)
{
    assert(m_entity_to_index.find(a_entity) != m_entity_to_index.end());

    size_t new_index = m_current_size;
    m_entity_to_index[a_entity] = new_index;
    m_index_to_entity[new_index] = a_entity;
    m_component_array[new_index] = a_component;
    m_current_size++;
}

template<typename T>
void ComponentArray<T>::remove_data(const Entity &a_entity)
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

template<typename T>
T &ComponentArray<T>::get_data(const Entity &a_entity)
{
    assert(m_entity_to_index.find(a_entity) != m_entity_to_index.end());

    size_t index_of_component = m_entity_to_index[a_entity];

    return m_component_array[index_of_component];
}

template<typename T>
void ComponentArray<T>::on_entity_destroyed(const Entity &a_entity)
{
    if(m_entity_to_index.find(a_entity) != m_entity_to_index.end())
    {
        remove_data(a_entity);
    }
}

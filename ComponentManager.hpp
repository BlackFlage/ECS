//
// Created by BlackFlage on 30.11.2021.
//

#ifndef ECS_COMPONENTMANAGER_HPP
#define ECS_COMPONENTMANAGER_HPP

#include <bitset>
#include <unordered_map>
#include <memory>
#include <cassert>
#include "ComponentArray.hpp"
#include "Types.hpp"

class ComponentManager
{
public:
    ComponentManager()
    {
        m_component_arrays = std::unordered_map<const char*, std::shared_ptr<IComponentArray>>{};
        m_component_types = std::unordered_map<const char*, ComponentType>{};
        m_next_component_type = 0;
    }

    template<typename T>
    void register_component()
    {
        const char* component_name = typeid(T).name();

        assert(m_component_types.find(component_name) == m_component_types.end());

        m_component_types.insert({component_name, m_next_component_type});
        m_component_arrays.insert({component_name, std::make_shared<ComponentArray<T>>()});

        ++m_next_component_type;
    }

    template<typename T>
    ComponentType get_component_type()
    {
        const char* component_name = typeid(T).name();

        assert(m_component_types.find(component_name) != m_component_types.end());

        return m_component_types[component_name];
    }

    template<typename T>
    void add_component(const Entity& a_entity, T a_component)
    {
        get_component_array<T>()->insert_data(a_entity, a_component);
    }

    template<typename T>
    void remove_component(const Entity& a_entity)
    {
        get_component_array<T>()->remove_data(a_entity);
    }

    template<typename T>
    T& get_component(const Entity& a_entity)
    {
        return get_component_array<T>()->get_data(a_entity);
    }

    void on_entity_destroyed(const Entity& a_entity)
    {
        for(const auto& pair : m_component_arrays)
        {
            auto& component = pair.second;
            component->on_entity_destroyed(a_entity);
        }
    }
private:
    template<typename T>
    std::shared_ptr<ComponentArray<T>> get_component_array()
    {
        const char* component_name = typeid(T).name();

        assert(m_component_arrays.find(component_name) != m_component_arrays.end());

        return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[component_name]);
    }
private:
    std::unordered_map<const char*, ComponentType> m_component_types;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_component_arrays;
    ComponentType m_next_component_type;
};


#endif //ECS_COMPONENTMANAGER_HPP

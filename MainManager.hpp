//
// Created by BlackFlage on 02.12.2021.
//

#ifndef ECS_MAINMANAGER_HPP
#define ECS_MAINMANAGER_HPP

#include <cassert>
#include <memory>

#include "Types.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

class MainManager
{
public:
    MainManager()
    {
        m_entity_manager = std::make_unique<EntityManager>();
        m_component_manager = std::make_unique<ComponentManager>();
        m_system_manager = std::make_unique<SystemManager>();
    }

    Entity create_entity()
    {
        return m_entity_manager->create_entity();
    }

    void destroy_entity(const Entity& a_entity)
    {
        m_entity_manager->destroy_entity(a_entity);
        m_component_manager->on_entity_destroyed(a_entity);
        m_system_manager->on_entity_destroyed(a_entity);
    }

    template<typename T>
    void register_component()
    {
        m_component_manager->register_component<T>();
    }

    template<typename T>
    void add_component(const Entity& a_entity, T a_component)
    {
        m_component_manager->template add_component(a_entity, a_component);

        auto signature = m_entity_manager->get_signature(a_entity);
        signature.set(m_component_manager->get_component_type<T>(), true);

        m_entity_manager->set_signature(a_entity, signature);
        m_system_manager->entity_signature_changed(a_entity, signature);
    }

    template<typename T>
    T& get_component(const Entity& a_entity)
    {
        return m_component_manager->get_component<T>(a_entity);
    }

    template<typename T>
    ComponentType get_component_type()
    {
        return m_component_manager->get_component_type<T>();
    }

    template<typename T>
    std::shared_ptr<T> register_system()
    {
        return m_system_manager->register_system<T>();
    }

    template<typename T>
    void set_system_signature(const Signature& a_signature)
    {
        m_system_manager->set_signature<T>(a_signature);
    }
private:
    std::unique_ptr<EntityManager> m_entity_manager;
    std::unique_ptr<ComponentManager> m_component_manager;
    std::unique_ptr<SystemManager> m_system_manager;
};

#endif //ECS_MAINMANAGER_HPP

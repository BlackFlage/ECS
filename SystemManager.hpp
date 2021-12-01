//
// Created by BlackFlage on 01.12.2021.
//

#ifndef ECS_SYSTEMMANAGER_HPP
#define ECS_SYSTEMMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <cassert>

#include "Types.hpp"
#include "System.hpp"

class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> register_system()
    {
        const char* system_name = typeid(T).name();

        assert(m_systems.find(system_name) == m_system.end());

        auto system = std::make_shared<T>();
        m_systems.insert({system_name, system});

        return system;
    }

    template<typename T>
    void set_signature(const Signature& a_signature)
    {
        const char* system_name = typeid(T).name();

        assert(m_systems.find(system_name) != m_system.end());

        m_signatures.insert({system_name, a_signature});
    }

    void on_entity_destroyed(const Entity& a_entity)
    {
        for(const auto& sys_pair : m_systems)
        {
            auto& system = sys_pair.second;
            system->m_entities.erase(a_entity);
        }
    }

    void entity_signature_changed(const Entity& a_entity, const Signature& a_signature)
    {
        for(const auto& sys_pair : m_systems)
        {
            const auto& name = sys_pair.first;
            const auto& system = sys_pair.second;
            const auto& system_signature = m_signatures[name];

            if((system_signature & a_signature) == system_signature)
            {
                system->m_entities.insert(a_entity);
            }
            else
            {
                system->m_entities.erase(a_entity);
            }
        }
    }
private:
    std::unordered_map<const char*, Signature> m_signatures;
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
};

#endif //ECS_SYSTEMMANAGER_HPP

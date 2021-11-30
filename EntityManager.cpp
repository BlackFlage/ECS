//
// Created by BlackFlage on 30.11.2021.
//

#include "EntityManager.hpp"
#include <cassert>

EntityManager::EntityManager()
{
    for(Entity entity = 0; entity < MAX_ENTITIES; entity++)
    {
        m_available_entities.push(entity);
    }

    m_used_entities = 0;
}

Entity EntityManager::create_entity()
{
    assert(m_used_entities < MAX_ENTITIES);

    Entity id = m_available_entities.front();
    m_available_entities.pop();
    ++m_used_entities;

    return id;
}

void EntityManager::destroy_entity(const Entity &a_entity)
{
    assert(a_entity >= 0 && a_entity < MAX_ENTITIES);

    m_signatures[a_entity].reset();
    m_available_entities.push(a_entity);
    --m_used_entities;
}

Signature EntityManager::get_signature(const Entity &a_entity)
{
    assert(a_entity >= 0 && a_entity < MAX_ENTITIES);

    return m_signatures[a_entity];
}

void EntityManager::set_signature(const Entity& a_entity, const Signature& a_signature)
{
    assert(a_entity > 0 && a_entity < MAX_ENTITIES);

    m_signatures[a_entity] = a_signature;
}

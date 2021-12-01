//
// Created by BlackFlage on 01.12.2021.
//

#ifndef ECS_SYSTEM_HPP
#define ECS_SYSTEM_HPP

#include <set>
#include "Types.hpp"

class System
{
public:
    std::set<Entity> m_entities;
};

#endif //ECS_SYSTEM_HPP

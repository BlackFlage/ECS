//
// Created by BlackFlage on 30.11.2021.
//

#ifndef ECS_TYPES_HPP
#define ECS_TYPES_HPP

#include <cstdint>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

static constexpr Entity MAX_ENTITIES = 1024;
static constexpr ComponentType MAX_COMPONENTS = 64;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif //ECS_TYPES_HPP

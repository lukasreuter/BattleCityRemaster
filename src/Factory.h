#pragma once

#include "Components.h"


typedef entt::DefaultRegistry::entity_type Entity;

class Factory
{
public:
    static Entity createTank(entt::DefaultRegistry& where, std::string prefix, float velocity, float angularVelocity, Magnum::Vector3 overHeating, int health, bool ai);
    static Entity createBlock(entt::DefaultRegistry& where, int x, int y, int z, std::string material);
    static void createFloor(entt::DefaultRegistry& where, int sizex, int sizey, int repetition_x, int repetition_y, std::string material);
    static Entity createProjectile(entt::DefaultRegistry& where, Magnum::Vector3 pos, Magnum::Quaternion ori, float velocity, std::string materialName);
};

//
// Created by shurj on 01-Nov-2024.
//

#include "Particle.h"

Particle CreateParticle(glm::vec2 initialPosition, glm::vec2 initialVelocity, float mass) {
    static uint64_t nextID = 0;
    return {nextID++, initialPosition, initialVelocity, {0, 0}, mass};
}

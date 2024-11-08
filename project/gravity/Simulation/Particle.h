//
// Created by shurj on 01-Nov-2024.
//

#ifndef GRAVITY_PARTICLE_H
#define GRAVITY_PARTICLE_H

#include <glm/glm.hpp>

struct Particle {
    uint64_t id;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float mass;
};

Particle CreateParticle(glm::vec2 initialPosition, glm::vec2 initialVelocity, float mass);

#endif //GRAVITY_PARTICLE_H

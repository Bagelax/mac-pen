//
// Created by Milutin on 6.12.2019..
//

#ifndef MAC_PEN_PACMAN_H
#define MAC_PEN_PACMAN_H

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class pacman {
private:
    const long speed = 5;

public:
    pacman(const int, const glm::vec4);
    ~pacman();
    int size;
    glm::vec2 position;
    glm::vec4 color;
    void updateCoords(const bool up, const bool down, const bool left, const bool right);
};


#endif //MAC_PEN_PACMAN_H

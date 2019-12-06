//
// Created by Milutin on 6.12.2019..
//

#include "pacman.h"

pacman::pacman(int size, glm::vec4 color) {
    this->size = size;
    this->position = glm::vec2(13.5 * size, 23 * size);
    this->color = color;
}

void pacman::updateCoords(const bool up, const bool down, const bool left, const bool right) {
    if(up)     this->position.y -= this->speed;
    if(down)   this->position.y += this->speed;
    if(left)   this->position.x -= this->speed;
    if(right)  this->position.x += this->speed;
}

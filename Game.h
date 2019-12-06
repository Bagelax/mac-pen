#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "utils.h"
#include "Shader.h"
#include "SpriteRenderer.h"
#include "pacman.h"

#ifndef MAC_PEN_GAME_H
#define MAC_PEN_GAME_H


class Game {
public:
    Game();
    ~Game();
    void startRenderLoop();

private:
    unsigned int score = 0, time = 0, blockSize, SCR_WIDTH, SCR_HEIGHT;
    GLFWwindow *window;
    Shader *shader;
    SpriteRenderer *spriteRenderer;
    std::string terain[31];
    pacman *player;
    bool up = false, down = false, left = false, right = false;
    void processInput(GLFWwindow *window);
    void Initialize();
};

#endif //MAC_PEN_GAME_H

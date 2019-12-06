#include "Game.h"

Game::~Game() {}

Game::Game() {
    this->Initialize();

}

void Game::Initialize() {
    // glfw: initialize and configure

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    this->blockSize = (mode->height - (mode->height / 5)) / 31;
    this->SCR_HEIGHT = blockSize * 31;
    this->SCR_WIDTH = blockSize * 28;

    std::cout << blockSize << " " << SCR_HEIGHT << " " << SCR_WIDTH << std::endl;

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mac-Pen", NULL, NULL);
    glm::mat4 projection = glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, -1.0f, -1.0f, 1.0f);
    std::cout << glm::to_string(projection * glm::vec4((float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0, 1.0)) << std::endl;

    if (this->window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }
    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(0);
    }

    this->shader = new Shader();
    this->shader->Compile("shaders/vertex.glsl", "shaders/fragment.glsl", "");
    this->spriteRenderer = new SpriteRenderer((*this->shader), projection);

    std::ifstream file("terain.txt");
    if (file.is_open()) {
        for (int i = 0; i < 31; i++) {
            getline(file, this->terain[i]);
        }
    }
    file.close();

    this->player = new pacman(this->blockSize, RGBColor(255, 255, 0));
}

void Game::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->down = false;
        this->left = false;
        this->right = false;
        this->up = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->up = false;
        this->left = false;
        this->right = false;
        this->down = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->right = false;
        this->down = false;
        this->up = false;
        this->left = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->left = false;
        this->down = false;
        this->up = false;
        this->right = true;
    }
}

void Game::startRenderLoop() {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        player->updateCoords(this->up, this->down, this->left, this->right);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float topOffset = 0, botOffset = 0, leftOffset = 0, rightOffset = 0;
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 28; j++) {
                topOffset = 0;
                botOffset = 0;
                leftOffset = 0;
                rightOffset = 0;
                if (terain[i][j] == '#') {
                    if (i != 0 && terain[i - 1][j] != '#') topOffset = this->blockSize / 2;
                    if (i != 30 && terain[i + 1][j] != '#') botOffset = this->blockSize / 2;
                    if (j != 0 && terain[i][j - 1] != '#') leftOffset = this->blockSize / 2;
                    if (j != 27 && terain[i][j + 1] != '#') rightOffset = this->blockSize / 2;
                    if (topOffset != 0 && botOffset != 0)
                        if (i < 15) botOffset = 0;
                        else topOffset = 0;
                    if (leftOffset != 0 && rightOffset != 0)
                        if (j < 14) rightOffset = 0;
                        else leftOffset = 0;
                    spriteRenderer->DrawSprite(glm::vec2(this->blockSize * j + leftOffset, this->blockSize * i + topOffset),
                                               glm::vec2(this->blockSize - rightOffset - leftOffset,this->blockSize - botOffset - topOffset),
                                               0.0f, RGBColor(0, 0, 255));

                }
            }
        }

        spriteRenderer->DrawSprite(this->player->position, glm::vec2(this->player->size), 0.0f, this->player->color);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
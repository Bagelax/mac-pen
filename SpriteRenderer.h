//
// Created by Milutin on 15.11.2019..
//

#ifndef MAC_PEN_SPRITERENDERER_H
#define MAC_PEN_SPRITERENDERER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"


class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader, glm::mat4 projection);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(glm::vec2 position, glm::vec2 size = glm::vec2(37, 37), GLfloat rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));
private:
    // Render state
    Shader shader;
    GLuint quadVAO;
    glm::mat4 projection;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif //MAC_PEN_SPRITERENDERER_H

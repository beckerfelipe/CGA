#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"
#include "MainCamera.h"
#include <glm/glm.hpp>

class Cube {
private:
    GLuint VAO, VBO;

    void SetupCube();

public:
    glm::vec3 position;
    Shader* shader;
    glm::mat4 model;

    Cube(glm::vec3 position);
    void Update();
};

#endif // CUBE_H

#pragma once

#include "Common.hpp"

class RocketProjection
{
private:
    GLuint program;
    GLuint VAO;
    GLuint VBO;

public:
    RocketProjection();
    void Draw();
};


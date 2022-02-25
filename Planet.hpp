#pragma once

#include "Common.hpp"

class Planet
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint program;

public:
    Planet( float x, float y, float radius );
    ~Planet();

    void Draw();
};


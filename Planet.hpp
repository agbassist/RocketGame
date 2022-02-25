#pragma once

#include "Common.hpp"

class Planet
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint program;
    GLuint translationLoc;
    GLuint lookatLoc;

public:
    Planet( GLuint program, float x, float y, float radius );
    ~Planet();

    void Draw();
};


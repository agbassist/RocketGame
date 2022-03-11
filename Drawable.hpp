#pragma once

#include "Common.hpp"

class Drawable
{
protected:
    GLuint VAO;
    GLuint VBO;
    GLuint program;

public:
    Drawable( const char* vert, const char* frag );
    ~Drawable();

    void UseProgram();
    void Bind();
};


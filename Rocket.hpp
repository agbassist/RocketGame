#pragma once

#include "Common.hpp"

class Rocket
{
private:
    vec2   pos;
    float  direction;

    GLuint VBO;
    GLuint program;

    GLuint translationLoc;
    GLuint lookatLoc;

public:
    Rocket();
    ~Rocket();

    void Draw();
    void setPosition( float x, float y );
    void setDirection( float dir );
};


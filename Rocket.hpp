#pragma once

#include "Common.hpp"

class Rocket
{
private:
    vec2   pos;
    vec2   direction;
    float  directionAngle;

    GLuint VBO;
    GLuint program;

    GLuint translationLoc;
    GLuint lookatLoc;

public:
    Rocket();
    ~Rocket();

    void Draw();
    void setPosition( float x, float y );
    void setDirection( float x, float y );
    void addDirection( float theta );
};


#pragma once

#include "Common.hpp"
#include "Rocket.hpp"

class Planet
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint program;
    GLuint translationLoc;
    GLuint lookatLoc;

    float radius;
    vec2  pos;

public:
    Planet( GLuint program, float x, float y, float radius );
    ~Planet();

    void Draw();
    void ImpartGravity( Rocket& rocket );
};


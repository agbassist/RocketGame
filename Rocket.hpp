#pragma once

#include "Common.hpp"

class Rocket
{
private:
    //vec2   pos;
    //float  direction;

    GLuint VBO;

public:
    Rocket();
    ~Rocket();

    void Draw();

};


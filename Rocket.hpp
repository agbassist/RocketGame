#pragma once

#include "Common.hpp"

class Rocket
{
private:
    vec2   pos;
    float  angle;
    float  accel;
    float  speed;
    float  deltaTime;

    GLuint VAO;
    GLuint VBO;
    GLuint program;

    GLuint translationLoc;
    GLuint lookatLoc;

    void checkHitForceField( float& val, float min, float max );

public:
    Rocket( float x, float y );
    ~Rocket();

    void Draw();
    void incrementAngle( float theta );
    void accelerate( float accel );
    void incrementTime( float deltaTime );
};


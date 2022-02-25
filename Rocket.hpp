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

    GLuint VBO;
    GLuint program;

    GLuint translationLoc;
    GLuint lookatLoc;

    void checkHitForceField( float& val, float min, float max );

public:
    Rocket();
    ~Rocket();

    void Draw();
    void setPosition( float x, float y );
    void incrementAngle( float theta );
    void accelerate( float accel );
    void incrementTime( float deltaTime );
};


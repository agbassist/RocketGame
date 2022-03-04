#pragma once

#include "Common.hpp"

class Rocket
{
private:
    vec2   pos;
    float  angle;
    vec2   accel;
    vec2   velo;
    float  deltaTime;

    GLuint VAO;
    GLuint VBO;
    GLuint program;

    GLuint translationLoc;
    GLuint lookatLoc;

    void checkHitForceField( float& val, float min, float max );

public:
    Rocket( GLuint program, float x, float y );
    ~Rocket();

    void Draw();

    void Move();
    void Stop( bool stop );

    vec2 getPos();

    void incrementAngle( float theta );
    void accelerate( float accel );
    void incrementTime( float deltaTime );
};


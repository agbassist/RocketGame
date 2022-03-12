#pragma once

#include "Common.hpp"

class Rocket
{
private:
    glm::vec2   pos;
    float       angle;
    glm::vec2   accel;
    glm::vec2   velo;
    float       deltaTime;

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

    /* Getters */
    glm::vec2 getPos() { return pos; }
    glm::vec2 getVelo() { return velo; }
    glm::vec2 getAccel() { return accel; }

    /* Setters */
    void setPos( glm::vec2 pos ) { this->pos = pos; }

    void incrementAngle( float theta );
    void addAccel( float accel );
    void addAccel( glm::vec2 accel );
    void incrementTime( float deltaTime );
    void setSpeed( float speed );
    void Move();
    void Stop( bool stop );
};


#pragma once

#include "Common.hpp"
#include "Drawable.hpp"

class Rocket : public Drawable
{
private:
    glm::vec2   pos;
    float       angle;
    glm::vec2   accel;
    glm::vec2   velo;
    float       deltaTime;

    GLuint      translationLoc;
    GLuint      lookatLoc;

    void checkHitForceField( float& val, float min, float max );

public:
    Rocket( float x, float y );
    ~Rocket();

    void Draw();

    void Move();
    void Stop( bool stop );

    glm::vec2 getPos();
    void setPos( glm::vec2 pos );

    void incrementAngle( float theta );
    void addAccel( float accel );
    void addAccel( glm::vec2 accel );
    void incrementTime( float deltaTime );
    void setSpeed( float speed );
};


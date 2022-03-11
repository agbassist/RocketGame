#pragma once

#include "Common.hpp"
#include "Drawable.hpp"
#include "Rocket.hpp"
#include "Shader.hpp"

class Planet : public Drawable
{
private:
    float      radius;
    glm::vec2  pos;

public:
    Planet( float x, float y, float radius );    
    ~Planet();

    void Draw();
    void ImpartGravity( Rocket& rocket );
};


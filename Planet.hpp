#pragma once

#include "Common.hpp"
#include "Rocket.hpp"

class Planet
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint program;

    // Uniforms
    GLuint colorLoc;

    float      radius;
    glm::vec2  pos;

public:
    Planet( float x, float y, float radius );
    ~Planet();

    void Draw();
    void ImpartGravity( Rocket& rocket );
    glm::vec2 ImpartGravity( glm::vec2 pos );
    bool IsInside(glm::vec2 pos);
};


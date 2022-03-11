
#include "Planet.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

#define NUM_VERTS 32

Planet::Planet( float x, float y, float radius )
    : Drawable( SHADER_PLANET_VERT, SHADER_PLANET_FRAG )
{
    this->radius = radius;
    this->pos    = { x, y };

    float verts[NUM_VERTS][2];
    for( int i = 0; i < NUM_VERTS; i++ )
        {
        verts[i][0] = x + ( radius * cos( i * 6.28f / NUM_VERTS ) );
        verts[i][1] = y + ( radius * sin( i * 6.28f / NUM_VERTS ) );
        }

    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
}

Planet::~Planet()
{ 
}

void Planet::Draw()
{
    UseProgram();
    Bind();
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_LINE_LOOP, 0, NUM_VERTS );
}

void Planet::ImpartGravity( Rocket& rocket )
{
    glm::vec2 deltaPos = this->pos - rocket.getPos();
    float radius = glm::length( deltaPos );
    float angle = atan2( deltaPos[1], deltaPos[0] );

    if( radius < this->radius )
        {
        glm::vec2 newPos;
        newPos[0] = this->pos[0] + ( ( 1.0f + this->radius ) * cos( 3.14f + angle ) );
        newPos[1] = this->pos[1] + ( ( 1.0f + this->radius ) * sin( 3.14f + angle ) );

        rocket.Stop( true );
        rocket.setPos( newPos );
        return;
        }

    #define SCALAR 4500000.0f // G * m1 * m2 - just make this something that feels nice
    glm::vec2 force;
    float force_scalar = ( SCALAR / ( radius * radius ) );
    force[0] = force_scalar * cos( angle );
    force[1] = force_scalar * sin( angle );

    rocket.addAccel( force );
}
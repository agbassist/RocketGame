
#include "Planet.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

#define NUM_VERTS 32

Planet::Planet( float x, float y, float radius )
{
    this->radius = radius;
    this->pos    = { x, y };

    program = LoadShader( SHADER_PLANET_VERT, SHADER_PLANET_FRAG );
    glUseProgram( program );

    glm::mat4 projection = glm::ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    colorLoc = glGetUniformLocation( program, "in_color" );

    float verts[NUM_VERTS][2];
    for( int i = 0; i < NUM_VERTS; i++ )
        {
        verts[i][0] = x + ( radius * cos( i * 6.28f / NUM_VERTS ) );
        verts[i][1] = y + ( radius * sin( i * 6.28f / NUM_VERTS ) );
        }

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glEnableVertexAttribArray( 0 );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

Planet::~Planet()
{
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( program );
    glDeleteVertexArrays( 1, &VAO );
}

void Planet::Draw()
{
    glUseProgram( program );
    
    glm::vec3 color = { 0.0f, 0.0f, 1.0f };
    glUniform3fv( colorLoc, 1, &color[0] );

    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glDrawArrays( GL_LINE_LOOP, 0, NUM_VERTS );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( GL_ZERO );
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

glm::vec2 Planet::ImpartGravity( glm::vec2 pos )
{
    glm::vec2 deltaPos = this->pos - pos;
    float radius = glm::length( deltaPos );
    float angle = atan2( deltaPos[1], deltaPos[0] );

    #define SCALAR 4500000.0f // G * m1 * m2 - just make this something that feels nice
    glm::vec2 force;
    float force_scalar = ( SCALAR / ( radius * radius ) );
    force[0] = force_scalar * cos( angle );
    force[1] = force_scalar * sin( angle );
    
    return( force );
}

bool Planet::IsInside( glm::vec2 pos )
{
    return( glm::length( pos - this->pos ) <= this->radius );
}
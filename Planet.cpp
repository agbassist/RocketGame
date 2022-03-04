#include "Planet.hpp"
#include <glm/gtc/matrix_transform.hpp>

#define NUM_VERTS 32

Planet::Planet( GLuint program, float x, float y, float radius )
{
    this->radius = radius;
    this->pos    = { x, y };

    this->program = program;
    glUseProgram( program );

    mat4 projection = ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    translationLoc = glGetUniformLocation( program, "translation" );
    lookatLoc = glGetUniformLocation( program, "lookat" );

    float verts[NUM_VERTS][2];
    for( int i = 0; i < NUM_VERTS; i++ )
        {
        verts[i][0] = x + ( radius * cos( i * 6.28f / NUM_VERTS ) );
        verts[i][1] = y + ( radius * sin( i * 6.28f / NUM_VERTS ) );
        }

    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );

    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );

    glBindVertexArray( GL_ZERO );
}

Planet::~Planet()
{
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( program );
    glDeleteVertexArrays( 1, &VAO );
}

void Planet::Draw()
{
    vec2 pos = { 0.0f, 0.0f };
    glUniform2fv( translationLoc, 1, &pos[0] );

    glm::mat2 rotation;
    rotation[0][0] = 1.0f;
    rotation[0][1] = 0.0f;
    rotation[1][0] = 0.0f;
    rotation[1][1] = 1.0f;
    glUniformMatrix2fv( lookatLoc, 1, GL_FALSE, &rotation[0][0] );

    glBindVertexArray( VAO );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_LINE_LOOP, 0, NUM_VERTS );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( VAO );
}

void Planet::ImpartGravity( Rocket& rocket )
{
    vec2 deltaPos = this->pos - rocket.getPos();
    float radius = length( deltaPos );
    float angle = atan2( deltaPos[1], deltaPos[0] );

    if( radius <= this->radius )
        {
        // Doesn't work like I thought it would
        //rocket.Stop( true );
        //return;
        }

    //std::cout << "( " << deltaPos[0] << ", " << deltaPos[1] << " )\n";

    #define SCALAR 20000000.0f // G * m1 * m2 - just make this something that feels nice
    vec2 force;
    float force_scalar = ( SCALAR / ( radius * radius ) );
    force[0] = force_scalar * cos( angle );
    force[1] = force_scalar * sin( angle );

    rocket.addAccel( force );
}
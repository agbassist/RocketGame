#include "Planet.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

#define NUM_VERTS 16

Planet::Planet( float x, float y, float radius )
{
    program = LoadShaders( "shaders/planet.vert", "shaders/planet.frag" );
    glUseProgram( program );

    mat4 projection = ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

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
    glBindVertexArray( VAO );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_LINE_LOOP, 0, NUM_VERTS );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( VAO );
}
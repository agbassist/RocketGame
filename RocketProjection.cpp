
#include "RocketProjection.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

static float verts[10][2];

RocketProjection::RocketProjection()
{
    program = LoadShader( SHADER_PLANET_VERT, SHADER_PLANET_FRAG );

    glm::mat4 projection = glm::ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    for( int i = 0; i < 10; i++ )
        {
        verts[i][0] = 1000.0f;
        verts[i][1] = 900.0f * ( i / 10.0f );
        }

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    glBindVertexArray( VAO );
        {
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

        glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
        }
    glBindVertexArray( GL_ZERO );
}

void RocketProjection::Draw()
{
    glUseProgram( program );
    glBindVertexArray( VAO );
        {
        glDrawArrays( GL_LINE_STRIP, 0, CNT_OF_ARRAY( verts ) );
        }
    glBindVertexArray( GL_ZERO );
}
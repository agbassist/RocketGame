
#include "RocketProjection.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

RocketProjection::RocketProjection()
{
    program = LoadShader( SHADER_PLANET_VERT, SHADER_PLANET_FRAG );

    glm::mat4 projection = glm::ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STREAM_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

void RocketProjection::CalculatePath( Rocket &rocket, Planet &planet )
{    
    glm::vec2 pos = rocket.getPos();
    glm::vec2 velo = rocket.getVelo();

    /* Simulate 1 second and show path during that interval */
    for( int i = 0; i < CNT_OF_ARRAY( verts ); i++ )
        {
        float deltaTime = ( 0.5f * i ) / CNT_OF_ARRAY( verts );
        glm::vec2 accel = planet.ImpartGravity( pos );
        pos = KINETIC_EQ( pos, velo, accel, deltaTime );
        velo += accel * deltaTime;
        #define MAX_SPEED 1000.0f
        if( glm::length( velo ) > MAX_SPEED )
            {
            velo = MAX_SPEED * glm::normalize( velo );
            }
        verts[i] = pos;
        }

    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STREAM_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

void RocketProjection::Draw()
{
    glUseProgram( program );
    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glDrawArrays( GL_LINE_STRIP, 0, CNT_OF_ARRAY( verts ) );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}
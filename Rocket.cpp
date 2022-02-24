
#include "Rocket.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

static const GLfloat verts[] = 
{
     50.0f,     0.0f,
    -50.0f,    50.0f,
      0.0f,     0.0f,
     50.0f,     0.0f,
      0.0f,     0.0f,
    -50.0f,   -50.0f,
};

Rocket::Rocket() {

    program = LoadShaders("shaders/rocket.vert", "shaders/rocket.frag");
    glUseProgram( program );
    
    mat4 projection = ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    translationLoc = glGetUniformLocation( program, "translation" );
    lookatLoc      = glGetUniformLocation( program, "lookat"      );

    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );

    directionAngle = 0.0f;
}

Rocket::~Rocket() {
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( program );
}

void Rocket::Draw() {

    float theta = atan2f(
        direction[1] - pos[1],
        direction[0] - pos[0]
    );

    //pos[0] += ( direction[0] - pos[0] ) / 200.0f;
    //pos[1] += ( direction[1] - pos[1] ) / 200.0f;
    
    #define SPEED ( 2.0f / 3.14f )
    pos[0] += SPEED * cosf( directionAngle );
    pos[1] += SPEED * sinf(directionAngle);

    glUniform2fv( translationLoc, 1, &pos[0] );    

    /*glm::mat2 rotation = 
        {
        vec2(         cosf( theta ), sinf( theta ) ),
        vec2( -1.0f * sinf( theta ), cosf( theta ) )
        };*/
    glm::mat2 rotation =
        {
        vec2(cosf(directionAngle), sinf(directionAngle)),
        vec2(-1.0f * sinf(directionAngle), cosf(directionAngle))
        };
    glUniformMatrix2fv( lookatLoc, 1, GL_FALSE, &rotation[0][0] );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );
    glDisableVertexAttribArray( 0 );
}

void Rocket::setPosition( float x, float y ) {
    pos[ 0 ] = x;
    pos[ 1 ] = y;
}

void Rocket::setDirection( float x, float y ) {
    direction[0] = x;
    direction[1] = y;
}

void Rocket::addDirection(float theta) {
    directionAngle += theta;
}
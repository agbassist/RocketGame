
#include "Rocket.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

Rocket::Rocket( float x, float y )
{
    program = LoadShader( "shaders/rocket.vert", "shaders/rocket.frag" );
    glUseProgram( program );
    
    mat4 projection = ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    translationLoc = glGetUniformLocation( program, "translation" );
    lookatLoc      = glGetUniformLocation( program, "lookat"      );

    #define SIZE 25.0f
    GLfloat verts[] =
        {
        SIZE,    0.0f,
       -SIZE,    SIZE,
        0.0f,    0.0f,
        SIZE,    0.0f,
        0.0f,    0.0f,
       -SIZE,   -SIZE,
        };

    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );

    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );

    glBindVertexArray( GL_ZERO );

    angle = 0.0f;
    accel = { 0.0f, 0.0f };
    velo = { 0.0f, 0.0f };
    pos = { x, y };
    deltaTime = 0.0f;
}

Rocket::~Rocket()
{
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( program );
    glDeleteVertexArrays( 1, &VAO );
}

void Rocket::checkHitForceField( float& val, float min, float max )
{
    if( val < min )
        {
        val = min;
        velo = { 0.0f, 0.0f };
        accel = { 0.0f, 0.0f };
        }
    else if( val > max )
        {
        val = max;
        velo = { 0.0f, 0.0f };
        accel = { 0.0f, 0.0f };
        }    
}

void Rocket::Move()
{
    /* Position Calculation s = s0 + v0t + 0.5at^2 */
    vec2 delta_pos = ( velo * deltaTime )                   \
                    + ( 0.5f * accel * deltaTime * deltaTime );

    pos[0] += delta_pos[ 0 ];
    pos[1] += delta_pos[ 1 ];

    checkHitForceField( pos[0], 0, WINDOW_WIDTH );
    checkHitForceField( pos[1], 0, WINDOW_HEIGHT );

    /* Speed Calculation v = v0 + at */
    velo += accel * deltaTime;

    #define MAX_SPEED 1000.0f
    if( length( velo ) > MAX_SPEED )
        {
        velo = MAX_SPEED * normalize( velo );
        }

    accel = { 0.0f, 0.0f };
}

void Rocket::Stop( bool stop )
{
    if( stop )
        {
        accel = { 0.0f, 0.0f };
        velo = { 0.0f, 0.0f };
        }
}

vec2 Rocket::getPos()
{
    return( pos );
}

void Rocket::setPos( vec2 pos )
{
    this->pos = pos;
}

void Rocket::Draw()
{
    glUseProgram( program );
    glUniform2fv( translationLoc, 1, &pos[0] );    

    glm::mat2 rotation =
        {
        vec2(         cos( angle ), sin( angle ) ),
        vec2( -1.0f * sin( angle ), cos( angle ) )
        };
    glUniformMatrix2fv( lookatLoc, 1, GL_FALSE, &rotation[0][0] );

    glBindVertexArray( VAO );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( GL_ZERO );
}

void Rocket::incrementAngle( float angle )
{
    this->angle += angle;
}

void Rocket::addAccel( float accel )
{
    this->accel = this->accel + vec2( { accel * cos( angle ), accel * sin( angle ) } );
}

void Rocket::addAccel( vec2 accel )
    {
    this->accel = this->accel + accel;
    }

void Rocket::incrementTime( float deltaTime )
{
    this->deltaTime = deltaTime;
}

void Rocket::setSpeed( float speed )
{
    this->velo = vec2( { speed * cos( angle ), speed * sin( angle ) } );
}
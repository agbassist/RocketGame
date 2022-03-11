
#include "Rocket.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

Rocket::Rocket( float x, float y )
    : Drawable( SHADER_ROCKET_VERT, SHADER_ROCKET_FRAG )
{
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

    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );

    angle = 0.0f;
    accel = { 0.0f, 0.0f };
    velo = { 0.0f, 0.0f };
    pos = { x, y };
    deltaTime = 0.0f;
}

Rocket::~Rocket()
{
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
    glm::vec2 delta_pos = ( velo * deltaTime )                   \
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
        velo = MAX_SPEED * glm::normalize( velo );
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

glm::vec2 Rocket::getPos()
{
    return( pos );
}

void Rocket::setPos( glm::vec2 pos )
{
    this->pos = pos;
}

void Rocket::Draw()
{
    UseProgram();
    glUniform2fv( translationLoc, 1, &pos[0] );    

    glm::mat2 rotation =
        {
        glm::vec2(         cos( angle ), sin( angle ) ),
        glm::vec2( -1.0f * sin( angle ), cos( angle ) )
        };
    glUniformMatrix2fv( lookatLoc, 1, GL_FALSE, &rotation[0][0] );

    Bind();
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
}

void Rocket::incrementAngle( float angle )
{
    this->angle += angle;
}

void Rocket::addAccel( float accel )
{
    this->accel = this->accel + glm::vec2( { accel * cos( angle ), accel * sin( angle ) } );
}

void Rocket::addAccel( glm::vec2 accel )
    {
    this->accel = this->accel + accel;
    }

void Rocket::incrementTime( float deltaTime )
{
    this->deltaTime = deltaTime;
}

void Rocket::setSpeed( float speed )
{
    this->velo = glm::vec2( { speed * cos( angle ), speed * sin( angle ) } );
}
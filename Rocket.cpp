#include "Rocket.hpp"

static const GLfloat verts[] = 
{
      0.0f,   -50.0f,
    -50.0f,    50.0f,
      0.0f,     0.0f,
      0.0f,   -50.0f,
      0.0f,     0.0f,
     50.0f,    50.0f,
};

Rocket::Rocket() {
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), verts, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );
}

Rocket::~Rocket() {
    glDeleteBuffers( 1, &VBO );
}

void Rocket::Draw() {
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    glBindBuffer( GL_ARRAY_BUFFER, GL_ZERO );
    glDisableVertexAttribArray( 0 );
}
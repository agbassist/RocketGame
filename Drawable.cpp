
#include "Drawable.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

Drawable::Drawable( const char* vert, const char* frag )
{
    program = LoadShader( vert, frag );
    UseProgram();

    // Assume everything is 2D using the same coordinate system
    // Every shader needs this projection
    glm::mat4 projection = glm::ortho( 0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT );
    GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, &projection[0][0] );

    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    // Sub-classes can assume proper binding and program
    Bind();
}

Drawable::~Drawable()
{
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( program );
    glDeleteVertexArrays( 1, &VAO );
}

void Drawable::Bind()
{
    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
}

void Drawable::UseProgram()
    {
    glUseProgram( program );
    }
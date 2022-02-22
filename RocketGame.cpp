// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "common/shader.hpp"

#define WINDOW_WIDTH  ( 1024 )
#define WINDOW_HEIGHT ( 768 )

int main(void)
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // To make MacOS happy; should not be needed
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Rocket Game", NULL, NULL );
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders(
        "shaders/shader.vert",
        "shaders/shader.frag");

    static const GLfloat verts[] = {
          0.0f,   -50.0f,  
        -50.0f,    50.0f, 
          0.0f,     0.0f,
          0.0f,   -50.0f,
          0.0f,     0.0f,
         50.0f,    50.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    static const GLfloat translation[] = {
        (float)WINDOW_WIDTH / 2.0f,
        (float)WINDOW_HEIGHT / 2.0f
    };

    glm::mat4 projection;
    projection = glm::ortho( 0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f );

    // Use our shader
    glUseProgram( programID );
    GLuint MatrixID = glGetUniformLocation( programID, "projection" );
    glUniformMatrix4fv( MatrixID, 1, GL_FALSE, &projection[0][0] );

    GLuint translation_loc = glGetUniformLocation( programID, "translation" );
    glUniform2fv( translation_loc, 1, &translation[0] );

    GLuint lookat_loc = glGetUniformLocation( programID, "lookat" );

    do {

        double xpos, ypos;
        glfwGetCursorPos( window, &xpos, &ypos);

        xpos = xpos - ( (double)WINDOW_WIDTH  / 2 );
        ypos = ypos - ( (double)WINDOW_HEIGHT / 2 );
        double angle = atan2( xpos, ypos );
        angle += (double)3.14f;

        glm::mat2 rotation = {
            vec2( cosf((float)angle ), -1.0f*sinf( (float)angle ) ),
            vec2( sinf((float)angle ),       cosf( (float)angle ) ) };
        glUniformMatrix2fv( lookat_loc, 1, GL_FALSE, &rotation[0][0] );

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  
            2,                  
            GL_FLOAT,           
            GL_FALSE,           
            0,                  
            (void*)0 );

        // Draw the triangle !
        glDrawArrays( GL_TRIANGLES, 0, 6 );

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


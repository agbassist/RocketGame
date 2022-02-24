
#include "Common.hpp"
#include "Rocket.hpp"

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

int main(void)
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
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
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    GLuint VertexArrayID;
    glGenVertexArrays( 1, &VertexArrayID );
    glBindVertexArray( VertexArrayID );

    Rocket rocket;
    
    // Initialize position to the middle of the screen
    rocket.setPosition((float)WINDOW_WIDTH / 2.0f, (float)WINDOW_HEIGHT / 2.0f);

    do {
        double xpos, ypos;
        glfwGetCursorPos( window, &xpos, &ypos);
        ypos = (float)WINDOW_HEIGHT - ypos;
        //rocket.setDirection( xpos, ypos );

        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            
        }
        // Turn Left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            rocket.addDirection( 0.5f * 3.14f / 180.0f );
        } // Turn Right
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            rocket.addDirection(-0.5f * 3.14f / 180.0f);
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        rocket.Draw();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    // Cleanup
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


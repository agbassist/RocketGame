
#include "Common.hpp"
#include "Rocket.hpp"

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

int main()
{
    // Initialise GLFW
    if( !glfwInit() )
        {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return( -1 );
        }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Rocket Game", NULL, NULL );
    if( window == NULL )
        {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
        }
    glfwMakeContextCurrent( window );

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if( glewInit() != GLEW_OK )
        {
        fprintf( stderr, "Failed to initialize GLEW\n" );
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
    rocket.setPosition( (float)WINDOW_WIDTH / 2.0f, (float)WINDOW_HEIGHT / 2.0f );

    do {
        double currentTime, lastTime = 0.0f;
        
        double xpos, ypos;
        glfwGetCursorPos( window, &xpos, &ypos );
        ypos = (float)WINDOW_HEIGHT - ypos;
        //rocket.setDirection( xpos, ypos );

        #define ACCEL 0.6f
        if( glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS )
            {
            rocket.accelerate( ACCEL );
            }
        if( glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS )
            {
            rocket.accelerate( -ACCEL );
            }

        #define TURN ( 0.8f )
        #define DEGREE_TO_RADIANS ( 3.14f / 180.0f )
        if( glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS )
            {
            rocket.incrementAngle( TURN * DEGREE_TO_RADIANS );
            }
        if( glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS )
            {
            rocket.incrementAngle( -TURN * DEGREE_TO_RADIANS );
            }

        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Calculate time that has passed
        currentTime = glfwGetTime();
        float deltaTime = float( currentTime - lastTime );
        lastTime = currentTime;

        rocket.incrementTime( deltaTime / 1000.0f );
        rocket.Draw();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();

    } while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
          && glfwWindowShouldClose( window ) == 0 );

    // Cleanup
    glDeleteVertexArrays( 1, &VertexArrayID );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return( 0 );
}



#include "Common.hpp"
#include "Planet.hpp"
#include "Rocket.hpp"
#include "RocketProjection.hpp"
#include "Shader.hpp"

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
    
    Rocket rocket( 100.0f, 100.0f );
    Planet planet( (float)WINDOW_WIDTH / 2.0f, (float)WINDOW_HEIGHT / 2.0f, 100.0f );
    RocketProjection projection;

    double currentTime;
    double lastTime;
    float  deltaTime;

    currentTime = glfwGetTime();
    lastTime = currentTime;
    deltaTime = 0.0f;

    do {
        double xpos, ypos;
        glfwGetCursorPos( window, &xpos, &ypos );
        ypos = (float)WINDOW_HEIGHT - ypos;
        //rocket.setDirection( xpos, ypos );

        #define ACCEL 800.0f
        float acceleration = 0.0f;
        if( glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS )
            {
            acceleration += ACCEL;            
            }
        if( glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS )
            {
            acceleration += -ACCEL;
            }

        #define TURN ( 0.8f )
        float turn = 0.0f;
        if( glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS )
            {
            turn = TURN * DEGREE_TO_RADIANS;
            }
        if( glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS )
            {
            turn = -TURN * DEGREE_TO_RADIANS;
            }
        
        bool stop = false;
        if( glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS )
            {
            stop = true;
            }

        // Calculate time that has passed
        currentTime = glfwGetTime();
        deltaTime = float( currentTime - lastTime );
        lastTime = currentTime;

        rocket.incrementTime( deltaTime );
        rocket.incrementAngle( turn );
        rocket.addAccel( acceleration );
        planet.ImpartGravity( rocket );
        rocket.Stop( stop );
        rocket.Move();
        projection.CalculatePath( rocket, planet );
    
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        planet.Draw();
        projection.Draw();
        rocket.Draw();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();

    } while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
          && glfwWindowShouldClose( window ) == 0 );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return( 0 );
}


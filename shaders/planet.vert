#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 pos;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4( pos, 0, 1 );
}


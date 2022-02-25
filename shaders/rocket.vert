#version 330 core

// Input vertex data, different for all executions of this shader.
layout( location = 0 ) in vec2 pos;

uniform mat4 projection;
uniform vec2 translation;
uniform mat2 lookat;

void main()
{
	vec2 rotated = lookat * pos; 
	vec2 translated = rotated + translation;

    gl_Position = projection * vec4( translated, 0, 1 );
}


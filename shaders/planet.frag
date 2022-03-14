#version 330 core

uniform vec3 in_color;

// Ouput data
out vec3 color;

void main()
{
	// Output color = blue 
	color = in_color;
}
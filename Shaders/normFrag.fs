#version 410 core

uniform vec4 fColour; // colour is set as a uniform 

out vec4 fragColor;

void main()
{    
	fragColor = fColour; //for triangles only
}


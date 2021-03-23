#version 410 core

layout(triangles) in; //triangle goes in
layout(triangle_strip, max_vertices = 3) out; //triangles strip with max vertices of 3 goes out

void main()
{
	for(int i = 0; i < 3; i++) //loop 3 times for the triangle
	{
		gl_Position = gl_in[i].gl_Position; //gl_Position at each iteration assigned to ith index of gl_in array of each vertex in a triangle
		EmitVertex(); //emit the current values of output variables to the output primitive
	}
	EndPrimitive(); //end the stream of triangle vertices into the output primitive
}
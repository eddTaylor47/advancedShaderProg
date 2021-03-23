#version 410 core

//DRAWING VERTEX NORMALS EX.

layout(triangles) in; //triangles come in from vertex shader
layout(line_strip, max_vertices = 2) out; //line strip with max vertices of 2 goes out to fragment shader

in GS_NORM
{
    vec3 vNormal; //vertex normal
}gs_norm[];

uniform float vLength;

void main()
{
	for(int i = 0; i < 3; i++) //loop 3 times for the triangle
	{
		gl_Position = gl_in[i].gl_Position; //Initialise a vec3 for the position of the triangle's vertex at index i
		EmitVertex(); //emit the vertex above
		gl_Position = (gl_in[i].gl_Position + vec4(gs_norm[i].vNormal * vLength, 0.0)); // assign the vertex of the line's end point to the vertex position at index i + (vertex normal at index i * uniform length)
		EmitVertex(); //emit the above vertex
	}
	EndPrimitive(); //end the stream of triangle vertices into the output primitive
	
}
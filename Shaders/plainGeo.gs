#version 410 core

//TRIANGLE EX.
//layout(triangles) in; //triangle goes in
//layout(triangle_strip, max_vertices = 3) out; //triangles strip with max vertices of 3 goes out

//POINTS EX 1. A LINE
//layout(points) in; //point goes in
//layout(line_strip, max_vertices = 2) out; //line strip with max vertices of 2 goes out

//POINTS EX 1. A TRIANGLE
//layout(points) in; //point goes in
//layout(line_strip, max_vertices = 4) out; //line strip with max vertices of 2 goes out

//POINTS EX 1. A SQUARE
//ayout(points) in; //point goes in
//ayout(line_strip, max_vertices = 5) out; //line strip with max vertices of 2 goes out

//POINTS EX 1. A SQUARE AND A TRIANGLE
layout(points) in; //point goes in
layout(line_strip, max_vertices = 8) out; //line strip with max vertices of 2 goes out

void main()
{
	//for(int i = 0; i < 3; i++) //loop 3 times for the triangle
	//{
	//	gl_Position = gl_in[i].gl_Position; //gl_Position at each iteration assigned to ith index of gl_in array of each vertex in a triangle
	//	EmitVertex(); //emit the current values of output variables to the output primitive
	//}
	//EndPrimitive(); //end the stream of triangle vertices into the output primitive

	// A LINE
	//gl_Position = gl_in[0].gl_Position;
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position + vec4(0.f, 10.f, 0.f, 0.f);
	//EmitVertex();
	//EndPrimitive();
	
	// A TRIANGLE FROM A SINGLE POINT READ IN
	//gl_Position = gl_in[0].gl_Position;
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position + vec4(2.5f, 10.f, 0.f, 0.f);
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position + vec4(5f, 0.f, 0.f, 0.f);
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position;
	//EmitVertex();
	//EndPrimitive();
	
	// A SQUARE FROM A SINGLE POINT READ IN
	//gl_Position = gl_in[0].gl_Position;
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position + vec4(0.f, 10.f, 0.f, 0.f);
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position + vec4(7.5f, 10.f, 0.f, 0.f);
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position + vec4(7.5f, 0.f, 0.f, 0.f);
	//EmitVertex();
	//gl_Position = gl_in[0].gl_Position;
	//EmitVertex();
	//EndPrimitive();
	
	// A SQUARE AND A TRIANGLE FROM A SINGLE POINT READ IN
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.f, 10.f, 0.f, 0.f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(7.5f, 10.f, 0.f, 0.f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(7.5f, 0.f, 0.f, 0.f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-2.5f, 10.f, 0.f, 0.f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-5f, 0.f, 0.f, 0.f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}
#vertex
#version 330

uniform float Grids;
uniform float Gap;

void main()
{
	gl_Position = vec4(gl_vertexId % Grids * Gap, 0.0, gl_vertexId / Grids * Gap, 1);
}

#fragment
#version 330

vec4 outColor;

void main()
{
	outColor = vec4(0.0, 0.0, 1.0, 1.0);
}

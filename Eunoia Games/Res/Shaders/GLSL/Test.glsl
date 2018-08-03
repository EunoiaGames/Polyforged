#vertex
#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 WorldMatrix;

out vec3 color0;

void main()
{
	gl_Position = WorldMatrix * vec4(pos, 1.0);
	color0 = color;
}

#fragment
#version 330

in vec3 color0;
out vec4 outColor;

void main()
{
	outColor = vec4(color0, 1.0);
}

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

out vec3 color0;
out vec3 normal0;
out vec3 worldPos0;

void main()
{
	gl_Position = Projection * View * Model * vec4(pos, 1.0);
	worldPos0 = (Model * vec4(pos, 1.0)).xyz;
	normal0 = (Model * vec4(normal, 0.0)).xyz;
	color0 = color;
}

in vec3 color0;
in vec3 worldPos0;
in vec3 normal0;
out vec4 outColor;
uniform vec3 CamPos;

void main()
{
	outColor = CalcForwardRender(normalize(normal0), CamPos, worldPos0, color0);
}

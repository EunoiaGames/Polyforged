cbuffer Camera : register(b1)
{
	float3 CamPos;
}

cbuffer Material : register(b2)
{
	float3 Specular;
	float Shininess;
}

float4 PSMain(VSOutput input) : SV_TARGET0
{
	return CalcForwardRender(normalize(input.normal), CamPos, input.worldPos, input.color, Specular, Shininess);
}
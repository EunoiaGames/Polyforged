#include "Res/Shaders/HLSL/Lighting/Forward/LightVS.hlsl"

#include "Res/Shaders/HLSL/Lighting/Lighting.hlsl"

cbuffer Light : register(b0)
{
	DirectionalLight light;
}

float4 CalcForwardRender(float3 normal, float3 camPos, float3 worldPos, float3 albedo, float3 specular, float shininess)
{
	return CalcDirectionalLight(light, normal, camPos, worldPos, albedo, specular, shininess);
}

#include "Res/Shaders/HLSL/Lighting/Forward/LightingMain.hlsl"
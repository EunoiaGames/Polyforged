#vertex
#version 330
#include Res/Shaders/GLSL/Lighting/Forward/LightVS.glsl

#fragment
#version 330

#include Res/Shaders/GLSL/Lighting/Lighting.glsl

uniform DirectionalLight directionalLight;

vec4 CalcForwardRender(vec3 normal, vec3 camPos, vec3 worldPos, vec3 albedo)
{
	return CalcDirectionalLight(directionalLight, normal, camPos, worldPos, albedo);
}

#include Res/Shaders/GLSL/Lighting/Forward/LightingMain.glsl

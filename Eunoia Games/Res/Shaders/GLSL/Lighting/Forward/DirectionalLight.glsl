#vertex
#version 330
#include Res/Shaders/GLSL/Lighting/Forward/LightVS.glsl

#fragment
#version 330

#include Res/Shaders/GLSL/Lighting/Lighting.glsl

uniform DirectionalLight Light;

vec4 CalcForwardRender(vec3 normal, vec3 camPos, vec3 worldPos, vec3 albedo, vec3 specular, float shininess)
{
	return CalcDirectionalLight(Light, normal, camPos, worldPos, albedo, specular, shininess);
}

#include Res/Shaders/GLSL/Lighting/Forward/LightingMain.glsl

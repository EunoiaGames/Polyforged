struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight baseLight;
	vec3 direction;
};

vec4 CalcBaseLight(BaseLight baseLight, vec3 lightDirection, vec3 normal, vec3 camPos, vec3 worldPos, vec3 albedo)
{
	vec3 diffuse = max(dot(normal, lightDirection), 0.0) * baseLight.color * baseLight.intensity;
	return vec4(diffuse * albedo, 1.0);
}

vec4 CalcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 camPos, vec3 worldPos, vec3 albedo)
{
	return CalcBaseLight(directionalLight.baseLight, directionalLight.direction, normal, camPos, worldPos, albedo);
}

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

vec4 CalcBaseLight(BaseLight baseLight, vec3 lightDirection, vec3 normal, vec3 camPos, vec3 worldPos, vec3 albedo, vec3 specular, float shininess)
{
	vec3 diffuse = max(dot(normal, -lightDirection), 0.0) * baseLight.color * baseLight.intensity;
	vec3 viewDirection = normalize(camPos - worldPos);
	vec3 reflectDirection = normalize(reflect(lightDirection, normal));
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
	vec3 specularColor = spec * specular * baseLight.color;
	return vec4((diffuse + specularColor) * albedo, 1.0);
}

vec4 CalcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 camPos, vec3 worldPos, vec3 albedo, vec3 specular, float shininess)
{
	return CalcBaseLight(directionalLight.baseLight, -directionalLight.direction, normal, camPos, worldPos, albedo, specular, shininess);
}

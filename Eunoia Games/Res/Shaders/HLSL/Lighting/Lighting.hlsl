struct BaseLight
{
	float3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight baseLight;
	float3 direction;
};

float4 CalcBaseLight(BaseLight baseLight, float3 lightDirection, float3 normal, float3 camPos, float3 worldPos, float3 albedo,
	float3 specular, float shininess)
{
	float3 diffuse = max(dot(normal, -lightDirection), 0.0) * baseLight.color * baseLight.intensity;
	float3 viewDirection = normalize(camPos - worldPos);
	float3 reflectDirection = normalize(reflect(lightDirection, normal));
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
	float3 specularColor = spec * specular * baseLight.color;
	return float4((diffuse + specularColor) * albedo, 1.0);
}

float4 CalcDirectionalLight(DirectionalLight directionalLight, float3 normal, float3 camPos, float3 worldPos, float3 albedo,
	float3 specular, float shininess)
{
	return CalcBaseLight(directionalLight.baseLight, -directionalLight.direction, normal, camPos, worldPos, albedo, specular, shininess);
}
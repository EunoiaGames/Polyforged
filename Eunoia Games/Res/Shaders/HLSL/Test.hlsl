struct VSInput
{
	float3 pos : POSITION;
	float3 color : COLOR;
};

struct VSOutput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.pos = float4(input.pos.x, input.pos.y, input.pos.z, 1.0);
	output.color = input.color;
	return output;
}

float4 PSMain(VSOutput input) : SV_TARGET0
{
	return float4(input.color.r, input.color.g, input.color.b, 1.0);
}
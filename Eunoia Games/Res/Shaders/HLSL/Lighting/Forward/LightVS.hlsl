struct VSInput
{
	float3 pos : POSITION;
	float3 color : COLOR;
	float3 normal : NORMAL;
};

struct VSOutput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
	float3 normal : NORMAL;
	float3 worldPos : POSITION;
};

cbuffer Transform : register(b0)
{
	float4x4 Model;
};

cbuffer ViewProjection : register(b1)
{
	float4x4 Projection;
	float4x4 View;
}

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.pos = mul(float4(input.pos.x, input.pos.y, input.pos.z, 1.0), Model);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	output.color = input.color;
	output.normal = mul(float4(input.normal, 0.0), Model).xyz;
	output.worldPos = mul(float4(input.pos, 1.0), Model).xyz;
	return output;
}

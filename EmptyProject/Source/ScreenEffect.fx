float3	g_FadeColor;
float	g_FadeValue;

struct VS_INPUT
{
	float4 pos		: POSITION;
	float4 color	: COLOR;
	float2 uv		: TEXCOORD0;
};
struct PS_INPUT
{
	float4 pos		: POSITION;
	float4 color	: COLOR;
	float2 Tex		: TEXCOORD0;
};

PS_INPUT FadeVS( VS_INPUT In)
{
	PS_INPUT Out = (PS_INPUT)0;

	Out.pos = In.pos;
	Out.color = float4(0.f, 0.f, 0.f, 0.f);
	Out.Tex = In.uv;
   return Out;
}
float4 FadePS(PS_INPUT In) : COLOR
{
	return float4(g_FadeColor.xyz, g_FadeValue);
}

technique Fade
{

	pass P0
	{
		AlphaBlendEnable	= True;
		SrcBlend			= SrcAlpha;
		DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 FadeVS();
		PixelShader			= compile ps_2_0 FadePS();
	}
}
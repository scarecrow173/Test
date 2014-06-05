//-------------------------------------------------------------
//!	@brief		: ì¸óÕópÇÃç\ë¢ëÃ
//-------------------------------------------------------------
sampler BlurringTexture : register(s0);
float2	Center = float2(0.f, 0.f);
float	g_BlurPower		= 0.f;
int		g_SamplingNum	= 0;
static const float IMAGE_SIZE = 1024.f;
float radScale							= 50.f;
static const float radOffset			= 0.f;
struct Blur_VS_Input
{
	float4 Pos		: POSITION;
	float2 UV		: TEXCOORD0;
};

struct Blur_PS_Input
{
	float4 Pos		: POSITION;
	float2 UV		: TEXCOORD0;
};

Blur_PS_Input BlurVS(Blur_VS_Input In)
{
	Blur_VS_Input Out = (Blur_VS_Input)0;
	
	Out.Pos = In.Pos;
	Out.UV	= In.UV;

	return Out;
}

float4 BlurPS(Blur_PS_Input In) : COLOR0
{
	float4 Out = float4(0.0f, 0.0f, 0.0f, 0.0f);

//	float2 ss_center = float2( (Center.x + 1.0f) * 0.5f, (-Center.y + 1.0f) * 0.5f );
//	
//	float2 uvOffset = (ss_center - In.UV ) * (g_BlurPower / IMAGE_SIZE);
//	
//
//	float InvSampling = 1.0f / g_SamplingNum;
//
//	float2 uv = In.UV;
//
//	for ( int i = 0; i < g_SamplingNum; ++i )
//	{
//		Out += tex2D( BlurringTexture, uv ) * InvSampling;
//		uv += uvOffset;
//	}
	
	float2 texcoord = In.UV - 0.5f;
	float len		= length(texcoord);
	float rad		= len * g_BlurPower + radOffset;
	float c			= cos(rad);
	float s			= sin(rad);
	texcoord		= mul(texcoord, float2x2(c, -s, s, c)) + 0.5f;
	Out				= tex2D(BlurringTexture, texcoord);

	return Out;
}
technique Blur
{

	pass P0
	{
		//AlphaBlendEnable	= True;
		//SrcBlend			= SrcAlpha;
		//DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 BlurVS();
		PixelShader			= compile ps_3_0 BlurPS();
	}
}

#include "ShadingMath.h"
int	BlendTextureNum = 0;
sampler FinalTexture  : register(s0);
sampler BlendTexture1 : register(s1);
sampler BlendTexture2 : register(s2);
sampler BlendTexture3 : register(s3);
sampler BlendTexture4 : register(s4);
sampler BlendTexture5 : register(s5);

struct BlendMultiTexture_VS_Input
{
	float4 Pos		: POSITION;
	float2 UV		: TEXCOORD0;
};
struct BlendMultiTexture_PS_Input
{
	float4 Pos		: POSITION;
	float2 UV		: TEXCOORD0;
};

BlendMultiTexture_PS_Input BlendMultiTextureVS(BlendMultiTexture_VS_Input In)
{
	BlendMultiTexture_VS_Input Out = (BlendMultiTexture_VS_Input)0;
	Out.Pos = In.Pos;
	Out.UV	= In.UV;
	return Out;
}
float4 BlendMultiTexturePS(BlendMultiTexture_PS_Input In) : COLOR0
{

	float4	Out = tex2D(FinalTexture, In.UV);
	
	if (BlendTextureNum == 0)
		return Out;
	Out += tex2D(BlendTexture1, In.UV);
	
	if (BlendTextureNum == 1)
		return Out;
	Out += tex2D(BlendTexture2, In.UV);
	
	if (BlendTextureNum == 2)
		return Out;
	Out += tex2D(BlendTexture3, In.UV);
	
	if (BlendTextureNum == 3)
		return Out;
	Out += tex2D(BlendTexture4, In.UV);
	
	if (BlendTextureNum == 4)
		return Out;
	Out += tex2D(BlendTexture5, In.UV);

	return Out;
}
technique BlendMultiTexture
{
	pass P0
	{
		AlphaBlendEnable	= False;
		//SrcBlend			= SrcAlpha;
		//DestBlend			= InvSrcAlpha;
		ZEnable				= False;
		VertexShader		= compile vs_2_0 BlendMultiTextureVS();
		PixelShader			= compile ps_3_0 BlendMultiTexturePS();
	}
}
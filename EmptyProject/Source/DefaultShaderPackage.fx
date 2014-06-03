#include "ShadingMath.h"

//-------------------------------------------------------------
//!	@brief		: 入力用の構造体
//-------------------------------------------------------------
struct Default_VS_Input
{
	float3 Pos		: POSITION;
	float3 Normal	: NORMAL;
	float2 UV		: TEXCOORD0;
};

struct Default_PS_Input
{
	float4 Pos		: POSITION;
	float4 Color	: COLOR0;
	float2 UV		: TEXCOORD0;
	float3 Normal	: TEXCOORD1;
	float3 Light	: TEXCOORD2;
	float3 Eye		: TEXCOORD3;
};

//-------------------------------------------------------------
//!	@brief		: バーテックスシェーダは固定(簡単な代わりに無駄がある)
//-------------------------------------------------------------
Default_PS_Input DefaultVS(Default_VS_Input In)
{
	Default_PS_Input Out = (Default_PS_Input)0;

	Out.Pos = mul(float4(In.Pos, 1.f), g_World);
	Out.Pos = mul(Out.Pos, g_View);
	Out.Pos = mul(Out.Pos, g_Projection);

	Out.Normal	= normalize(In.Normal);
	Out.UV		= In.UV;

	Out.Light		= -g_LightDir.xyz;
	Out.Color		= min(dot(Out.Normal, Out.Light), 1.f);
	float3	eyepos	= float3(g_View._41, g_View._42, g_View._43);
	Out.Eye			= eyepos - In.Pos;

	return Out;
}
//-------------------------------------------------------------
//!	@brief		: 各ピクセルシェーダ(ピクセルシェーダの入れ替えでシェーダを入れ替えられる)
//-------------------------------------------------------------
float4 PhongPS(Default_PS_Input In) : COLOR0
{
	float4 Out = (float4)0;

	float3 normal	= normalize(In.Normal);
	float3 eye		= normalize(In.Eye);
	float3 light	= normalize(In.Light);

	Out.rgb = PhongLighting(normal, light, eye, g_Diffuse.xyz, g_Specular.xyz, g_Power) + g_Ambient.xyz; 
	Out.a	= g_Diffuse.a + g_Ambient.a;

	return Out;
}
float4 BlinnPhongPS(Default_PS_Input In) : COLOR0
{
	float4 Out = (float4)0;

	float3 normal	= normalize(In.Normal);
	float3 eye		= normalize(In.Eye);
	float3 light	= normalize(In.Light);

	Out.rgb = BlinnPhongLighting(normal, light, eye, g_Diffuse.xyz, g_Specular.xyz, g_Power) + g_Ambient.xyz; 
	Out.a	= g_Diffuse.a + g_Ambient.a;

	return Out;
}

float4 CookTorrancePS(Default_PS_Input In) : COLOR0
{
	float4 Out = (float4)0;

	float3 normal	= normalize(In.Normal);
	float3 eye		= normalize(In.Eye);
	float3 light	= normalize(In.Light);

	Out.rgb = CookTorranceLighting(normal, light, eye, g_Diffuse.xyz, g_Specular.xyz, g_Power) + g_Ambient.xyz; 
	Out.a	= g_Diffuse.a + g_Ambient.a;

	return Out;
}

float4 LambertPS(Default_PS_Input In) : COLOR0
{
	float4 Out = (float4)0;

	float3 normal	= normalize(In.Normal);
	float3 light	= normalize(In.Light);

	Out.rgb = LambertLighting(normal, light, g_Diffuse.xyz) + g_Ambient.xyz; 
	Out.a	= g_Diffuse.a + g_Ambient.a;

	return Out;
}
float4 HalfLambertPS(Default_PS_Input In) : COLOR0
{
	float4 Out = (float4)0;

	float3 normal	= normalize(In.Normal);
	float3 light	= normalize(In.Light);

	Out.rgb = HalfLambertLighting(normal, light, g_Diffuse.xyz) + g_Ambient.xyz; 
	Out.a	= g_Diffuse.a + g_Ambient.a;

	return Out;
}
//-------------------------------------------------------------
//!	@brief		: デフォルトシェーダテクニック。ピクセルシェーダのみ入れ替え
//				  (Phong,BlinnPhong,CookTorrance,Lambert,HalfLambert)
//-------------------------------------------------------------
technique Phong
{

	pass P0
	{
		AlphaBlendEnable	= True;
		SrcBlend			= SrcAlpha;
		DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 DefaultVS();
		PixelShader			= compile ps_2_0 PhongPS();
	}
}
technique BlinnPhong
{

	pass P0
	{
		AlphaBlendEnable	= True;
		SrcBlend			= SrcAlpha;
		DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 DefaultVS();
		PixelShader			= compile ps_3_0 BlinnPhongPS();
	}
}
technique CookTorrance
{

	pass P0
	{
		AlphaBlendEnable	= True;
		SrcBlend			= SrcAlpha;
		DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 DefaultVS();
		PixelShader			= compile ps_3_0 CookTorrancePS();
	}
}
technique Lambert
{

	pass P0
	{
		AlphaBlendEnable	= True;
		SrcBlend			= SrcAlpha;
		DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 DefaultVS();
		PixelShader			= compile ps_3_0 LambertPS();
	}
}
technique HalfLambert
{

	pass P0
	{
		AlphaBlendEnable	= True;
		SrcBlend			= SrcAlpha;
		DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 DefaultVS();
		PixelShader			= compile ps_3_0 HalfLambertPS();
	}
}
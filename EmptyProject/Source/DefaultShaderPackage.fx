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
struct Velocity_PS_Input
{
	float4	Pos		: POSITION;
	float4	Color	: COLOR0;
	float3	Tex		: TEXCOORD0;
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
Velocity_PS_Input VelocityMapVS(Default_VS_Input In)
{
	Velocity_PS_Input	Out = (Velocity_PS_Input)0;
	float4		now_pos, prev_pos, n;
	float3		vel, norm;
	float		d;
	matrix		matWV, matPrevWV, matWVP, matPrevWVP;

	matWV		= mul(g_World, g_View);
	matPrevWV	= mul(g_PrevWorld, g_View);
	matWVP		= mul(matWV, g_Projection);
	matPrevWVP	= mul(matPrevWV, g_Projection);
	
	// 今回と前回の位置を計算する
	now_pos  = mul(float4(In.Pos.xyz, 1.f), matWV);
	prev_pos = mul(float4(In.Pos.xyz, 1.f), matPrevWV);

	// 速度を求める
	vel.xyz = now_pos.xyz - prev_pos.xyz;

	n.xyz = In.Normal;
	n.w = 0.0f;
	norm.xyz = mul(n, matWV);

	now_pos  = mul(float4(In.Pos.xyz, 1.f), matWVP);
	prev_pos = mul(float4(In.Pos.xyz, 1.f), matPrevWVP);

	// 法線と速度のベクトルの内積から出力する頂点データを決定する
	d = dot(norm, vel);
	d = step(0.0f, d);
	float4	o_pos = d * now_pos + (1.0f - d) * prev_pos;
	Out.Pos = o_pos;

	// カラーに速度を出力する
	now_pos.xy	= now_pos.xy / now_pos.w;
	prev_pos.xy = prev_pos.xy / prev_pos.w;
	Out.Tex.x	= (now_pos.x - prev_pos.x);
	Out.Tex.y	= -(now_pos.y - prev_pos.y);
	Out.Tex.z	= o_pos.z / o_pos.w;

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
	float4 texcolor = tex2D(tex0, In.UV);
	float3 diffuse	= g_Diffuse.xyz + tex2D(tex0, In.UV).rgb;
	float ch = texcolor.r + texcolor.g + texcolor.b;
	if (ch != 0.0)
	{
		diffuse = texcolor.rgb;
		Out.a	= ch;
	}

	Out.rgb = HalfLambertLighting(normal, light, diffuse) + g_Ambient.xyz; 
	Out.a	+= g_Diffuse.a + g_Ambient.a;

	return Out;
}
float4 VelocityMapPS(Velocity_PS_Input In) : COLOR0
{
	float4	Out;

	Out.rgb = In.Tex.xyz;
	Out.a	= 1.0f;
	
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
	pass P1
	{
		ZEnable				= False;
		AlphaBlendEnable	= False;
		VertexShader		= compile vs_2_0 VelocityMapVS();
		PixelShader			= compile ps_2_0 VelocityMapPS();
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
	pass P1
	{
		ZEnable				= False;
		AlphaBlendEnable	= False;
		VertexShader		= compile vs_2_0 VelocityMapVS();
		PixelShader			= compile ps_2_0 VelocityMapPS();
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
	pass P1
	{
		ZEnable				= TRUE;
		AlphaBlendEnable	= False;
		VertexShader		= compile vs_2_0 VelocityMapVS();
		PixelShader			= compile ps_2_0 VelocityMapPS();
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
	pass P1
	{
		ZEnable				= False;
		AlphaBlendEnable	= False;
		VertexShader		= compile vs_2_0 VelocityMapVS();
		PixelShader			= compile ps_2_0 VelocityMapPS();
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
		PixelShader			= compile ps_2_0 HalfLambertPS();
	}
	pass P1
	{
		ZEnable				= False;
		AlphaBlendEnable	= False;
		VertexShader		= compile vs_2_0 VelocityMapVS();
		PixelShader			= compile ps_2_0 VelocityMapPS();
	}
}


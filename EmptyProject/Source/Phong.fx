struct Material
{
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
	float4 Emissive;
	float  Power;
};



float4x4	g_World			;//: register(c0);	// c0~c3
float4x4	g_View			;//: register(c4); // c4~c7
float4x4	g_Projection	;//: register(c8); // c8~c11

float3		g_LightDir	= float3(0.0f, 0.0f, -1.f);	//: register(c12); // c12
float3		g_EyePos		;//: register(c13); // c13

Material	g_Material;

struct Phong_VS_Input
{
	float3 Pos		: POSITION;
	float3 Normal	: NORMAL;
	float2 UV		: TEXCOORD0;
};

struct Phong_PS_Input
{
	float4 Pos		: POSITION;
	float4 Color	: COLOR0;
	float2 UV		: TEXCOORD0;
	float3 Normal	: TEXCOORD1;
	float3 Light	: TEXCOORD2;
	float3 Eye		: TEXCOORD3;
};

Phong_PS_Input PhongVS(Phong_VS_Input In)
{
	Phong_PS_Input Out = (Phong_PS_Input)0;

	Out.Pos = mul(float4(In.Pos, 1.f), g_World);
	Out.Pos = mul(Out.Pos, g_View);
	Out.Pos = mul(Out.Pos, g_Projection);

	
	//Out.Normal	= mul(In.Normal, g_World);
	Out.Normal	= normalize(In.Normal);
	Out.UV		= In.UV;

	Out.Light	= -g_LightDir.xyz;
	Out.Color	= min(dot(Out.Normal, Out.Light), 1.f);
	float3	eyepos = float3(g_View._41, g_View._42, g_View._43);
	Out.Eye		= eyepos - In.Pos;

	return Out;
}

float4 PhongPS(Phong_PS_Input In) : COLOR0
{
	float4 Out = (float4)0;

	float3 normal	= normalize(In.Normal);
	float3 H		= normalize(In.Light + normalize(In.Eye));
	float  S		= pow(max(0.f, dot(normal, H)), 20.f) * 0.75f;

	return (In.Color * g_Material.Diffuse) + S ;

	float diffuseLight	= max(dot(In.Light, normal), 0.f);
	float3 diffuse		= g_Material.Diffuse.xyz * diffuseLight;

	float3 R = -In.Eye + 2.f * dot(normal, In.Eye) * normal;
	float3 specularLight	= pow(max(dot(In.Light, R), 0.f), g_Material.Power);
	float3 specular			= g_Material.Specular.xyz * specularLight;

	float3 R2 = -In.Eye + (2.f * dot(normal, In.Eye) * normal);
//	return float4(g_Material.Diffuse.xyz * (g_Material.Specular.xyz * pow(max(dot(light, R2), 0.2f), g_Material.Power) * ((g_Material.Power + 1.f) / 2.f * 3.1415)), 1.f);

//	return float4(g_Material.Ambient.xyz + diffuse + specular, 1.f);
//	return float4(g_Material.Ambient.xyz, 1.f);


	//float3 N = normalize(In.Normal);

	//float3 H = normalize(In.Light + normalize(In.Eye));

	//float  S = pow(max(0.f, dot(N, H)), g_Material.Power)

}

technique Phong
{

	pass P0
	{
		//AlphaBlendEnable	= True;
		//SrcBlend			= SrcAlpha;
		//DestBlend			= InvSrcAlpha;
		VertexShader		= compile vs_2_0 PhongVS();
		PixelShader			= compile ps_2_0 PhongPS();
	}
}
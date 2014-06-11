float4x4	g_World			;//: register(c0);	// c0~c3
float4x4	g_View			;//: register(c4); // c4~c7
float4x4	g_Projection	;//: register(c8); // c8~c11
float4x4	g_PrevWorld		;//����View��Projection���Œ�Ȃ̂őO��World����

float3		g_LightDir	= float3(0.0f, 0.f, -1.f);	//: register(c12); // c12
float3		g_EyePos	= float3(0.0f, 0.0f, 1.f);//: register(c13); // c13
float		g_Kr		= 0.5f;
float4		g_RimColor	= float4( 1.0f, 1.0f, 1.0f, 1.0f );
//struct Material
//{
	//float4 Diffuse;
	//float4 Ambient;
	//float4 Specular;
	//float4 Emissive;
	//float  Power;
//};
//Material	g_Material;
float4 g_Diffuse;
float4 g_Ambient;
float4 g_Specular;
float4 g_Emissive;
float  g_Power;
sampler tex0 : register(s0);

//----------------------------------------------------------------------------------
// Name : CalculateBeckmann()
// Desc : Beckmann���z�֐��̌v�Z
//----------------------------------------------------------------------------------
float CalculateBeckmann(float m, float cosbeta)
{
	return (exp(- (1 - (cosbeta * cosbeta)) / (m * m * cosbeta * cosbeta)) / (4 * m * m * cosbeta * cosbeta * cosbeta * cosbeta));
}

//----------------------------------------------------------------------------------
// Name : CalculateFresnelTerm()
// Desc : �t���l�����̌v�Z
//----------------------------------------------------------------------------------
float CalculateFresnelTerm(float n, float c)
{
	float g = sqrt(n * n + c * c - 1);
	float T1 = ((g - c) *(g - c)) / ((g + c) * (g + c));
	float T2 = 1 + ((c *(g + c) - 1) * (c * (g + c) - 1) ) / ( (c * (g - c) + 1) * (c * (g - c) + 1));
	return 0.5 * T1 * T2;
}
//---------------------------------------------------------------------
//! @brief �K���}�ϊ����s��
//! @param [in] fLinear ���`�l
//! @return �K���}2.2�ɕϊ������l��ԋp
//---------------------------------------------------------------------
float4 Gamma( float4 fLinear )
{
	return pow( fLinear, 2.2f );
}
//---------------------------------------------------------------------
//! @brief Phong���f���Ń��C�e�B���O����
//! @param [in] N �@���x�N�g��
//! @param [in] L ���C�g�x�N�g��
//! @param [in] V �����x�N�g��
//! @param [in] Kd �f�B�t���[�Y�A���x�h
//! @param [in] Ks �X�y�L�����[�A���x�h
//! @param [in] n ���ʔ��ˋ��x
//---------------------------------------------------------------------
float3 PhongLighting
(
    float3 N,
    float3 L,
    float3 V,
    float3 Kd,
    float3 Ks,
    float  n
)
{
	float3 R = normalize( reflect( N, V ) );
	float3 cosAr = saturate( dot( V, N ) );
	float3 cosAl = saturate( dot( N, L ) );
	float3 C = ( Kd + Ks * ( n + 2 ) * 0.5f * pow( cosAr, n ) ) * cosAl;

	return C;
}
//---------------------------------------------------------------------
//! @brief Blinn-Phong���f���Ń��C�e�B���O����
//! @param [in] N �@���x�N�g��
//! @param [in] L ���C�g�x�N�g��
//! @param [in] V �����x�N�g��
//! @param [in] Kd �f�B�t���[�Y�A���x�h
//! @param [in] Ks �X�y�L�����[�A���x�h
//! @param [in] n ���ʔ��ˋ��x
//---------------------------------------------------------------------
float3 BlinnPhongLighting
( 
    float3 N, 
    float3 L,
    float3 V,
    float3 Kd,
    float3 Ks,
    float  n
)
{
	float3 H = normalize( V + L );
	float3 cosAh = saturate( dot( H, N ) );
	float3 cosAl = saturate( dot( N, L ) );
	float3 C = ( Kd + Ks * ( n + 4 ) * 0.125f * pow( cosAh, n ) ) * cosAl;

	return C;
}
float3 CookTorranceLighting
(
	float3 N,
	float3 L,
	float3 V,
	float3 Kd,
	float3 Ks,
	float  n
)
{
	float3 H = normalize(L + V);

	float NV = dot(N, V);
	float NH = dot(N, H);
	float VH = dot(V, H);
	float NL = dot(N, L);

	float D = CalculateBeckmann(0.35f, NH);
	float G = min(1, min(2 * NH * NV / VH, 2 * NH * NL / VH));
	float F = CalculateFresnelTerm(20.f, dot(L, H));
	float3 diffuse	= Kd * max(dot(L, N), 0);
	float3 specular	= Ks * max(0, F * D * G / NV);
	return (diffuse + specular);
}
float3 LambertLighting
(
	float3 N,
	float3 L,
	float3 Kd
)
{
	float diffuseLight = max(dot(L, N), 0);
	float3 diffuse = Kd * diffuseLight;
	return diffuse;

}
float3 HalfLambertLighting
(
	float3 N,
	float3 L,
	float3 Kd
)
{
	float diffuseLight = max(dot(L, N), 0) * 0.5f + 0.5f;
	float3 diffuse = Kd * (diffuseLight * diffuseLight);
	return diffuse;
}
float3 RimLight(float3 RimColor, float Kr, float3 N, float3 E)
{
	return RimColor * Kr * pow( 1 - dot( N, E), 2.f );
}
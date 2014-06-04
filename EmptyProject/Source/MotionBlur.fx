sampler s1 : register(s0);
sampler s2: register(s1);
float		fBias = 0.001f;		// Z�o�C�A�X
struct VS_INPUT1{
	float4	vPos	: POSITION;
	float2	vTex	: TEXCOORD0;
};
// ���_�V�F�[�_�o��
struct VS_OUTPUT{
	float4	vPos	: POSITION;
	float4	vCol	: COLOR0;
	float3	vTex	: TEXCOORD0;
};
// �ŏI�`��
VS_OUTPUT vsFinal(const VS_INPUT1 v)
{
	VS_OUTPUT	o = (VS_OUTPUT)0;

	// ���W
	o.vPos = v.vPos;

	// �e�N�X�`�����W
	o.vTex.xy = v.vTex.xy;

	return o;
}
float4 psFinalCheckZ(const VS_OUTPUT v) : COLOR
{
	float4	Out;
	float4	vel;
	float4	chkz;
	float2	uv;
	float	div = 1.0f;

	// ���x�����߂�
	vel = tex2D(s2, v.vTex.xy);
	vel.xy /= 3.0f;
	vel.z -= fBias;

	// �e�s�N�Z���̃J���[�����߂�
	Out = tex2D(s1, v.vTex.xy);
	uv = v.vTex.xy + vel.xy;
	chkz = tex2D(s2, uv);
	if(chkz.z >= vel.z){
		div += 1.0f;
		Out += tex2D(s1, uv);
	}
	uv = uv + vel.xy;
	chkz = tex2D(s2, uv);
	if(chkz.z >= vel.z){
		div += 1.0f;
		Out += tex2D(s1, uv);
	}
	uv = uv + vel.xy;
	chkz = tex2D(s2, uv);
	if(chkz.z >= vel.z){
		div += 1.0f;
		Out += tex2D(s1, uv);
	}

	// �ŏI�o�͂����߂�
	return Out / div;
}
technique Tec3_FinalCheckZ
{
	pass P0
	{
		VertexShader = compile vs_2_0 vsFinal();
		PixelShader = compile ps_2_0 psFinalCheckZ();

		ZEnable = False;
		AlphaBlendEnable = False;
	}
}
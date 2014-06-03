//-------------------------------------------------------------
//!	@brief		: ���͗p�̍\����
//-------------------------------------------------------------
sampler BlurringTexture : register(s0);
float2 Center = float2(0.0, 0.0);
float Power = 50.f;
static const float IMAGE_SIZE = 512.0f;

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

	//�@���˒��S
	float2 ss_center = float2( (Center.x + 1.0f) * 0.5f, (-Center.y + 1.0f) * 0.5f );
	
	//�@�I�t�Z�b�g
	float2 uvOffset = (ss_center - In.UV ) * (1.f / IMAGE_SIZE);
	
	//�@�T���v�����O���̋t��
	float InvSampling = 1.0f / 32.0f;

	//�@�e�N�X�`�����W
	float2 uv = In.UV;

	//�@�T���v�����O�̉񐔂������s
	for ( int i = 0; i<32; ++i )
	{
		Out += tex2D( BlurringTexture, uv ) * InvSampling;
		uv += uvOffset;
	}

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

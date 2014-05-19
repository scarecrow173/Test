sampler tex0 : register(s0);

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

PS_INPUT SpectrumVS( VS_INPUT In)
{
	PS_INPUT Out = (PS_INPUT)0;

	Out.pos = In.pos;
	Out.color = In.color;
	Out.Tex = In.uv;
   return Out;
}
float4 SpectrumPS(PS_INPUT In) : COLOR
{
	return In.color; 
	//return tex2D(tex0, In.Tex);// * In.color;
}

technique Spectrum
{
   pass P0
   {
      VertexShader = compile vs_2_0 SpectrumVS();
      PixelShader = compile ps_2_0 SpectrumPS();
	  
   }
}
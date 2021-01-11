SamplerState SampleType;
Texture2D shaderTexture;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : tex;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	textureColor = shaderTexture.Sample(SampleType, input.tex);
	return textureColor;
}

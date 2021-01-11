cbuffer CAMERAPROJ
{
	matrix proj;
	float3 cameraPos;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : tex;
	float2 pos : POS;
	float2 size : SIZE;

};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : tex;
};


PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	input.position.w = 1.0f;

	//matrix scale =
	//	{
	//		{ input.size.x /800, 0, 0, 0 },
	//		{ 0, input.size.y /800, 0, 0 },
	//		{ 0, 0, 1, 0 },
	//		{ 0, 0, 0, 1 }
	//	};
	//matrix translate =
	//{
	//	{ 1, 0, 0, (input.pos.x + input.size.x / 2) * 2 / 800 - 1 },
	//	{ 0, 1, 0, (input.pos.y + input.size.y / 2) * 2 / 800 - 1  },
	//	{ 0, 0, 1, 0 },
	//	{ 0, 0, 0, 1 }
	//};


	input.pos.x -= cameraPos.x;
	input.pos.y -= cameraPos.y;
	//output.position = input.position * float4(input.size, 1, 1) + float4(input.pos, 0, 0);
	//output.position = output.position * float4(input.pos, 1, 1);
	output.position = input.position * float4(input.size, 1, 1) + float4(input.pos + input.size, 0, 0);
	output.position = mul(output.position,proj);

		//matrix world = mul(translate,scale);
	//output.position = mul(world,input.position);

	output.tex = input.tex;
    
	return output;
}

// 0番のテクスチャスロットを使用する
Texture2D g_texture : register(t0);
// 0番のサンプラスロットを使用する
SamplerState g_sampler : register(s0);

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix Trans2D;
    matrix UVMatrix;
    float4 RGBABlend;
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
void VS(
    in float4 inPos : POSITION,
    in float4 inUV : UV,
    out float4 outPos : SV_POSITION,
    out float4 outUV : UV0
) {
    /*
    outPos = mul(inPos, World);
    outPos = mul(outPos, View);
    outPos = mul(outPos, Projection);
    */
    //*
    outPos = mul(inPos, World);
    outPos = mul(outPos, Trans2D);
    /*/
    outPos = inPos;
    //*/
    outUV = mul(inUV, UVMatrix);
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
void PS(
    in float4 inPos : SV_POSITION,
    in float4 inUV : UV0,
    out float4 outColor : SV_TARGET
) {
    //*
    outColor = g_texture.Sample(g_sampler, inUV);
    outColor = outColor * RGBABlend;
    //outColor = outColor * float4(1.0f, 1.0f, 1.0f, 1.0f);
    /*/
    outColor = float4(0.5f, 0.5f, 0.5f, 1.0f);
    //*/
}

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix Trans2D;
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
void VS(
    in float4 inPos : POSITION,
    in float4 inColor : COLOR,
    out float4 outPos : SV_POSITION,
    out float4 outColor : COLOR0
) {
    /*
    outPos = mul(inPos, World);
    outPos = mul(outPos, View);
    outPos = mul(outPos, Projection);*/
    //*
    outPos = mul(inPos, World);
    outPos = mul(outPos, Trans2D);
    /*/
    outPos = inPos;
    //*/
    outColor = inColor;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
void PS(
    in float4 inPos : SV_POSITION,
    in float4 inColor : COLOR0,
    out float4 outColor : SV_TARGET
) {
    outColor = inColor;
    //outColor = float4(1.0f, 0.0f, 0.0f, 0.35f);
}
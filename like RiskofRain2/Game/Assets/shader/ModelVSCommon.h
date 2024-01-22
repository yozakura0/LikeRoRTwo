//モデルの頂点シェーダー関係の共通ヘッダー

// 定数バッファ
// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// 構造体
// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos : POSITION;          //頂点座標。
    float3 normal : NORMAL;         //法線。
    float2 uv : TEXCOORD0;          //UV座標。
    float3 tangent : TANGENT;      //接ベクトル。
    float3 biNormal : BINORMAL;     //従ベクトル。
    int4  Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

// グローバル変数
StructuredBuffer<float4x4> g_boneMatrix         : register(t3);	    //ボーン行列。
StructuredBuffer<float4x4> g_worldMatrixArray   : register(t10);	//ワールド行列の配列。インスタンシング描画の際に有効。

// 関数宣言
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer);

//スキン行列を計算する。
float4x4 CalcSkinMatrix(SVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
    [unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}

// ワールド空間の頂点座標を計算する
float4 CalcVertexPositionInWorldSpace(float4 vertexPos, float4x4 mWorld, uniform bool isUsePreComputedVertexBuffer)
{
    float4 pos;
    if (isUsePreComputedVertexBuffer) {
        pos = vertexPos;
    }
    else {
        pos = mul(mWorld, vertexPos);  // モデルの頂点をワールド座標系に変換
    }

    return pos;
}

// スキンなしメッシュ用の頂点シェーダーのエントリー関数
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, mWorld, false);
}

// スキンなしメッシュ用の頂点シェーダーのエントリー関数(インスタンシング描画用)
SPSIn VSMainInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
    return VSMainCore(vsIn, g_worldMatrixArray[instanceID], false);
}

// スキンありメッシュの頂点シェーダーのエントリー関数
SPSIn VSMainSkin(SVSIn vsIn)
{
    return VSMainCore(vsIn, CalcSkinMatrix(vsIn), false);
}

// スキンありメッシュの頂点シェーダーのエントリー関数(インスタンシング描画用)
SPSIn VSMainSkinInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
    float4x4 mWorldLocal = CalcSkinMatrix(vsIn);
    mWorldLocal = mul(g_worldMatrixArray[instanceID], mWorldLocal);
    return VSMainCore(vsIn, mWorldLocal, false);
}

// 事前計算済みの頂点バッファを使う頂点シェーダーのエントリー関数
// スキンメッシュ用
SPSIn VSMainSkinUsePreComputedVertexBuffer(SVSIn vsIn)
{
    return VSMainCore(vsIn, (float4x4)0, true);
}

// 事前計算済みの頂点バッファを使う頂点シェーダーのエントリー関数
// スキンなしメッシュ用
SPSIn VSMainUsePreComputedVertexBuffer(SVSIn vsIn)
{
    return VSMainCore(vsIn, (float4x4)0, true);
}

// ワールドスペースの法線、接ベクトル、従ベクトルを計算する
void CalcVertexNormalTangentBiNormalInWorldSpace(
    out float3 oNormal,
    out float3 oTangent,
    out float3 oBiNormal,
    float4x4 mWorld,
    float3 iNormal,
    float3 iTangent,
    float3 iBiNormal,
    uniform bool isUsePreComputedVertexBuffer
)
{
    if (isUsePreComputedVertexBuffer) {
        // 事前計算済み頂点バッファを利用する
        oNormal = iNormal;
        oTangent = iTangent;
        oBiNormal = iBiNormal;
    }
    else {
        float3x3 m3x3 = (float3x3)mWorld;
        oNormal = normalize(mul(m3x3, iNormal));
        oTangent = normalize(mul(m3x3, iTangent));
        oBiNormal = normalize(mul(m3x3, iBiNormal));
    }
}
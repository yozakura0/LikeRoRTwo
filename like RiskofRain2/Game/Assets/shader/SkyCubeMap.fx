/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
	float3 tangent	: TANGENT;		//接ベクトル
	float3 biNormal	: BINORMAL;		//従ベクトル
	int4 Indices	: BLENDINDICES0;
	float4 Weights	: BLENDWEIGHT0;
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;
	float3 tangent		: TANGENT;
	float3 biNormal		: BINORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
};
cbuffer SkyCubeCb; register(b1)
{
	float luminance;	//明るさ
}

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normal : register(t1);
Texture2D<float4> g_spacular : register(t2);
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
StructuredBuffer<float4x4> g_worldMatrixArray : register(t10);//ワールド行列の配列。
TextureCube<float4> g_skyCubeMap : register(t10);

sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
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
//ワールド空間の頂点座標を計算する
float4 CalcVertexPositionInWorldSpace(float4 vertexPos, float4x4 mWorld, uniform bool isUsePreComputedVertexBuffer)
{
	float4 pos;
	if (isUsePreComputedVertexBuffer)
	{
		pos = vertexPos;
	}
	else
	{
		pos = mul(mWorld, vertexPos);
	}

	return pos;
}
/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMainSkin( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
//事前計算済みの頂点バッファを使う頂点シェーダーのエントリー関数
//スキンありメッシュ用
SPSIn VSMainSkinUsePreComputedVertwxBuffer(SVSIn vsIn)
{
	return VSMainCore(vsIn, (float4x4)0, true);
}
//事前計算済みの頂点バッファを使う頂点シェーダーのエントリー関数
//スキンなしメッシュ用
SPSIn VSMainUsePreComputedVertwxBuffer(SVSIn vsIn)
{
	return VSMainCore(vsIn, (float4x4)0, true);
}
//ワールドスペースの法線、接ベクトル、従ベクトルを計算する
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
	if (isUsePreComputedVertexBuffer)
	{
		//事前計算済み頂点バッファを利用
		oNormal = iNormal;
		oTangent = iTangent;
		oBiNormal = iBiNormal;
	}
	else
	{
		float3x3 m3x3 = (float3x3)mWorld;
		oNormal = normalize(mul(m3x3, iNormal));
		oTangent = normalize(mul(m3x3, iTangent));
		oBiNormal = normalize(mul(m3x3, iBiNormal));
	}
}
//法線マップから法線を取得
float3 GetNormalFromNormalMap(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
	float3 binSpaceNoemal = g_normal.SampleLevel(g_sampler, uv, 0.0f).xyz;
	binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

	float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

	return newNormal;
}
/// <summary>
/// モデル用頂点シェーダーのエントリーポイント
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;

	//頂点座標をワールド座標に変換する
	psIn.pos = CalcVertexPositionInWorldSpace(vsIn.pos, mWorldLocal, isUsePreComputedVertexBuffer);

	//頂点シェーダーからワールド座標を出力
	psIn.worldPos = (float3)psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//ワールド空間の法線、接ベクトル、従ベクトルを計算する
	CalcVertexNormalTangentBiNormalInWorldSpace(
		psIn.normal,
		psIn.tangent,
		psIn.biNormal,
		mWorldLocal.
		vsIn.normal,
		vsIn.tangent,
		vsIn.biNormal,
		isUsePreComputedVertexBuffer
	);

	psIn.uv = vsIn.uv;

	return psIn;
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor;
	float3 normal = normalize(psIn.normal);
	albedoColor = g_skyCubeMap.Sample(g_sampler, normal * -1.0f) * luminance;

	return albedoColor;
}
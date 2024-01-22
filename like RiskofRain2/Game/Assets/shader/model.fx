/*!
 * @brief	シンプルなモデルシェーダー。
 */

 //シーンのディレクションライトの最大数
static const int MAX_DIRECTIONAL_LIGHT = 1;
//シーンのポイントライトの最大数
static const int MAX_POINT_LIGHT = 8;
//シーンのスポットライトの最大数
static const int MAX_SPOT_LIGHT = 8;

struct DirectionalLig
{
	//ライトの方向
	float3 dirDirection;
	//ライトを使用中か
	float isUse;
	//ライトのカラー
	float3 dirColor;
};

struct PointLig
{
	//ポイントライトの位置
	float3 ptPosition;
	//ライトを使用中か
	float isUse;
	//ポイントライトのカラー
	float3 ptColor;
	//ポイントライトの影響範囲
	float ptRange;
};

struct SpotLig
{
	//位置
	float3 spPosition;
	//ライトを使用中か
	//float isUse;
	//カラー
	float3 spColor;
	//影響範囲
	float spRange;
	//射出方向
	float3 spDirection;
	//射出角度
	float spAngle;
};

struct Light
{
	////ディレクションライト用のデータ
	////ライトの方向
	//float3 dirDirection;
	////ライトのカラー
	//float3 dirColor;

	DirectionalLig directionalLig/*[MAX_DIRECTIONAL_LIGHT]*/;

	////ポイントライト用のデータ
	////ポイントライトの位置
	//float3 ptPosition;
	////ポイントライトのカラー
	//float3 ptColor;
	////ポイントライトの影響範囲
	//float ptRange;

	PointLig pointLig[MAX_POINT_LIGHT];

	////スポットライト用のデータ
	////スポットライトの位置
	//float3 spPosition;
	////スポットライトのカラー
	//float3 spColor;
	////スポットライトの射出範囲
	//float spRange;
	////スポットライトの射出方向
	//float3 spDirection;
	////スポットライトの射出角度
	//float spAngle;

	SpotLig spotLig[MAX_SPOT_LIGHT];

	////半球ライト用のデータ
	////照り返しのライト
	//float3 groundColor;
	////天球ライト
	//float3 skyColor;
	////地面の法線
	//float3 groundNormal;

	//視点の位置
	float3 eyePos;

	//ポイントライトの数
	int numPointLight;
	//float specPow;

	//環境光
	float3 ambientLight;

	//スポットライトの数
	int numSpotLight;
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ライトのデータを受け取る定数バッファ
cbuffer DirectionLightCb : register(b1)
{
	Light light;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;		//接ベクトル
	float3 biNormal	: BINORMAL;		//従ベクトル
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float3 tangent		: TANGENT;		//接ベクトル
	float3 biNormal		: BINORMAL;		//従ベクトル
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	float3 normalInView	: TEXCOORD2;	//カメラ空間の法線
};

//関数を宣言
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal, float2 uv);
float3 CalcLigFromSpotLight(int num, SPSIn psIn, float3 normal);
float3 CalcLigFromPointLight(int num, SPSIn psIn, float3 normal);
float3 CalcLigFromDirectionLight(SPSIn psIn, float3 normal);

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
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

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = vsIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダーに渡す
	psIn.normal = mul(mWorld, vsIn.normal);

	psIn.tangent = normalize(mul(mWorld, vsIn.tangent));
	psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));

	psIn.uv = vsIn.uv;

	//カメラ空間の法線を求める
	psIn.normalInView = mul(mView, psIn.normal);

	return psIn;
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
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//法線マップからタンジェントスペースの法線をサンプリング
	float3 localNormal = g_normalMap.Sample(g_sampler,psIn.uv).xyz;
	//タンジェントスペースの法線を0～1の範囲から-1～1の範囲に復元
	localNormal = (localNormal - 0.5f) * 2.0f;

	float3 normal = psIn.normal;

	//タンジェントスペースの法線をワールドスペースに変換
	normal = psIn.tangent * localNormal.x
		+ psIn.biNormal * localNormal.y
		+ normal * localNormal.z;

	//スペキュラマップから鏡面反射の強さをサンプリング
	//float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;

	//ディレクションライトによるライティングを計算
	float3 directionLig = CalcLigFromDirectionLight(psIn, normal);
	float3 lig = directionLig;

	for (int i = 0; i < MAX_POINT_LIGHT; i++)
	{
	//	if (pointLig[i].isUse == 1)
	//	{
			//ポイントライトによるライティングを計算
		float3 pointLig = CalcLigFromPointLight(i, psIn, normal);
		lig += pointLig;
	//	}
	}

	for (int j = 0; j < MAX_POINT_LIGHT; j++)
	{
		//スポットライトによるライティングを計算
		float3 spotLig = CalcLigFromSpotLight(j, psIn, normal);
		lig += spotLig;
	}

	////サーフェイスの法線と光の入射方向に依存するリムの強さを求める
	//float power1 = 1.0f - max(0.0f, dot(directionalLig.dirDirection, psIn.normal));

	////サーフェイスの法線と視線の方向に依存するリムの強さを求める
	//float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);

	////最終的なリムの強さを求める
	//float limPower = power1 * power2;
	//limPower = pow(limPower, 1.3f);

	////リムライトのカラーを計算
	//float3 limColor = limPower * directionalLig.dirColor;

	////サーフェイスの法線と地面の法線との内積を計算
	//float t = dot(psIn.normal, groundNormal);

	////内積の結果を0～1の範囲に変換する
	//t = (t + 1.0f) / 2.0f;

	////地面色と天球色を補完率tで線形補完
	//float3 hemiLight = lerp(groundColor, skyColor, t);

	//ライトの効果を合わせる
	//float3 lig = directionLig;
	//lig += pointLig;
	//lig += spotLig;
	lig += light.ambientLight;
	//lig += limColor + hemiLight;

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//最終出力カラーに光を乗算
	albedoColor.xyz *= lig;

	return albedoColor;
}

//拡散反射光を計算する
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//ピクセルの法線とライトの方向の内積を計算する
	float t = dot(normal, lightDirection);
	t *= -1.0f;

	//内積の値を0以上の値にする
	t = max(0.0f, t);

	//拡散反射光を計算
	return lightColor * t;
}
//鏡面反射光を計算する
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal, float2 uv)
{
	//反射ベクトルを求める
	float3 refVec = reflect(lightDirection, normal);

	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = light.eyePos - worldPos;
	toEye = normalize(toEye);

	//鏡面反射の強さを求める
	float t = dot(refVec, toEye);

	//鏡面反射の強さを0以上の値にする
	t = max(0.0f, t);

	//鏡面反射の強さを絞る
	t = pow(t, 5.0f);

	//鏡面反射光を求める
	float3 specularLig = lightColor * t;

	//スペキュラマップから鏡面反射の強さをサンプリング
	float specPower = g_specularMap.Sample(g_sampler, uv).r;

	//鏡面反射の強さを鏡面反射光に乗算
	specularLig *= specPower;

	return specularLig;
}

//スポットライトによる反射光を計算
float3 CalcLigFromSpotLight(int num, SPSIn psIn, float3 normal)
{
	//このサーフェイスに入射しているスポットライトの光の向きを計算する
	float3 ligDir = psIn.worldPos - light.spotLig[num].spPosition;

	//正規化して大きさ1のベクトルにする
	ligDir = normalize(ligDir);

	//減衰なしの拡散反射光を計算する
	float3 diffSpot = CalcLambertDiffuse(
		//ライトの方向
		ligDir,
		//ライトのカラー
		light.spotLig[num].spColor,
		//サーフェイスの法線
		/*psIn.*/normal
	);

	//減衰なしの鏡面反射光を計算する
	float3 specSpot = CalcPhongSpecular(
		//ライトの方向
		ligDir,
		//ライトのカラー
		light.spotLig[num].spColor,
		//サーフェイスのワールド座標
		psIn.worldPos,
		//サーフェイスの法線
		psIn.normal,
		//
		psIn.uv
	);

	//距離による影響率を計算する
	//ポイントライトとの距離を計算する
	float3 distance = length(psIn.worldPos - light.spotLig[num].spPosition);

	//影響率は距離に比例して小さくなっていく
	float affect = 1.0f - 1.0f / light.spotLig[num].spRange * distance;

	//影響力がマイナスにならないように補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	//影響の仕方を指数関数的にする
	affect = pow(affect, 3.0f);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	diffSpot *= affect;
	specSpot *= affect;

	//入射光と射出方向の角度を求める
	float angle = dot(ligDir, light.spotLig[num].spDirection);

	angle = abs(acos(angle));

	//角度に比例して小さくなっていく影響率を計算する
	affect = 1.0f - 1.0f / light.spotLig[num].spAngle * angle;

	//影響率がマイナスにならないよう補正する
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	//影響の仕方を指数関数的にする
	affect = pow(affect, 0.5f);

	//角度による影響率を反射光に乗算して、影響を弱める
	diffSpot *= affect;
	specSpot *= affect;

	return diffSpot + specSpot;
}

//ポイントライトによる反射光を計算
float3 CalcLigFromPointLight(int num, SPSIn psIn, float3 normal)
{
	//このサーフェイスに入射しているポイントライトの光の向きを計算する
	float3 ligDir = psIn.worldPos - light.pointLig[num].ptPosition;

	//正規化して大きさ1のベクトルにする
	ligDir = normalize(ligDir);

	//減衰なしの拡散反射光を計算する
	float3 diffPoint = CalcLambertDiffuse(
		//ライトの方向
		ligDir,
		//ライトのカラー
		light.pointLig[num].ptColor,
		//サーフェイスの法線
		/*psIn.*/normal
	);

	//減衰なしの鏡面反射光を計算する
	float3 specPoint = CalcPhongSpecular(
		//ライトの方向
		ligDir,
		//ライトのカラー
		light.pointLig[num].ptColor,
		//サーフェイスのワールド座標
		psIn.worldPos,
		//サーフェイスの法線
		psIn.normal,
		//
		psIn.uv
	);

	//距離による影響率を計算する
	//ポイントライトとの距離を計算する
	float3 distance = length(psIn.worldPos - light.pointLig[num].ptPosition);

	//影響率は距離に比例して小さくなっていく
	float affect = 1.0f - 1.0f / light.pointLig[num].ptRange * distance;

	//影響力がマイナスにならないように補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}

	//影響の仕方を指数関数的にする
	affect = pow(affect, 3.0f);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	diffPoint *= affect;
	specPoint *= affect;

	return diffPoint + specPoint;
}

//ディレクションライトによる反射光を計算
float3 CalcLigFromDirectionLight(SPSIn psIn, float3 normal)
{
	//拡散反射光を計算する
	float3 diffDirection = CalcLambertDiffuse(light.directionalLig.dirDirection, light.directionalLig.dirColor, /*psIn.*/normal);

	//鏡面反射光を計算する
	float3 specDirection = CalcPhongSpecular(light.directionalLig.dirDirection, light.directionalLig.dirColor, psIn.worldPos, psIn.normal, psIn.uv);

	return diffDirection + specDirection;
}
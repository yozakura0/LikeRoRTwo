/*!
 * @brief	ブルーム。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
cbuffer Cb : register(b0)
{
	float4x4 mvp;
	float4 mulColor;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//頂点シェーダーへの入力。
struct VSInput{
	float4 pos 		: POSITION;		//モデルの頂点座標
	float2 uv 		: TEXCOORD0;	//UV座標
};
//ピクセルシェーダーへの入力。
struct PSInput{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 			: TEXCOORD0;	//uv座標。
};

//頂点シェーダー
PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
//メインレンダリングターゲットのテクスチャ
Texture2D<float4> mainRenderTargetTexture : register(t0);

//ボケ画像にアクセスするための変数を追加
Texture2D<float4> g_bokeTexture_0 : register(t0);
Texture2D<float4> g_bokeTexture_1 : register(t1);
Texture2D<float4> g_bokeTexture_2 : register(t2);
Texture2D<float4> g_bokeTexture_3 : register(t3);

//サンプラーステート
sampler Sampler : register(s0);

////////////////////////////////////////////////
// 輝度抽出
////////////////////////////////////////////////
float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
	//メインレンダリングターゲットからカラーをサンプリング
	float4 color = mainRenderTargetTexture.Sample(Sampler,In.uv);

	//サンプリングしたカラーの明るさを計算
	float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));

	//カラーの明るさが1以下ならピクセルキル
	clip(t - 1.0f);
	return color;
}

float4 PSBloomFinal(PSInput In) : SV_Target0
{
	//ボケ画像ををサンプリングして、平均をとって出力する
	float4 combineColor = g_bokeTexture_0.Sample(Sampler,In.uv);
	combineColor += g_bokeTexture_1.Sample(Sampler, In.uv);
	combineColor += g_bokeTexture_2.Sample(Sampler, In.uv);
	combineColor += g_bokeTexture_3.Sample(Sampler, In.uv);

	combineColor /= 4.0f;
	combineColor.a = 1.0f;

	return combineColor;
}
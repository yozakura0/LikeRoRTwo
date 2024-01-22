//ポイントライトの最大数
static const int MAX_POINT_LIGHT = 256;
//スポットライトの最大数
static const int MAX_SPOT_LIGHT = 256;
//ディレクションライトの最大数
static const int MAX_DIRECTIONAL_LIGHT = 4;


//ディレクションライトの構造体
struct DirectionLight
{
	//ライトの方向
	float3 direction;
	//影をキャストするか
	int castShadow;
	//ライトの色
	float4 color;
};

//ポイントライトの構造体
struct PointLight
{
	//座標
	float3 position;
	//カメラ空間の座標
	float3 positionInView;
	//色
	float3 color;
	//減衰のパラメータ
	float3 attn;
};

//スポットライトの構造体
struct SpotLight
{
	//座標
	float3 position;
	//使用中かのフラグ
	int inUse;
	//カメラ空間の座標
	float3 positionInView;
	//ライトの番号
	int no;
	//射出方向
	float3 direction;
	//影響範囲
	float range;
	//1つ目の色
	float3 color;
	//2つ目の色
	float3 color2;
	//3つ目の色
	float3 color3;
	//カメラ空間での射出方向
	float3 directionInView;
	//距離による光の影響率に累乗するパラメータ
	float3 rangePow;
	//射出角度
	float3 angle;
	//スポットライトとの角度による光の影響率に累乗するパラメータ
	float3 anglePow;
};

//ライトのデータをまとめた構造体
struct Light
{
	//ディレクションライト
	DirectionLight directionalLight;
	//ポイントライト
	PointLight pointLight;
	//スポットライト
	SpotLight spotLight;
	//ビュープロジェクション行列の逆行列
	float4x4 mViewProjInv;
	//カメラの視点
	float3 eyePos;
	//ポイントライトの数
	int numPointLight;
	//環境光
	float3 ambientLight;
	//スポットライトの数
	int numSpotLight;
};
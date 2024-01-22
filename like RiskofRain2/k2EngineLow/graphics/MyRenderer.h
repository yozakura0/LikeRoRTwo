#pragma once

namespace nsK2EngineLow {

	//シーンのディレクションライトの最大数
	const int MAX_DIRECTIONAL_LIGHT = 1;
	//シーンのポイントライトの最大数
	const int MAX_POINT_LIGHT = 8;
	//シーンのスポットライトの最大数
	const int MAX_SPOT_LIGHT = 8;
	
	const int NUM_SHADOW_MAPS = 3;
	
	//シャドウマップ
	enum
	{
		SHADOW_MAP_AREA_NEAR,		//近影範囲のシャドウマップ
		SHADOW_MAP_AREA_MIDDLE,		//中影範囲のシャドウマップ
		SHADOW_MAP_AREA_FAR,		//遠影範囲のシャドウマップ
		
	};
}
#pragma once

namespace nsK2EngineLow {

	class IRenderer : public Noncopyable 
	{
	public:
		//シャドウマップへの描画パスから呼ばれる処理
		virtual void OnRenderShadowMap(
			RenderContext& rc
		)
		{

		}

		//2D描画への描画パスから呼ばれる処理
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		//レンダラーが描画するオブジェクトの最大座標と最小座標を取得
		virtual void GetAABB(Vector3& vMax, Vector3& vMin, bool& isGet)
		{
			vMax.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			vMin.Set(FLT_MAX, FLT_MAX, FLT_MAX);
			isGet = false;
		}
	};
}
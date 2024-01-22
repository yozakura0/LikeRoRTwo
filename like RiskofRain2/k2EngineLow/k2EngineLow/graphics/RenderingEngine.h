#pragma once
//#include "IRenderer.h"
//#include "Light/SceneLight.h"

namespace nsK2EngineLow {

	class ModelRender;

	class RenderingEngine :public Noncopyable
	{
	public:
		//ディファードライティング用の定数バッファ
		//struct SDeferredLightingCB
		//{
		//	/*Light m_light;*/
		//	
		//};

		//メインレンダリングターゲットのスナップショット
		enum class EnMainRTSnapshot
		{
			//不透明オブジェクトの描画完了時点
			enDrawnOpacity,
			//スナップショットの数
			enNum
		};

		//レンダリングパス
		enum class EnRenderingPass
		{
			//アニメーション済み頂点計算
			enomComputeAnimatedVertex,
			//シャドウマップへの描画パス
			enRenderToShadowMap,
			//ZPrepass
			enZPrepass,
			//G-Bufferへの描画パス
			enRenderToGBuffer,
			//フォワードレンダリングの描画パス
			enForwardRender,
			//2D描画
			enRender2D
		};

		//イベント
		enum EnEvent
		{
			//IBLテクスチャの再初期化
			enEventReInitIBLTexture
		};

		/*RenderingEngine();
		~RenderingEngine();*/

		void Init();

		//void Update();

		//描画オブジェクトを追加
		/*void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}*/

		/*Texture& GetLuminanceAvgTextureInScene()
		{
			return m_postEffect.GetLuminanceAvgTextureInScene();
		}*/

		//イベントリスナーを追加
		void AddEventListener(void* pListenerObj,std::function<void(EnEvent enEvent)> listenerFunc)
		{
			m_eventListeners.push_back({ pListenerObj,listenerFunc });
		}

		//std::vector< IRenderer* > m_renderObjects;
	private:
		//シーンライト
		//SceneLight m_sceneLight;

		//イベントリスナーのデータ
		struct SEventListenerData
		{
			//リスナーオブジェクト
			void* pListenerObj;
			std::function<void(EnEvent enEvent)> listenerfunc;
		};

		//イベントリスナー
		std::list<SEventListenerData> m_eventListeners;
	};
}
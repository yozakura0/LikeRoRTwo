#pragma once
#include "MyRenderer.h"
#include "IRenderer.h"
#include "Light/SceneLight.h"
#include "postEffect/Bloom.h"
#include "shadow/ShadowProjection.h"

namespace nsK2EngineLow {

	class SceneLight;
	class ModelRender;
	class Bloom;
	class ShadowProjection;

	class RenderingEngine :public Noncopyable
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void Init();

		void SetRenderTarget(RenderContext& rc);

		void Update();

		void Execute(RenderContext& rc);

		//描画オブジェクトを追加
		void AddRenderObject(Model& model)
		{
			m_renderObjects.push_back(&model);
		}

		//影用のオブジェクトを追加
		void AddRenderObjectToShadow(Model& model)
		{
			m_renderObjectsToShadow.push_back(&model);
		}

		//2Dの描画オブジェクトを追加
		void AddRenderObject2D(IRenderer* obj2D)
		{
			m_renderObjectsTo2D.push_back(obj2D);
		}

		//メインレンダリングターゲット
		RenderTarget m_mainRenderTarget;

		//シャドウマップ
		RenderTarget m_shadowMap;

		//2Dのレンダリングターゲット
		RenderTarget m_2DRenderTarget;

		//ライトカメラ
		Camera m_lightCamera;

		//輝度抽出用のスプライトデータ
		SpriteInitData m_luminanceSpriteInitData;
		//輝度抽出用のスプライト
		Sprite m_luminanceSprite;

		//ボケ画像を合成して書き込むためのスプライトデータ
		SpriteInitData m_finalSpriteInitData;
		//ボケ画像を合成して書き込むためのスプライト
		Sprite m_finalSprite;

		//ガウシアンブラー
		GaussianBlur m_gaussianBlur[4];
	private:
		//シャドウマップに描画
		void RenderToShadowMap(RenderContext& rc);

		//2Dのレンダリングターゲットに描画
		void RenderTo2DRenderTarget(RenderContext& rc);

		//メインレンダリングターゲットの初期化
		void InitMainRenderTarget();

		//シャドウマップへの描画処理を初期化
		//void InitCascadeShadow();

		//シャドウマップへの描画処理を初期化
		void InitShadowMap();

		//2Dのレンダリングターゲットの初期化
		void Init2DRenderTarget();
		
		//メインレンダリングターゲットのカラーバッファの情報を
		//フレームバッファにコピーするためのスプライトを初期化
		void InitCopyMainRenderTargetToFrameBufferSprite();

		//メインレンダリングターゲットの情報をフレームバッファにコピーする処理
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		//メインレンダリングターゲット
		//RenderTarget m_mainRenderTarget;
		//メインレンダリングターゲットをフレームバッファにコピーするためのスプライト
		Sprite m_copyToFrameBufferSprite;

		//2D合成用のスプライト
		Sprite m_2DSprite;
		Sprite m_mainSprite;

		//シャドウマップを映すスプライト
		//Sprite m_shadowSprite;
		
		Bloom m_bloom;

		ShadowProjection m_shadowProj;
		
		//シーンライト
		SceneLight m_sceneLight;

		Light m_light;


		//描画オブジェクトのリスト
		std::vector<Model*> m_renderObjects;

		//影用の描画オブジェクトのリスト
		std::vector<Model*> m_renderObjectsToShadow;

		//2D用の描画オブジェクトのリスト
		std::vector<IRenderer*> m_renderObjectsTo2D;
	};
}
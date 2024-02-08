#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"
#include "Light/SceneLight.h"

namespace nsK2EngineLow {
	
	RenderingEngine::RenderingEngine()
	{
		g_sceneLight = &m_sceneLight;
	}
	RenderingEngine::~RenderingEngine()
	{
		g_sceneLight = nullptr;
	}

	void RenderingEngine::Init()
	{
		InitMainRenderTarget();
		InitShadowMap();
		Init2DRenderTarget();

		InitCopyMainRenderTargetToFrameBufferSprite();

		m_bloom.BloomInit(m_mainRenderTarget);


		/*SpriteInitData shadowSpriteInitData;
		shadowSpriteInitData.m_textures[0] = &m_shadowMap.GetRenderTargetTexture();
		shadowSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		shadowSpriteInitData.m_width = 256;
		shadowSpriteInitData.m_height = 256;

		m_shadowSprite.Init(shadowSpriteInitData);*/
	}

	void RenderingEngine::InitMainRenderTarget()
	{
		m_mainRenderTarget.Create(
			1920,
			1080,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	//void RenderingEngine::InitCascadeShadow()
	//{
	//	///*auto&& shadowMapRender = m_shadowMapRenders;*/
	//	//for (int shadowNum = 0; shadowNum < MAX_DIRECTIONAL_LIGHT; shadowNum++)
	//	//{
	//	//	m_shadowMapRenders[shadowNum].Init();
	//	//}

	//	for (auto& shadowMapRender: m_shadowMapRenders)
	//	{
	//		shadowMapRender.Init();
	//	}
	//}

	void RenderingEngine::InitShadowMap()
	{
		m_shadowProj.Start();
	}

	void RenderingEngine::Init2DRenderTarget()
	{
		m_2DRenderTarget.Create(
			1920,
			1080,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);


		SpriteInitData spriteInitData;

		spriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();

		spriteInitData.m_width = m_mainRenderTarget.GetWidth();
		spriteInitData.m_height = m_mainRenderTarget.GetHeight();

		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSMain";

		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;

		spriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();

		m_2DSprite.Init(spriteInitData);

		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

		spriteInitData.m_width = m_2DRenderTarget.GetWidth();
		spriteInitData.m_height = m_2DRenderTarget.GetHeight();

		spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();

		m_mainSprite.Init(spriteInitData);
	}

	void RenderingEngine::SetRenderTarget(RenderContext& rc)
	{
		//メインレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_mainRenderTarget);
	}

	void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
	{
		SpriteInitData spriteInitData;

		// テクスチャはmainRenderTargetのカラーバッファー
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

		spriteInitData.m_width = 1920;
		spriteInitData.m_height = 1080;

		// モノクロ用のシェーダーを指定する
		spriteInitData.m_fxFilePath = "Assets/shader/sample2D.fx";

		// 初期化オブジェクトを使って、スプライトを初期化する
		m_copyToFrameBufferSprite.Init(spriteInitData);
	}

	/*void RenderingEngine::Update()
	{
		

		luminanceRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}*/

	void RenderingEngine::Execute(RenderContext& rc)
	{
		/*m_bloom.SetSpriteData();
		m_bloom.LuminanceExtraction(rc);
		m_bloom.Execute(rc);*/
		
		RenderToShadowMap(rc);

		SetRenderTarget(rc);

		for (auto& model : m_renderObjects)
		{
			model->Draw(rc);
		}

		m_bloom.BloomRender(rc, m_mainRenderTarget);

		//RenderTo2DRenderTarget(rc);
		for (auto& obj2D : m_renderObjectsTo2D)
		{
			obj2D->OnRender2D(rc);
		}

		//エフェクトを描画
		EffectEngine::GetInstance()->Draw();

		CopyMainRenderTargetToFrameBuffer(rc);

		//shadowSprite.Update({ FRAME_BUFFER_W / -2.0f,FRAME_BUFFER_H / 2.0f,0.0f }, g_quatIdentity, g_vec3One, { 0.0f,1.0f });
		//shadowSprite.Draw(rc);

		m_renderObjects.clear();
		m_renderObjectsToShadow.clear();
		m_renderObjectsTo2D.clear();
	}

	void RenderingEngine::RenderToShadowMap(RenderContext& rc)
	{
		m_light = g_sceneLight->GetSceneLight();

		//シャドウマップに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_shadowMap);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_shadowMap);

		for (auto& model : m_renderObjectsToShadow)
		{
			model->Draw(rc, m_lightCamera);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		/*int ligNo = 0;
		for (auto& shadowMapRender: m_shadowMapRenders)
		{
			shadowMapRender.Render(
				rc,
				m_light.directionalLight.dirDirection
			);
			ligNo++;
		}*/


	}

	void RenderingEngine::RenderTo2DRenderTarget(RenderContext& rc)
	{
		//2Dレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_2DRenderTarget);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_2DRenderTarget);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_2DRenderTarget);

		m_mainSprite.Draw(rc);

		for (auto& obj2D : m_renderObjectsTo2D)
		{
			obj2D->OnRender2D(rc);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_2DRenderTarget);

		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);

		m_2DSprite.Draw(rc);

		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToFrameBufferSprite.Draw(rc);
	}
}
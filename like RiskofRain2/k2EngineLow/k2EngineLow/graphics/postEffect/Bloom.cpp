#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow {
	void Bloom::OnInit(
		/*RenderTarget& mainRenderTarget,
		RenderTarget& zprepassRenderTarget,
		RenderTarget& normalRenderTarget,
		RenderTarget& metallicSmoothRenderTarget,
		RenderTarget& albedoRenderTarget*/
	)
	{
		m_luminanceRenderTarget.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			DXGI_FORMAT_UNKNOWN
		);

		SpriteInitData luminanceSpriteInitData;

		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/bloom.fx";
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		luminanceSpriteInitData.m_expandConstantBuffer = &m_samplingLuminanceCB1;
		luminanceSpriteInitData.m_expandConstantBufferSize = sizeof(m_samplingLuminanceCB1);

		luminanceSpriteInitData.m_width = mainRenderTarget.GetWidth();
		luminanceSpriteInitData.m_height = mainRenderTarget.GetHeight();

		luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

		//luminanceSpriteInitData.m_textures[1]=&g_renderingEngine->

		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_luminanceSprite.Init(luminanceSpriteInitData);

		//ガウシアンブラーを初期化
		m_gaussianBlur.Init(&m_luminanceRenderTarget.GetRenderTargetTexture());

		//ボケ画像を加算合成するスプライトを初期化
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur.GetBokeTexture();

		finalSpriteInitData.m_width = mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = mainRenderTarget.GetHeight();

		finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_finalSprite.Init(finalSpriteInitData);

		//テクスチャを貼り付けるためのスプライトを初期化
		spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = mainRenderTarget.GetWidth();
		spriteInitData.m_height = mainRenderTarget.GetHeight();

		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void Bloom::OnRender(RenderContext& rc/*, RenderTarget& mainRenderTarget*/)
	{
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		rc.ClearRenderTargetView(mainRenderTarget);

		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
		rc.ClearRenderTargetView(m_luminanceRenderTarget);
		m_luminanceSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);

		m_gaussianBlur.ExecuteOnGPU(rc, 20);

		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		m_finalSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		copyToFrameBufferSprite.Draw(rc);
	}
}
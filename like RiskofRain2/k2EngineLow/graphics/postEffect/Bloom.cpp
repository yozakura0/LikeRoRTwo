#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow
{
	void Bloom::BloomInit(
		RenderTarget& mainRenderTarget
	)
	{
		m_luminanceRenderTarget.Create(
			1920,
			1080,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		SpriteInitData luminanceSpriteInitData;

		//輝度抽出用のシェーダーのファイルパスを指定
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/bloom.fx";

		//頂点シェーダのエントリーポイントを指定
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

		//ピクセルシェーダーのエントリーポイントを指定
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";

		//スプライトの幅と高さを設定
		luminanceSpriteInitData.m_width = 1920;
		luminanceSpriteInitData.m_height = 1080;

		//テクスチャはメインレンダリングターゲットのカラーバッファ
		luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

		//書き込むレンダリングターゲットのフォーマットを指定
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//作成した初期化情報をもとにスプライトを初期化
		m_luminanceSprite.Init(luminanceSpriteInitData);


		//gaussianBlur[0]は輝度テクスチャにガウシアンブラーをかける
		m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());

		//gaussianBlur[1]はgaussianBlur[0]のテクスチャにガウシアンブラーをかける
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());

		//gaussianBlur[2]はgaussianBlur[1]のテクスチャにガウシアンブラーをかける
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());

		//gaussianBlur[3]はgaussianBlur[2]のテクスチャにガウシアンブラーをかける
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		//最終合成用のスプライトを初期化
		SpriteInitData finalSpriteInitData;

		//ボケテクスチャを4枚指定
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();

		//解像度を設定
		finalSpriteInitData.m_width = 1920;
		finalSpriteInitData.m_height = 1080;

		//シェーダーを指定
		finalSpriteInitData.m_fxFilePath = "Assets/shader/bloom.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		//アルファブレンディングモードを加算にする
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		//カラーバッファのフォーマットを設定
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//初期化情報をもとに加算合成用のスプライトを初期化
		m_finalSprite.Init(finalSpriteInitData);
	}

	//void Bloom::LuminanceExtraction(RenderContext& rc)
	//{
	//	//輝度抽出用のレンダリングターゲットに変更
	//	rc.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);

	//	//レンダリングターゲットを設定
	//	rc.SetRenderTargetAndViewport(luminanceRenderTarget);

	//	//レンダリングターゲットをクリア
	//	rc.ClearRenderTargetView(luminanceRenderTarget);

	//	//輝度抽出を行う
	//	g_renderingEngine->luminanceSprite.Draw(rc);

	//	//レンダリングターゲットへの書き込み終了待ち
	//	rc.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
	//}

	//void Bloom::Execute(RenderContext& rc)
	//{
	//	//ガウシアンブラーを4回実行
	//	g_renderingEngine->gaussianBlur[0].ExecuteOnGPU(rc, 10);
	//	g_renderingEngine->gaussianBlur[1].ExecuteOnGPU(rc, 10);
	//	g_renderingEngine->gaussianBlur[2].ExecuteOnGPU(rc, 10);
	//	g_renderingEngine->gaussianBlur[3].ExecuteOnGPU(rc, 10);

	//	//レンダリングターゲットとして利用できるまで待つ
	//	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);

	//	//レンダリングターゲットを設定
	//	rc.SetRenderTargetAndViewport(mainRenderTarget);

	//	//最終合成
	//	g_renderingEngine->finalSprite.Draw(rc);

	//	//レンダリングターゲットへの書き込み終了待ち
	//	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	//}

	void Bloom::BloomRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//輝度抽出用のレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_luminanceRenderTarget);

		//輝度抽出を行う
		m_luminanceSprite.Draw(rc);

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);


		//ガウシアンブラーを4回実行
		m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(mainRenderTarget);

		//最終合成
		m_finalSprite.Draw(rc);

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	}
}
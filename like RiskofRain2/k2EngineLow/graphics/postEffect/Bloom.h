#pragma once

namespace nsK2EngineLow
{

	class Bloom : public Noncopyable
	{
	public:
		//ブルームに必要な情報の初期化
		void BloomInit(
		RenderTarget& mainRenderTarget
		);

		////輝度抽出の処理
		//void LuminanceExtraction(RenderContext& rc);

		////ブルームの実行
		//void Execute(RenderContext& rc);

		//ブルームの描画
		void BloomRender(RenderContext& rc, RenderTarget& mainRenderTarget);

		//ブルームを実行した結果のテクスチャを取得
		Texture& GetBloomResultTexture()
		{
			return m_luminanceRenderTarget.GetRenderTargetTexture();
		}


	private:
		//ガウシアンブラー
		GaussianBlur m_gaussianBlur[4];

		//輝度抽出用のレンダリングターゲット
		RenderTarget m_luminanceRenderTarget;

		//輝度抽出用のスプライト
		Sprite m_luminanceSprite;

		//ボケ画像を合成して書き込むためのスプライト
		Sprite m_finalSprite;

	};

}
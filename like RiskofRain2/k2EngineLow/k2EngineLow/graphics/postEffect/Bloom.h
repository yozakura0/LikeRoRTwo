#pragma once

namespace nsK2EngineLow {

	class Bloom
	{
	public:
		void OnInit(
			/*RenderTarget& mainRenderTarget,
			RenderTarget& zprepassRenderTarget,
			RenderTarget& normalRenderTarget,
			RenderTarget& metallicSmoothRenderTarget,
			RenderTarget& albedoRenderTarget*/
		);

		void OnRender(RenderContext& rc/*, RenderTarget& mainRenderTarget*/);

		Texture& GetResultTexture()
		{
			return m_luminanceRenderTarget.GetRenderTargetTexture();
		}

	private:
		struct SSamplingLuminanceCB1 {
			int isTonemap;
			float moddlegrey;
		};

		RenderTarget& mainRenderTarget;
		RenderTarget& zprepassRenderTarget;
		RenderTarget& normalRenderTarget;
		RenderTarget& metallicSmoothRenderTarget;
		RenderTarget& albedoRenderTarget;
		RenderTarget m_luminanceRenderTarget;
		Sprite m_luminanceSprite;
		Sprite m_finalSprite;
		Sprite copyToFrameBufferSprite;
		SSamplingLuminanceCB1 m_samplingLuminanceCB1;
		SpriteInitData spriteInitData;
		GaussianBlur m_gaussianBlur;
	};

}
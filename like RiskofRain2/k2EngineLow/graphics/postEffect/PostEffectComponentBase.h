#pragma once

namespace nsK2EngineLow {
	class PostEffectComponentBase :public Noncopyable
	{
	public:
		void Init(
			RenderTarget& mainRenderTarget
		);

		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		void Disable()
		{
			m_isEnable = false;
		}

		void Enable()
		{
			m_isEnable = true;
		}

		bool IsEnable() const
		{
			return m_isEnable;
		}

	private:
		virtual void OnInit(
			RenderTarget& mainRenderTarget,
			RenderTarget& zprepassRenderTarget,
			RenderTarget& normalRenderTarget,
			RenderTarget& metallicSmoothRenderTarget,
			RenderTarget& albedoRenderTarget
		) = 0;

		virtual void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) = 0;

	private:
		bool m_isEnable = true;
		Sprite m_copyMainRtSprite;
	};
}
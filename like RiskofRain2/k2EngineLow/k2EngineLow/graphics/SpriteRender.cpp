#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	void SpriteRender::Init(const char* filepath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData initData;
		//DDSファイルのパスを指定する
		initData.m_ddsFilePath[0] = filepath;
		//Sprite表示用のシェーダーのファイルパスを指定する
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		//スプライトの幅と高さを指定する
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);

		//半透明描画をするか設定する
		initData.m_alphaBlendMode = alphaBlendMode;

		//Sprite初期化オブジェクトを使って、Spriteを初期化
		m_sprite.Init(initData);
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		//g_renderingEngine->AddRenderObject(this);

		m_sprite.Draw(rc);
	}
}

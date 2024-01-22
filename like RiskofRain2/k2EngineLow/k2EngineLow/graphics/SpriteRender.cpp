#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	void SpriteRender::Init(const char* filepath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData initData;
		//DDS�t�@�C���̃p�X���w�肷��
		initData.m_ddsFilePath[0] = filepath;
		//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		//�X�v���C�g�̕��ƍ������w�肷��
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);

		//�������`������邩�ݒ肷��
		initData.m_alphaBlendMode = alphaBlendMode;

		//Sprite�������I�u�W�F�N�g���g���āASprite��������
		m_sprite.Init(initData);
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		//g_renderingEngine->AddRenderObject(this);

		m_sprite.Draw(rc);
	}
}

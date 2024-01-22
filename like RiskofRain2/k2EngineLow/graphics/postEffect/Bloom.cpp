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

		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w��
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/bloom.fx";

		//���_�V�F�[�_�̃G���g���[�|�C���g���w��
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w��
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";

		//�X�v���C�g�̕��ƍ�����ݒ�
		luminanceSpriteInitData.m_width = 1920;
		luminanceSpriteInitData.m_height = 1080;

		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@
		luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

		//�������ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w��
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�쐬�����������������ƂɃX�v���C�g��������
		m_luminanceSprite.Init(luminanceSpriteInitData);


		//gaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������
		m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());

		//gaussianBlur[1]��gaussianBlur[0]�̃e�N�X�`���ɃK�E�V�A���u���[��������
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());

		//gaussianBlur[2]��gaussianBlur[1]�̃e�N�X�`���ɃK�E�V�A���u���[��������
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());

		//gaussianBlur[3]��gaussianBlur[2]�̃e�N�X�`���ɃK�E�V�A���u���[��������
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		//�ŏI�����p�̃X�v���C�g��������
		SpriteInitData finalSpriteInitData;

		//�{�P�e�N�X�`����4���w��
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();

		//�𑜓x��ݒ�
		finalSpriteInitData.m_width = 1920;
		finalSpriteInitData.m_height = 1080;

		//�V�F�[�_�[���w��
		finalSpriteInitData.m_fxFilePath = "Assets/shader/bloom.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		//�A���t�@�u�����f�B���O���[�h�����Z�ɂ���
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		//�J���[�o�b�t�@�̃t�H�[�}�b�g��ݒ�
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�������������Ƃɉ��Z�����p�̃X�v���C�g��������
		m_finalSprite.Init(finalSpriteInitData);
	}

	//void Bloom::LuminanceExtraction(RenderContext& rc)
	//{
	//	//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
	//	rc.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);

	//	//�����_�����O�^�[�Q�b�g��ݒ�
	//	rc.SetRenderTargetAndViewport(luminanceRenderTarget);

	//	//�����_�����O�^�[�Q�b�g���N���A
	//	rc.ClearRenderTargetView(luminanceRenderTarget);

	//	//�P�x���o���s��
	//	g_renderingEngine->luminanceSprite.Draw(rc);

	//	//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	//	rc.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
	//}

	//void Bloom::Execute(RenderContext& rc)
	//{
	//	//�K�E�V�A���u���[��4����s
	//	g_renderingEngine->gaussianBlur[0].ExecuteOnGPU(rc, 10);
	//	g_renderingEngine->gaussianBlur[1].ExecuteOnGPU(rc, 10);
	//	g_renderingEngine->gaussianBlur[2].ExecuteOnGPU(rc, 10);
	//	g_renderingEngine->gaussianBlur[3].ExecuteOnGPU(rc, 10);

	//	//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
	//	rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);

	//	//�����_�����O�^�[�Q�b�g��ݒ�
	//	rc.SetRenderTargetAndViewport(mainRenderTarget);

	//	//�ŏI����
	//	g_renderingEngine->finalSprite.Draw(rc);

	//	//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	//	rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	//}

	void Bloom::BloomRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);

		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_luminanceRenderTarget);

		//�P�x���o���s��
		m_luminanceSprite.Draw(rc);

		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);


		//�K�E�V�A���u���[��4����s
		m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(mainRenderTarget);

		//�ŏI����
		m_finalSprite.Draw(rc);

		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	}
}
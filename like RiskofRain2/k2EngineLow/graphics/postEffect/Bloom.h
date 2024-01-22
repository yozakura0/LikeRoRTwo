#pragma once

namespace nsK2EngineLow
{

	class Bloom : public Noncopyable
	{
	public:
		//�u���[���ɕK�v�ȏ��̏�����
		void BloomInit(
		RenderTarget& mainRenderTarget
		);

		////�P�x���o�̏���
		//void LuminanceExtraction(RenderContext& rc);

		////�u���[���̎��s
		//void Execute(RenderContext& rc);

		//�u���[���̕`��
		void BloomRender(RenderContext& rc, RenderTarget& mainRenderTarget);

		//�u���[�������s�������ʂ̃e�N�X�`�����擾
		Texture& GetBloomResultTexture()
		{
			return m_luminanceRenderTarget.GetRenderTargetTexture();
		}


	private:
		//�K�E�V�A���u���[
		GaussianBlur m_gaussianBlur[4];

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g
		RenderTarget m_luminanceRenderTarget;

		//�P�x���o�p�̃X�v���C�g
		Sprite m_luminanceSprite;

		//�{�P�摜���������ď������ނ��߂̃X�v���C�g
		Sprite m_finalSprite;

	};

}
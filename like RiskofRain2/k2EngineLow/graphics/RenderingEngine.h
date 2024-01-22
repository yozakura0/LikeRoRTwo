#pragma once
#include "MyRenderer.h"
#include "IRenderer.h"
#include "Light/SceneLight.h"
#include "postEffect/Bloom.h"
#include "shadow/ShadowProjection.h"

namespace nsK2EngineLow {

	class SceneLight;
	class ModelRender;
	class Bloom;
	class ShadowProjection;

	class RenderingEngine :public Noncopyable
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void Init();

		void SetRenderTarget(RenderContext& rc);

		void Update();

		void Execute(RenderContext& rc);

		//�`��I�u�W�F�N�g��ǉ�
		void AddRenderObject(Model& model)
		{
			m_renderObjects.push_back(&model);
		}

		//�e�p�̃I�u�W�F�N�g��ǉ�
		void AddRenderObjectToShadow(Model& model)
		{
			m_renderObjectsToShadow.push_back(&model);
		}

		//2D�̕`��I�u�W�F�N�g��ǉ�
		void AddRenderObject2D(IRenderer* obj2D)
		{
			m_renderObjectsTo2D.push_back(obj2D);
		}

		//���C�������_�����O�^�[�Q�b�g
		RenderTarget m_mainRenderTarget;

		//�V���h�E�}�b�v
		RenderTarget m_shadowMap;

		//2D�̃����_�����O�^�[�Q�b�g
		RenderTarget m_2DRenderTarget;

		//���C�g�J����
		Camera m_lightCamera;

		//�P�x���o�p�̃X�v���C�g�f�[�^
		SpriteInitData m_luminanceSpriteInitData;
		//�P�x���o�p�̃X�v���C�g
		Sprite m_luminanceSprite;

		//�{�P�摜���������ď������ނ��߂̃X�v���C�g�f�[�^
		SpriteInitData m_finalSpriteInitData;
		//�{�P�摜���������ď������ނ��߂̃X�v���C�g
		Sprite m_finalSprite;

		//�K�E�V�A���u���[
		GaussianBlur m_gaussianBlur[4];
	private:
		//�V���h�E�}�b�v�ɕ`��
		void RenderToShadowMap(RenderContext& rc);

		//2D�̃����_�����O�^�[�Q�b�g�ɕ`��
		void RenderTo2DRenderTarget(RenderContext& rc);

		//���C�������_�����O�^�[�Q�b�g�̏�����
		void InitMainRenderTarget();

		//�V���h�E�}�b�v�ւ̕`�揈����������
		//void InitCascadeShadow();

		//�V���h�E�}�b�v�ւ̕`�揈����������
		void InitShadowMap();

		//2D�̃����_�����O�^�[�Q�b�g�̏�����
		void Init2DRenderTarget();
		
		//���C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�̏���
		//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g��������
		void InitCopyMainRenderTargetToFrameBufferSprite();

		//���C�������_�����O�^�[�Q�b�g�̏����t���[���o�b�t�@�ɃR�s�[���鏈��
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		//���C�������_�����O�^�[�Q�b�g
		//RenderTarget m_mainRenderTarget;
		//���C�������_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
		Sprite m_copyToFrameBufferSprite;

		//2D�����p�̃X�v���C�g
		Sprite m_2DSprite;
		Sprite m_mainSprite;

		//�V���h�E�}�b�v���f���X�v���C�g
		//Sprite m_shadowSprite;
		
		Bloom m_bloom;

		ShadowProjection m_shadowProj;
		
		//�V�[�����C�g
		SceneLight m_sceneLight;

		Light m_light;


		//�`��I�u�W�F�N�g�̃��X�g
		std::vector<Model*> m_renderObjects;

		//�e�p�̕`��I�u�W�F�N�g�̃��X�g
		std::vector<Model*> m_renderObjectsToShadow;

		//2D�p�̕`��I�u�W�F�N�g�̃��X�g
		std::vector<IRenderer*> m_renderObjectsTo2D;
	};
}
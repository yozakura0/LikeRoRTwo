#pragma once
//#include "IRenderer.h"
//#include "Light/SceneLight.h"

namespace nsK2EngineLow {

	class ModelRender;

	class RenderingEngine :public Noncopyable
	{
	public:
		//�f�B�t�@�[�h���C�e�B���O�p�̒萔�o�b�t�@
		//struct SDeferredLightingCB
		//{
		//	/*Light m_light;*/
		//	
		//};

		//���C�������_�����O�^�[�Q�b�g�̃X�i�b�v�V���b�g
		enum class EnMainRTSnapshot
		{
			//�s�����I�u�W�F�N�g�̕`�抮�����_
			enDrawnOpacity,
			//�X�i�b�v�V���b�g�̐�
			enNum
		};

		//�����_�����O�p�X
		enum class EnRenderingPass
		{
			//�A�j���[�V�����ςݒ��_�v�Z
			enomComputeAnimatedVertex,
			//�V���h�E�}�b�v�ւ̕`��p�X
			enRenderToShadowMap,
			//ZPrepass
			enZPrepass,
			//G-Buffer�ւ̕`��p�X
			enRenderToGBuffer,
			//�t�H���[�h�����_�����O�̕`��p�X
			enForwardRender,
			//2D�`��
			enRender2D
		};

		//�C�x���g
		enum EnEvent
		{
			//IBL�e�N�X�`���̍ď�����
			enEventReInitIBLTexture
		};

		/*RenderingEngine();
		~RenderingEngine();*/

		void Init();

		//void Update();

		//�`��I�u�W�F�N�g��ǉ�
		/*void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}*/

		/*Texture& GetLuminanceAvgTextureInScene()
		{
			return m_postEffect.GetLuminanceAvgTextureInScene();
		}*/

		//�C�x���g���X�i�[��ǉ�
		void AddEventListener(void* pListenerObj,std::function<void(EnEvent enEvent)> listenerFunc)
		{
			m_eventListeners.push_back({ pListenerObj,listenerFunc });
		}

		//std::vector< IRenderer* > m_renderObjects;
	private:
		//�V�[�����C�g
		//SceneLight m_sceneLight;

		//�C�x���g���X�i�[�̃f�[�^
		struct SEventListenerData
		{
			//���X�i�[�I�u�W�F�N�g
			void* pListenerObj;
			std::function<void(EnEvent enEvent)> listenerfunc;
		};

		//�C�x���g���X�i�[
		std::list<SEventListenerData> m_eventListeners;
	};
}
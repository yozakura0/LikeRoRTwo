#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"
#include "Light/SceneLight.h"

namespace nsK2EngineLow 
{

	ModelRender::ModelRender()
	{
		//m_light = new modelSLight();
		//g_sceneLight = m_sceneLight;
		//mslight->directionalLights.Init();
	}

	ModelRender::~ModelRender()
	{

	}

	/*void ModelRender::SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData)
	{
		modelInitData.m_vsSkinEntryPointFunc = "VSMainUsePreComputedVertexBuffer";
		modelInitData.m_vsEntryPointFunc = "VSMainUsePreComputedVertexBuffer";
	}*/

	void ModelRender::Init(
		const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isShadowReceiver
	)
	{

		if (isShadowReceiver)
		{
			//���f���A�V�F�[�_�[��ݒ�
			m_modelInitData.m_tkmFilePath = filePath;
			m_modelInitData.m_fxFilePath = "Assets/shader/ProjectionShadowReceiver.fx";

			m_modelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->m_shadowMap.GetRenderTargetTexture();

			m_modelInitData.m_expandConstantBuffer = (void*)&g_renderingEngine->m_lightCamera.GetViewProjectionMatrix();
			m_modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->m_lightCamera.GetViewProjectionMatrix());
			m_modelInitData.m_tkmFilePath = filePath;

			m_Model.Init(m_modelInitData);
		}
		else
		{
			//���f���A�V�F�[�_�[�A���f���̏������ݒ�
			m_modelInitData.m_tkmFilePath = filePath;
			m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			m_modelInitData.m_modelUpAxis = enModelUpAxis;

			//SetupVertexShaderEntryPointFunc(m_modelInitData);
			//�X�P���g����������
			InitSkeleton(filePath);
			//�A�j���[�V������������
			InitAnimation(animationClips, numAnimationClips, enModelUpAxis);

			//�萔�o�b�t�@�ɑ���
			m_modelInitData.m_expandConstantBuffer = &g_sceneLight->GetSceneLight();
			m_modelInitData.m_expandConstantBufferSize = sizeof(g_sceneLight->GetSceneLight());

			m_Model.Init(m_modelInitData);
			InitShadowModel(filePath);

		}

	}

	void ModelRender::InitSkeleton(const char* filepath)
	{
		//�X�P���g���̃f�[�^��ǂݍ���
		std::string skeletonFilePath = filepath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;

		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips
			);

			//�X�P���g���̗L���Œ��_�V�F�[�_�[�̃G���g���[�|�C���g�Ȃǂ�ύX
			/*if (m_skeleton.GetNumBones() != 0)
			{*/
				m_modelInitData.m_skeleton = &m_skeleton;
				m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			/*}
			else
			{
				m_modelInitData.m_vsSkinEntryPointFunc = "VSMain";
			}*/
		}
	}

	void ModelRender::InitShadowModel(const char* filePath)
	{
		ModelInitData shadowModelInitData;

		shadowModelInitData.m_fxFilePath = "Assets/shader/DrawProjectionShadowMap.fx";
		shadowModelInitData.m_tkmFilePath = filePath;

		m_shadowModel.Init(shadowModelInitData);
		/*m_shadowModel.UpdateWorldMatrix(

		)*/
	}

	/*void ModelRender::InitComputeAnimatoinVertexBuffer(
		const char* tkmFilePath,
		EnModelUpAxis enModelUpAxis)
	{
		StructuredBuffer* worldMatrxiArraySB = nullptr;
		
		m_computeAnimationVertexBuffer.Init(
			tkmFilePath,
			m_skeleton.GetNumBones(),
			m_skeleton.GetBoneMatricesTopAddress(),
			enModelUpAxis,
			worldMatrxiArraySB
		);
	}*/

	void ModelRender::UpdateWorldMatrixInModes()
	{
		m_Model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}

	void ModelRender::Update()
	{
		UpdateWorldMatrixInModes();

		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_Model.GetWorldMatrix());
		}

		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{

		//���X�g�Ƀ��f����ǉ�
		g_renderingEngine->AddRenderObject(m_Model);

		if (m_isShadowCaster)
		{
			//���X�g�ɉe�p�̃��f����ǉ�
			g_renderingEngine->AddRenderObjectToShadow(m_shadowModel);
		}

		//m_Model.Draw(rc);
		
		//bloom.OnRender(rc);
	}
}
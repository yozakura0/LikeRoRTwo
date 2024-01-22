#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow 
{

	ModelRender::ModelRender()
	{
		
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
		EnModelUpAxis enModelUpAxis
	)
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

		//���C�g�̏�������������
		sdirectionalLight.Setup();
		spointLight.SetUp();
		sspotLight.SetUp();
		shemiLight.SetUp();
		sotherLight.Setup();

		//sceneLight.Init();

		//���C�g�̏����ʂɎ����Ă���
		light.directionalLight.ligDirection = sdirectionalLight.GetligDir();
		light.directionalLight.ligColor = sdirectionalLight.GetColor();
		light.pointLight.ptPosition = spointLight.GetPosition();
		light.pointLight.ptColor = spointLight.GetColor();
		light.pointLight.ptRange = spointLight.GetRange();
		light.ambientLight = sotherLight.GetAmbientLight();
		light.eyePos = sotherLight.GetEyePos();
		light.spotLight.spPosition = sspotLight.GetPosition();
		light.spotLight.spColor = sspotLight.GetColor();
		light.spotLight.spRange = sspotLight.GetRange();
		light.spotLight.spDirection = sspotLight.GetDirection();
		light.spotLight.spAngle = sspotLight.GetAngle();
		light.hemiLight.groundColor = shemiLight.GetGroundColor();
		light.hemiLight.skyColor = shemiLight.GetSkyColor();
		light.hemiLight.groundNormal = shemiLight.GetGroundNormal();

		//�萔�o�b�t�@�ɑ���
		m_modelInitData.m_expandConstantBuffer = &light;
		m_modelInitData.m_expandConstantBufferSize = sizeof(light);
		
		m_Model.Init(m_modelInitData);
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
		//�ʏ�`��
		//g_renderingEngine->AddRenderObject(this);

		m_Model.Draw(rc);
		
		//bloom.OnRender(rc);
	}
}
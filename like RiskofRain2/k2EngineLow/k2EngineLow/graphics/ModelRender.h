#pragma once

//#include "geometry/"
#include "Light/SceneLight.h"
#include "postEffect/Bloom.h"

namespace nsK2EngineLow {

	class RenderingEngine;
	//class SceneLight;

	struct DirectionalLight
	{
		//���C�g�̕���
		Vector3 ligDirection;
		//�p�f�B���O
		float pad1;
		//���C�g�̃J���[
		Vector4 ligColor;
	};

	struct PointLight
	{
		//���C�g�̈ʒu
		Vector3 ptPosition;
		float pad2;
		//���C�g�̃J���[
		Vector3 ptColor;
		//���C�g�̉e���͈�
		float ptRange;
	};

	struct SpotLight
	{
		//�ʒu
		Vector3 spPosition;
		float pad3;
		//�J���[
		Vector3 spColor;
		//�e���͈�
		float spRange;
		//�ˏo����
		Vector3 spDirection;
		//�ˏo�p�x
		float spAngle;
	};

	struct HemiLight
	{
		//�n�ʐF
		Vector3 groundColor;
		float pad4;
		//�V���F
		Vector3 skyColor;
		float pad5;
		//�n�ʂ̖@��
		Vector3 groundNormal;
	};

	struct Light
	{
		//�f�B���N�V�������C�g�̔z��(�ő�1�u����)
		DirectionalLight directionalLight;
		//�|�C���g���C�g�̔z��
		PointLight pointLight;
		//�X�|�b�g���C�g�̔z��
		SpotLight spotLight;
		//�������C�g�̔z��
		HemiLight hemiLight;

		//�J�����̈ʒu
		Vector3 eyePos;
		//�X�y�L�����̍i��
		float specPow = 5.0f;
		//����
		Vector3 ambientLight;
	};

	class ModelRender :public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		//���f�������_�[�̏�����
		void Init(
			//�t�@�C���̃p�X
			const char* filePath,
			//�A�j���[�V�����N���b�v
			AnimationClip* animationClips = nullptr,
			//�A�j���[�V�����N���b�v�̐�
			int numAnimationClips = 0,
			//���f���̏�����̐ݒ�
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);

		//�X�V����
		void Update();

		//�`�揈��
		void Draw(RenderContext& rc);

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		//���f���̎擾
		Model& GetModel()
		{
			return m_Model;
		}

		//���W�A��]�A�傫����S�Đݒ�
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//���W�̐ݒ�
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		//���W�̐ݒ�
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//��]�̐ݒ�
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//�g�嗦�̐ݒ�
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//�g�嗦�̐ݒ�
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}
		//�A�j���[�V�����̑����̕ύX
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//�A�j���[�V�����C�x���g
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		void SetPointLightPosition(const Vector3& pos)
		{
			PointLight pointLight;
			pointLight.ptPosition = pos;
		}

	private:
		//�X�P���g���̏�����
		void InitSkeleton(
			//�t�@�C���p�X
			const char* filepath
		);

		//�A�j���[�V�����̏�����
		void InitAnimation(
			//�A�j���[�V�����N���b�v
			AnimationClip* animationClips,
			//�A�j���[�V�����N���b�v�̐�
			int numAnimationClips,
			//���f���̏����
			EnModelUpAxis enModelUpAxis
		);

		////�A�j���[�V�����ϒ��_�o�b�t�@�̌v�Z������������
		//void InitComputeAnimatoinVertexBuffer(
		//	const char* tkmFilePath,
		//	EnModelUpAxis enModelUpAxis
		//);

		//�e�탂�f���̃��[���h���W���X�V����
		void  UpdateWorldMatrixInModes();

		//�e�탂�f���̒��_�V�F�[�_�[�̃G���g���[�|�C���g��ݒ�
		//void SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData);

	private:
		//�A�j���[�V�����N���b�v
		AnimationClip* m_animationClips = nullptr;
		//�A�j���[�V�����N���b�v�̐�
		int m_numAnimationClips = 0;
		//���W
		Vector3 m_position = Vector3::Zero;
		//��]
		Quaternion m_rotation = Quaternion::Identity;
		//�g�嗦
		Vector3 m_scale = Vector3::One;
		//�A�j���[�V����
		Animation m_animation;
		//
		
		//���f��
		Model m_Model;
		//���f���̏������f�[�^
		ModelInitData m_modelInitData;
		//�t�H���[�h�����_�����O�̕`��p�X�ŕ`�悳��郂�f��
		//Model m_forwardRenderModel;
		
		//RenderToGBuffer�ŕ`�悳��郂�f��
		//Model m_renderToGBufferModel;
		
		//�X�P���g��
		Skeleton m_skeleton;
		//�A�j���[�V�����̍Đ����x
		float m_animationSpeed = 1.0f;
		//�W�I���g�����
		//std::vector<Gemo>

		//SceneLight sceneLight;
		
		//�V�[�����C�g�̃��C�g
		/*SLight slight;*/

		//�V�[�����C�g�̃f�B���N�V�������C�g
		SDirectionalLight sdirectionalLight;

		//�V�[�����C�g�̃|�C���g���C�g
		SPointLight spointLight;

		//�V�[�����C�g�̃X�|�b�g���C�g
		SSpotLight sspotLight;

		//�V�[�����C�g�̔������C�g
		SHemiLight shemiLight;

		//�V�[�����C�g�̂��̂ق����C�g
		SOtherLight sotherLight;

		//���f�������_�[���̃f�B���N�V�������C�g
		//DirectionalLight directionalLight;

		//���C�g
		Light light;
	};
}


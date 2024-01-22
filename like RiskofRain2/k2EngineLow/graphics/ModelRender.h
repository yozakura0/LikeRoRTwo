#pragma once

#include "MyRenderer.h"
#include "Light/SceneLight.h"
#include "postEffect/Bloom.h"

namespace nsK2EngineLow {

	class RenderingEngine;
	class SceneLight;
	class Light;

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
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			//�e�𗎂Ƃ���
			bool isShadowReceiver = false
		);

		void InitShadowModel(const char* filePath);

		//�X�V����
		void Update();

		//�`�揈��
		void Draw(RenderContext& rc);

		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		//�A�j���[�V�������Đ������ǂ���
		bool PlayingAnimation()
		{
			return m_animation.IsPlaying();
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

		//�{�[���̖��O����{�[���ԍ����擾
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		//�{�[���ԍ�����{�[�����擾
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
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

		//�e�탂�f���̃��[���h���W���X�V����
		void  UpdateWorldMatrixInModes();

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

		//�e�p���f��
		Model m_shadowModel;

		//���f���̏������f�[�^
		ModelInitData m_modelInitData;
		
		//�V���h�E�L���X�^�[�t���O
		bool m_isShadowCaster = true;
		
		//�X�P���g��
		Skeleton m_skeleton;
		//�A�j���[�V�����̍Đ����x
		float m_animationSpeed = 1.0f;

		//Light m_light;
	};
}


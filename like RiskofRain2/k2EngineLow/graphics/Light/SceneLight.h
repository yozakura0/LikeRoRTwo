#pragma once

namespace nsK2EngineLow {

	struct DirectionalLight
	{
		//���C�g�̕���
		Vector3 dirDirection;

		////�g�p����
		//int isUse;
		float pad0;

		//���C�g�̃J���[
		Vector3 dirColor;

		float pad1;
	};

	struct PointLight
	{
		//���W
		Vector3 ptPosition;

		////���C�g���g�p���Ă��邩
		//int isUse;

		float pad2;

		//�J���[
		Vector3 ptColor;

		//�e���͈�
		float ptRange;
	};

	struct SpotLight
	{
		//���W
		Vector3 spPosition;

		////�g�p�����ǂ���
		//int isUse;

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

	//���C�g�̍\����
	struct Light
	{
		//�f�B���N�V�������C�g
		DirectionalLight directionalLight/*[MAX_DIRECTIONAL_LIGHT]*/;

		//�|�C���g���C�g
		PointLight pointLight[/*MAX_POINT_LIGHT*/8];

		//�X�|�b�g���C�g
		SpotLight spotLight[/*MAX_SPOT_LIGHT*/8];

		//���_�̍��W
		Vector3 eyePos;
		
		//�|�C���g���C�g�̐�
		float numPointLight;

		//����
		Vector3 ambientLight;

		//�X�|�b�g���C�g�̐�
		float numSpotLight;
	};

	class SceneLight :public Noncopyable
	{
	public:
		//SceneLight();

		//�V�[�����C�g�̏���n��
		Light& GetSceneLight()
		{
			return m_light;
		}

		void SetDirPosition(Vector3 position)
		{
			m_light.directionalLight.dirDirection = position;
		}
		void SetDirColor(Vector3 color)
		{
			m_light.directionalLight.dirColor = color;
		}

		void SetPtPosition(Vector3 position)
		{
			m_light.pointLight[0].ptPosition = position;
		}
		void SetPtColor(Vector3 color)
		{
			m_light.pointLight[0].ptColor = color;
		}
		void SetPtRange(float range)
		{
			m_light.pointLight[0].ptRange = range;
		}

		void SetSpPosition(Vector3 position)
		{
			m_light.spotLight[0].spPosition = position;
		}
		void SetSpColor(Vector3 color)
		{
			m_light.spotLight[0].spColor = color;
		}
		void SetSpRange(float range)
		{
			m_light.spotLight[0].spRange = range;
		}
		void SetSpDirection(Vector3 direction)
		{
			m_light.spotLight[0].spDirection = direction;
		}
		void SetSpAngle(float angle)
		{
			m_light.spotLight[0].spAngle = angle;
		}

		void SetAmbient(Vector3 ambient)
		{
			m_light.ambientLight = ambient;
		}
		void SetEyePos(Vector3 eyePos)
		{
			m_light.eyePos = eyePos;
		}

	private:
		//SceneLight* m_sceneLight;
		Light m_light;
	};
}
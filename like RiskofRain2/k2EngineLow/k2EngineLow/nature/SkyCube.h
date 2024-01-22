#pragma once

namespace nsK2EngineLow {
	enum EnSkyCubeType {
		//����
		enSkyCubeType_Day,

		//���
		enSkyCubeType_Night,

		//��R
		enSkyCubeType_Snow,

		//��R_2
		enSkyCubeType_Snow_2,

		//�r��
		enSkyCubeType_Wild,

		//�r��Q
		enSkyCubeType_Wild_2,

		//�r��(���)
		enSkyCubeType_Wild_Night,

		//�Ő�
		enSkyCubeType_Grass,

		//���B
		enSkyCubeType_Euro,

		//����(�g�D�[����)
		enSkyCubeType_DayToon,

		//����(�g�D�[����)�Q
		enSkyCubeType_DayToon_2,

		//����(�g�D�[����)�R
		enSkyCubeType_DayToon_3,

		//����(�g�D�[����)�S
		enSkyCubeType_DayToon_4,

		//���(�g�D�[����)
		enSkyCubeType_NightToon,

		//���(�g�D�[����)�Q
		enSkyCubeType_NightToon_2,

		//������(�g�D�[����)
		enSkyCubeType_SunriseToon,

		//��C��(�g�D�[����)
		enSkyCubeType_SpaceToon,

		//��C��(�g�D�[����)�Q
		enSkyCubeType_SpaceToon_2,

		enSkyCubeType_Num
	};

	class SkyCube :public IGameObject
	{
	public:
		SkyCube();
		bool Start()override final;
		void Update()override final;
		void Render(RenderContext& rc)override final;

	public:
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}
		void SetScale(const float scale)
		{
			m_scale = g_vec3One;
			m_scale.Scale(scale);
			m_isDirty = true;
		}

		//�X�J�C�L���[�u�̃^�C�v��ݒ�
		void SetType(EnSkyCubeType type)
		{
			m_type = type;
		}

		//���邳��ݒ�
		void SetLuminance(float lum)
		{
			m_luminance = lum;
		}

		const wchar_t* GetTxtureFilePath()
		{
			return m_textureFilePaths[m_type];
		}

	private:
		ModelRender m_modelRender;

		Texture m_texture[enSkyCubeType_Num];
		const wchar_t* m_textureFilePaths[enSkyCubeType_Num];
		Vector3 m_position = g_vec3Zero;
		Vector3 m_scale = g_vec3One * 1000.0f;
		float m_luminance = 1.0f;
		bool m_isDirty = false;
		EnSkyCubeType m_type = enSkyCubeType_Day;
	};
}

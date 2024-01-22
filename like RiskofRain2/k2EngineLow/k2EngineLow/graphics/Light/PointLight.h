#pragma once

namespace nsK2EngineLow {

	class PPointLight : Noncopyable{
	public:
		//������
		void Init();

		//���W�̐ݒ�
		void SetPosition(const Vector3& position)
		{
			m_pointLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_pointLight->SetPosition(x, y, z);
		}

		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			m_pointLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_pointLight->SetColor(r, g, b);
		}

		//�͈͂�ݒ�
		void SetRange(float range)
		{
			m_pointLight->SetRange(range);
		}

		//�X�V
		void Update()
		{
			//m_pointLight
		}

	private:
		SPointLight* m_pointLight = nullptr;
	};

}
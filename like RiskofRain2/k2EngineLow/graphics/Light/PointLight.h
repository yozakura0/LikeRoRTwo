#pragma once

	class SceneLight;

namespace nsK2EngineLow {



	class PPointLight : Noncopyable
	{
	public:
		//������
		int Init();

		//���W�̐ݒ�
		void SetPosition(const Vector3& position, int num)
		{
			m_light.pointLight[num].ptPosition = position;
		}
		/*void SetPosition(float x, float y, float z, int num)
		{
			light.pointLight[num]->SetPosition({ x, y, z }, num);
		}*/

		//�J���[��ݒ�
		void SetColor(const Vector3& color, int num)
		{
			m_light.pointLight[num].ptColor = color;
		}
		/*void SetColor(float r, float g, float b, int num)
		{
			light.pointLight[num]->SetColor({ r, g, b }, num);
		}*/

		//�͈͂�ݒ�
		void SetRange(float range, int num)
		{
			m_light.pointLight[num].ptRange = range;
		}

		////�X�V
		//void Update()
		//{
		//	m_sceneLight.PointLight->Update();
		//}

	private:
		//SceneLight m_sceneLight;
		Light m_light;
	};

}
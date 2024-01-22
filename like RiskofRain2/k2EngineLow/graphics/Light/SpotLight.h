#pragma once

class SceneLight;

namespace nsK2EngineLow {
	
	
	class SSpotLight : Noncopyable
	{
	public:

		//座標の設定
		void SetPosition(const Vector3& position, int num)
		{
			m_light.spotLight[num].spPosition = position;
		}
		/*void SetPosition(float x, float y, float z, int num)
		{
			m_sceneLight.spotLight[num]->SetPosition({ x, y, z }, num);
		}*/

		//カラーを設定
		void SetColor(const Vector3& color, int num)
		{
			m_light.spotLight[num].spColor = color;
		}
		/*void SetColor(float r, float g, float b, int num)
		{
			m_sceneLight.spotLight[num]->SetColor({ r, g, b }, num);
		}*/

		//範囲を設定
		void SetRange(float range, int num)
		{
			m_light.spotLight[num].spRange = range;
		}

		//射出方向の設定
		void SetDirection(const Vector3& direction, int num)
		{
			m_light.spotLight[num].spDirection = direction;
		}
		/*void SetPosition(float x, float y, float z, int num)
		{
			m_sceneLight.spotLight[num]->SetDirection({ x, y, z }, num);
		}*/

		//射出角度を設定
		void SetAngle(float angle, int num)
		{
			m_light.spotLight[num].spAngle = angle;
		}

	private:
		//SceneLight m_sceneLight;
		Light m_light;
	};
}
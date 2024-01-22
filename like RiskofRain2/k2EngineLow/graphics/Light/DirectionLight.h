#pragma once

//class SceneLight;

namespace nsK2EngineLow {
	
	class DirectionLight : Noncopyable
	{
	public:
		void Init();

		//•ûŒü‚ÌÝ’è
		void SetDirection(const Vector3& direction/*, int num*/)
		{
			m_light.directionalLight/*[num]*/.dirDirection = direction;
			m_light.directionalLight/*[num]*/.dirDirection.Normalize();
		}
		/*void SetDirection(float x, float y, float z)
		{
			m_sceneLight.directionalLight->SetDirection({ x, y, z });
		}*/

		//ƒJƒ‰[‚ðÝ’è
		void SetColor(const Vector3& color/*, int num*/)
		{
			m_light.directionalLight/*[num]*/.dirColor = color;
		}
		/*void SetColor(float r, float g, float b)
		{
			light.directionalLight->SetColor({ r, g, b });
		}*/

	private:
		//SceneLight m_sceneLight;
		Light m_light;
	};
}
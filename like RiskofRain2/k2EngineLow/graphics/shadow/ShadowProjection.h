#pragma once

namespace nsK2EngineLow {
	class ShadowProjection
	{
	public:

		ShadowProjection();
		~ShadowProjection();

		void Start();
		void CreateShadowMap();
		void CreateLightCamera();

	private:
		//Camera m_lightCamera;
	};
}
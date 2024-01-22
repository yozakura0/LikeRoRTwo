#include "k2EngineLowPreCompile.h"
#include "shadowProjection.h"

namespace nsK2EngineLow {

	ShadowProjection::ShadowProjection()
	{
	}

	ShadowProjection::~ShadowProjection()
	{
	}

	void ShadowProjection::Start()
	{
		CreateShadowMap();
		CreateLightCamera();
	}

	void ShadowProjection::CreateShadowMap()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		g_renderingEngine->m_shadowMap.Create(
			1024,
			1024,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void ShadowProjection::CreateLightCamera()
	{
		g_renderingEngine->m_lightCamera.SetPosition(0, 600, 0);

		g_renderingEngine->m_lightCamera.SetTarget(0, 0, 0);

		g_renderingEngine->m_lightCamera.SetUp(1, 0, 0);

		g_renderingEngine->m_lightCamera.SetViewAngle(Math::DegToRad(50.0f));

		g_renderingEngine->m_lightCamera.Update();
	}


}
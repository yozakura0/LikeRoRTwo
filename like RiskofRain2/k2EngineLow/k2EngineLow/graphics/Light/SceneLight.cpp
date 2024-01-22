#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {

	void SceneLight::Init()
	{
		//太陽光(ディレクションライト)
		sdirectionalLight.ligColor.x = 1.2f;
		sdirectionalLight.ligColor.y = 1.2f;
		sdirectionalLight.ligColor.z = 1.2f;

		sdirectionalLight.ligDirection.x = 1.0f;
		sdirectionalLight.ligDirection.y = -1.0f;
		sdirectionalLight.ligDirection.z = -1.0f;
		sdirectionalLight.ligDirection.Normalize();

		//環境光
		sotherLight.ambientLight.x = 0.1f;
		sotherLight.ambientLight.y = 0.1f;
		sotherLight.ambientLight.z = 0.1f;

		sotherLight.eyePos = g_camera3D->GetPosition();
	}
}
#pragma once

namespace nsK2EngineLow {

	struct DirectionalLight
	{
		//ライトの方向
		Vector3 dirDirection;

		////使用中か
		//int isUse;
		float pad0;

		//ライトのカラー
		Vector3 dirColor;

		float pad1;
	};

	struct PointLight
	{
		//座標
		Vector3 ptPosition;

		////ライトを使用しているか
		//int isUse;

		float pad2;

		//カラー
		Vector3 ptColor;

		//影響範囲
		float ptRange;
	};

	struct SpotLight
	{
		//座標
		Vector3 spPosition;

		////使用中かどうか
		//int isUse;

		float pad3;

		//カラー
		Vector3 spColor;

		//影響範囲
		float spRange;

		//射出方向
		Vector3 spDirection;

		//射出角度
		float spAngle;
	};

	//ライトの構造体
	struct Light
	{
		//ディレクションライト
		DirectionalLight directionalLight/*[MAX_DIRECTIONAL_LIGHT]*/;

		//ポイントライト
		PointLight pointLight[/*MAX_POINT_LIGHT*/8];

		//スポットライト
		SpotLight spotLight[/*MAX_SPOT_LIGHT*/8];

		//視点の座標
		Vector3 eyePos;
		
		//ポイントライトの数
		float numPointLight;

		//環境光
		Vector3 ambientLight;

		//スポットライトの数
		float numSpotLight;
	};

	class SceneLight :public Noncopyable
	{
	public:
		//SceneLight();

		//シーンライトの情報を渡す
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
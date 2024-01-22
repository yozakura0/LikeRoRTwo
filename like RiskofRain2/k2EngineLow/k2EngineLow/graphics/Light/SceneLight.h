#pragma once

namespace nsK2EngineLow {

	//ディレクションライトの構造体
	struct SDirectionalLight
	{
		//ライトの方向
		Vector3 ligDirection;
		////パディング
		//float pad;
		//ライトのカラー
		Vector4 ligColor;

		void Setup()
		{
			ligColor.x = 1.2f;
			ligColor.y = 1.2f;
			ligColor.z = 1.2f;

			ligDirection.x = 1.0f;
			ligDirection.y = -1.0f;
			ligDirection.z = -1.0f;
			ligDirection.Normalize();
		}

		//ライトの方向を取得
		const Vector3& GetligDir() const
		{
			return ligDirection;
		}
		//ライトのカラーを取得
		const Vector4& GetColor() const
		{
			return ligColor;
		}
	};

	//ポイントライトの構造体
	struct SPointLight
	{
	private:
		//ライトの位置
		Vector3 ptPosition;
		//ライトのカラー
		Vector3 ptColor;
		//ライトの影響範囲
		float ptRange;

	public:
		void SetUp()
		{
			ptPosition = { 0,50,150 };
			ptColor = { 15,0,0 };
			ptRange=100;
		}

		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->ptPosition = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->ptColor = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}

		//範囲を設定
		void SetRange(float range)
		{
			ptRange = range;
		}

		//座標を取得
		const Vector3& GetPosition() const
		{
			return ptPosition;
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return ptColor;
		}
		//影響範囲を取得
		const float& GetRange() const
		{
			return ptRange;
		}
	};

	//スポットライトの構造体
	struct SSpotLight
	{
		//位置
		Vector3 spPosition;
		float pad3;
		//カラー
		Vector3 spColor;
		//影響範囲
		float spRange;
		//射出方向
		Vector3 spDirection;
		//射出角度
		float spAngle;

	public:
		void SetUp()
		{
			spPosition = { 0,50,150 };
			spColor = { 10,10,10 };
			spRange = 100;

			spDirection = { 1.0,-1.0,1.0 };
			spDirection.Normalize();

			spRange = 300;
			spAngle = Math::DegToRad(25.0f);
		}

		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->spPosition = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->spColor = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}

		//範囲を設定
		void SetRange(float range)
		{
			this->spRange = range;
		}

		//射出方向を設定
		void SetDirection(const Vector3& direction)
		{
			this->spDirection = direction;
		}
		void SetDirection(float x,float y,float z)
		{
			SetDirection({ x,y,z });
		}

		//範囲を設定
		void SetAngle(float angle)
		{
			this->spAngle = Math::DegToRad(angle);
		}

		//座標を取得
		const Vector3& GetPosition() const
		{
			return spPosition;
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return spColor;
		}
		//影響範囲を取得
		const float& GetRange() const
		{
			return spRange;
		}
		//射出方向を取得
		const Vector3& GetDirection() const
		{
			return spDirection;
		}
		//射出角度を取得
		const float& GetAngle() const
		{
			return spAngle;
		}
	};

	struct SHemiLight
	{
		//地面色
		Vector3 groundColor;
		//天球色
		Vector3 skyColor;
		//地面の法線
		Vector3 groundNormal;

		void SetUp()
		{
			groundColor = { 0.7f,0.5f,0.3f };
			skyColor = { 0.15f,0.7f,0.95f };
			groundNormal = { 0.0f,1.0f,0.0f };
		}

		//地面色を取得
		const Vector3& GetGroundColor() const
		{
			return groundColor;
		}
		//天球色を取得
		const Vector3& GetSkyColor() const
		{
			return skyColor;
		}
		//地面の法線を取得
		const Vector3& GetGroundNormal() const
		{
			return groundNormal;
		}
	};

	struct SOtherLight
	{
		//カメラの位置
		Vector3 eyePos;
		
		//環境光
		Vector3 ambientLight;

	public:
		void Setup()
		{
			//環境光
			ambientLight.x = 0.3f;
			ambientLight.y = 0.3f;
			ambientLight.z = 0.3f;

			eyePos = g_camera3D->GetPosition();
		}

		//カメラの位置を取得
		const Vector3& GetEyePos() const
		{
			return eyePos;
		}
		//環境光を取得
		const Vector3& GetAmbientLight() const
		{
			return ambientLight;
		}
	};

	class SceneLight : public Noncopyable
	{
	public:
		//初期化
		void Init();
	
	private:
		//ディレクションライト
		SDirectionalLight sdirectionalLight;

		//そのほかのライト
		SOtherLight sotherLight;
	};

}
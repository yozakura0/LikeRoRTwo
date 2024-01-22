#pragma once

namespace nsK2EngineLow {

	class PPointLight : Noncopyable{
	public:
		//初期化
		void Init();

		//座標の設定
		void SetPosition(const Vector3& position)
		{
			m_pointLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_pointLight->SetPosition(x, y, z);
		}

		//カラーを設定
		void SetColor(const Vector3& color)
		{
			m_pointLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_pointLight->SetColor(r, g, b);
		}

		//範囲を設定
		void SetRange(float range)
		{
			m_pointLight->SetRange(range);
		}

		//更新
		void Update()
		{
			//m_pointLight
		}

	private:
		SPointLight* m_pointLight = nullptr;
	};

}
#pragma once

namespace nsK2EngineLow {
	enum EnSkyCubeType {
		//昼間
		enSkyCubeType_Day,

		//夜間
		enSkyCubeType_Night,

		//雪山
		enSkyCubeType_Snow,

		//雪山_2
		enSkyCubeType_Snow_2,

		//荒野
		enSkyCubeType_Wild,

		//荒野２
		enSkyCubeType_Wild_2,

		//荒野(夜間)
		enSkyCubeType_Wild_Night,

		//芝生
		enSkyCubeType_Grass,

		//欧州
		enSkyCubeType_Euro,

		//昼間(トゥーン調)
		enSkyCubeType_DayToon,

		//昼間(トゥーン調)２
		enSkyCubeType_DayToon_2,

		//昼間(トゥーン調)３
		enSkyCubeType_DayToon_3,

		//昼間(トゥーン調)４
		enSkyCubeType_DayToon_4,

		//夜間(トゥーン調)
		enSkyCubeType_NightToon,

		//夜間(トゥーン調)２
		enSkyCubeType_NightToon_2,

		//明け方(トゥーン調)
		enSkyCubeType_SunriseToon,

		//大気圏(トゥーン調)
		enSkyCubeType_SpaceToon,

		//大気圏(トゥーン調)２
		enSkyCubeType_SpaceToon_2,

		enSkyCubeType_Num
	};

	class SkyCube :public IGameObject
	{
	public:
		SkyCube();
		bool Start()override final;
		void Update()override final;
		void Render(RenderContext& rc)override final;

	public:
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}
		void SetScale(const float scale)
		{
			m_scale = g_vec3One;
			m_scale.Scale(scale);
			m_isDirty = true;
		}

		//スカイキューブのタイプを設定
		void SetType(EnSkyCubeType type)
		{
			m_type = type;
		}

		//明るさを設定
		void SetLuminance(float lum)
		{
			m_luminance = lum;
		}

		const wchar_t* GetTxtureFilePath()
		{
			return m_textureFilePaths[m_type];
		}

	private:
		ModelRender m_modelRender;

		Texture m_texture[enSkyCubeType_Num];
		const wchar_t* m_textureFilePaths[enSkyCubeType_Num];
		Vector3 m_position = g_vec3Zero;
		Vector3 m_scale = g_vec3One * 1000.0f;
		float m_luminance = 1.0f;
		bool m_isDirty = false;
		EnSkyCubeType m_type = enSkyCubeType_Day;
	};
}

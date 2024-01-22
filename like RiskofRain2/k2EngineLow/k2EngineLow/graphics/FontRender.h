#pragma once

#include "IRenderer.h"

namespace nsK2EngineLow{

	class FontRender : public IRenderer
	{
		static const int MAX_TEXT_SIZE = 256;
	public:

		//表示する文字を設定
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		//表示する文字を取得
		const wchar_t* GetText() const
		{
			return m_text;
		}

		//座標を設定、zは0.0f
		void SetPosition(float x, float y)
		{
			SetPosition({ x,y });
		}
		void SetPosition(const Vector2& position)
		{
			m_position = position;
		}

		//座標を取得
		const Vector2& GetPosition() const
		{
			return m_position;
		}

		//大きさを設定
		void SetScale(const float scale)
		{
			m_scale = scale;
		}

		//大きさを取得
		const float GetScale() const
		{
			return m_scale;
		}

		//色を設定
		void SetColor(float r, float g, float b, float a)
		{
			SetColor({ r,g,b,a });
		}
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}

		const Vector4& GetColor() const
		{
			return m_color;
		}

		//回転を設定
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}

		//回転を取得
		const float GetRotation() const
		{
			return m_rotation;
		}

		//ピボットを設定
		//x = 0.5、y = 0.5で画像の中心が基点
		//x = 0.0、y = 0.0で画像の左下
		//x = 1.0、y = 1.0で画像の右上
		void SetPivot(float x, float y)
		{
			SetPivot({ x,y });
		}
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		//ピボットを取得
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		//描画処理
		void Draw(RenderContext& rc);

		//影のパラメータを設定

	private:
		Vector2 m_position = Vector2::Zero;
		float m_scale = 1.0f;
		Vector4 m_color = g_vec4White;
		float m_rotation = 0.0f;
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;
		wchar_t m_text[MAX_TEXT_SIZE];
		Font m_font;
	};
}
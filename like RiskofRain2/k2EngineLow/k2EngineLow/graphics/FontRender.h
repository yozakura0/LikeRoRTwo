#pragma once

#include "IRenderer.h"

namespace nsK2EngineLow{

	class FontRender : public IRenderer
	{
		static const int MAX_TEXT_SIZE = 256;
	public:

		//�\�����镶����ݒ�
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		//�\�����镶�����擾
		const wchar_t* GetText() const
		{
			return m_text;
		}

		//���W��ݒ�Az��0.0f
		void SetPosition(float x, float y)
		{
			SetPosition({ x,y });
		}
		void SetPosition(const Vector2& position)
		{
			m_position = position;
		}

		//���W���擾
		const Vector2& GetPosition() const
		{
			return m_position;
		}

		//�傫����ݒ�
		void SetScale(const float scale)
		{
			m_scale = scale;
		}

		//�傫�����擾
		const float GetScale() const
		{
			return m_scale;
		}

		//�F��ݒ�
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

		//��]��ݒ�
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}

		//��]���擾
		const float GetRotation() const
		{
			return m_rotation;
		}

		//�s�{�b�g��ݒ�
		//x = 0.5�Ay = 0.5�ŉ摜�̒��S����_
		//x = 0.0�Ay = 0.0�ŉ摜�̍���
		//x = 1.0�Ay = 1.0�ŉ摜�̉E��
		void SetPivot(float x, float y)
		{
			SetPivot({ x,y });
		}
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		//�s�{�b�g���擾
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		//�`�揈��
		void Draw(RenderContext& rc);

		//�e�̃p�����[�^��ݒ�

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
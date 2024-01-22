#pragma once

namespace nsK2EngineLow {
	class SpriteRender : public IRenderer
	{
	public:
		//����������
		void Init(
			//�t�@�C���p�X
			const char* filepath, 
			//����
			const float w, 
			//�c��
			const float h,
			//���������������邩
			AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans
		);

		//���W��ݒ�
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		//�傫����ݒ�
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		//��]��ݒ�
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}

		//�X�V����
		void Update()
		{
			m_sprite.Update(
				m_position,
				m_rotation,
				m_scale
			);
		}

		//�`�揈��
		void Draw(RenderContext& rc);

	private:
		//�X�v���C�g
		Sprite m_sprite;
		//���W
		Vector3 m_position = Vector3::Zero;
		//��]
		Quaternion m_rotation = Quaternion::Identity;
		//�傫��
		Vector3 m_scale = Vector3::One;
	};

}
#pragma once

namespace nsK2EngineLow {
	class SpriteRender : public IRenderer
	{
	public:
		//初期化処理
		void Init(
			//ファイルパス
			const char* filepath, 
			//横幅
			const float w, 
			//縦幅
			const float h,
			//半透明合成をするか
			AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans
		);

		//座標を設定
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		//大きさを設定
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		//回転を設定
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}

		//更新処理
		void Update()
		{
			m_sprite.Update(
				m_position,
				m_rotation,
				m_scale
			);
		}

		//描画処理
		void Draw(RenderContext& rc);

	private:
		//スプライト
		Sprite m_sprite;
		//座標
		Vector3 m_position = Vector3::Zero;
		//回転
		Quaternion m_rotation = Quaternion::Identity;
		//大きさ
		Vector3 m_scale = Vector3::One;
	};

}
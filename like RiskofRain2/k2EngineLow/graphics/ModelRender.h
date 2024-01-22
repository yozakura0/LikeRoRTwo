#pragma once

#include "MyRenderer.h"
#include "Light/SceneLight.h"
#include "postEffect/Bloom.h"

namespace nsK2EngineLow {

	class RenderingEngine;
	class SceneLight;
	class Light;

	class ModelRender :public IRenderer
	{
	public:

		ModelRender();
		~ModelRender();

		//モデルレンダーの初期化
		void Init(
			//ファイルのパス
			const char* filePath,
			//アニメーションクリップ
			AnimationClip* animationClips = nullptr,
			//アニメーションクリップの数
			int numAnimationClips = 0,
			//モデルの上方向の設定
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			//影を落とすか
			bool isShadowReceiver = false
		);

		void InitShadowModel(const char* filePath);

		//更新処理
		void Update();

		//描画処理
		void Draw(RenderContext& rc);

		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		//アニメーションの再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		//アニメーションが再生中かどうか
		bool PlayingAnimation()
		{
			return m_animation.IsPlaying();
		}

		//モデルの取得
		Model& GetModel()
		{
			return m_Model;
		}

		//座標、回転、大きさを全て設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		//座標の設定
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		//座標の設定
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//回転の設定
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//拡大率の設定
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//拡大率の設定
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}
		//アニメーションの速さの変更
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//アニメーションイベント
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		//ボーンの名前からボーン番号を取得
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		//ボーン番号からボーンを取得
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}

	private:
		//スケルトンの初期化
		void InitSkeleton(
			//ファイルパス
			const char* filepath
		);

		//アニメーションの初期化
		void InitAnimation(
			//アニメーションクリップ
			AnimationClip* animationClips,
			//アニメーションクリップの数
			int numAnimationClips,
			//モデルの上向き
			EnModelUpAxis enModelUpAxis
		);

		//各種モデルのワールド座標を更新する
		void  UpdateWorldMatrixInModes();

	private:
		//アニメーションクリップ
		AnimationClip* m_animationClips = nullptr;
		//アニメーションクリップの数
		int m_numAnimationClips = 0;
		//座標
		Vector3 m_position = Vector3::Zero;
		//回転
		Quaternion m_rotation = Quaternion::Identity;
		//拡大率
		Vector3 m_scale = Vector3::One;
		//アニメーション
		Animation m_animation;
		//
		
		//モデル
		Model m_Model;

		//影用モデル
		Model m_shadowModel;

		//モデルの初期化データ
		ModelInitData m_modelInitData;
		
		//シャドウキャスターフラグ
		bool m_isShadowCaster = true;
		
		//スケルトン
		Skeleton m_skeleton;
		//アニメーションの再生速度
		float m_animationSpeed = 1.0f;

		//Light m_light;
	};
}


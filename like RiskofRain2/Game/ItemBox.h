#pragma once
#include "Number.h"

class ItemBox : public IGameObject
{
public:

	ItemBox();
	~ItemBox();
	//アニメーションの初期化
	void InitAnimation();
	//箱を設置する
	void SetBox();
	//箱が開く
	void OpenBox();
	void Update();
	void Render(RenderContext& rc);

	//モデルレンダー
	ModelRender m_itemBoxRender;

	void SetPosition(Vector3 pos)
	{
		m_boxPos = pos;
	}
	bool OpenBoxFlag()
	{
		if (m_boxOpenedFlag)
		{
			return false;
		}

		m_boxOpenFlag = true;
		return true;
	}
	void SetBoxType(int type)
	{
		m_boxType = type;
	}

private:
	//座標
	Vector3 m_boxPos;

	//開くフラグ
	bool m_boxOpenFlag = false;

	//開いているフラグ
	bool m_boxOpenedFlag = false;

	//箱タイプ
	int m_boxType;

	//アニメーション番号
	enum m_openCommonBoxAnimation
	{
		COMMON,
		COMMONBOXOPEN_ANIMATIONNUM
	};

	//アニメーションクリップ
	AnimationClip m_commonBoxOpenAnimationClips[COMMONBOXOPEN_ANIMATIONNUM];

	//アニメーション番号
	enum m_openUncommonBoxAnimation
	{
		UNCOMMON,
		UNCOMMONBOXOPEN_ANIMATIONNUM
	};

	//アニメーションクリップ
	AnimationClip m_uncommonBoxOpenAnimationClips[UNCOMMONBOXOPEN_ANIMATIONNUM];

	//アニメーション番号
	enum m_openRareBoxAnimation
	{
		RARE,
		RAREBOXOPEN_ANIMATIONNUM
	};

	//アニメーションクリップ
	AnimationClip m_rareBoxOpenAnimationClips[RAREBOXOPEN_ANIMATIONNUM];
};
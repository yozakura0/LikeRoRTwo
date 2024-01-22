#pragma once
#include "Number.h"

class ItemBox : public IGameObject
{
public:

	ItemBox();
	~ItemBox();
	//�A�j���[�V�����̏�����
	void InitAnimation();
	//����ݒu����
	void SetBox();
	//�����J��
	void OpenBox();
	void Update();
	void Render(RenderContext& rc);

	//���f�������_�[
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
	//���W
	Vector3 m_boxPos;

	//�J���t���O
	bool m_boxOpenFlag = false;

	//�J���Ă���t���O
	bool m_boxOpenedFlag = false;

	//���^�C�v
	int m_boxType;

	//�A�j���[�V�����ԍ�
	enum m_openCommonBoxAnimation
	{
		COMMON,
		COMMONBOXOPEN_ANIMATIONNUM
	};

	//�A�j���[�V�����N���b�v
	AnimationClip m_commonBoxOpenAnimationClips[COMMONBOXOPEN_ANIMATIONNUM];

	//�A�j���[�V�����ԍ�
	enum m_openUncommonBoxAnimation
	{
		UNCOMMON,
		UNCOMMONBOXOPEN_ANIMATIONNUM
	};

	//�A�j���[�V�����N���b�v
	AnimationClip m_uncommonBoxOpenAnimationClips[UNCOMMONBOXOPEN_ANIMATIONNUM];

	//�A�j���[�V�����ԍ�
	enum m_openRareBoxAnimation
	{
		RARE,
		RAREBOXOPEN_ANIMATIONNUM
	};

	//�A�j���[�V�����N���b�v
	AnimationClip m_rareBoxOpenAnimationClips[RAREBOXOPEN_ANIMATIONNUM];
};
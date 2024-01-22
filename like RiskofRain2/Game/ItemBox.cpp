#include "stdafx.h"
#include "ItemBox.h"

ItemBox::ItemBox()
{
	
}
ItemBox::~ItemBox()
{

}

void ItemBox::InitAnimation()
{
	m_commonBoxOpenAnimationClips[COMMON].Load("Assets/animData/itembox/itembox_common_open.tka");
	m_commonBoxOpenAnimationClips[COMMON].SetLoopFlag(false);
	m_uncommonBoxOpenAnimationClips[UNCOMMON].Load("Assets/animData/itembox/itembox_uncommon_open.tka");
	m_uncommonBoxOpenAnimationClips[UNCOMMON].SetLoopFlag(false);
	m_rareBoxOpenAnimationClips[RARE].Load("Assets/animData/itembox/itembox_rare_open.tka");
	m_rareBoxOpenAnimationClips[RARE].SetLoopFlag(false);
}

void ItemBox::SetBox()
{
	InitAnimation();
	
	switch (m_boxType)
	{
	case Common:
		m_itemBoxRender.Init("Assets/modelData/itembox/box_common.tkm", m_commonBoxOpenAnimationClips, COMMONBOXOPEN_ANIMATIONNUM);
		break;
	case Uncommon:
		m_itemBoxRender.Init("Assets/modelData/itembox/box_uncommon.tkm"/*, m_uncommonBoxOpenAnimationClips, UNCOMMONBOXOPEN_ANIMATIONNUM*/);
		break;
	case Rare:
		m_itemBoxRender.Init("Assets/modelData/itembox/box_rare.tkm"/*, m_rareBoxOpenAnimationClips, RAREBOXOPEN_ANIMATIONNUM*/);
		break;
	default:
		break;
	}

	m_itemBoxRender.SetScale(Vector3(0.5f,0.5f,0.5f));
	m_itemBoxRender.SetPosition(m_boxPos);
}

void ItemBox::Update()
{
	if (m_boxOpenFlag && m_boxOpenedFlag == false)
	{
		OpenBox();
	}
	m_itemBoxRender.Update();
}

void ItemBox::OpenBox()
{
	switch (m_boxType)
	{
	case Common:
		m_itemBoxRender.PlayAnimation(COMMON, 0.0f);
		break;
	case Uncommon:
		m_itemBoxRender.PlayAnimation(UNCOMMON, 0.0f);
		break;
	case Rare:
		m_itemBoxRender.PlayAnimation(RARE, 0.0f);
		break;
	default:
		break;
	}
	m_boxOpenedFlag = true;
}

void ItemBox::Render(RenderContext& rc)
{
	//•`‰æ
	m_itemBoxRender.Draw(rc);
}
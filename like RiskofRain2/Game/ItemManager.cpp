#include "stdafx.h"
#include "ItemManager.h"
#include "Item.h"
#include "Player.h"

ItemManager::ItemManager()
{
	m_player = FindGO<Player>("player");
}

ItemManager::~ItemManager()
{
	for (int i = 0; i < m_itemNum; i++)
	{
		DeleteGO(m_item[i]);
	}
}

void ItemManager::SetItem(Vector3 pos, int boxtype)
{
	m_item[m_itemNum] = NewGO<Item>(0, "item");
	m_item[m_itemNum]->Create(pos, boxtype);
	m_itemPos[m_itemNum] = pos;

	m_itemNum++;
}

void ItemManager::Update()
{
	GetItem();
}

void ItemManager::GetItem()
{
	if (m_player->m_actionFlag)
	{
		NearItemSearchAndDelete();
	}
}

void ItemManager::NearItemSearchAndDelete()
{
	m_nearDistance = DefaultNearDistance;
	m_nearItemNum = DefaultNearItemNum;

	for (int i = 0; i < m_itemNum; i++)
	{
		if (m_item[i] == nullptr) return;

		int x = pow(m_player->m_position.x - m_itemPos[i].x, 2.0f);
		int y = pow(m_player->m_position.y - m_itemPos[i].y, 2.0f);
		int z = pow(m_player->m_position.z - m_itemPos[i].z, 2.0f);
		float distance = sqrt(x + y + z);

		//近いアイテムがあったら
		if (m_nearDistance > distance)
		{
			m_nearDistance = distance;
			m_nearItemNum = i;
		}
	}

	//近いアイテムがない
	if (m_nearItemNum == -1) { return; }


	int itemRarity = m_item[m_nearItemNum]->GetItemRarity();
	int itemNum = m_item[m_nearItemNum]->GetItemNum();

	m_player->ItemGet(itemRarity, itemNum);
	DeleteGO(m_item[m_nearItemNum]);
}
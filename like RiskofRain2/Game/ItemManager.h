#pragma once
#include "Number.h"

class Item;
class Player;

class ItemManager : public IGameObject
{
public:
	ItemManager();
	~ItemManager();
	//�A�C�e����u��
	void SetItem(Vector3 pos, int boxtype);
	//�A�C�e�������������
	void GetItem();
	//�A�C�e����T���ď�������
	void NearItemSearchAndDelete();
	void Update();

private:
	//�A�C�e�����\���������W
	Vector3 m_itemPos[ItemNum];

	//�A�C�e���̔ԍ�
	int m_itemNum = m_firstItemNum;

	//�A�C�e���̔ԍ��̏����l
	const int m_firstItemNum = 0;

	//�������߂����m�F����l
	float m_nearDistance = DefaultNearDistance;

	//�߂��A�C�e���̔ԍ�
	int m_nearItemNum = DefaultNearItemNum;

	//�������߂����m�F����l�̏����l
	const float DefaultNearDistance = 100.0f;

	//�߂��A�C�e���̔ԍ��̏����l
	const int DefaultNearItemNum = -1;

	Item* m_item[ItemNum];
	Player* m_player;
};
#pragma once
#include "Number.h"

class Item;
class Player;

class ItemManager : public IGameObject
{
public:
	ItemManager();
	~ItemManager();
	//アイテムを置く
	void SetItem(Vector3 pos, int boxtype);
	//アイテムを回収させる
	void GetItem();
	//アイテムを探して除去する
	void NearItemSearchAndDelete();
	void Update();

private:
	//アイテムが表示される座標
	Vector3 m_itemPos[ItemNum];

	//アイテムの番号
	int m_itemNum = m_firstItemNum;

	//アイテムの番号の初期値
	const int m_firstItemNum = 0;

	//距離が近いか確認する値
	float m_nearDistance = DefaultNearDistance;

	//近いアイテムの番号
	int m_nearItemNum = DefaultNearItemNum;

	//距離が近いか確認する値の初期値
	const float DefaultNearDistance = 100.0f;

	//近いアイテムの番号の初期値
	const int DefaultNearItemNum = -1;

	Item* m_item[ItemNum];
	Player* m_player;
};
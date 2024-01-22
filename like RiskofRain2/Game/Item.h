#pragma once

class Item : public IGameObject
{
public:
	void Create(Vector3 pos, int boxtype);
	//コモンのどのアイテムを出すか判定する
	void ItemJudge_common();
	//アンコモンのどのアイテムを出すか判定する
	void ItemJudge_uncommon();
	//レアのどのアイテムを出すか判定する
	void ItemJudge_rare();
	void Update();
	void Render(RenderContext& rc);

	//アイテムの番号を返す
	int GetItemNum()
	{
		return m_itemNum;
	}
	//アイテムのレアリティを返す
	int GetItemRarity()
	{
		return m_itemRarity;
	}

	//モデルレンダー
	ModelRender m_itemRender;
private:
	//座標
	Vector3 m_itemPos;

	//回転
	Quaternion m_itemRotation;

	//アイテムのレア度
	int m_itemRarity;
	//アイテムの番号
	int m_itemNum;

	//レア度普通
	const int m_common = 0;
	//レア度普通じゃない
	const int m_uncommon = 1;
	//レア度レア
	const int m_rare = 2;
};
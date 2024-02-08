#pragma once
#include "Number.h"

class Game;
class Player;
class ItemBox;
class ItemManager;

class ItemBoxManager : public IGameObject
{
public:
	ItemBoxManager();
	~ItemBoxManager();
	//箱を設置
	void SetBox();
	//座標を設定
	Vector3 SetPosition();
	void Update();
	//箱が開いた時の処理
	void OpenBoxManage();
	//近くの箱を判定する
	void NearBoxJudge(Vector3 boxPos[], int boxCount, int judgeBoxType);

private:
	//箱
	ItemBox* m_commonItemBox[CommonBoxNum];
	ItemBox* m_uncommonItemBox[UncommonBoxNum];
	ItemBox* m_rareItemBox[RareBoxNum];

	//箱の座標
	Vector3 m_commonBoxPos[CommonBoxNum];
	Vector3 m_uncommonBoxPos[UncommonBoxNum];
	Vector3 m_rareBoxPos[RareBoxNum];

	//開いているかのフラグ
	bool m_commonBoxOpenFlag[CommonBoxNum];
	bool m_uncommonBoxOpenFlag[UncommonBoxNum];
	bool m_rareBoxOpenFlag;

	//レア箱がでるかのフラグ
	bool m_setRareBoxFlag = false;

	//今のレベル
	int m_level = 0;

	//現在の箱の値段
	int m_nowBoxPrice;

	//箱の初期値段
	const int BoxDefaultPrice = 25;

	//箱の値段増加量
	const int BoxPriceMul = 7;

	//アンコモン箱の値段倍率
	const int UncommonboxPriceMul = 2;

	//レア箱の値段倍率
	const int RareboxPriceMul = 16;

	//距離が近いか確認する値
	float m_nearDistance = DefaultNearDistance;

	//近い箱の番号
	int m_nearBoxNum = DefaultNearBoxNum;

	//近い箱の種類を表す変数
	int m_nearBoxType = DefaultNearBoxType;

	//判定中の箱を表す変数
	int m_judgeBoxType = DefaultJudgeBoxType;

	//箱が開いたかを見る変数
	bool m_boxOpen;

	//箱のx、z座標の上限
	int m_boxXZLimit = 11500;

	//距離が近いか確認する値の初期値
	const float DefaultNearDistance = 100.0f;

	//近い箱の番号の初期値
	const int DefaultNearBoxNum = -1;

	//近い箱の種類を表す変数の初期値
	const int DefaultNearBoxType = 0;

	//判定中の箱を表す変数の初期値
	const int DefaultJudgeBoxType = 0;

	Game* m_game;
	Player* m_player = nullptr;
	ItemManager* m_itemManager = nullptr;

};
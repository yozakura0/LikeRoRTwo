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
	//����ݒu
	void SetBox();
	//���W��ݒ�
	Vector3 SetPosition();
	void Update();
	//�����J�������̏���
	void OpenBoxManage();
	//�߂��̔��𔻒肷��
	void NearBoxJudge(Vector3 boxPos[], int boxCount, int judgeBoxType);

private:
	//��
	ItemBox* m_commonItemBox[CommonBoxNum];
	ItemBox* m_uncommonItemBox[UncommonBoxNum];
	ItemBox* m_rareItemBox[RareBoxNum];

	//���̍��W
	Vector3 m_commonBoxPos[CommonBoxNum];
	Vector3 m_uncommonBoxPos[UncommonBoxNum];
	Vector3 m_rareBoxPos[RareBoxNum];

	//�J���Ă��邩�̃t���O
	bool m_commonBoxOpenFlag[CommonBoxNum];
	bool m_uncommonBoxOpenFlag[UncommonBoxNum];
	bool m_rareBoxOpenFlag;

	//���A�����ł邩�̃t���O
	bool m_setRareBoxFlag = false;

	//���̃��x��
	int m_level = 0;

	//���݂̔��̒l�i
	int m_nowBoxPrice;

	//���̏����l�i
	const int BoxDefaultPrice = 25;

	//���̒l�i������
	const int BoxPriceMul = 7;

	//�A���R�������̒l�i�{��
	const int UncommonboxPriceMul = 2;

	//���A���̒l�i�{��
	const int RareboxPriceMul = 16;

	//�������߂����m�F����l
	float m_nearDistance = DefaultNearDistance;

	//�߂����̔ԍ�
	int m_nearBoxNum = DefaultNearBoxNum;

	//�߂����̎�ނ�\���ϐ�
	int m_nearBoxType = DefaultNearBoxType;

	//���蒆�̔���\���ϐ�
	int m_judgeBoxType = DefaultJudgeBoxType;

	//�����J������������ϐ�
	bool m_boxOpen;

	//����x�Az���W�̏��
	int m_boxXZLimit = 11500;

	//�������߂����m�F����l�̏����l
	const float DefaultNearDistance = 100.0f;

	//�߂����̔ԍ��̏����l
	const int DefaultNearBoxNum = -1;

	//�߂����̎�ނ�\���ϐ��̏����l
	const int DefaultNearBoxType = 0;

	//���蒆�̔���\���ϐ��̏����l
	const int DefaultJudgeBoxType = 0;

	Game* m_game;
	Player* m_player = nullptr;
	ItemManager* m_itemManager = nullptr;

};
#include "stdafx.h"
#include "Game.h"
#include "ItemBoxManager.h"
#include "ItemBox.h"
#include "ItemManager.h"
#include "Player.h"

ItemBoxManager::ItemBoxManager()
{
	//箱を設置する
	SetBox();
}

ItemBoxManager::~ItemBoxManager()
{
	for (int i = 0; i < CommonBoxNum; i++)
	{
		DeleteGO(m_commonItemBox[i]);
	}
	for (int i = 0; i < UncommonBoxNum; i++)
	{
		DeleteGO(m_uncommonItemBox[i]);
	}

	DeleteGO(m_rareItemBox[0]);
}

void ItemBoxManager::SetBox()
{
	m_nowBoxPrice = BoxDefaultPrice + BoxPriceMul * m_level;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < CommonBoxNum; i++)
	{
		m_commonBoxPos[i] = SetPosition();
		m_commonItemBox[i] = NewGO<ItemBox>(0, "commonItemBox");
		m_commonItemBox[i]->SetPosition(m_commonBoxPos[i]);
		m_commonItemBox[i]->SetBoxType(Common);
		m_commonItemBox[i]->SetPrice(m_nowBoxPrice);
		m_commonItemBox[i]->SetBox();
	}
	for (int i = 0; i < UncommonBoxNum; i++)
	{
		m_uncommonBoxPos[i] = SetPosition();
		m_uncommonItemBox[i] = NewGO<ItemBox>(0, "uncommonItemBox");
		m_uncommonItemBox[i]->SetPosition(m_uncommonBoxPos[i]);
		m_uncommonItemBox[i]->SetBoxType(Uncommon);
		m_uncommonItemBox[i]->SetPrice(m_nowBoxPrice * UncommonboxPriceMul);
		m_uncommonItemBox[i]->SetBox();
	}

	if (m_setRareBoxFlag)
	{
		m_rareBoxPos[0] = SetPosition();
		m_rareItemBox[0] = NewGO<ItemBox>(0, "rareItemBox");
		m_rareItemBox[0]->SetPosition(m_rareBoxPos[0]);
		m_rareItemBox[0]->SetBoxType(Rare);
		m_rareItemBox[0]->SetPrice(m_nowBoxPrice * RareboxPriceMul);
		m_rareItemBox[0]->SetBox();
	}
	/*m_commonItemBox[0] = NewGO<ItemBox>(0, "commonItemBox");
	m_commonItemBox[0]->SetPosition({ 1000.0f,50.0f,1000.0f });
	m_commonItemBox[0]->SetBoxType(Common);
	m_commonItemBox[0]->SetBox();*/
}

Vector3 ItemBoxManager::SetPosition()
{
	int x = rand() % m_boxXZLimit - m_boxXZLimit / 2;
	int z = rand() % m_boxXZLimit - m_boxXZLimit / 2;
	Vector3 pos = { (float)x, 10000.0f, (float)z };
	CharacterController boxController;
	boxController.Init(5.0f, 5.0f, pos);
	Vector3 moveSpeed = { 0.0f,0.0f,0.0f };

	while (true)
	{
		moveSpeed.y -= 490.0f * g_gameTime->GetFrameDeltaTime();
		boxController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());

		if (boxController.IsOnGround())
		{
			return boxController.GetPosition();
		}
	}
}

void ItemBoxManager::Update()
{
	if (m_game == nullptr)
	{
		m_game = FindGO<Game>("game");
	}
	else
	{
		m_level = m_game->GetEnemyLevel();
	}

	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}
	if (m_itemManager == nullptr)
	{
		m_itemManager = FindGO<ItemManager>("itemManager");
	}
	if (m_player != nullptr && m_itemManager != nullptr)
	{
		OpenBoxManage();
	}
}

void ItemBoxManager::OpenBoxManage()
{
	if (m_player->m_actionFlag)
	{
		m_nearDistance = DefaultNearDistance;
		m_nearBoxNum = DefaultNearBoxNum;
		m_nearBoxType = DefaultNearBoxType;
		m_judgeBoxType = DefaultJudgeBoxType;

		//箱との距離を計算
		NearBoxJudge(m_commonBoxPos, CommonBoxNum, m_judgeBoxType);
		m_judgeBoxType++;
		NearBoxJudge(m_uncommonBoxPos, UncommonBoxNum, m_judgeBoxType);
		m_judgeBoxType++;
		NearBoxJudge(m_rareBoxPos, RareBoxNum, m_judgeBoxType);

		//近い箱がない
		if (m_nearBoxNum == -1)
		{
			//m_player->m_actionFlag = false;
			return;
		}
		else
		{
			switch (m_nearBoxType)
			{
			case 0:
				//お金が足りないか
				if (m_player->GetMoney() < m_commonItemBox[m_nearBoxNum]->GetPrice())
				{
					return;
				}
				//すでに開いてるか
				if (m_commonItemBox[m_nearBoxNum]->OpenBoxFlag() == false)
				{
					return;
				}

				m_itemManager->SetItem(m_commonBoxPos[m_nearBoxNum], m_nearBoxType);
				m_player->DecMoney(m_commonItemBox[m_nearBoxNum]->GetPrice());
				break;
			case 1:
				//お金が足りないか
				if (m_player->GetMoney() < m_uncommonItemBox[m_nearBoxNum]->GetPrice())
				{
					return;
				}
				//すでに開いてるか
				if (m_uncommonItemBox[m_nearBoxNum]->OpenBoxFlag() == false)
				{
					return;
				}
				
				m_itemManager->SetItem(m_uncommonBoxPos[m_nearBoxNum], m_nearBoxType);
				m_player->DecMoney(m_uncommonItemBox[m_nearBoxNum]->GetPrice());
				break;
			case 2:
				//お金が足りないか
				if (m_player->GetMoney() < m_rareItemBox[m_nearBoxNum]->GetPrice())
				{
					return;
				}
				//すでに開いてるか
				if (m_rareItemBox[m_nearBoxNum]->OpenBoxFlag() == false)
				{
					return;
				}

				m_itemManager->SetItem(m_rareBoxPos[m_nearBoxNum], m_nearBoxType);
				m_player->DecMoney(m_rareItemBox[m_nearBoxNum]->GetPrice());
				break;
			default:
				break;
			}

			m_player->m_actionFlag = false;

			return;
		}
	}
}

void ItemBoxManager::NearBoxJudge(Vector3 boxPos[], int boxCount, int judgeBoxType)
{
	//箱との距離を計算
	for (int i = 0; i < boxCount; i++)
	{
		int x = pow(m_player->m_position.x - boxPos[i].x, 2.0f);
		int y = pow(m_player->m_position.y - boxPos[i].y, 2.0f);
		int z = pow(m_player->m_position.z - boxPos[i].z, 2.0f);
		float distance = sqrt(x + y + z);

		//近い箱があったら
		if (m_nearDistance > distance)
		{
			m_nearDistance = distance;
			m_nearBoxNum = i;
			m_nearBoxType = judgeBoxType;
		}
	}
}
#include "stdafx.h"
#include "E_Golem.h"
#include "Player.h"

#include "graphics/effect/EffectEmitter.h"

E_Golem::E_Golem()
{
	m_golemAnimationClips[GOLEM_PUNCH].Load("Assets/animData/enemy/golem_punch.tka");
	m_golemAnimationClips[GOLEM_PUNCH].SetLoopFlag(false);
	m_golemAnimationClips[GOLEM_MOVE].Load("Assets/animData/enemy/golem_move.tka");
	m_golemAnimationClips[GOLEM_MOVE].SetLoopFlag(true);
	m_golemAnimationClips[GOLEM_BREAK].Load("Assets/animData/enemy/golem_break.tka");
	m_golemAnimationClips[GOLEM_BREAK].SetLoopFlag(false);

	m_player = FindGO<Player>("player");

	// ナビメッシュを構築。
	m_nvmMesh.Init("Assets/nvm/a.tkn");

	m_golemRender.AddAnimationEvent
	([&](const wchar_t* clipName, const wchar_t* eventName)
		{
			OnAnimationEvent(clipName, eventName);
		}
	);

}

E_Golem::~E_Golem()
{
	if (m_golemStateNumber == BROKEN)
	{
		m_player->AddMoney(m_dropMoney);
	}
}

void E_Golem::ShowGolem()
{
	m_golemController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_golemRender.Init("Assets/modelData/enemy/golem.tkm", m_golemAnimationClips, GOLEM_ANIMNUM);
	m_golemRender.SetPosition(m_pos);

	SetStatus();

	m_bone = m_golemRender.GetBone(m_golemRender.FindBoneID(L"head"));
	//Vector3  i = m_bone->SetRotation()

	
}

void E_Golem::SetStatus()
{
	m_HP += AddHPtoLv * m_Level;
	m_damage += AddDamagetoLv * m_Level;
}

void E_Golem::Move()
{
	bool isEnd;

	m_previousPos = m_pos;
	// パス検索
	m_pathFiding.Execute(
		m_path,							// 構築されたパスの格納先
		m_nvmMesh,						// ナビメッシュ
		m_pos,						// 開始座標
		m_player->m_position,			// 移動目標座標
		PhysicsWorld::GetInstance(),	// 物理エンジン	
		50.0f,							// AIエージェントの半径
		200.0f							// AIエージェントの高さ。
	);


	// パス上を移動する。
	m_pos = m_path.Move(
		m_pos,
		2.0f,
		isEnd
	);

	//Rot
	Quaternion qgolem;
	qgolem.SetRotation(m_bone->GetBonePosition(), m_player->m_position);

	//座標
	auto pos = m_bone->GetBonePosition();
	m_bone->SetRotation(qgolem);

	m_golemController.SetPosition(m_pos);
	m_golemController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_golemRender.SetPosition(m_pos);
	m_golemRender.Update();
	
}

void E_Golem::Rotation()
{
	/*if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}*/

	//float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotation(m_previousPos, m_pos);

	m_golemRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
	
}

void E_Golem::Attack()
{
	//攻撃していない時、攻撃をどうするか判定
	if (m_notAttack)
	{
		int x = pow(m_player->m_position.x - m_pos.x, 2.0f);
		int y = pow(m_player->m_position.y - m_pos.y, 2.0f);
		int z = pow(m_player->m_position.z - m_pos.z, 2.0f);
		float distance = sqrt(x + y + z);

		//プレイヤーが近い
		if (m_nearDistance > distance && m_closeRangedAttackCoolFlag == false)
		{
			//近距離攻撃
			m_closeRangedAttackFlag = true;
			m_notAttack = false;
		}
		//中距離にいる
		else if (m_longDistance > distance && m_rangedAttackCoolFlag == false)
		{
			//遠距離攻撃
			m_rangedAttackFlag = true;
			m_notAttack = false;
		}
		//かなり遠い
		else
		{
			//何もしない
			m_closeRangedAttackFlag = false;
			m_rangedAttackFlag = false;
		}
	}
	else
	{
		if (m_rangedAttackFlag)
		{
			RangedAttack();
			return;
		}
		else if (m_closeRangedAttackFlag)
		{
			CloseRangedAttack();
			return;
		}
	}
}

void E_Golem::RangedAttack()
{
	m_notAttack = true;
	m_rangedAttackCoolFlag = true;
}

void E_Golem::CloseRangedAttack()
{
	if (m_attackForAnim)
	{
		MakeAttackCollision();
	}
	if (m_golemRender.PlayingAnimation() == false)
	{
		m_notAttack = true;
		m_closeRangedAttackCoolFlag = true;
	}
}

void E_Golem::AttackCoolCount()
{
	if (m_closeRangedAttackCoolFlag)
	{
		m_closeRangedAttackCool += g_gameTime->GetFrameDeltaTime();
		if (m_closeRangedAttackCool >= m_closeRangedAttackCoolLimit)
		{
			m_closeRangedAttackCool = 0;
			m_closeRangedAttackCoolFlag = false;
		}
	}
	if (m_rangedAttackCoolFlag)
	{
		m_rangedAttackCool += g_gameTime->GetFrameDeltaTime();
		if (m_rangedAttackCool >= m_rangedAttackCoolLimit)
		{
			m_rangedAttackCool = 0;
			m_rangedAttackCoolFlag = false;
		}
	}
}

void E_Golem::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//アニメーションのキーでフラグを変更
	if (wcscmp(eventName, L"attack_start") == 0)
	{
		m_attackForAnim = true;
	}
	else if (wcscmp(eventName, L"attack_end") == 0)
	{
		m_attackForAnim = false;
	}
}

void E_Golem::MakeAttackCollision()
{
	if (m_attackForAnim)
	{
		auto collisionObject = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_pos;
		collisionPosition.y += 100.0f;
		collisionPosition += m_forward * 80.0f;

		collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, 100.0f);

		collisionObject->SetName("golem_attack");

		if (collisionObject->IsHit(m_player->m_characterController))
		{
			m_attackForAnim = false;
		}
	}
}

void E_Golem::Damage()
{
	//無敵時間のカウント
	if (m_invincibleFlag)
	{
		m_invincible += g_gameTime->GetFrameDeltaTime();

		if (m_invincible < InvincibleTime)
		{
			return;
		}
	}
	m_invincibleFlag = false;
	m_invincible = 0.0f;

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_bullet");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_golemController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("frostRelic_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_golemController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dynamite_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_golemController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("gasoline_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_golemController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	if (m_invincibleFlag)
	{
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);

		effectEmitter->Init(0);
		effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
		effectEmitter->SetPosition({ m_pos.x,m_pos.y + 40.0f,m_pos.z });
		effectEmitter->Play();
	}
}

void E_Golem::StateManage()
{
	if (m_HP <= 0)
	{
		m_golemStateNumber = BROKEN;
	}
	else if (m_closeRangedAttackFlag)
	{
		m_golemStateNumber = ATTACK_CLOSE;
	}
	else if(m_rangedAttackFlag)
	{
		m_golemStateNumber = ATTACK_RANGE;
	}
	else
	{
		m_golemStateNumber = MOVE;
	}
}

void E_Golem::AnimationState()
{
	switch (m_golemStateNumber)
	{
	case MOVE:
		m_golemRender.PlayAnimation(GOLEM_MOVE, 0.2f);
		m_golemRender.SetAnimationSpeed(1.0f);
		break;
	case ATTACK_CLOSE:
		m_golemRender.PlayAnimation(GOLEM_PUNCH, 0.2f);
		m_golemRender.SetAnimationSpeed(1.0f);
		break;
	case ATTACK_RANGE:

		break;
	case BROKEN:
		m_golemRender.PlayAnimation(GOLEM_BREAK, 0.2f);
		m_golemRender.SetAnimationSpeed(1.0f);
		break;
	default:
		break;
	}
}

void E_Golem::Update()
{
	if (m_golemStateNumber == BROKEN)
	{
		m_golemRender.Update();


		if (m_golemRender.PlayingAnimation() == false)
		{
			EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);

			effectEmitter->Init(1);
			effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
			effectEmitter->SetPosition({ m_pos.x,m_pos.y + 40.0f,m_pos.z });
			effectEmitter->Play();

			DeleteGO(this);
		}
		return;
	}

	Damage();



	Move();
	Rotation();

	Attack();
	AttackCoolCount();

	/*StateManage();
	AnimationState();*/

	//m_bone->SetRotation(m_bone->GetBonePosition(), m_player->m_position);
	//m_bone->SetRotation(float(5.0f));
	
	m_golemRender.Update();

	
}

void E_Golem::Render(RenderContext& rc)
{
	m_golemRender.Draw(rc);
}
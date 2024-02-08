#include "stdafx.h"
#include "E_Drone.h"

#include "Player.h"

#include "graphics/effect/EffectEmitter.h"

E_Drone::E_Drone()
{
	m_player = FindGO<Player>("player");

	// ナビメッシュを構築。
	m_nvmMesh.Init("Assets/nvm/a.tkn");
}

E_Drone::~E_Drone()
{
	if (/*m_redWispStateNumber == BROKEN*/m_HP <= 0)
	{
		m_player->AddMoney(m_dropMoney);
	}
}

void E_Drone::ShowDrone()
{
	m_pos.y += 100.0f;

	m_droneController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_droneRender.Init("Assets/modelData/enemy/drone.tkm");
	m_droneRender.SetPosition(m_pos);

	m_startEmitter = NewGO<EffectEmitter>(0);

	m_startEmitter->Init(2);
	m_startEmitter->SetScale({ 10.0f,10.0f,10.0f });
	m_startEmitter->SetPosition({ m_pos.x,m_pos.y + 40.0f,m_pos.z });
	m_startEmitter->Play();

	/*m_redWispRender.PlayAnimation(REDWISP_ENTRY, 0.2f);
	m_redWispRender.SetAnimationSpeed(1.0f);*/

	SetStatus();
}

void E_Drone::SetStatus()
{
	m_HP += AddHPtoLv * m_Level;
	m_damage += AddDamagetoLv * m_Level;
}

void E_Drone::Move()
{
	bool isEnd;

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
		5.0f,
		isEnd
	);

	//座標を高くして浮いてるようにする
	Vector3 resultPos = m_pos;
	resultPos.y += 100.0f;

	m_droneController.SetPosition(resultPos);
	m_droneController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	m_droneRender.SetPosition(resultPos);
	m_droneRender.Update();
}

void E_Drone::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotationY(-angle);

	m_droneRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void E_Drone::Attack()
{
	if (m_notAttack)
	{
		int x = pow(m_player->m_position.x - m_pos.x, 2.0f);
		int y = pow(m_player->m_position.y - m_pos.y, 2.0f);
		int z = pow(m_player->m_position.z - m_pos.z, 2.0f);
		float distance = sqrt(x + y + z);

		//プレイヤーとの距離が近い
		if (m_nearDistance > distance && m_attackCoolFlag == false)
		{
			//攻撃する
			m_notAttack = false;
		}
	}
	else
	{
		RangedAttack();
	}
}

void E_Drone::RangedAttack()
{
	m_attackCoolFlag = true;
	m_notAttack = true;
}

void E_Drone::AttackCoolCount()
{
	if (m_attackCoolFlag)
	{
		m_attackCool += g_gameTime->GetFrameDeltaTime();

		if (m_attackCool >= m_attackCoolLimit)
		{
			m_attackCool = 0.0f;
			m_attackCoolFlag = false;
		}
	}
}

//void E_Drone::StateManage()
//{
//	if (m_HP <= 0)
//	{
//		m_redWispStateNumber = BROKEN;
//	}
//	else if (m_notAttack == false)
//	{
//		m_redWispStateNumber = ATTACK_RANGE;
//	}
//	else
//	{
//		m_redWispStateNumber = MOVE;
//	}
//}

//void E_Drone::AnimationState()
//{
//	switch (m_redWispStateNumber)
//	{
//	case CREATE:
//		m_redWispRender.PlayAnimation(REDWISP_ENTRY, 0.2f);
//		m_redWispRender.SetAnimationSpeed(1.0f);
//		break;
//	case MOVE:
//		m_redWispRender.PlayAnimation(REDWISP_MOVE, 0.2f);
//		m_redWispRender.SetAnimationSpeed(1.0f);
//		break;
//	case ATTACK_RANGE:
//		m_redWispRender.PlayAnimation(REDWISP_ATTACK, 0.2f);
//		m_redWispRender.SetAnimationSpeed(1.0f);
//		break;
//	case BROKEN:
//		m_redWispRender.PlayAnimation(REDWISP_BREAK, 0.2f);
//		m_redWispRender.SetAnimationSpeed(1.0f);
//		break;
//	default:
//		break;
//	}
//}

void E_Drone::Damage()
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

	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_bullet");

	for (auto collision : collisions)
	{
		if (collision->IsHit(m_droneController))
		{
			//ダメージ
			int m_receiveDamage = m_player->m_playerDamage;

			//受けたダメージ分体力を減らす
			m_HP -= m_receiveDamage;

			m_invincibleFlag = true;
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

void E_Drone::Update()
{
	if (m_HP <= 0)
	{
		m_droneRender.Update();

		if (m_droneRender.PlayingAnimation() == false)
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

	if (m_startEmitter->IsPlay())
	{
		m_droneRender.Update();

		return;
	}

	Move();
	Rotation();
	Attack();
	AttackCoolCount();
	/*StateManage();
	AnimationState();*/
	m_droneRender.Update();
}

void E_Drone::Render(RenderContext& rc)
{
	m_droneRender.Draw(rc);
}
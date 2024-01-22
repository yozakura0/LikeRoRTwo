#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "ShotManager.h"
#include "Item.h"
#include "collision/CollisionObject.h"

Player::Player()
{
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_position
	);

	m_playerAnimationClips[ANIMATION_IDLE].Load("Assets/animData/idle.tka");
	m_playerAnimationClips[ANIMATION_IDLE].SetLoopFlag(true);

	//���f����ǂݍ���
	m_playerRender.Init("Assets/modelData/unityChan.tkm", m_playerAnimationClips, ANIMATION_NUM, enModelUpAxisY);

	//m_playerItemList_rare[frostRelic][havingItemNum]++;
}

Player::~Player()
{

}

void Player::Update()
{
	if (m_gameCamera == nullptr)
	{
		m_gameCamera = FindGO<GameCamera>("gameCamera");
	}
	else
	{
		Attack();

		////�f�o�b�O:���C�Փˍ��W�ɋ����o��
		//m_testRen.Init("Assets/modelData/testBall.tkm");
		//m_testRen.SetPosition(m_gameCamera->m_rayHitPos);
		//m_testRen.Update();
	}

	m_oneSecond += g_gameTime->GetFrameDeltaTime();

	Move();
	Turn();
	Action();
	ItemPower();
	Damaged();
	Dead();
	LevelUp();
	StatusSetUp();

	if (m_oneSecond >= 1.0f)
	{
		//���R��
		m_playerHP += m_autoHeal;

		//1�b�J�E���g�����Z�b�g
		m_oneSecond = ZeroSecond;
	}

	//���݂̗̑͂��ő�̗͂𒴂��Ȃ�
	if (m_playerHP > m_playerMaxHP)
	{
		m_playerHP = m_playerMaxHP;
	}

	m_playerRender.PlayAnimation(ANIMATION_IDLE, 0.2f);

	m_playerRender.Update();

	//�f�o�b�O:���W�̕\��
	swprintf_s(m_posText, 256, L"x:%f,y:%f,z:%f", m_gameCamera->m_rayHitPos.x, m_gameCamera->m_rayHitPos.y, m_gameCamera->m_rayHitPos.z);
	m_fontRender.SetText(m_posText);
	m_fontRender.SetPosition({ 0.0f,0.0f });
	m_fontRender.SetScale(1.0f);
	m_fontRender.SetColor(Vector4::White);

	swprintf_s(m_posText, 256, L"x:%f,y:%f,z:%f", m_position.x, m_position.y, m_position.z);
	m_posfontRender.SetText(m_posText);
	m_posfontRender.SetPosition({ 0.0f,50.0f });
	m_posfontRender.SetScale(1.0f);
	m_posfontRender.SetColor(Vector4::White);

}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	Vector2 stickL = { g_pad[0]->GetLStickXF(),g_pad[0]->GetLStickYF() };

	//�J�����̑O�����ƉE�������擾
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();

	//XZ���ʂł̑O�����A�E�����ɕϊ�
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();

	//XZ�����̈ړ����x���N���A
	m_moveSpeed.x = FirstMoveSpeed.x;
	m_moveSpeed.z = FirstMoveSpeed.z;

	//���ւ̈ړ����x�����Z
	m_moveSpeed += cameraForward * stickL.y * m_playerMoveMultiplier * m_moveBoost;
	//�E�ւ̈ړ����x�����Z
	m_moveSpeed += cameraRight * stickL.x * m_playerMoveMultiplier * m_moveBoost;

	//�ǉ��ŉ�������(�_�b�V��)
	if (g_pad[0]->IsPress(enButtonLB3))
	{
		if (m_dashFlag)
		{
			m_dashFlag = false;
		}
		else
		{
			m_dashFlag = true;
		}
	}

	if (m_dashFlag == true)
	{
		m_moveSpeed.x *= 1.5f;
		m_moveSpeed.z *= 1.5f;
	}

	//�W�����v����
	//A��������A���n�ʂɂ�����W�����v
	if (g_pad[0]->IsTrigger(enButtonA) && m_characterController.IsOnGround())
	{
		m_moveSpeed.y = JumpPower;
	}

	//y�̈ړ����x�����炵������
	m_moveSpeed.y -= FallSpeed * g_gameTime->GetFrameDeltaTime();

	//�L�����N�^�[�R���g���[���[�ō��W���X�V����
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	//�n�ʂɒ�����
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = FirstMoveSpeed.y;
	}

	//���W��ݒ�
	m_playerRender.SetPosition(m_position);
}

void Player::Turn()
{
	//�ړ����Ă��Ȃ����A
	if (fabsf(m_moveSpeed.x) < NoneMoveJudge
		&& fabsf(m_moveSpeed.z) < NoneMoveJudge)
	{
		//�������X�L�b�v����
		return;
	}

	//��]����p�x�����߂�
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	//�p�x��ݒ肷��
	m_playerRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Player::LevelUp()
{
	if (m_playerEXP >= m_playerLevel * NeedPlayerEXPMultiplier)
	{
		m_playerEXP -= m_playerLevel * NeedPlayerEXPMultiplier;
		m_playerLevel++;
		m_needPlayerEXP = m_playerLevel * NeedPlayerEXPMultiplier;
	}
}

void Player::ItemPower()
{
	for (int comItem = 0; comItem < CommonNum; comItem++)
	{
		if (m_playerItemList_common[comItem][havingItem] == 0)
		{
			continue;
		}

		switch (comItem)
		{
		case gasoline:
			if (m_killEnemyFlag)
			{
				for (int i = 0; i < m_killEnemyCount; i++)
				{
					auto collisionObject = NewGO<CollisionObject>(0);

					Vector3 collisionPosition = m_killEnemyPos[i];

					//�K�\�����̍U���͈͂��v�Z
					float sphereRadius
						= DefaultGasolineRange + BoostGasolineRange
						* m_playerItemList_common[gasoline][havingItemNum] - 1;

					collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, sphereRadius);

					collisionObject->SetName("gasoline_attack");
				}
				
			}
			break;
		case armorPlate:
			m_abatement = 5 * m_playerItemList_common[armorPlate][havingItemNum];
			break;
		case Crowber:
			//m_playerItemList_common[Crowber][havingItemNum];
			break;
		case tougherTimes:
			m_blockProb = 1 - 1 / (0.15 * m_playerItemList_common[tougherTimes][havingItemNum] + 1);
			break;
		case lensMakerGlasses:
			m_criticalBoost = 10 * m_playerItemList_common[lensMakerGlasses][havingItemNum];
			break;
		/*case armorPiercingRounds:

			break;*/
		case goatHoof:
			m_moveBoost = 1 + (0.1 * m_playerItemList_common[goatHoof][havingItemNum]);
			break;
		default:
			break;
		}

	}
	for (int uncomItem = 0; uncomItem < UncommonNum; uncomItem++)
	{
		if (m_playerItemList_uncommon[uncomItem][havingItem] == 0)
		{
			continue;
		}

		switch (uncomItem)
		{
		case Dynamite:
			if (m_killEnemyFlag)
			{
				for (int i = 0; i < m_killEnemyCount; i++)
				{
					auto collisionObject = NewGO<CollisionObject>(0);

					Vector3 collisionPosition = m_killEnemyPos[i];

					//�_�C�i�}�C�g�̍U���͈͂��v�Z
					float sphereRadius
						= DefaultDynamiteRange
						+ BoostDynamiteRange * m_playerItemList_uncommon[Dynamite][havingItemNum] - 1;

					collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, sphereRadius);

					collisionObject->SetName("dynamite_attack");
				}
			}
			break;
		/*case hopooFeather:

			break;*/
		case infusion:
			if (m_killEnemyFlag)
			{
				for (int i = 0; i < m_killEnemyCount; i++)
				{
					m_hpBoost += m_playerItemList_uncommon[infusion][havingItemNum];
					
				}
				if (m_hpBoost > BoostInfusionLimit * m_playerItemList_uncommon[infusion][havingItemNum])
				{
					m_hpBoost = BoostInfusionLimit * m_playerItemList_uncommon[infusion][havingItemNum];
				}
			}
			break;
		case roseBuckler:
			m_armorBoost = 0;
			if (m_dashFlag)
			{
				m_armorBoost = 30 * m_playerItemList_uncommon[roseBuckler][havingItemNum];
			}
			break;
		default:
			break;
		}
	}
	for (int rareItem = 0; rareItem < RareNum; rareItem++)
	{
		if (m_playerItemList_rare[rareItem][havingItem] == 0)
		{
			continue;
		}

		switch (rareItem)
		{
		case frostRelic:
			if (m_killEnemyFlag)
			{
				m_frostRelicRepetitive++;
				
				if (m_frostRelicRepetitive > m_playerItemList_rare[frostRelic][havingItemNum])
				{
					m_frostRelicRepetitive = m_playerItemList_rare[frostRelic][havingItemNum];
				}
				
				m_frostRelicTime = FrostRelicTimeLimit;
			}
			if (m_frostRelicRepetitive)
			{
				auto collisionObject = NewGO<CollisionObject>(0);

				Vector3 collisionPosition = m_position;

				//�X�̈╨�̍U���͈͂��v�Z
				float sphereRadius
					= DefaultFrostRelicRange
					+ BoostFrostRelicRange * m_frostRelicRepetitive - 1;

				collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, sphereRadius);

				collisionObject->SetName("frostRelic_attack");

				m_frostRelicTime -= g_gameTime->GetFrameDeltaTime();

				if (m_frostRelicTime <= 0.0f)
				{
					m_frostRelicRepetitive = 0;
				}
			}
			break;
		default:
			break;
		}
	}

	m_killEnemyFlag = false;
}

void Player::Action()
{
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_actionFlag = true;
	}
	else
	{
		m_actionFlag = false;
	}
}

void Player::ItemGet(int itemRarity, int itemNum)
{
	switch (itemRarity)
	{
	case Common:
		if (m_playerItemList_common[itemNum][0] == 0)
		{
			m_playerItemList_common[itemNum][0] = 1;
		}
		m_playerItemList_common[itemNum][1]++;
		break;
	case Uncommon:
		if (m_playerItemList_uncommon[itemNum][0] == 0)
		{
			m_playerItemList_uncommon[itemNum][0] = 1;
		}
		m_playerItemList_uncommon[itemNum][1]++;
		break;
	case Rare:
		if (m_playerItemList_rare[itemNum][0] == 0)
		{
			m_playerItemList_rare[itemNum][0] = 1;
		}
		m_playerItemList_rare[itemNum][1]++;
		break;
	default:
		break;
	}
}

void Player::Damaged()
{
	//���G���Ԃ̃J�E���g
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

	const auto& collisions_g = g_collisionObjectManager->FindCollisionObjects("golem_attack");

	for (auto collision : collisions_g)
	{
		if (collision->IsHit(m_characterController))
		{
			//���_���[�W
			m_receiveDamage = 20;

			//�����擾
			float randNum = rand() % 100;
			//�U�����Ւf����
			if (randNum < m_blockProb)
			{
				continue;
			}

			//��_���{������Z
			m_receiveDamage *= m_playerTakenDamageMultiply;

			//�Œ�l�̌y��������
			m_receiveDamage -= m_abatement;
	
			//��_���ɍŒ�ۏ������
			if (m_receiveDamage <= 0)
			{
				m_receiveDamage = 1;
			}

			//�󂯂��_���[�W���̗͂����炷
			m_playerHP -= m_receiveDamage;

			//���G�t���O�𗧂Ă�
			m_invincibleFlag = true;
		}
	}

	const auto& collisions_b = g_collisionObjectManager->FindCollisionObjects("beetle_attack");

	for (auto collision : collisions_b)
	{
		if (collision->IsHit(m_characterController))
		{
			//���_���[�W
			m_receiveDamage = 8;

			//�����擾
			float randNum = rand() % 100;
			//�U�����Ւf����
			if (randNum < m_blockProb)
			{
				continue;
			}

			//��_���{������Z
			m_receiveDamage *= m_playerTakenDamageMultiply;

			//�Œ�l�̌y��������
			m_receiveDamage -= m_abatement;

			//��_���ɍŒ�ۏ������
			if (m_receiveDamage <= 0)
			{
				m_receiveDamage = 1;
			}

			//�󂯂��_���[�W���̗͂����炷
			m_playerHP -= m_receiveDamage;

			//���G�t���O�𗧂Ă�
			m_invincibleFlag = true;
		}
	}

	////�����_���[�W����
	//if (m_position.y < -1500)
	//{
	//	m_playerHP -= m_playerMaxHP * 0.3;

	//	if (m_playerHP <= 0)
	//	{
	//		m_playerHP = 1;
	//	}

	//	Vector3 returnVec = { 0.0f,60.0f,0.0f };
	//	returnVec = returnVec - m_position;

	//	m_position = { m_position + returnVec };
	//	m_characterController.SetPosition(m_position);
	//	Vector3 cameraPos = m_gameCamera->GetPosition();
	//	cameraPos = cameraPos + returnVec;
	//	m_gameCamera->SetPosition(cameraPos);
	//}
}

void Player::Dead()
{
	if (m_playerHP > 0) return;

	m_deadFlag = true;
}

void Player::Attack()
{
	AttackInterval();

	if (g_pad[0]->IsTrigger(enButtonRB2) && m_normalShot)
	{
		ShotManager* shotManager = NewGO<ShotManager>(0);
		Vector3 shotPosition = m_position;
		shotPosition.y += 70.0f;
		shotManager->SetPosition(shotPosition);
		//Quaternion m_shotRotation;
		//m_shotRotation.SetRotation(m_forward, m_gameCamera->m_rayHitPos);
		//shotManager->SetMoveSpeed(m_forward);
		//m_shotRotation.Apply(m_moveSpeed);
		Vector3 m_shotMoveSpeed = { m_gameCamera->m_rayHitPos - shotPosition };
		shotManager->SetMoveSpeed(m_shotMoveSpeed);
		//shotManager->SetRotation(m_shotRotation);
		shotManager->NormalShot();
		m_normalShot = false;
	}
}

void Player::AttackInterval()
{
	if (m_normalShot == false)
	{
		m_normalShotInterval += g_gameTime->GetFrameDeltaTime();
		if (m_normalShotInterval > NormalShotIntervalLimit)
		{
			m_normalShotInterval = 0.0f;
			m_normalShot = true;
		}
	}
}

void Player::StatusSetUp()
{
	//�ő�̗�
	m_playerMaxHP = FirstPlayerMaxHP + (m_playerLevel - 1) * HpUpbyLevel;
	m_playerMaxHP += m_hpBoost;

	//���R������
	m_autoHeal = FirstAutoHeal + (m_playerLevel - 1) * AutoHealUpbyLevel;
	m_autoHeal += m_healBoost;

	//��b�_���[�W
	m_playerDamage = FirstPlayerDamage + (m_playerLevel - 1) * AttackUpbyLevel;

	//�A�[�}�[��
	m_playerArmor = FirstPlayerArmor;
	m_playerArmor += m_armorBoost;

	//��_���{��
	m_playerTakenDamageMultiply = FirstPlayerTakenDamageMultiply - m_playerArmor / (100 + abs(m_playerArmor));

	//�N���e�B�J���m��
	m_criticalRate = FirstCriticalRate;
	m_criticalRate += m_criticalBoost;
}

void Player::Render(RenderContext& rc)
{
	//�f�o�b�O:�h���[
	m_fontRender.Draw(rc);
	m_posfontRender.Draw(rc);
	m_testRen.Draw(rc);

	if (m_deadFlag) return;
	
	//�`��
	m_playerRender.Draw(rc);
}
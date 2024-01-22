#pragma once
namespace nsK2EngineLow {

	//�K�v�o���l�̌v�Z�Ɏg���{��
	const int NeedPlayerEXPMultiplier = 13.0f;

	//�ő�̗͂̏����l
	const float FirstPlayerMaxHP = 110;

	//���R�����͂̏����l
	const float FirstAutoHeal = 1.0f;

	//��b�_���[�W�̏����l
	const float FirstPlayerDamage = 12.0f;

	//�A�[�}�[�ʂ̏����l
	const int FirstPlayerArmor = 0;

	//���x���ɉ����ďオ��̗�
	const int HpUpbyLevel = 33;

	//���x���ɉ����ďオ�鎡����
	const float AutoHealUpbyLevel = 0.2f;

	//���x���ɉ����ďオ��U����
	const float AttackUpbyLevel = 3.0f;

	//�����蔻��̔��a
	const float CapsuleRadius = 20.0f;

	//�����蔻��̍���
	const float CapsuleHeight = 100.0f;

	//�W�����v��
	const int JumpPower = 400.0f;

	//�������x
	const int FallSpeed = 490.0f;

	//�ʏ�U���Ԋu
	const float NormalShotIntervalLimit = 0.25f;

	//�L�����̖��G����
	const float InvincibleTime = 0.2f;

	//0�b
	const float ZeroSecond = 0.0f;

	//�K�\�����̊�b�U���͈�
	const float DefaultGasolineRange = 120.0f;
	//�K�\�����̒ǉ��U���͈�
	const float BoostGasolineRange = 40.0f;
	//�_�C�i�}�C�g�̊�b�U���͈�
	const float DefaultDynamiteRange = 120.0f;
	//�_�C�i�}�C�g�̒ǉ��U���͈�
	const float BoostDynamiteRange = 24.0f;
	//�����t�̌��ʏ��
	const int BoostInfusionLimit = 100;
	//�X�̈╨�̊�b�U���͈�
	const float DefaultFrostRelicRange = 180.0f;
	//�X�̈╨�̒ǉ��U���͈�
	const float BoostFrostRelicRange = 120.0f;
	//�X�̈╨�̍U���͈͑�����
	const float SpreadIceRelicRange = 20.0f;
	//�X�̈╨�̌��ʌp������
	const float FrostRelicTimeLimit = 5.0f;
}
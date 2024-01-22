#pragma once
namespace nsK2EngineLow {

	//必要経験値の計算に使う倍率
	const int NeedPlayerEXPMultiplier = 13.0f;

	//最大体力の初期値
	const float FirstPlayerMaxHP = 110;

	//自然治癒力の初期値
	const float FirstAutoHeal = 1.0f;

	//基礎ダメージの初期値
	const float FirstPlayerDamage = 12.0f;

	//アーマー量の初期値
	const int FirstPlayerArmor = 0;

	//レベルに応じて上がる体力
	const int HpUpbyLevel = 33;

	//レベルに応じて上がる治癒力
	const float AutoHealUpbyLevel = 0.2f;

	//レベルに応じて上がる攻撃力
	const float AttackUpbyLevel = 3.0f;

	//当たり判定の半径
	const float CapsuleRadius = 20.0f;

	//当たり判定の高さ
	const float CapsuleHeight = 100.0f;

	//ジャンプ力
	const int JumpPower = 400.0f;

	//落下速度
	const int FallSpeed = 490.0f;

	//通常攻撃間隔
	const float NormalShotIntervalLimit = 0.25f;

	//キャラの無敵時間
	const float InvincibleTime = 0.2f;

	//0秒
	const float ZeroSecond = 0.0f;

	//ガソリンの基礎攻撃範囲
	const float DefaultGasolineRange = 120.0f;
	//ガソリンの追加攻撃範囲
	const float BoostGasolineRange = 40.0f;
	//ダイナマイトの基礎攻撃範囲
	const float DefaultDynamiteRange = 120.0f;
	//ダイナマイトの追加攻撃範囲
	const float BoostDynamiteRange = 24.0f;
	//注入液の効果上限
	const int BoostInfusionLimit = 100;
	//氷の遺物の基礎攻撃範囲
	const float DefaultFrostRelicRange = 180.0f;
	//氷の遺物の追加攻撃範囲
	const float BoostFrostRelicRange = 120.0f;
	//氷の遺物の攻撃範囲増加量
	const float SpreadIceRelicRange = 20.0f;
	//氷の遺物の効果継続時間
	const float FrostRelicTimeLimit = 5.0f;
}
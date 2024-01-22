#include "stdafx.h"
#include "GameCamera.h"

#include "player.h"

GameCamera::GameCamera()
{
	m_physicsWorld = PhysicsWorld::GetInstance();

	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(0.0f, 100.0f, 400.0f);

	//プレイヤーのインスタンスを探す
	m_player = FindGO<Player>("player");

	//ばねカメラの初期化
	m_springCamera.Init(
		*g_camera3D,
		1000.0f,
		true,
		5.0f
	);

	m_springCamera.SetFar(15000.0f);
}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//注視点を計算
	m_target = m_player->m_position;

	//ちょっと上を見る
	m_target.y += 200.0f;
	//m_target += g_camera3D->GetForward() * 1.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//パッドの入力を使ってカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);

	//X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);

	//カメラの回転の上限をチェック
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.9f)
	{
		//カメラが上を向きすぎている
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f)
	{
		//カメラが下を向きすぎている
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算
	m_pos = m_target + m_toCameraPos;

	//カメラに注視点と視点を設定
	m_springCamera.SetTarget(m_target);
	m_springCamera.SetPosition(m_pos);

	//カメラの更新
	m_springCamera.Update();

	//座標を実際の座標に置き換え
	m_pos = m_springCamera.GetRealPosition();

	SearchObstacle();
}

void GameCamera::SearchObstacle()
{
	Vector3 vectorTtoP = m_target - m_pos;
	vectorTtoP.Normalize();
	//レイの終点の座標を計算
	Vector3 rayEndPos = { m_pos.x + vectorTtoP.x * 3000, m_pos.y + vectorTtoP.y * 3000, m_pos.z + vectorTtoP.z * 3000 };
	
	//レイを発射、衝突座標を記録する
	bool rayHit = m_physicsWorld->RayTest(m_pos, rayEndPos, m_rayHitPos);
	
	//レイが当たらなかった時、衝突座標をレイの終点にする
	if (rayHit == false)
	{
		m_rayHitPos = rayEndPos;
	}
}
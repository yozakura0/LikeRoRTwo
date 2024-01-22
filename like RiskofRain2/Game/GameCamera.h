#pragma once

#include "camera/SpringCamera.h"

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void SearchObstacle();

	Player* m_player;
	Vector3 m_toCameraPos = Vector3::One;
	SpringCamera m_springCamera;

	Vector3 m_rayHitPos;

	Vector3 GetPosition()
	{
		return m_pos;
	}
	void SetPosition(Vector3 pos)
	{
		//m_springCamera.SetPosition(pos);
		m_pos = pos;
		g_camera3D->SetPosition(m_pos);
	}

private:
	Vector3 m_pos;
	Vector3 m_target;
	PhysicsWorld* m_physicsWorld;
};


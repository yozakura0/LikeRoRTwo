#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Render(RenderContext& rc);

private:
	//モデルレンダー
	ModelRender m_bgModelRender;

	//座標
	Vector3 m_bgPos = { 0.0f,0.0f,0.0f };

	//静的物理オブジェクト
	PhysicsStaticObject m_physicsStaticObj;
};


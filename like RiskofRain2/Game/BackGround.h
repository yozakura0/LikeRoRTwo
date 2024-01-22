#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Render(RenderContext& rc);

private:
	//���f�������_�[
	ModelRender m_bgModelRender;

	//���W
	Vector3 m_bgPos = { 0.0f,0.0f,0.0f };

	//�ÓI�����I�u�W�F�N�g
	PhysicsStaticObject m_physicsStaticObj;
};


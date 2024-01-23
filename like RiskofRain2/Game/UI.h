#pragma once

class UI : public IGameObject
{
public:
	UI();
	~UI();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_shotTargetRender;
	SpriteRender m_timerRender;
private:
	const Vector3 m_shotTargetPos = { 0.0f,0.0f,0.0f };
	//const Vector3 m_

};


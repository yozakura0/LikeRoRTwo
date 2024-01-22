#include "stdafx.h"
#include "UI.h"

UI::UI()
{
	m_shotTargetRender.Init("Assets/sprite/UI/shotTarget.DDS", 32.0f, 32.0f);
}

UI::~UI()
{

}

void UI::Update()
{
	m_shotTargetRender.SetPosition(m_shotTargetPos);
	m_shotTargetRender.Update();
}

void UI::Render(RenderContext& rc)
{
	m_shotTargetRender.Draw(rc);
}
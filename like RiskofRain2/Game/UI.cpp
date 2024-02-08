#include "stdafx.h"
#include "UI.h"
#include "Game.h"
#include "Player.h"

UI::UI()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_shotTargetRender.Init("Assets/sprite/UI/shotTarget.DDS", 32.0f, 32.0f);
	m_timerbackRender.Init("Assets/sprite/UI/timerUI.DDS", 200.0f, 70.0f);
	m_screenFilter.Init("Assets/sprite/UI/damageScreen.DDS", 1920.0f, 1080.0f);

	m_timerbackRender.SetPosition(m_timerPos);
	m_timerbackRender.Update();
	m_shotTargetRender.SetPosition(m_shotTargetPos);
	m_shotTargetRender.Update();
}

UI::~UI()
{

}

void UI::Update()
{
	TimerTextSet();
	MoneyTextSet();
	FilterCleanness();
}

void UI::FilterCleanness()
{
	if (m_player->IsReceiveDamage() == false)
	{
		m_mulAlpha = 0.0f;
		return;
	}

	m_mulAlpha += 0.5f;
	if (m_mulAlpha > 1.0f)
	{
		m_mulAlpha = 1.0f;
	}
	m_screenFilter.SetMulColor({ 1.0f,1.0f,1.0f,m_mulAlpha });
}

void UI::TimerTextSet()
{
	if (m_second < 10)
	{
		swprintf_s(m_timeText, 256, L"%d : %d%d", m_minute, 0, m_second);
	}
	else
	{
		swprintf_s(m_timeText, 256, L"%d : %d", m_minute, m_second);
	}
	m_timerRender.SetText(m_timeText);
	m_timerRender.SetPosition({ 800.0f,490.0f });
	m_timerRender.SetScale(1.0f);
	m_timerRender.SetColor(Vector4::White);
}

void UI::MoneyTextSet()
{
	swprintf_s(m_moneyText, 256, L"%d", m_player->GetMoney());
	m_moneyRender.SetText(m_moneyText);
	m_moneyRender.SetPosition({ -800.0f,490.0f });
	m_moneyRender.SetScale(1.0f);
	m_moneyRender.SetColor(Vector4::Yellow);
}

void UI::Render(RenderContext& rc)
{
	if (m_player->IsReceiveDamage())
	{
		m_screenFilter.Draw(rc);
	}

	m_shotTargetRender.Draw(rc);
	m_timerbackRender.Draw(rc);
	m_timerRender.Draw(rc);
	m_moneyRender.Draw(rc);
}
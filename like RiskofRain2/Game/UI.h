#pragma once

class Game;
class Player;

class UI : public IGameObject
{
public:
	UI();
	~UI();
	void Update();
	void TimerTextSet();
	void MoneyTextSet();
	void FilterCleanness();
	void Render(RenderContext& rc);

	//照準レンダー
	SpriteRender m_shotTargetRender;
	//タイマーの背景レンダー
	SpriteRender m_timerbackRender;
	//ダメージを受けたときの画面フィルター
	SpriteRender m_screenFilter;
	//タイマーレンダー
	FontRender m_timerRender;
	//所持金レンダー
	FontRender m_moneyRender;

	//時間を設定する
	void SetTime(int minute, int second)
	{
		m_minute = minute;
		m_second = second;
	}
private:
	const Vector3 m_shotTargetPos = { 0.0f,0.0f,0.0f };
	const Vector3 m_timerPos = { 850.0f,480.0f,0.0f };

	float m_mulAlpha = 0.0f;

	wchar_t m_timeText[256];
	int m_minute;
	int m_second;

	wchar_t m_moneyText[256];

	Game* m_game;
	Player* m_player;
};


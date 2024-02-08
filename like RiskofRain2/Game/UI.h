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

	//�Ə������_�[
	SpriteRender m_shotTargetRender;
	//�^�C�}�[�̔w�i�����_�[
	SpriteRender m_timerbackRender;
	//�_���[�W���󂯂��Ƃ��̉�ʃt�B���^�[
	SpriteRender m_screenFilter;
	//�^�C�}�[�����_�[
	FontRender m_timerRender;
	//�����������_�[
	FontRender m_moneyRender;

	//���Ԃ�ݒ肷��
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


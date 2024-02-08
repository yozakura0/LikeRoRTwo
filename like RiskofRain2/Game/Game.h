#pragma once

class Player;
class BackGround;
class GameCamera;
class ItemBoxManager;
class ItemManager;
class EnemyManager;
class UI;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Timer();
	void Render(RenderContext& rc);

	//�o�߃t���[����
	int m_frameCount = FirstFrameCount;
	//�������l
	const int FirstFrameCount = 0;
	
	//�b�����v
	int m_secondCount = FirstSecondCount;
	const int FirstSecondCount = 0;

	//�������v
	int m_minuteCount = FirstMinuteCount;
	//�������l
	const int FirstMinuteCount = 0;

	//�G�̃��x�����擾����
	int GetEnemyLevel()
	{
		return m_enemyLevel;
	}

private:
	//�G�̃��x��
	int m_enemyLevel = 0;

	//���f���̍��W
	Vector3 m_modelPos = { 0.0f,0.0f,0.0f };

	bool flag = true;

	//SceneLight m_sceneLight;
	//modelSLight m_light;
	int m_pointNum;

	//��
	SkyCube* m_skyCube = nullptr;
	//�v���C���[
	Player* m_player = nullptr;
	//�w�i
	BackGround* m_backGround = nullptr;
	//�Q�[���J����
	GameCamera* m_gameCamera = nullptr;
	//���}�l�[�W���[
	ItemBoxManager* m_itemBoxManager = nullptr;
	//�A�C�e���}�l�[�W���[
	ItemManager* m_itemManager = nullptr;
	//�G�}�l�[�W���[
	EnemyManager* m_enemyManager = nullptr;
	//UI
	UI* m_ui = nullptr;
};


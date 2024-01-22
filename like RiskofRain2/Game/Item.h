#pragma once

class Item : public IGameObject
{
public:
	void Create(Vector3 pos, int boxtype);
	//�R�����̂ǂ̃A�C�e�����o�������肷��
	void ItemJudge_common();
	//�A���R�����̂ǂ̃A�C�e�����o�������肷��
	void ItemJudge_uncommon();
	//���A�̂ǂ̃A�C�e�����o�������肷��
	void ItemJudge_rare();
	void Update();
	void Render(RenderContext& rc);

	//�A�C�e���̔ԍ���Ԃ�
	int GetItemNum()
	{
		return m_itemNum;
	}
	//�A�C�e���̃��A���e�B��Ԃ�
	int GetItemRarity()
	{
		return m_itemRarity;
	}

	//���f�������_�[
	ModelRender m_itemRender;
private:
	//���W
	Vector3 m_itemPos;

	//��]
	Quaternion m_itemRotation;

	//�A�C�e���̃��A�x
	int m_itemRarity;
	//�A�C�e���̔ԍ�
	int m_itemNum;

	//���A�x����
	const int m_common = 0;
	//���A�x���ʂ���Ȃ�
	const int m_uncommon = 1;
	//���A�x���A
	const int m_rare = 2;
};
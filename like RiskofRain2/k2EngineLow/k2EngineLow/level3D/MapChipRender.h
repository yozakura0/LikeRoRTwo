#pragma once

namespace nsK2EngineLow {
	struct LevelRenderObjectData;

	struct MapChipData
	{
		//���W
		Vector3 position;
		//�傫��
		Vector3 scale;
		//��]
		Quaternion rotation;

	};

	class MapChipRender :public Noncopyable
	{
	public:
		MapChipRender(const LevelRenderObjectData& objData,const char* filepath);

		//�}�b�v�`�b�v�f�[�^��ǉ�
		void AddMapChipData(const LevelRenderObjectData& objData);

		//������
		void Init();

		//���f���̍X�V
		void Update();

		//�`�揈��
		void Draw(RenderContext& rc);

	private:
		//���f�������_�[
		ModelRender m_modelRender;
		//�}�b�v�`�b�v�f�[�^�̃��X�g
		std::vector<MapChipData> m_mapChipDataVector;
		//tkm�t�@�C���p�X
		std::unique_ptr<const char*> m_filepath;
		//�ÓI�����I�u�W�F�N�g�̃X�}�[�g�|�C���^�̔z��
		std::vector<std::unique_ptr<PhysicsStaticObject>> m_physicsStaticObjectPtrVector;
		//�}�b�v�`�b�v�f�[�^�̐�
		int m_mapChipDataNum;
	};

}
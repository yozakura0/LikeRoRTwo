#pragma once

#include "TklFile.h"

namespace nsK2EngineLow {
	class MapChipRender;

	//�I�u�W�F�N�g��
	struct LevelRenderObjectData
	{
		//���W
		Vector3 position;
		//��]
		Quaternion rotation;
		//�g�嗦
		Vector3 scale;
		//���O
		const wchar_t* name;
		int number = 0;

		//�����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}

		//���O���O����v���邩���ׂ�
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);

			//���O��������false��Ԃ�
			if (len > namelen)
			{
				return false;
			}

			return wcsncmp(n, name, len) == 0;
		}

	};


	class LevelRender :public Noncopyable
	{
	private:
		using MapChipRenderPtr = std::shared_ptr<MapChipRender>;
	public:
		//���x����������
		void Init(
			//tkl�t�@�C���p�X
			const char* filepath, 
			//�I�u�W�F�N�g�쐬���̏������t�b�N���邽�߂̊֐��I�u�W�F�N�g
			std::function<bool(LevelRenderObjectData& objData)> hookFunc
		);

		//�X�V����
		void Update();

		//���f����`��
		void Draw(RenderContext& rc);

	private:
		//�}�b�v�`�b�v���쐬
		void CreateMapChipRender(const LevelRenderObjectData& objData, const char* filePath);

		//tkl�t�@�C���̍s���ϊ�����
		void MatrixTklToLevel();

	private:
		//�{�[��Ptr
		using BonePtr = std::unique_ptr<Bone>;
		//�{�[���̃��X�g
		std::vector<BonePtr> m_bonelist;
		//�s��̃��X�g
		std::unique_ptr<Matrix[]> m_matrixlist;
		//�}�b�v�`�b�v�̉ϒ��z��
		std::map < std::string, MapChipRenderPtr > m_mapChipRenderPtrs;
		//tkl�t�@�C��
		TklFile m_tklFile;
	};

}
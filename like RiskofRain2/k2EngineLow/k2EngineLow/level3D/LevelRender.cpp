#include "k2EngineLowPreCompile.h"
#include "LevelRender.h"
#include "MapChipRender.h"

#include "TklFile.h"

namespace nsK2EngineLow {

	void LevelRender::CreateMapChipRender(const LevelRenderObjectData& objData, const char* filePath)
	{
		std::string key = filePath;

		//�}�b�v�`�b�v�����_�[�ɂ܂��t�b�N����Ă��Ȃ�������
		if (m_mapChipRenderPtrs.count(key) == 0)
		{
			//�}�b�v�`�b�v���쐬
			auto mapChipRender = std::make_shared<MapChipRender>(objData, filePath);
			m_mapChipRenderPtrs[key] = mapChipRender;
		}
		else
		{
			auto& mapChipRender = m_mapChipRenderPtrs[key];
			//�}�b�v�`�b�v�f�[�^��ǉ�
			mapChipRender->AddMapChipData(objData);
		}
	}

	void LevelRender::Init(
		const char* filePath,
		std::function<bool(LevelRenderObjectData& objData)> hookFunc
	)
	{
		//tkl�t�@�C�������[�h
		m_tklFile.Load(filePath);

		MatrixTklToLevel();

		for (int i = 1; i < m_bonelist.size(); i++) {
			auto bone = m_bonelist[i].get();
			if (bone->GetParentBoneNo() == 0) {

				//�}�b�v�`�b�v���쐬
				
				//�s�񂩂�|�W�V�������쐬
				LevelRenderObjectData levelObjData;
				bone->CalcWorldTRS(levelObjData.position, levelObjData.rotation, levelObjData.scale);

				//Zup��Yup�̕ύX
				float fix = levelObjData.position.y;
				levelObjData.position.y = levelObjData.position.z;
				levelObjData.position.z = -fix;

				fix = levelObjData.rotation.y;
				levelObjData.rotation.y = levelObjData.rotation.z;
				levelObjData.rotation.z = -fix;

				std::swap(levelObjData.scale.y, levelObjData.scale.z);

				levelObjData.name = m_bonelist[i]->GetName();
				std::wstring name = levelObjData.name;

				//@�����邩�ǂ�������
				int pos = static_cast<int>(name.find('@'));
				//@�������@��̐������擾
				if (pos != std::wstring::npos)
				{
					std::wstring number = name.substr(static_cast<size_t>(pos) + 1);

					levelObjData.number = std::stoi(number.c_str());
				}

				//�p�X�̍쐬
				wchar_t filePath[256];
				swprintf_s(filePath, L"Assets/modelData/%s.tkm", levelObjData.name);

				//�}���`�o�C�g�ɕϊ�
				
				//�x�[�X�̕�����
				size_t origsize = wcslen(filePath) + 1;
				//�ϊ�����������
				size_t convertedChars = 0;
				//�}���`�o�C�g�i�[�p
				char strCon[] = "";
				//�T�C�Y
				size_t strConSize = (strlen(strCon) + 1) * 2;
				//�ϊ���̃T�C�Y
				const size_t newsize = origsize * 2;
				//�A����̃T�C�Y
				char* cFilePath = new char[newsize + strConSize];
				//�}���`�o�C�g�ɕϊ�
				wcstombs_s(&convertedChars, cFilePath, newsize, filePath, _TRUNCATE);
				//������̘A��
				_mbscat_s((unsigned char*)cFilePath, newsize + strConSize, (unsigned char*)strCon);

				bool isHooked = false;
				if (hookFunc != nullptr) {
					isHooked = hookFunc(levelObjData);
				}

				//hook��false�Ȃ܂܂Ȃ��
				if (isHooked == false) {
					//�}�b�v�`�b�v�����_�[���쐬
					CreateMapChipRender(levelObjData, cFilePath);
				}

			}
		}

		for (auto& mapChipRender : m_mapChipRenderPtrs)
		{
			//�}�b�v�`�b�v�����_�[��������
			mapChipRender.second->Init();
		}
	}

	void LevelRender::MatrixTklToLevel()
	{
		m_tklFile.QuaryObject(

			[&](TklFile::SObject& tklObj) 
			{
				//�R�s�[
				//�o�C���h�|�[�Y
				Matrix bindPoseMatrix;
				memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
				memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
				memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
				memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
				bindPoseMatrix.m[0][3] = 0.0f;
				bindPoseMatrix.m[1][3] = 0.0f;
				bindPoseMatrix.m[2][3] = 0.0f;
				bindPoseMatrix.m[3][3] = 1.0f;

				// �o�C���h�|�[�Y�̋t�s��
				Matrix invBindPoseMatirx;
				memcpy(invBindPoseMatirx.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
				memcpy(invBindPoseMatirx.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
				memcpy(invBindPoseMatirx.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
				memcpy(invBindPoseMatirx.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
				invBindPoseMatirx.m[0][3] = 0.0f;
				invBindPoseMatirx.m[1][3] = 0.0f;
				invBindPoseMatirx.m[2][3] = 0.0f;
				invBindPoseMatirx.m[3][3] = 1.0f;

				wchar_t boneName[256];

				// tkl�̃I�u�W�F�N�g���̌^�����C�h�����ɕϊ�
				mbstowcs(
					// �ϊ�����char�^�̕�����
					boneName, 
					// �ϊ����ʂ�wchar_t�^������
					tklObj.name.get(), 
					// �T�C�Y
					256
				);

				BonePtr bone = std::make_unique<Bone>(
					boneName,
					bindPoseMatrix,
					invBindPoseMatirx,
					tklObj.parentNo,
					tklObj.no
				);
			
				//�{�[����ς�
				m_bonelist.push_back(std::move(bone));
			}

		);
	}

	void LevelRender::Update()
	{
		for (auto& mapChipRender : m_mapChipRenderPtrs)
		{
			//�}�b�v�`�b�v�����_�[���X�V����
			mapChipRender.second->Update();
		}
	}

	void LevelRender::Draw(RenderContext& rc)
	{
		for (auto mapChipRenderPtr : m_mapChipRenderPtrs)
		{
			mapChipRenderPtr.second->Draw(rc);
		}
	}
}

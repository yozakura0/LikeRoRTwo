#pragma once

namespace nsK2EngineLow {

	//�V�[���̃f�B���N�V�������C�g�̍ő吔
	const int MAX_DIRECTIONAL_LIGHT = 1;
	//�V�[���̃|�C���g���C�g�̍ő吔
	const int MAX_POINT_LIGHT = 8;
	//�V�[���̃X�|�b�g���C�g�̍ő吔
	const int MAX_SPOT_LIGHT = 8;
	
	const int NUM_SHADOW_MAPS = 3;
	
	//�V���h�E�}�b�v
	enum
	{
		SHADOW_MAP_AREA_NEAR,		//�߉e�͈͂̃V���h�E�}�b�v
		SHADOW_MAP_AREA_MIDDLE,		//���e�͈͂̃V���h�E�}�b�v
		SHADOW_MAP_AREA_FAR,		//���e�͈͂̃V���h�E�}�b�v
		
	};
}
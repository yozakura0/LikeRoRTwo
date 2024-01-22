#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "BackGround.h"

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);

	//g_camera3D->SetPosition(cameraPos);
	//g_camera3D->SetTarget(cameraTarget);
	g_sceneLight->SetAmbient(Vector3(0.1f, 0.1f, 0.1f));

	NewGO<Game>(0, "game");

	g_sceneLight->SetDirPosition(Vector3(0.0f, 0.0f, -1.0f));
	g_sceneLight->SetDirColor(Vector3(2.0f, 2.0f, 2.0f));

	/*g_sceneLight->SetPtPosition(pointLPos);
	g_sceneLight->SetPtColor(Vector3(10.0f, 10.0f, 10.0f));
	g_sceneLight->SetPtRange(100.0f);*/

	Vector3 ligPos = { 0,300,0 };

	RenderContext& renderContext = g_graphicsEngine->GetRenderContext();

	Vector3 lightColor = { 2.0f,2.0f,2.0f };

	//////////////////////////////
	// �����܂�
	//////////////////////////////

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();
		//g_sceneLight->SetEyePos(g_camera3D->GetPosition());

		g_renderingEngine->SetRenderTarget(renderContext);

		//lightColor.x += g_pad[0]->GetLStickXF() * 0.5f;
		//lightColor.y += g_pad[0]->GetLStickXF() * 0.5f;
		//lightColor.z += g_pad[0]->GetLStickXF() * 0.5f;
		//g_sceneLight->SetDirColor(lightColor);

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		//g_renderingEngine->Update();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		g_renderingEngine->Execute(renderContext);

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();

		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}


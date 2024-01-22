#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "BackGround.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	// k2EngineLowの初期化。
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
	// ここまで
	//////////////////////////////

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();
		//g_sceneLight->SetEyePos(g_camera3D->GetPosition());

		g_renderingEngine->SetRenderTarget(renderContext);

		//lightColor.x += g_pad[0]->GetLStickXF() * 0.5f;
		//lightColor.y += g_pad[0]->GetLStickXF() * 0.5f;
		//lightColor.z += g_pad[0]->GetLStickXF() * 0.5f;
		//g_sceneLight->SetDirColor(lightColor);

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		//g_renderingEngine->Update();

		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_k2EngineLow->ExecuteRender();

		g_renderingEngine->Execute(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}


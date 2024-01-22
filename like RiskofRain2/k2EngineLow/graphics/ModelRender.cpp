#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"
#include "Light/SceneLight.h"

namespace nsK2EngineLow 
{

	ModelRender::ModelRender()
	{
		//m_light = new modelSLight();
		//g_sceneLight = m_sceneLight;
		//mslight->directionalLights.Init();
	}

	ModelRender::~ModelRender()
	{

	}

	/*void ModelRender::SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData)
	{
		modelInitData.m_vsSkinEntryPointFunc = "VSMainUsePreComputedVertexBuffer";
		modelInitData.m_vsEntryPointFunc = "VSMainUsePreComputedVertexBuffer";
	}*/

	void ModelRender::Init(
		const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isShadowReceiver
	)
	{

		if (isShadowReceiver)
		{
			//モデル、シェーダーを設定
			m_modelInitData.m_tkmFilePath = filePath;
			m_modelInitData.m_fxFilePath = "Assets/shader/ProjectionShadowReceiver.fx";

			m_modelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->m_shadowMap.GetRenderTargetTexture();

			m_modelInitData.m_expandConstantBuffer = (void*)&g_renderingEngine->m_lightCamera.GetViewProjectionMatrix();
			m_modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->m_lightCamera.GetViewProjectionMatrix());
			m_modelInitData.m_tkmFilePath = filePath;

			m_Model.Init(m_modelInitData);
		}
		else
		{
			//モデル、シェーダー、モデルの上方向を設定
			m_modelInitData.m_tkmFilePath = filePath;
			m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
			m_modelInitData.m_modelUpAxis = enModelUpAxis;

			//SetupVertexShaderEntryPointFunc(m_modelInitData);
			//スケルトンを初期化
			InitSkeleton(filePath);
			//アニメーションを初期化
			InitAnimation(animationClips, numAnimationClips, enModelUpAxis);

			//定数バッファに送る
			m_modelInitData.m_expandConstantBuffer = &g_sceneLight->GetSceneLight();
			m_modelInitData.m_expandConstantBufferSize = sizeof(g_sceneLight->GetSceneLight());

			m_Model.Init(m_modelInitData);
			InitShadowModel(filePath);

		}

	}

	void ModelRender::InitSkeleton(const char* filepath)
	{
		//スケルトンのデータを読み込み
		std::string skeletonFilePath = filepath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;

		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips
			);

			//スケルトンの有無で頂点シェーダーのエントリーポイントなどを変更
			/*if (m_skeleton.GetNumBones() != 0)
			{*/
				m_modelInitData.m_skeleton = &m_skeleton;
				m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			/*}
			else
			{
				m_modelInitData.m_vsSkinEntryPointFunc = "VSMain";
			}*/
		}
	}

	void ModelRender::InitShadowModel(const char* filePath)
	{
		ModelInitData shadowModelInitData;

		shadowModelInitData.m_fxFilePath = "Assets/shader/DrawProjectionShadowMap.fx";
		shadowModelInitData.m_tkmFilePath = filePath;

		m_shadowModel.Init(shadowModelInitData);
		/*m_shadowModel.UpdateWorldMatrix(

		)*/
	}

	/*void ModelRender::InitComputeAnimatoinVertexBuffer(
		const char* tkmFilePath,
		EnModelUpAxis enModelUpAxis)
	{
		StructuredBuffer* worldMatrxiArraySB = nullptr;
		
		m_computeAnimationVertexBuffer.Init(
			tkmFilePath,
			m_skeleton.GetNumBones(),
			m_skeleton.GetBoneMatricesTopAddress(),
			enModelUpAxis,
			worldMatrxiArraySB
		);
	}*/

	void ModelRender::UpdateWorldMatrixInModes()
	{
		m_Model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}

	void ModelRender::Update()
	{
		UpdateWorldMatrixInModes();

		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_Model.GetWorldMatrix());
		}

		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{

		//リストにモデルを追加
		g_renderingEngine->AddRenderObject(m_Model);

		if (m_isShadowCaster)
		{
			//リストに影用のモデルを追加
			g_renderingEngine->AddRenderObjectToShadow(m_shadowModel);
		}

		//m_Model.Draw(rc);
		
		//bloom.OnRender(rc);
	}
}
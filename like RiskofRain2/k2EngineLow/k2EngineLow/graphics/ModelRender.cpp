#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow 
{

	ModelRender::ModelRender()
	{
		
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
		EnModelUpAxis enModelUpAxis
	)
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

		//ライトの情報を初期化する
		sdirectionalLight.Setup();
		spointLight.SetUp();
		sspotLight.SetUp();
		shemiLight.SetUp();
		sotherLight.Setup();

		//sceneLight.Init();

		//ライトの情報を大量に持ってくる
		light.directionalLight.ligDirection = sdirectionalLight.GetligDir();
		light.directionalLight.ligColor = sdirectionalLight.GetColor();
		light.pointLight.ptPosition = spointLight.GetPosition();
		light.pointLight.ptColor = spointLight.GetColor();
		light.pointLight.ptRange = spointLight.GetRange();
		light.ambientLight = sotherLight.GetAmbientLight();
		light.eyePos = sotherLight.GetEyePos();
		light.spotLight.spPosition = sspotLight.GetPosition();
		light.spotLight.spColor = sspotLight.GetColor();
		light.spotLight.spRange = sspotLight.GetRange();
		light.spotLight.spDirection = sspotLight.GetDirection();
		light.spotLight.spAngle = sspotLight.GetAngle();
		light.hemiLight.groundColor = shemiLight.GetGroundColor();
		light.hemiLight.skyColor = shemiLight.GetSkyColor();
		light.hemiLight.groundNormal = shemiLight.GetGroundNormal();

		//定数バッファに送る
		m_modelInitData.m_expandConstantBuffer = &light;
		m_modelInitData.m_expandConstantBufferSize = sizeof(light);
		
		m_Model.Init(m_modelInitData);
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
		//通常描画
		//g_renderingEngine->AddRenderObject(this);

		m_Model.Draw(rc);
		
		//bloom.OnRender(rc);
	}
}
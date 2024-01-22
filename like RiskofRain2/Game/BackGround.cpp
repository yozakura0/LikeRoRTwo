#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_bgModelRender.Init("Assets/modelData/stage/stage.tkm", nullptr, 0, enModelUpAxisZ, true);
	m_bgModelRender.SetShadowCasterFlag(false);
	m_bgModelRender.SetPosition(m_bgPos);

	//静的物理オブジェクトを作成
	m_physicsStaticObj.CreateFromModel(m_bgModelRender.GetModel(), m_bgModelRender.GetModel().GetWorldMatrix());

}

BackGround::~BackGround()
{

}

void BackGround::Update()
{
	m_bgModelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	//描画
	m_bgModelRender.Draw(rc);
}
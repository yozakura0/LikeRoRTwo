#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_bgModelRender.Init("Assets/modelData/stage/stage.tkm", nullptr, 0, enModelUpAxisZ, true);
	m_bgModelRender.SetShadowCasterFlag(false);
	m_bgModelRender.SetPosition(m_bgPos);

	//�ÓI�����I�u�W�F�N�g���쐬
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
	//�`��
	m_bgModelRender.Draw(rc);
}
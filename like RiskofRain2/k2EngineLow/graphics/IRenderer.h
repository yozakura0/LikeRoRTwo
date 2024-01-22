#pragma once

namespace nsK2EngineLow {

	class IRenderer : public Noncopyable 
	{
	public:
		//�V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈��
		virtual void OnRenderShadowMap(
			RenderContext& rc
		)
		{

		}

		//2D�`��ւ̕`��p�X����Ă΂�鏈��
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		//�����_���[���`�悷��I�u�W�F�N�g�̍ő���W�ƍŏ����W���擾
		virtual void GetAABB(Vector3& vMax, Vector3& vMin, bool& isGet)
		{
			vMax.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			vMin.Set(FLT_MAX, FLT_MAX, FLT_MAX);
			isGet = false;
		}
	};
}
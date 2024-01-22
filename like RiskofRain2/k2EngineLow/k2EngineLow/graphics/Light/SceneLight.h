#pragma once

namespace nsK2EngineLow {

	//�f�B���N�V�������C�g�̍\����
	struct SDirectionalLight
	{
		//���C�g�̕���
		Vector3 ligDirection;
		////�p�f�B���O
		//float pad;
		//���C�g�̃J���[
		Vector4 ligColor;

		void Setup()
		{
			ligColor.x = 1.2f;
			ligColor.y = 1.2f;
			ligColor.z = 1.2f;

			ligDirection.x = 1.0f;
			ligDirection.y = -1.0f;
			ligDirection.z = -1.0f;
			ligDirection.Normalize();
		}

		//���C�g�̕������擾
		const Vector3& GetligDir() const
		{
			return ligDirection;
		}
		//���C�g�̃J���[���擾
		const Vector4& GetColor() const
		{
			return ligColor;
		}
	};

	//�|�C���g���C�g�̍\����
	struct SPointLight
	{
	private:
		//���C�g�̈ʒu
		Vector3 ptPosition;
		//���C�g�̃J���[
		Vector3 ptColor;
		//���C�g�̉e���͈�
		float ptRange;

	public:
		void SetUp()
		{
			ptPosition = { 0,50,150 };
			ptColor = { 15,0,0 };
			ptRange=100;
		}

		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->ptPosition = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->ptColor = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}

		//�͈͂�ݒ�
		void SetRange(float range)
		{
			ptRange = range;
		}

		//���W���擾
		const Vector3& GetPosition() const
		{
			return ptPosition;
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return ptColor;
		}
		//�e���͈͂��擾
		const float& GetRange() const
		{
			return ptRange;
		}
	};

	//�X�|�b�g���C�g�̍\����
	struct SSpotLight
	{
		//�ʒu
		Vector3 spPosition;
		float pad3;
		//�J���[
		Vector3 spColor;
		//�e���͈�
		float spRange;
		//�ˏo����
		Vector3 spDirection;
		//�ˏo�p�x
		float spAngle;

	public:
		void SetUp()
		{
			spPosition = { 0,50,150 };
			spColor = { 10,10,10 };
			spRange = 100;

			spDirection = { 1.0,-1.0,1.0 };
			spDirection.Normalize();

			spRange = 300;
			spAngle = Math::DegToRad(25.0f);
		}

		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->spPosition = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->spColor = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}

		//�͈͂�ݒ�
		void SetRange(float range)
		{
			this->spRange = range;
		}

		//�ˏo������ݒ�
		void SetDirection(const Vector3& direction)
		{
			this->spDirection = direction;
		}
		void SetDirection(float x,float y,float z)
		{
			SetDirection({ x,y,z });
		}

		//�͈͂�ݒ�
		void SetAngle(float angle)
		{
			this->spAngle = Math::DegToRad(angle);
		}

		//���W���擾
		const Vector3& GetPosition() const
		{
			return spPosition;
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return spColor;
		}
		//�e���͈͂��擾
		const float& GetRange() const
		{
			return spRange;
		}
		//�ˏo�������擾
		const Vector3& GetDirection() const
		{
			return spDirection;
		}
		//�ˏo�p�x���擾
		const float& GetAngle() const
		{
			return spAngle;
		}
	};

	struct SHemiLight
	{
		//�n�ʐF
		Vector3 groundColor;
		//�V���F
		Vector3 skyColor;
		//�n�ʂ̖@��
		Vector3 groundNormal;

		void SetUp()
		{
			groundColor = { 0.7f,0.5f,0.3f };
			skyColor = { 0.15f,0.7f,0.95f };
			groundNormal = { 0.0f,1.0f,0.0f };
		}

		//�n�ʐF���擾
		const Vector3& GetGroundColor() const
		{
			return groundColor;
		}
		//�V���F���擾
		const Vector3& GetSkyColor() const
		{
			return skyColor;
		}
		//�n�ʂ̖@�����擾
		const Vector3& GetGroundNormal() const
		{
			return groundNormal;
		}
	};

	struct SOtherLight
	{
		//�J�����̈ʒu
		Vector3 eyePos;
		
		//����
		Vector3 ambientLight;

	public:
		void Setup()
		{
			//����
			ambientLight.x = 0.3f;
			ambientLight.y = 0.3f;
			ambientLight.z = 0.3f;

			eyePos = g_camera3D->GetPosition();
		}

		//�J�����̈ʒu���擾
		const Vector3& GetEyePos() const
		{
			return eyePos;
		}
		//�������擾
		const Vector3& GetAmbientLight() const
		{
			return ambientLight;
		}
	};

	class SceneLight : public Noncopyable
	{
	public:
		//������
		void Init();
	
	private:
		//�f�B���N�V�������C�g
		SDirectionalLight sdirectionalLight;

		//���̂ق��̃��C�g
		SOtherLight sotherLight;
	};

}
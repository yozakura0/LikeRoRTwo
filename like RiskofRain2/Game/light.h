//�|�C���g���C�g�̍ő吔
static const int MAX_POINT_LIGHT = 256;
//�X�|�b�g���C�g�̍ő吔
static const int MAX_SPOT_LIGHT = 256;
//�f�B���N�V�������C�g�̍ő吔
static const int MAX_DIRECTIONAL_LIGHT = 4;


//�f�B���N�V�������C�g�̍\����
struct DirectionLight
{
	//���C�g�̕���
	float3 direction;
	//�e���L���X�g���邩
	int castShadow;
	//���C�g�̐F
	float4 color;
};

//�|�C���g���C�g�̍\����
struct PointLight
{
	//���W
	float3 position;
	//�J������Ԃ̍��W
	float3 positionInView;
	//�F
	float3 color;
	//�����̃p�����[�^
	float3 attn;
};

//�X�|�b�g���C�g�̍\����
struct SpotLight
{
	//���W
	float3 position;
	//�g�p�����̃t���O
	int inUse;
	//�J������Ԃ̍��W
	float3 positionInView;
	//���C�g�̔ԍ�
	int no;
	//�ˏo����
	float3 direction;
	//�e���͈�
	float range;
	//1�ڂ̐F
	float3 color;
	//2�ڂ̐F
	float3 color2;
	//3�ڂ̐F
	float3 color3;
	//�J������Ԃł̎ˏo����
	float3 directionInView;
	//�����ɂ����̉e�����ɗݏ悷��p�����[�^
	float3 rangePow;
	//�ˏo�p�x
	float3 angle;
	//�X�|�b�g���C�g�Ƃ̊p�x�ɂ����̉e�����ɗݏ悷��p�����[�^
	float3 anglePow;
};

//���C�g�̃f�[�^���܂Ƃ߂��\����
struct Light
{
	//�f�B���N�V�������C�g
	DirectionLight directionalLight;
	//�|�C���g���C�g
	PointLight pointLight;
	//�X�|�b�g���C�g
	SpotLight spotLight;
	//�r���[�v���W�F�N�V�����s��̋t�s��
	float4x4 mViewProjInv;
	//�J�����̎��_
	float3 eyePos;
	//�|�C���g���C�g�̐�
	int numPointLight;
	//����
	float3 ambientLight;
	//�X�|�b�g���C�g�̐�
	int numSpotLight;
};
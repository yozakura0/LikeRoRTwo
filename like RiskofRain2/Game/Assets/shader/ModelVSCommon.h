//���f���̒��_�V�F�[�_�[�֌W�̋��ʃw�b�_�[

// �萔�o�b�t�@
// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// �\����
// ���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION;          //���_���W�B
    float3 normal : NORMAL;         //�@���B
    float2 uv : TEXCOORD0;          //UV���W�B
    float3 tangent : TANGENT;      //�ڃx�N�g���B
    float3 biNormal : BINORMAL;     //�]�x�N�g���B
    int4  Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

// �O���[�o���ϐ�
StructuredBuffer<float4x4> g_boneMatrix         : register(t3);	    //�{�[���s��B
StructuredBuffer<float4x4> g_worldMatrixArray   : register(t10);	//���[���h�s��̔z��B�C���X�^���V���O�`��̍ۂɗL���B

// �֐��錾
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer);

//�X�L���s����v�Z����B
float4x4 CalcSkinMatrix(SVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
    [unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}

// ���[���h��Ԃ̒��_���W���v�Z����
float4 CalcVertexPositionInWorldSpace(float4 vertexPos, float4x4 mWorld, uniform bool isUsePreComputedVertexBuffer)
{
    float4 pos;
    if (isUsePreComputedVertexBuffer) {
        pos = vertexPos;
    }
    else {
        pos = mul(mWorld, vertexPos);  // ���f���̒��_�����[���h���W�n�ɕϊ�
    }

    return pos;
}

// �X�L���Ȃ����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�֐�
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, mWorld, false);
}

// �X�L���Ȃ����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�֐�(�C���X�^���V���O�`��p)
SPSIn VSMainInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
    return VSMainCore(vsIn, g_worldMatrixArray[instanceID], false);
}

// �X�L�����胁�b�V���̒��_�V�F�[�_�[�̃G���g���[�֐�
SPSIn VSMainSkin(SVSIn vsIn)
{
    return VSMainCore(vsIn, CalcSkinMatrix(vsIn), false);
}

// �X�L�����胁�b�V���̒��_�V�F�[�_�[�̃G���g���[�֐�(�C���X�^���V���O�`��p)
SPSIn VSMainSkinInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
    float4x4 mWorldLocal = CalcSkinMatrix(vsIn);
    mWorldLocal = mul(g_worldMatrixArray[instanceID], mWorldLocal);
    return VSMainCore(vsIn, mWorldLocal, false);
}

// ���O�v�Z�ς݂̒��_�o�b�t�@���g�����_�V�F�[�_�[�̃G���g���[�֐�
// �X�L�����b�V���p
SPSIn VSMainSkinUsePreComputedVertexBuffer(SVSIn vsIn)
{
    return VSMainCore(vsIn, (float4x4)0, true);
}

// ���O�v�Z�ς݂̒��_�o�b�t�@���g�����_�V�F�[�_�[�̃G���g���[�֐�
// �X�L���Ȃ����b�V���p
SPSIn VSMainUsePreComputedVertexBuffer(SVSIn vsIn)
{
    return VSMainCore(vsIn, (float4x4)0, true);
}

// ���[���h�X�y�[�X�̖@���A�ڃx�N�g���A�]�x�N�g�����v�Z����
void CalcVertexNormalTangentBiNormalInWorldSpace(
    out float3 oNormal,
    out float3 oTangent,
    out float3 oBiNormal,
    float4x4 mWorld,
    float3 iNormal,
    float3 iTangent,
    float3 iBiNormal,
    uniform bool isUsePreComputedVertexBuffer
)
{
    if (isUsePreComputedVertexBuffer) {
        // ���O�v�Z�ςݒ��_�o�b�t�@�𗘗p����
        oNormal = iNormal;
        oTangent = iTangent;
        oBiNormal = iBiNormal;
    }
    else {
        float3x3 m3x3 = (float3x3)mWorld;
        oNormal = normalize(mul(m3x3, iNormal));
        oTangent = normalize(mul(m3x3, iTangent));
        oBiNormal = normalize(mul(m3x3, iBiNormal));
    }
}
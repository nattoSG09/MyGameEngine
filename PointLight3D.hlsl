////������������������������������������������������������������������������������
// // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
////������������������������������������������������������������������������������
//Texture2D	g_texture : register(t0);	//�e�N�X�`���[
//SamplerState	g_sampler : register(s0);	//�T���v���[
//
////������������������������������������������������������������������������������
//// �R���X�^���g�o�b�t�@
//// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
////������������������������������������������������������������������������������
//cbuffer ConstantBuffer
//{
//    float4x4 matW;          //���[���h�ϊ��s��
//    float4x4 matWVP;		// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
//    float4   Light;         //�������W
//    float4   Attenuation;   //���������p�����[�^
//}
//
////������������������������������������������������������������������������������
//// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
////������������������������������������������������������������������������������
//struct VS_IN
//{
//    float4 pos : POSITION0;
//    float2 uv  : TEXCOORD;
//    float4 nor : NORMAL0;
//};
//
//struct VS_OUT
//{
//    float4 pos  : SV_POSITION;
//    float4 posw : POSITION0;
//    float4 norw : NORMAL0;
//    float2 uv  : TEXCOORD;
//};
//
////������������������������������������������������������������������������������
//// ���_�V�F�[�_
////������������������������������������������������������������������������������
//VS_OUT VS(VS_IN input)
//{
//    VS_OUT outData;
//   /* float3 nor;
//    float  col;*/
//
//    //���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
//    //�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
//    outData.pos = mul(pos, matWVP);
//
//    //�e�N�X�`���f�[�^���s�N�Z���V�F�[�_�[��
//    outData.uv = uv;
//
//    //�@������]
//    output.norw = mul(input.nor, World);
//
//    return outData;
//}
//
//float4 PS(VS_OUT input) : SV_Target
//{
//    float3 dir;
//    float  len;
//    float  colD;
//    float  colA;
//    float  col;
//
//    //�_�����̕���
//    dir = Light.xyz - input.posw.xyz;
//
//    //�_�����̋���
//    len = length(dir);
//
//    //�_�����̕�����normalize
//    dir = dir / len;
//
//    //�g�U
//    colD = saturate(dot(normalize(input.norw.xyz), dir));
//    //����
//    colA = saturate(1.0f / (Attenuation.x + Attenuation.y * len + Attenuation.z * len * len));
//
//    col = colD * colA;
//    return float4(col, col, col, 1.0f);
//}
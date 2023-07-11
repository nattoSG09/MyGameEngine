//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	matWVP;		// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matNormal;	//�@��
	float4x4	matW;

	//���C�g�̏��
	float4		lightPos;
	float4		wLight;

	float4		diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	bool		isTexture;			// �e�N�X�`���\���Ă��邩�ǂ���
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos	: SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float4 color: COLOR;		//�F�i�P�x�j

	float4 lightDir : TEXCOORD1;
	float  lightLen : TEXCOORD2;
	float4 normal : TEXCOORD3;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�ɓn���\���̃f�[�^
	VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);

	//�e�N�X�`���f�[�^���s�N�Z���V�F�[�_�[��
	outData.uv = uv;

	// ���[���h���W�n�ł̌����̈ʒu���v�Z
	float4 worldLightPos = mul(lightPos, matW);

	//���C�g
	outData.lightDir = float4(worldLightPos.xyz, 1.0) - mul(pos.xyzw, matW);

	outData.lightLen = length(outData.lightDir);
	outData.lightDir = normalize(outData.lightDir);

	//�@��
	normal = float4(normal.xyz, 0);
	outData.normal = mul(normal, matWVP);

	//�P�x�����s�N�Z���V�F�[�_�\��
	float4 light = mul(lightPos,matW);
	light = normalize(light);
	outData.normal = mul(normal, matW);
	outData.color = clamp(dot(mul(normal, matW), outData.lightDir), 0, 1);;
	
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 ambientSource = float4(0.3, 0.3, 0.3, 1.0);
	float4 diffuse;
	float4 ambient;

	float scalar = dot(inData.lightDir.xyz, inData.normal.xyz) / inData.lightLen;

	if (scalar < 0.0f)
	{
		scalar = 0.0f;
	}

	//�e�N�X�`��������Ƃ�
	if (isTexture) {
		diffuse = (wLight * g_texture.Sample(g_sampler, inData.uv) * inData.color) / inData.lightLen;
		ambient = wLight * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}
	//�e�N�X�`�����Ȃ��Ƃ�
	else {
		diffuse = (wLight * diffuseColor * inData.color) / inData.lightLen;
		ambient = wLight * diffuseColor * ambientSource;
	}

	return diffuse + ambient + scalar;
}


//������������������������������������������������������������������������������
//�_�����̎����ɂ���(�A���S���Y��)
//������������������������������������������������������������������������������
/*
	3D��ԏ�̓���̈ʒu������˂�������\�����߂̌����B
	��������̌��̋��x�Ƌ����Ɋ�Â��āA���̂̕\�ʂ̖��邳���v�Z����B

	1.���C�g�̈ʒu�Ƌ��x�̐ݒ�
	�ʒu�Ƌ��x���R���X�^���g�o�b�t�@����擾����B

	2.��������̃x�N�g���̌v�Z
	��������̊e���_�̈ʒu�ւ̋������v�Z���邱�ƂŃx�N�g�����擾����B

	3.���̋��x�̌v�Z�i�����ɉ��������̌����j�̓K�p
	�����ƒ��_�̋������傫���Ȃ�΂Ȃ�قǈÂ��Ȃ�
*/
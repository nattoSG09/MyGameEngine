#pragma once

//�C���N���[�h
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

struct VERTEX_DATE
{
	VERTEX* vertices;
	int num;
};

class Quad
{
protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;		//�e�N�X�`��
public:
	//�R���X�g���N�^
	Quad();

	//�f�X�g���N�^
	~Quad();

	//������
	virtual HRESULT Initialize();

	//�`��
	virtual void Draw(XMMATRIX& worldMatrix);

	//���
	virtual void Release();

	//���_�f�[�^�̏�����
	virtual VERTEX_DATE SetVertexDate();
	
	//���_�f�[�^�p�̃o�b�t�@��ݒ�E�쐬����
	//�����P�F���_���	�����Q�F���_��
	HRESULT CreateVertexBuffer(VERTEX* _ver,int _n);


};


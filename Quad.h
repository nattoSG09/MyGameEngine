#pragma once

//�C���N���[�h
#include <DirectXMath.h>
#include <string>
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

	//�o�b�t�@���쐬
	//�����P�F���_���@�����Q�F���_��
	//�����R�F�C���f�b�N�X���@�����S�F�C���f�b�N�X��
	HRESULT CreateBuffers(VERTEX* _ver,int _vn,int* _index,int _in,string _imageData);

	//�o�b�t�@��ݒ�
	void SetBuffers(XMMATRIX& worldMatrix);

	//���_�f�[�^�p�̃o�b�t�@���쐬����
	//�����P�F���_���	�����Q�F���_��
	HRESULT CreateVertexBuffer(VERTEX* _ver,int _n);

	//�C���f�b�N�X�o�b�t�@���쐬����
	//�����P�F�C���f�b�N�X���	�����Q�@�C���f�b�N�X��
	HRESULT CreateIndexBuffer(int* _index, int _n);

	//�R���X�^���g�o�b�t�@���쐬����
	//�����F�@�摜�f�[�^
	HRESULT CreateConstantBuffer(string _imageData);
};


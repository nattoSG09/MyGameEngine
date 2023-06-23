#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"
#include <DirectXMath.h>
#include <vector>
#include <string>

using std::string;
using std::vector;
using namespace DirectX;

class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

protected:
	vector<VERTEX> veritices_;	//���_���(�z��)
	vector<int> index_;	//�C���f�b�N�X���(�z��)
	TexMetadata image_;	//�摜���

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;		//�e�N�X�`��

public:
	Sprite();
	~Sprite();

	//������
	HRESULT Initialize(int winW,int winH);

	//�`��
	void Draw(Transform _transform);

	//���
	void Release();

private:
	//�[�|�|�|�|�|Initialize����Ă΂��֐��[�|�|�|�|�|
	
	//���_����������
	virtual void InitVertexData(int winW, int winH);
	
	//���_�o�b�t�@���쐬
	HRESULT CreateVertexBuffer();

	//�C���f�b�N�X����������
	virtual void InitIndexData();
	
	//�C���f�b�N�X�o�b�t�@���쐬
	HRESULT CreateIndexBuffer();

	//�R���X�^���g�o�b�t�@���쐬
	HRESULT CreateConstantBuffer();
	
	//�e�N�X�`�������[�h
	HRESULT LoadTexture();

	//�[�|�|�|�|�|�[Draw����Ă΂��֐��[�[�|�|�|�|�|
	
	//�R���X�^���g�o�b�t�@�ɏ���n��
	void PassDataToCB(Transform _transform);
	
	//�p�C�v���C���ɏ���ݒ�
	void SetBufferToPipeline();


};


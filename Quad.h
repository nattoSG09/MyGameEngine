#pragma once

//�C���N���[�h
#include <DirectXMath.h>
#include <string>
#include <vector>

#include "Direct3D.h"
#include "Texture.h"

//using�錾
using namespace DirectX;
using std::size;
using std::string;
using std::vector;

class Quad
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matW;
		XMVECTOR	lightPos;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

protected:


	vector<VERTEX> veritices_;	//���_���(�z��)
	vector<int> index_;	//�C���f�b�N�X���(�z��)
	
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
	HRESULT Initialize();

	//�`��
	void Draw(XMMATRIX& worldMatrix);

	//���
	void Release();

private:
	//�[�|�|�|�|�|Initialize����Ă΂��֐��[�|�|�|�|�|

	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	//�[�|�|�|�|�|�[Draw����Ă΂��֐��[�[�|�|�|�|�|
	void PassDataToCB(XMMATRIX& worldMatrix);
	void SetBufferToPipeline();
};


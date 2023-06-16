#pragma once
#include "Direct3D.h"
#include "Texture.h"
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

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;		//�e�N�X�`��

public:
	Sprite();
	~Sprite();

	//������
	virtual HRESULT Initialize();

	//�`��
	virtual void Draw(XMMATRIX& worldMatrix);

	//���
	virtual void Release();

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


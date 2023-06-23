#pragma once

//�C���N���[�h
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

//�����J
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

//using�錾
using std::string;

class Fbx
{
private:
	//�R���X�^���g�o�b�t�@�ɏ���n�����߂̍\����
	struct CONSTANT_BUFFER{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMVECTOR	lightPos;
	};
	//���_���
	struct VERTEX{
		XMVECTOR position;
	};

	//�e�o�b�t�@���
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
public:
	//�R���X�g���N�^
	Fbx();

	//�f�X�g���N�^
	~Fbx();

	//Fbx�t�@�C�������[�h
	HRESULT Load(string fileName);

	//�`��
	void Draw(Transform& transform);
	
	//���
	void Release();

	//���_�o�b�t�@����
	void InitVertex(fbxsdk::FbxMesh* mesh);

	//�C���f�b�N�X�o�b�t�@����
	void InitIndex(fbxsdk::FbxMesh* mesh);

	//�R���X�^���g�o�b�t�@����
	void InitConstantBuffer();

};

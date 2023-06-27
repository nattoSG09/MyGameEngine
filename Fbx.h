#pragma once

//�C���N���[�h
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

//�O���錾
class Texture;

//�����J
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

//using�錾
using std::string;

class Fbx
{
private:

	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
	};

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
	MATERIAL* pMaterialList_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�
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

	//�e�o�b�t�@�̏�����
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};

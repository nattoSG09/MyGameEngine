#pragma once

//�C���N���[�h
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>

using std::vector;

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
		Texture* pTexture_;
		XMFLOAT4 diffuse_;
	};

	//�R���X�^���g�o�b�t�@�ɏ���n�����߂̍\����
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	matLightPos;
		XMFLOAT4	matLight;

		XMFLOAT4	diffuseColor;
		int			isTexture;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	//�e�o�b�t�@���
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�
	std::vector<int> indexCount_;

public:
	//�R���X�g���N�^
	Fbx();

	//�f�X�g���N�^
	~Fbx();

	//Fbx�t�@�C�������[�h
	HRESULT Load(string fileName);

	//�`��
	void Draw(Transform& _transform,XMFLOAT4 _worldLight,XMFLOAT4 _lightPos);
	
	//���
	void Release();

	//�e�o�b�t�@�̏�����
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};

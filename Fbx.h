#pragma once

//インクルード
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

//リンカ
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

//using宣言
using std::string;

class Fbx
{
private:
	//コンスタントバッファに情報を渡すための構造体
	struct CONSTANT_BUFFER{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMVECTOR	lightPos;
	};
	//頂点情報
	struct VERTEX{
		XMVECTOR position;
	};

	//各バッファ情報
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
public:
	//コンストラクタ
	Fbx();

	//デストラクタ
	~Fbx();

	//Fbxファイルをロード
	HRESULT Load(string fileName);

	//描画
	void Draw(Transform& transform);
	
	//解放
	void Release();

	//頂点バッファ準備
	void InitVertex(fbxsdk::FbxMesh* mesh);

	//インデックスバッファ準備
	void InitIndex(fbxsdk::FbxMesh* mesh);

	//コンスタントバッファ準備
	void InitConstantBuffer();

};

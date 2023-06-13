#pragma once

//インクルード
#include <DirectXMath.h>
#include <string>
#include "Direct3D.h"
#include "Texture.h"

//using宣言
using namespace DirectX;
using std::size;

//置換
#define SET_ARRAY_DATA(arr) arr,size(arr)

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
	XMVECTOR	light_;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;		//テクスチャ
public:
	//コンストラクタ
	Quad();

	//デストラクタ
	~Quad();

	//初期化
	virtual HRESULT Initialize();

	//描画
	virtual void Draw(XMMATRIX& worldMatrix);

	//解放
	virtual void Release();

	//バッファを作成
	//引数１：頂点情報	引数２：頂点数
	//引数３：インデックス情報　	引数４：インデックス数
	HRESULT CreateBuffers(VERTEX* _ver,int _vn,int* _index,int _in,string _imageData);

	//バッファを設定
	void SetBuffers(XMMATRIX& worldMatrix);

	//頂点データ用のバッファを作成
	//引数１：頂点情報	引数２：頂点数
	HRESULT CreateVertexBuffer(VERTEX* _ver,int _n);

	//インデックスバッファを作成
	//引数１：インデックス情報	引数２　インデックス数
	HRESULT CreateIndexBuffer(int* _index, int _n);

	//コンスタントバッファを作成す
	//引数：　画像データ
	HRESULT CreateConstantBuffer(string _imageData);
};


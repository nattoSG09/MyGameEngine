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
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

protected:
	vector<VERTEX> veritices_;	//頂点情報(配列)
	vector<int> index_;	//インデックス情報(配列)
	TexMetadata image_;	//画像情報

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;		//テクスチャ

public:
	Sprite();
	~Sprite();

	//初期化
	HRESULT Initialize(int winW,int winH);

	//描画
	void Draw(Transform _transform);

	//解放
	void Release();

private:
	//ー－－－－－Initializeから呼ばれる関数ー－－－－－
	
	//頂点情報を初期化
	virtual void InitVertexData(int winW, int winH);
	
	//頂点バッファを作成
	HRESULT CreateVertexBuffer();

	//インデックス情報を初期化
	virtual void InitIndexData();
	
	//インデックスバッファを作成
	HRESULT CreateIndexBuffer();

	//コンスタントバッファを作成
	HRESULT CreateConstantBuffer();
	
	//テクスチャをロード
	HRESULT LoadTexture();

	//ー－－－－－ーDrawから呼ばれる関数ーー－－－－－
	
	//コンスタントバッファに情報を渡す
	void PassDataToCB(Transform _transform);
	
	//パイプラインに情報を設定
	void SetBufferToPipeline();


};


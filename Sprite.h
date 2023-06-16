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
	virtual HRESULT Initialize(int winW,int winH);

	//描画
	virtual void Draw(XMMATRIX& worldMatrix);

	//解放
	virtual void Release();

private:
	//ー－－－－－Initializeから呼ばれる関数ー－－－－－

	virtual void InitVertexData(int winW, int winH);
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();
	
	HRESULT LoadTexture();

	//ー－－－－－ーDrawから呼ばれる関数ーー－－－－－
	void PassDataToCB(XMMATRIX& worldMatrix);
	void SetBufferToPipeline();


};


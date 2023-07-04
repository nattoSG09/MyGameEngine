#pragma once

//インクルード
#include <d3d11.h>
#include <string>
#include <wrl.h>

#include <DirectXTex.h>
//リンカ
#pragma comment( lib, "DirectxTex.lib" )

//using宣言
using namespace Microsoft::WRL;
using namespace DirectX;
using std::string;

class Texture
{
private:
	ID3D11SamplerState* pSampler_;	//サンプラー
	ID3D11ShaderResourceView* pSRV_;//シェーダーリソースビュー
	TexMetadata metadata_;	//画像情報

public:
	//コンストラクタ
	Texture();

	//デストラクタ
	~Texture();

	//画像ファイルのロード
	HRESULT Load(std::string fileName);

	//解放
	void Release();

	//サンプラーを取得
	ID3D11SamplerState* GetSampler();

	//シェーダ―リソースビューを取得
	ID3D11ShaderResourceView* GetSRV();

	//入力された画像情報を取得
	TexMetadata GetMetaData() { return this->metadata_; }
};
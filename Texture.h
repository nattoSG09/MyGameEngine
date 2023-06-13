#pragma once

//インクルード
#include <d3d11.h>
#include <string>
#include <wrl.h>

//using宣言
using namespace Microsoft::WRL;
using std::string;

class Texture
{
private:
	ID3D11SamplerState* pSampler_;	//サンプラー
	ID3D11ShaderResourceView* pSRV_;//シェーダーリソースビュー
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
};
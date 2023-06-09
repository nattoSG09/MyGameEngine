//インクルード
#include "Texture.h"
#include "Direct3D.h"

//コンストラクタ
Texture::Texture()
	:pSampler_(nullptr),pSRV_(nullptr), metadata_()
{
}

//デストラクタ
Texture::~Texture()
{
	Release();
}

//テクスチャデータをロード
HRESULT Texture::Load(std::string fileName)
{
	
	//////////画像読み込み部分(変更)//////////

	//マルチバイト文字→ワイド文字へ変換
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());

	
	ScratchImage image;
	HRESULT hr;
	hr = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, image);

	float a = metadata_.width;
	if (FAILED(hr)) { 
		MessageBox(nullptr, "画像の読み込みに失敗しました", "エラー", MB_OK);
		return E_FAIL; 
	}

	//サンプラーの作成
	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice_->CreateSamplerState(&SamDesc, &pSampler_);

	if (FAILED(hr)) {
		MessageBox(nullptr, "サンプラーの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	//シェーダ―リソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(Direct3D::pDevice_, image.GetImages(), image.GetImageCount(), metadata_, &pSRV_);
	if (FAILED(hr)) {
		MessageBox(nullptr, "シェーダ―リソースビューの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//解放
void Texture::Release()
{
	
	SAFE_RELEASE(pSRV_);
	SAFE_RELEASE(pSampler_);
}

//サンプラー取得
ID3D11SamplerState* Texture::GetSampler()
{
	return pSampler_;
}

//シェーダ―リソースビュー取得
ID3D11ShaderResourceView* Texture::GetSRV()
{
	return pSRV_;
}

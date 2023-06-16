//�C���N���[�h
#include "Texture.h"
#include"Direct3D.h"

//�R���X�g���N�^
Texture::Texture()
	:pSampler_(nullptr),pSRV_(nullptr), metadata_()
{
}

//�f�X�g���N�^
Texture::~Texture()
{
	Release();
}

//�e�N�X�`���f�[�^�����[�h
HRESULT Texture::Load(std::string fileName)
{
	
	//////////�摜�ǂݍ��ݕ���(�ύX)//////////

	//�}���`�o�C�g���������C�h�����֕ϊ�
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());

	
	ScratchImage image;
	HRESULT hr;
	hr = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, image);

	float a = metadata_.width;
	if (FAILED(hr)) { 
		MessageBox(nullptr, "�摜�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL; 
	}

	//�T���v���[�̍쐬
	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice_->CreateSamplerState(&SamDesc, &pSampler_);

	if (FAILED(hr)) {
		MessageBox(nullptr, "�T���v���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}

	//�V�F�[�_�\���\�[�X�r���[�̍쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(Direct3D::pDevice_, image.GetImages(), image.GetImageCount(), metadata_, &pSRV_);
	if (FAILED(hr)) {
		MessageBox(nullptr, "�V�F�[�_�\���\�[�X�r���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//���
void Texture::Release()
{
	
	SAFE_RELEASE(pSRV_);
	SAFE_RELEASE(pSampler_);
}

//�T���v���[�擾
ID3D11SamplerState* Texture::GetSampler()
{
	return pSampler_;
}

//�V�F�[�_�\���\�[�X�r���[�擾
ID3D11ShaderResourceView* Texture::GetSRV()
{
	return pSRV_;
}

#pragma once

//�C���N���[�h
#include <d3d11.h>
#include <string>
#include <wrl.h>

#include <DirectXTex.h>
//�����J
#pragma comment( lib, "DirectxTex.lib" )

//using�錾
using namespace Microsoft::WRL;
using namespace DirectX;
using std::string;

class Texture
{
private:
	ID3D11SamplerState* pSampler_;	//�T���v���[
	ID3D11ShaderResourceView* pSRV_;//�V�F�[�_�[���\�[�X�r���[
	TexMetadata metadata_;	//�摜���

public:
	//�R���X�g���N�^
	Texture();

	//�f�X�g���N�^
	~Texture();

	//�摜�t�@�C���̃��[�h
	HRESULT Load(std::string fileName);

	//���
	void Release();

	//�T���v���[���擾
	ID3D11SamplerState* GetSampler();

	//�V�F�[�_�\���\�[�X�r���[���擾
	ID3D11ShaderResourceView* GetSRV();

	//���͂��ꂽ�摜�����擾
	TexMetadata GetMetaData() { return this->metadata_; }
};
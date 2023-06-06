#pragma once
//�C���N���[�h
#include <d3d11.h>
#include <string>
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture
{
private:
	ID3D11SamplerState* pSampler_;	//�T���v���[
	ID3D11ShaderResourceView* pSRV_;//�V�F�[�_�[���\�[�X�r���[
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
};
#include "Sprite.h"
#include "Texture.h"


//�摜�T�C�Y	512*256

Sprite::Sprite()
	:veritices_(),index_(),image_()
	,pVertexBuffer_(nullptr), pTexture_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr)
{
}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize(int winW, int winH)
{
	HRESULT hr = S_OK;
	
	//�e�N�X�`�������[�h
	hr = LoadTexture();
	if (FAILED(hr)) {return hr;
	}
	//���_����ݒ�
	InitVertexData(winW, winH);

	//�C���f�b�N�X����ݒ�
	InitIndexData();

	//���_�o�b�t�@���쐬(�R���p�C��)
	hr = CreateVertexBuffer();
	if (FAILED(hr)) {return hr;
	}

	//�C���f�b�N�X�o�b�t�@���쐬(�R���p�C��)
	hr = CreateIndexBuffer();
	if (FAILED(hr)) {return hr;
	}


	//�R���X�^���g�o�b�t�@���쐬(�R���p�C��)
	hr = CreateConstantBuffer();
	if (FAILED(hr)) {return hr;
	}

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{

	//�V�F�[�_�[��؂�ւ���
	Direct3D::SetShader(SHADER_2D);

	//�R���X�^���g�o�b�t�@�ɏ����p�X
	PassDataToCB(worldMatrix);
	
	//�e�o�b�t�@�\�����Z�b�g
	SetBufferToPipeline();
}

void Sprite::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);

}

void Sprite::InitVertexData(int winW, int winH)
{
	//�摜�̈ʒu���W(���S)
	XMFLOAT3 Position = {0,0,0};
	
	veritices_ = {
	{ XMVectorSet(-((float)image_.width / 2) / winW, (((float)image_.height / 2) / winH) - 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},
	{ XMVectorSet( ((float)image_.width / 2) / winW, (((float)image_.height / 2) / winH) - 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },
	{ XMVectorSet( ((float)image_.width / 2) / winW,-(((float)image_.height / 2) / winH) - 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },
	{ XMVectorSet(-((float)image_.width / 2) / winW,-(((float)image_.height / 2) / winH) - 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) }
	};

	//���_�ʒu = (�摜�T�C�Y(��)/2) /�E�B���h�E�T�C�Y
}

HRESULT Sprite::CreateVertexBuffer()
{

	D3D11_BUFFER_DESC bd_vertex;

	bd_vertex.ByteWidth = sizeof(VERTEX)*  veritices_.size();
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = veritices_.data();

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		return hr;//�G���[���̖߂�l
	}
	return S_OK;
}

void Sprite::InitIndexData()
{
	//�C���f�b�N�X���
	index_ = vector<int>{
		 0, 2, 3,  0, 1, 2
	};
}

HRESULT Sprite::CreateIndexBuffer()
{

	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * index_.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {

		return hr;//�G���[���̖߂�l
	}
	return S_OK;
}

HRESULT Sprite::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		return hr;//�G���[���̖߂�l
	}
	return S_OK;
}

HRESULT Sprite::LoadTexture()
{
	pTexture_ = new Texture;
	HRESULT hr =pTexture_->Load("Assets\\Dice.png");
	if (FAILED(hr)) {
		return hr;//�G���[���̖߂�l
	}
	image_ = pTexture_->GetMetaData();
	return S_OK;

}

void Sprite::PassDataToCB(XMMATRIX& worldMatrix)
{
	//�R���X�^���g�o�b�t�@���Z�b�g
	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	//�e�N�X�`���ƃT���v���[���V�F�[�_�[��
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
}

void Sprite::SetBufferToPipeline()
{

	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
	Direct3D::pContext_->DrawIndexed(index_.size(), 0, 0);
}

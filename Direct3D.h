#pragma once

//�C���N���[�h
#include <d3d11.h>
#include <cassert>
#include <string>

//using�錾
using std::string;

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//�u��
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

enum SHADER_TYPE {
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX,
};

namespace Direct3D
{
	extern ID3D11Device* pDevice_;			//�f�o�C�X
	extern 	ID3D11DeviceContext* pContext_;	//�f�o�C�X�R���e�L�X�g
	extern ID3D11DepthStencilView* pDepthStencilView;

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	//�g�p����V�F�[�_�[��I��
	void SetShader(SHADER_TYPE _type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

};
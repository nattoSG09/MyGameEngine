//インクルード
#include <Windows.h>
#include "Direct3D.h"
#include "Dice.h"
#include "Camera.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* WIN_TITLE_NAME = "さんぷるげ～む";  //ウィンドウクラス名

const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント(プログラムのスタート地点)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);     //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		WIN_TITLE_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	//Direct3D初期化
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);
	}

	//Quadを作成
	//Quad* pQuad = new Quad;
	//hr = pQuad->Initialize();

	//DIceを作成
	Dice* pDice = new Dice;
	hr = pDice->Initialize();

	if (FAILED(hr)) {
		MessageBox(nullptr, "Diceの初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);
	}

	//カメラを初期化
	Camera::Initialize(winW,winH);

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)//プログラムが実行している間
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//Camaraの更新処理
			Camera::Update();

			//ゲームの処理
			Direct3D::BeginDraw();

			static float angle = 0;angle += 0.01f;
			XMMATRIX rotateMatY = XMMatrixRotationY(XMConvertToRadians(angle));
			XMMATRIX rotateMatX = XMMatrixRotationX(XMConvertToRadians(angle));
			XMMATRIX rotateMatZ = XMMatrixRotationZ(XMConvertToRadians(angle));
			XMMATRIX mat = rotateMatY * rotateMatX * rotateMatZ;
			pDice->Draw(mat);

			//描画処理
			Direct3D::EndDraw();
		}
	}

	//解放処理
	Direct3D::Release();
	SAFE_DELETE(pDice);

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//ウィンドウが閉じたら
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
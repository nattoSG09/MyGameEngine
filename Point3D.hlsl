//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matWVP;		// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matNormal;	//法線
	float4x4	matW;

	//ライトの情報
	float4		lightPos;
	float4		wLight;

	float4		diffuseColor;		// ディフューズカラー（マテリアルの色）
	bool		isTexture;			// テクスチャ貼ってあるかどうか
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos	: SV_POSITION;	//位置
	float2 uv	: TEXCOORD;		//UV座標
	float4 color: COLOR;		//色（輝度）

	float4 lightDir : TEXCOORD1;
	float  lightLen : TEXCOORD2;
	float4 normal : TEXCOORD3;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーに渡す構造体データ
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);

	//テクスチャデータをピクセルシェーダーへ
	outData.uv = uv;

	// ワールド座標系での光源の位置を計算
	float4 worldLightPos = mul(lightPos, matW);

	//ライト
	outData.lightDir = float4(worldLightPos.xyz, 1.0) - mul(pos.xyzw, matW);

	outData.lightLen = length(outData.lightDir);
	outData.lightDir = normalize(outData.lightDir);

	//法線
	normal = float4(normal.xyz, 0);
	outData.normal = mul(normal, matWVP);

	//輝度情報をピクセルシェーダ―へ
	float4 light = lightPos;
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);

	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
	float4 diffuse;
	float4 ambient;

	float4 scalar = dot(inData.lightDir.xyz, inData.normal.xyz) * inData.lightLen;

	//テクスチャがあるとき
	if (isTexture) {
		diffuse = (wLight * g_texture.Sample(g_sampler, inData.uv) * inData.color) / inData.lightLen;
		ambient = wLight * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}
	//テクスチャがないとき
	else {
		diffuse = (wLight * diffuseColor * inData.color) / inData.lightLen;
		ambient = wLight * diffuseColor * ambientSource;
	}

	return diffuse + ambient + scalar;
}


//───────────────────────────────────────
//点光源の実装について(アルゴリズム)
//───────────────────────────────────────
/*
	3D空間上の特定の位置から放射される光を表すための光源。
	光源からの光の強度と距離に基づいて、物体の表面の明るさを計算する。

	1.ライトの位置と強度の設定
	位置と強度をコンスタントバッファから取得する。

	2.光源からのベクトルの計算
	光源からの各頂点の位置への距離を計算することでベクトルを取得する。

	3.光の強度の計算（距離に応じた光の減衰）の適用
	光源と頂点の距離が大きくなればなるほど暗くなる
*/
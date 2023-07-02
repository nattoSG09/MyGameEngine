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
	float4x4	matNormal;	// ワールド行列
	float4		matLightPos;//ライトの位置
	float4		matLight;	//ライトの強度

	float4		diffuseColor;		// ディフューズカラー（マテリアルの色）
	bool		isTexture;		// テクスチャ貼ってあるかどうか
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos	: SV_POSITION;	//位置
	float2 uv	: TEXCOORD;		//UV座標
	float4 color: COLOR;		//色（輝度）

	float4 tmpPos: TMP_POSITION;//実際の位置
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーに渡す構造体データ
	VS_OUT outData;

	//スクリーン座標ではない実際の位置を補完する
	outData.tmpPos = pos;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);

	//テクスチャデータをピクセルシェーダーへ
	outData.uv = uv;

	//法線を回転
	normal = mul(normal, matNormal);

	//輝度情報をピクセルシェーダ―へ
	float4 light = matLightPos;
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

	//ライトと物体の距離を計算(ライトの位置ー物体の位置(頂点ごと))
	float len = length(matLightPos.xyz - mul(inData.tmpPos.xyz, matNormal));

	//テクスチャがあるとき
	if (isTexture) {
		diffuse = (matLight * g_texture.Sample(g_sampler, inData.uv) * inData.color) / len;
		ambient = matLight * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}
	//テクスチャがないとき
	else {
		diffuse = ((matLight * diffuseColor * inData.color)*2) / len;
		ambient = matLight * diffuseColor * ambientSource;
	}

	return diffuse + ambient;
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
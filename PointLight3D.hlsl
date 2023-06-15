////───────────────────────────────────────
// // テクスチャ＆サンプラーデータのグローバル変数定義
////───────────────────────────────────────
//Texture2D	g_texture : register(t0);	//テクスチャー
//SamplerState	g_sampler : register(s0);	//サンプラー
//
////───────────────────────────────────────
//// コンスタントバッファ
//// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
////───────────────────────────────────────
//cbuffer ConstantBuffer
//{
//    float4x4 matW;          //ワールド変換行列
//    float4x4 matWVP;		// ワールド・ビュー・プロジェクションの合成行列
//    float4   Light;         //光源座標
//    float4   Attenuation;   //光源減衰パラメータ
//}
//
////───────────────────────────────────────
//// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
////───────────────────────────────────────
//struct VS_IN
//{
//    float4 pos : POSITION0;
//    float2 uv  : TEXCOORD;
//    float4 nor : NORMAL0;
//};
//
//struct VS_OUT
//{
//    float4 pos  : SV_POSITION;
//    float4 posw : POSITION0;
//    float4 norw : NORMAL0;
//    float2 uv  : TEXCOORD;
//};
//
////───────────────────────────────────────
//// 頂点シェーダ
////───────────────────────────────────────
//VS_OUT VS(VS_IN input)
//{
//    VS_OUT outData;
//   /* float3 nor;
//    float  col;*/
//
//    //ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
//    //スクリーン座標に変換し、ピクセルシェーダーへ
//    outData.pos = mul(pos, matWVP);
//
//    //テクスチャデータをピクセルシェーダーへ
//    outData.uv = uv;
//
//    //法線を回転
//    output.norw = mul(input.nor, World);
//
//    return outData;
//}
//
//float4 PS(VS_OUT input) : SV_Target
//{
//    float3 dir;
//    float  len;
//    float  colD;
//    float  colA;
//    float  col;
//
//    //点光源の方向
//    dir = Light.xyz - input.posw.xyz;
//
//    //点光源の距離
//    len = length(dir);
//
//    //点光源の方向をnormalize
//    dir = dir / len;
//
//    //拡散
//    colD = saturate(dot(normalize(input.norw.xyz), dir));
//    //減衰
//    colA = saturate(1.0f / (Attenuation.x + Attenuation.y * len + Attenuation.z * len * len));
//
//    col = colD * colA;
//    return float4(col, col, col, 1.0f);
//}
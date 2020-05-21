#include "DxLib.h"

int PlayerGraph, PlayerGraph2, PlayerGraph3, PlayerGraph4, PlayerGraph5, PlayerGraph6;
//物体の位置
int px, py, px2, px3, px4,py2,py3,py4;
//物体の速度
float vx, vy, vx2,vy3,vy4;
//物体の加速度
float ax, ay;
//物体の重さ
float m1, m2;
//重力加速度
float g;
//時間
float t,time;


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(TRUE); // ウインドウモードに変更
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// グラフィックのロード
	PlayerGraph = LoadGraph(L"Player.png");
	PlayerGraph2 = LoadGraph(L"Player.png");
	PlayerGraph3 = LoadGraph(L"Player.png");
	PlayerGraph4 = LoadGraph(L"Player.png");
	PlayerGraph5 = LoadGraph(L"Player2.png");
	PlayerGraph6 = LoadGraph(L"Player.png");
	px = 30; px2 = 30; py = 400; px3 = 30; px4 = 100; py2 = 0;
	vx = 1.5f;
	vx2 = 0.02f;

	m1 = 5.0f; m2 = 20.0f;

	vy3 = m1 * 1.5f;
	vy4 = m2 * 1.5f;
	g = 0.98f;
	t = 0; time = 0;
	ax = 0;
	ay = 0;
	py3 = 20;
	py4 = 20;
	// 移動ルーチン
	while (1)
	{
		t++;
		// 画面を初期化する
		ClearDrawScreen();
		//等速度運動
		px += vx;
		if (px >= 640) {
			px = 0 - 64;
		}
		//等加速度運動
		ax += vx2;
		px2 += ax;
		if (px2 >= 640) {
			px2 = 0 - 64;
		}
		if (ax >= 20) {
			ax = 20;
		}
		//F=ma7
		if (t >= 180) {
			py3 += vy3;
			py4 += vy4;
		}
		if (py3 >= 600) {
			py3 = 600;
		}
		if (py4 >= 600) {
			py4 = 600;
		}
		//自由落下
		ay += 0.5*g;
		py2 +=ay;
		if (py2 >= 500) {
			py2 = 500;
		}
		//プレイヤーを描画
		DrawGraph(30, 400, PlayerGraph, TRUE);
		DrawGraph(px, py - 96, PlayerGraph2, TRUE);
		DrawGraph(px2, py - 96 * 2, PlayerGraph3, TRUE);
		DrawGraph(px3, py3, PlayerGraph4, TRUE);
		DrawGraph(px4, py4, PlayerGraph5, TRUE);
		DrawGraph(540, py2, PlayerGraph6, TRUE);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
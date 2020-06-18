#include "DxLib.h"
#include"Collision.h"
#include<math.h>

#define PI 3.141592
#define PI2 (PI*2)

typedef struct {
	//座標
	float x, y;
	//回転の中心座標
	float ox, oy;
	//周期
	float T;
	//半径
	float range;
}Point_t;

//回転
void Rotate(const float ox, const float oy, float *x, float *y, const float angle) {
	float tx = *x - ox;
	float ty = *y - oy;
	*x = tx * cos(angle) - ty * sin(angle) + ox;
	*y = tx * sin(angle) + ty * cos(angle) + oy;
}

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

	Collision collision;


	Point_t p1 = { 320,40,320,240,300,200 };
	Point_t p2 = { 320,140,320,240,3600,100 };

	int Cnt = 0;

	float aa =0.1f;
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
		ClearDrawScreen();

		Rotate(p1.ox, p1.oy, &p1.x, &p1.y, PI2 / p1.T);

		p2.x = p2.ox + cos(PI2 / p2.T*Cnt) * p2.range;
		p2.y = p2.oy + sin(PI2 / p2.T*Cnt) * p2.range;

		/*if (p2.T >100) {
			p2.T -= aa;
		}
		else {
			p2.T = 100;
		}*/

		DrawLine(p1.x, p1.y, 320, 240, GetColor(0, 255, 0), TRUE);
		DrawLine(p2.x, p2.y, 320, 240, GetColor(255, 255, 0), TRUE);
		DrawCircle(p1.x, p1.y, 10, GetColor(255, 0, 0), TRUE);
		DrawCircle(p2.x, p2.y, 10, GetColor(0, 0, 255), TRUE);
		DrawCircle(320, 240, 5, GetColor(255, 255, 255), TRUE);

		Cnt++;
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
#include "DxLib.h"
#include"Collision.h"
#include<math.h>
#include"Input.h"

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


//円
typedef struct {
	//座標
	Vector2D a;
	//半径
	float radius;
	//色
	int Col;
	//移動速度
	float speed;
}Circle;

//線
typedef struct {
	//座標
	Vector2D v1, v2;
	//色
	int Col;
}Line;

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(900, 600, 16);
	ChangeWindowMode(TRUE); // ウインドウモードに変更
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	Collision collision;

	Circle c = { Vector2D(200,200),20,GetColor(0, 255, 255),2.0f };
	Line l = { Vector2D(100,400),Vector2D(200,150),GetColor(50,50,150) };


	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
		ClearDrawScreen();
#pragma region 円の移動
		Input::Instance()->Update();
		if (Input::Instance()->isKey(KEY_INPUT_W)) {
			c.a.y -= 1.0f*c.speed;
		}
		if (Input::Instance()->isKey(KEY_INPUT_A)) {
			c.a.x -= 1.0f*c.speed;
		}
		if (Input::Instance()->isKey(KEY_INPUT_S)) {
			c.a.y += 1.0f*c.speed;
		}
		if (Input::Instance()->isKey(KEY_INPUT_D)) {
			c.a.x += 1.0f*c.speed;
		}
#pragma endregion

		//円と線分の判定
		if (collision.Circle_LineCollision(c.a, c.radius, l.v1, l.v2)) {
			DrawString(100, 50, L"当たった", GetColor(255, 0, 0), GetColor(150, 150, 255));
			c.Col = GetColor(0, 255, 0);
		}
		else c.Col = GetColor(0, 255, 255);


		DrawCircle(c.a.x, c.a.y, c.radius, c.Col, TRUE);

		DrawLine(l.v1.x, l.v1.y, l.v2.x, l.v2.y, l.Col, TRUE);
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
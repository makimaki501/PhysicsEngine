#include "DxLib.h"
#include"Collision.h"

//縦幅、横幅
int M_Circle_Width, M_Circle_Height;
int m_Circle_Width, m_Circle_Height;
//位置
float PosX, PosY;
float PosX2, PosY2;

//速度
float M_v, m_v;
float m_v1, m_v2;



//半径
float M_radius, m_radius;
//反発係数
float e;
//質量
float M, m;

//反発
float Repulsion(float e, float M, float m, float Mv, float mv) {
	float v;

	if (e == 1) {
		v = ((M - m) + 2 * mv) / (M + m);
	}
	else {
		v = (e * m * (m_v - M_v) + M_v + m_v) / (M + m);
	}
	return v;
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

	M_radius = 40;
	m_radius = 20;

	M_Circle_Width = M_radius;
	M_Circle_Height = M_radius;
	m_Circle_Width = m_radius;
	m_Circle_Height = m_radius;

	PosY = 350, PosX = 50;
	PosY2 = 370, PosX2 = 550;


	//設定
	M_v = 2.0f;   //大きい円の初速度
	m_v = -2.0f;  //小さい円の初速度
	e = 1.0f;     //反発係数
	M = 1.0f;     //大きい円の質量
	m = 0.5f;     //小さい円の質量

	Collision collision;


	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
		ClearDrawScreen();


		PosX += M_v;
		PosX2 += m_v;

		DrawFormatString(PosX + M_radius, 400, GetColor(255, 0, 0), L"%f", M_v);
		DrawFormatString(PosX2 + m_radius, 400, GetColor(255, 0, 0), L"%f", m_v);

		if (collision.CircleCollision(Vector2D(PosX, PosY), M_radius, Vector2D(PosX2, PosY2), m_radius)) {
			DrawString(0, 0, L"当たった！", GetColor(255, 0, 0));
			M_v = 0;
			m_v = 0;

			/*float V = Repulsion(e, m, M, m_v, M_v);
			float v = Repulsion(e, M, m, M_v, m_v);

			M_v = V;
			m_v = v;*/
		}
		else {

		}

		if (PosX < 0 || PosX>560) {
			M_v = -M_v;
		}
		if (PosX2 < 0 || PosX2>600) {
			m_v = -m_v;
		}

		//楕円表示
		DrawCircle(PosX + M_radius, PosY + M_radius, M_radius, GetColor(150, 150, 20), FALSE);

		DrawCircle(PosX2 + m_radius, PosY2 + m_radius, m_radius, GetColor(0, 150, 20), FALSE);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
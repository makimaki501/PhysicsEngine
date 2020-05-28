#include "DxLib.h"

enum SideState
{
	Right,
	Left,
};
SideState sideState;

//スペース用
int SPACE;

//縦幅、横幅
int Circle_Width, Circle_Height;
//位置
float PosX, PosY;
//今がジャンプ中かどうか
bool IsJamp;
//等速直線運動
bool moveX;
float moveXScale;

int JampPowerCnt;
float JampPower;

float prevY, tempY;

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

	sideState = Right;

	SPACE = -1;
	Circle_Width = 40;
	Circle_Height = 40;
	PosY = 350;
	PosX = 50;
	IsJamp = false;
	moveX = false;
	moveXScale = 0.5f;

	prevY = 0, tempY = 0;
	JampPowerCnt = 0;
	JampPower = 1.0f;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);


	while (1)
	{
		// 画面を初期化する
		ClearDrawScreen();

#pragma region 文字
		DrawFormatString(0, 0, GetColor(255, 255, 255), L"Y座標：%f", PosY);
		DrawFormatString(0, 20, GetColor(255, 255, 255), L"ジャンプパワー：%d", JampPowerCnt);
		switch (sideState)
		{
		case Right:
			DrawFormatString(300, 20, GetColor(255, 255, 255), L"今向いている向きは：右");
			break;
		case Left:
			DrawFormatString(300, 20, GetColor(255, 255, 255), L"今向いている向きは：左");
			break;
		}
		DrawFormatString(300, 0, GetColor(255, 255, 0), L"アローキーで向いている方向を選択");
#pragma endregion
		
#pragma region ジャンプ処理

		if (IsJamp) {
			tempY = PosY;
			PosY += (PosY - prevY) + 1 * JampPower;
			prevY = tempY;
			if (PosY >= 350) {
				IsJamp = false;
				moveX = false;
				PosY = 350;
				JampPowerCnt = 0;
				JampPower = 1.0f;
			}
		}
#pragma endregion

#pragma region ジャンプ中の移動
		if (moveX) {
			switch (sideState)
			{
			case Right:
				PosX +=moveXScale;
				break;
			case Left:
				PosX -= moveXScale;
				break;
			default:
				break;
			}
		}
#pragma endregion

#pragma region 方向の判定
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			sideState = Right;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			sideState = Left;
		}
#pragma endregion


#pragma region SPACE処理
		if (CheckHitKey(KEY_INPUT_SPACE) == 0)
		{
			// 押されていない
			if (SPACE > 0)
				SPACE = -1;		// SPACEキーが離れた瞬間
			else
				SPACE = 0;		// SPACEキーが離れている状態
		}
		else
		{
			// 押されている
			SPACE++;				// SPACEキーが押されている間は値を増やし続ける
			JampPowerCnt++;
		}

		if (PosY < 350) {
			SPACE = 0;
		}

		if (SPACE == -1) {
			IsJamp = true;
			moveX = true;
			prevY = PosY;
			PosY = PosY - 20;
			
		}
		else if (SPACE >= 1) {
			Circle_Width = 60;
			Circle_Height = 20;
			if (PosY == 350)
				PosY = 370;
		}
		else
		{
			Circle_Width = 40;
			Circle_Height = 40;
		}

#pragma endregion

#pragma region ジャンプパワー
		if (JampPowerCnt < 45) {
			JampPower = 1.0f;
			moveXScale = 0.5f;
		}
		if (JampPowerCnt >= 45 && JampPowerCnt < 90) {
			JampPower = 0.8f;
			moveXScale = 0.75f;
		}
		if (JampPowerCnt >= 90 && JampPowerCnt < 135) {
			JampPower = 0.6f;
			moveXScale = 1.0f;
		}
	    if (JampPowerCnt >= 135 && JampPowerCnt < 180) {
			JampPower = 0.4f;
			moveXScale = 1.25f;
		}
		if (JampPowerCnt >= 180) {
			JampPower = 0.2f;
			moveXScale = 1.5f;
		}
#pragma endregion


		//線
		DrawLine(0, 390, 640, 390, GetColor(255, 255, 255));



		//画面外に行けいないように(横)
		if (PosX <= 40) {
			PosX = 40;
		}
		else if (PosX >= 600) {
			PosX = 600;
		}

		//楕円表示
		DrawOval(PosX, PosY, Circle_Width, Circle_Height, GetColor(150, 150, 20), TRUE);


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
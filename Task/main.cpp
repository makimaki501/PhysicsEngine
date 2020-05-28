#include "DxLib.h"

enum SideState
{
	Right,
	Left,
};
SideState sideState;

//�X�y�[�X�p
int SPACE;

//�c���A����
int Circle_Width, Circle_Height;
//�ʒu
float PosX, PosY;
//�����W�����v�����ǂ���
bool IsJamp;
//���������^��
bool moveX;
float moveXScale;

int JampPowerCnt;
float JampPower;

float prevY, tempY;

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ɕύX
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
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

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);


	while (1)
	{
		// ��ʂ�����������
		ClearDrawScreen();

#pragma region ����
		DrawFormatString(0, 0, GetColor(255, 255, 255), L"Y���W�F%f", PosY);
		DrawFormatString(0, 20, GetColor(255, 255, 255), L"�W�����v�p���[�F%d", JampPowerCnt);
		switch (sideState)
		{
		case Right:
			DrawFormatString(300, 20, GetColor(255, 255, 255), L"�������Ă�������́F�E");
			break;
		case Left:
			DrawFormatString(300, 20, GetColor(255, 255, 255), L"�������Ă�������́F��");
			break;
		}
		DrawFormatString(300, 0, GetColor(255, 255, 0), L"�A���[�L�[�Ō����Ă��������I��");
#pragma endregion
		
#pragma region �W�����v����

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

#pragma region �W�����v���̈ړ�
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

#pragma region �����̔���
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			sideState = Right;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			sideState = Left;
		}
#pragma endregion


#pragma region SPACE����
		if (CheckHitKey(KEY_INPUT_SPACE) == 0)
		{
			// ������Ă��Ȃ�
			if (SPACE > 0)
				SPACE = -1;		// SPACE�L�[�����ꂽ�u��
			else
				SPACE = 0;		// SPACE�L�[������Ă�����
		}
		else
		{
			// ������Ă���
			SPACE++;				// SPACE�L�[��������Ă���Ԃ͒l�𑝂₵������
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

#pragma region �W�����v�p���[
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


		//��
		DrawLine(0, 390, 640, 390, GetColor(255, 255, 255));



		//��ʊO�ɍs�����Ȃ��悤��(��)
		if (PosX <= 40) {
			PosX = 40;
		}
		else if (PosX >= 600) {
			PosX = 600;
		}

		//�ȉ~�\��
		DrawOval(PosX, PosY, Circle_Width, Circle_Height, GetColor(150, 150, 20), TRUE);


		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
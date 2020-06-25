#include "DxLib.h"
#include"Collision.h"
#include<math.h>
#include"Input.h"

#define PI 3.141592
#define PI2 (PI*2)

typedef struct {
	//���W
	float x, y;
	//��]�̒��S���W
	float ox, oy;
	//����
	float T;
	//���a
	float range;
}Point_t;

//��]
void Rotate(const float ox, const float oy, float *x, float *y, const float angle) {
	float tx = *x - ox;
	float ty = *y - oy;
	*x = tx * cos(angle) - ty * sin(angle) + ox;
	*y = tx * sin(angle) + ty * cos(angle) + oy;
}


//�~
typedef struct {
	//���W
	Vector2D a;
	//���a
	float radius;
	//�F
	int Col;
	//�ړ����x
	float speed;
}Circle;

//��
typedef struct {
	//���W
	Vector2D v1, v2;
	//�F
	int Col;
}Line;

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(900, 600, 16);
	ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ɕύX
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	Collision collision;

	Circle c = { Vector2D(200,200),20,GetColor(0, 255, 255),2.0f };
	Line l = { Vector2D(100,400),Vector2D(200,150),GetColor(50,50,150) };


	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();
#pragma region �~�̈ړ�
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

		//�~�Ɛ����̔���
		if (collision.Circle_LineCollision(c.a, c.radius, l.v1, l.v2)) {
			DrawString(100, 50, L"��������", GetColor(255, 0, 0), GetColor(150, 150, 255));
			c.Col = GetColor(0, 255, 0);
		}
		else c.Col = GetColor(0, 255, 255);


		DrawCircle(c.a.x, c.a.y, c.radius, c.Col, TRUE);

		DrawLine(l.v1.x, l.v1.y, l.v2.x, l.v2.y, l.Col, TRUE);
		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
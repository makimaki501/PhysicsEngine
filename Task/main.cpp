#include "DxLib.h"
#include"Collision.h"

//�c���A����
int M_Circle_Width, M_Circle_Height;
int m_Circle_Width, m_Circle_Height;
//�ʒu
float PosX, PosY;
float PosX2, PosY2;

//���x
float M_v, m_v;
float m_v1, m_v2;



//���a
float M_radius, m_radius;
//�����W��
float e;
//����
float M, m;

//����
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

	M_radius = 40;
	m_radius = 20;

	M_Circle_Width = M_radius;
	M_Circle_Height = M_radius;
	m_Circle_Width = m_radius;
	m_Circle_Height = m_radius;

	PosY = 350, PosX = 50;
	PosY2 = 370, PosX2 = 550;


	//�ݒ�
	M_v = 2.0f;   //�傫���~�̏����x
	m_v = -2.0f;  //�������~�̏����x
	e = 1.0f;     //�����W��
	M = 1.0f;     //�傫���~�̎���
	m = 0.5f;     //�������~�̎���

	Collision collision;


	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();


		PosX += M_v;
		PosX2 += m_v;

		DrawFormatString(PosX + M_radius, 400, GetColor(255, 0, 0), L"%f", M_v);
		DrawFormatString(PosX2 + m_radius, 400, GetColor(255, 0, 0), L"%f", m_v);

		if (collision.CircleCollision(Vector2D(PosX, PosY), M_radius, Vector2D(PosX2, PosY2), m_radius)) {
			DrawString(0, 0, L"���������I", GetColor(255, 0, 0));
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

		//�ȉ~�\��
		DrawCircle(PosX + M_radius, PosY + M_radius, M_radius, GetColor(150, 150, 20), FALSE);

		DrawCircle(PosX2 + m_radius, PosY2 + m_radius, m_radius, GetColor(0, 150, 20), FALSE);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
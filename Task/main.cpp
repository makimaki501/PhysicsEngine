#include "DxLib.h"
#include"Collision.h"

//�c���A����
int M_Circle_Width, M_Circle_Height;
int m_Circle_Width, m_Circle_Height;


//���x(2����)
Vector2D v1, v2;
Vector2D pos1, pos2;

//���a
float M_radius, m_radius;
//�����W��
float e;
//����
float m1, m2;
bool isTouch;

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
	m_radius = 40;

	M_Circle_Width = M_radius;
	M_Circle_Height = M_radius;
	m_Circle_Width = m_radius;
	m_Circle_Height = m_radius;



	//�ݒ�
	e = 1.0f;     //�����W��
	m1 = 1.0f;     //�傫���~�̎���
	m2 = 1.0f;    //�������~�̎���

	//2����
	v1 = Vector2D(1, 1);
	v2 = Vector2D(-1, 1);
	pos1 = Vector2D(30, 50);
	pos2 = Vector2D(550, 50);

	Collision collision;

	isTouch = false;

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();

		pos1 += v1;
		pos2 += v2;

		DrawFormatString(pos1.x + M_radius, pos1.y + 40, GetColor(255, 0, 0), L"%f", v1);
		DrawFormatString(pos2.x + m_radius, pos2.y + 40, GetColor(255, 0, 0), L"%f", v2);

		if (collision.CircleCollision(Vector2D(pos1.x, pos1.y),
			40, Vector2D(pos2.x, pos2.y), 40) && !isTouch) {
			DrawString(0, 0, L"���������I", GetColor(255, 0, 0));
			//v1 = Vector2D();
			//v2 = Vector2D();

			Vector2D s = pos2 - pos1;
			Vector2D n = (pos2 - pos1).Normalize();

			Vector2D prevV1 = v1;
			Vector2D prevV2 = v2;
#pragma region ���s
			//v1 = prevV1 - Vector2D((((((1 + e) / (m1*m2)) / m2 + m1))*(prevV1.x - prevV2.y)*n.x))*n.x) / m1, ((((((1 + e)*m1*m2) / m2 + m1))*(prevV1.y - prevV2.y)*n.y)*n.y) / m1);
			//v2 = prevV2 - Vector2D((((((1 + e) / (m2*m1)) / m2 + m1))*(prevV2 - prevV1).Dot(n))*n.x) / m2, ((((((1 + e)*m2*m1) / m2 + m1))*(prevV2.y - prevV1.y).n.y)*n.y) / m2);
			/*v1 = Vector2D();
			v2 = Vector2D();*/
			//v1.x = -(((((1 + e) * m1*m2) / m1 + m2))*(prevV1 - prevV2).Dot(n))*n.x / m1 + prevV1.x;
			//v1.y = -(((((1 + e) * m1*m2) / m1 + m2))*(prevV1 - prevV2).Dot(n))*n.y / m1 + prevV1.y;

			//v2.x = -(((((1 + e) * m1*m2) / m1 + m2))*(prevV2 - prevV1).Dot(n))*n.x / m2 + prevV2.x;
			//v2.y = -(((((1 + e) * m1*m2) / m1 + m2))*(prevV2 - prevV1).Dot(n))*n.y / m2 + prevV2.y;
#pragma endregion
			if (m1 == m2) {
				v1 = (n * -((prevV1 - prevV2).Dot(n))) + prevV1;
				v2 = (n * -((prevV2 - prevV1).Dot(n))) + prevV2;
			}
			isTouch = true;
		}
		else {
			isTouch = false;
		}

		if (pos1.x < 0 || pos1.x>560) {
			v1 = Vector2D(-v1.x, -v1.y);
		}
		if (pos1.y < 0 || pos1.y>400) {
			v1 = Vector2D(-v1.x, -v1.y);
		}
		if (pos2.x < 0 || pos2.x>560) {
			v2 = Vector2D(-v2.x, -v2.y);

		}
		if (pos2.y < 0 || pos2.y>400) {
			v2 = Vector2D(-v2.x, -v2.y);

		}

		//�ȉ~�\��
		DrawCircle(pos1.x + M_radius, pos1.y + M_radius, M_radius, GetColor(150, 150, 20), FALSE);

		DrawCircle(pos2.x + m_radius, pos2.y + m_radius, m_radius, GetColor(0, 150, 20), FALSE);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
#include "DxLib.h"

int PlayerGraph, PlayerGraph2, PlayerGraph3, PlayerGraph4, PlayerGraph5, PlayerGraph6;
//���̂̈ʒu
int px, py, px2, px3, px4,py2,py3,py4;
//���̂̑��x
float vx, vy, vx2,vy3,vy4;
//���̂̉����x
float ax, ay;
//���̂̏d��
float m1, m2;
//�d�͉����x
float g;
//����
float t,time;


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

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// �O���t�B�b�N�̃��[�h
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
	// �ړ����[�`��
	while (1)
	{
		t++;
		// ��ʂ�����������
		ClearDrawScreen();
		//�����x�^��
		px += vx;
		if (px >= 640) {
			px = 0 - 64;
		}
		//�������x�^��
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
		//���R����
		ay += 0.5*g;
		py2 +=ay;
		if (py2 >= 500) {
			py2 = 500;
		}
		//�v���C���[��`��
		DrawGraph(30, 400, PlayerGraph, TRUE);
		DrawGraph(px, py - 96, PlayerGraph2, TRUE);
		DrawGraph(px2, py - 96 * 2, PlayerGraph3, TRUE);
		DrawGraph(px3, py3, PlayerGraph4, TRUE);
		DrawGraph(px4, py4, PlayerGraph5, TRUE);
		DrawGraph(540, py2, PlayerGraph6, TRUE);

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
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ME 'X' 
#define BLANK " " 
#define BLANK2 ' '

#define ESC 0x1b 

#define SPECIAL1 0xe0 
#define SPECIAL2 0x00 

#define UP  0x48 
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'

#define WIDTH 88 
#define HEIGHT 41 

#define TRUE 1
#define FALSE 0

#define box "|"
#define box2 "��"
#define GEM	"o"

#define MAXBULLET 5

int run_time, start_time, remain_time, last_remain_time, startkey, i;
int topaz_time, sapphire_time, emerald_time, ruby_time, diamond_time;
int topaz_time = 0; sapphire_time = 0; emerald_time = 0; ruby_time = 0; diamond_time = 0;

int Delay = 10;
int enemy_generate = 8, quit_end = 0;
int time_out = 60;
int p_life = 5, b_life = 3000, p_damage = 10, damage_sign = 0, b_damage = 0, m_damage = 50, score = 0;
int sx = 0, sy = 0, shooting = 0, ending = 0, random_damage = 0, life_damage = 0;
int t_x = 0, t_y = 0, s_x = 0, s_y = 0, e_x = 0, e_y = 0, r_x = 0, r_y = 0, d_x = 0, d_y = 0;

int bsels = 37, move = 0;

int px = 46, py = 32;
int bx = -1; by;
int mx = -1, my;

unsigned char ch, sel;

struct
{
	BOOL exist;
	int x, y;
} Bullet[MAXBULLET];

typedef struct
{
	int x;
	int y;
	int status;
} Dangers;

Dangers Enemy[90];

void init()
{
	int i;
	for (i = 3; i < 86; i++)
		Enemy[i].status = FALSE;
}

void removeCursor(void) {

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}

void draw_box(int x1, int y1, int x2, int y2)
{
	int x, y;
	gotoxy(x1, y2); printf("��");
	for (x = x1 + 1; x < x2 - 2; x++) {
		gotoxy(x, y2);
		printf("%s", box2);
	}
	gotoxy(x + 1, y2); printf("��");
	for (y = y1 + 1; y < y2; y++) {
		gotoxy(x1, y);
		printf("%s", box);
		gotoxy(x2, y);
		printf("%s", box);
	}
}

void draw_box2(int x1, int y1, int x2, int y2)
{
	int x, y;
	for (x = x1; x <= x2; x++) {
		gotoxy(x, y1);
		printf("%s", "��");
		gotoxy(x, y2);
		printf("%s", "��");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", "��");
		gotoxy(x2, y);
		printf("%s", "��");
	}
	gotoxy(x1, y1); printf("��");
	gotoxy(x1, y2); printf("��");
	gotoxy(x2, y1); printf("��");
	gotoxy(x2, y2); printf("��");
}

void show_topaz()
{
	t_x = 2 + rand() % 86;
	t_y = 10 + rand() % 30;
	textcolor(14, 0);
	gotoxy(t_x, t_y);
	printf("%s", GEM);
	textcolor(15, 0);
}

void show_sapphire() {
	s_x = 2 + rand() % 86;
	s_y = 10 + rand() % 30;
	textcolor(9, 0);
	gotoxy(s_x, s_y);
	printf("%s", GEM);
	textcolor(15, 0);
}

void show_emerald() {
	e_x = 2 + rand() % 86;
	e_y = 10 + rand() % 30;
	textcolor(10, 0);
	gotoxy(e_x, e_y);
	printf("%s", GEM);
	textcolor(15, 0);
}

void show_ruby() {
	r_x = 2 + rand() % 86;
	r_y = 10 + rand() % 30;
	textcolor(12, 0);
	gotoxy(r_x, r_y);
	printf("%s", GEM);
	textcolor(15, 0);
}

void show_diamond() {
	d_x = 2 + rand() % 86;
	d_y = 10 + rand() % 30;
	textcolor(11, 0);
	gotoxy(d_x, d_y);
	printf("%s", GEM);
	textcolor(15, 0);
}

void show_time(int remain_time)
{
	gotoxy(2, 1);
	textcolor(15, 8);
	if (remain_time <= 10)
		textcolor(15, 12);
	printf("���� �ð� : ");
	printf("%02d\r", remain_time);
	textcolor(15, 0);
}

void boss(int x)
{
	if (x < 5)
		x = 5;
	if (x > 65)
		x = 65;
	printf("\n");
	gotoxy(x, 4);
	printf("    =##  II|II  ##=    \n");
	gotoxy(x, 5);
	printf("    =-  <<###>>  -=    \n");
	gotoxy(x, 6);
	printf("   <((  ##---##  ))>   \n");
	gotoxy(x, 7);
	printf("  <{{###_-   -_###}}>  \n");
	gotoxy(x, 8);
	printf("      <**## ##**>      \n");
	gotoxy(x, 9);
	printf("       [| ||| |]       \n");
	damage_sign = 0;
}

void title_screen() {
	while (1) {
		gotoxy(50, 3); textcolor(1 + rand() % 15, 0);
		printf("��������������������������������������������������������"); gotoxy(50, 4);
		printf("�� ������������������������������������������������ ��"); gotoxy(50, 5);
		printf("�� ��  �������������������������������������� �� ��"); gotoxy(50, 6);
		printf("�� ��  ��  Shooting Game  �� �� ��"); gotoxy(50, 7);
		printf("�� ��  �������������������������������������� �� ��"); gotoxy(50, 8);
		printf("�� ������������������������������������������������ ��"); gotoxy(50, 9);
		printf("��������������������������������������������������������");
		textcolor(15, 0);
		gotoxy(0, 6);
		printf("<�⺻ ���۹�>\n\n");
		printf("�̵� : ����Ű ( �� , �� , �� , �� )\n");
		printf("���� : SPACE BAR (������ 10)\n");
		printf("�̻��� : F (������ 50) \n\n");
		printf("[������ ���]\n\n");
		textcolor(14, 0);
		printf("���� �� : ������ 1�� �߰� (�ִ� 5)\n");
		textcolor(9, 0);
		printf("��� �� : ȹ���� ������ �Ѿ� ���ݷ� ���� (�ִ� 1�߿� 50)\n");
		textcolor(10, 0);
		printf("�׸� �� : ȹ���� ������ �̻��� ���ݷ� ���� (�ִ� 500)\n");
		textcolor(12, 0);
		printf("���� �� : 30,50,100 �� �ϳ��� �������� ������ �ش�\n");
		textcolor(11, 0);
		printf("���̾� �� : �� 4���� ������ ȿ���� ��� ��´�\n");
		textcolor(15, 0);
		printf("\n\n");
		printf("- ���� ��Ģ -\n\n");
		printf("���� �ð� ���� �������� ���� �������� �ٿ� �����߷��ּ��� !\n");
		printf("������ �����Ҽ��� (���� �������� �پ�����) ������ �ö󰩴ϴ�.\n");
		printf("���� ���� ���Ḧ ���ϽŴٸ� Q�� �����ֽʽÿ�.\n\n\n\n");
		printf("���� : SPACE BAR\n");
		printf("���� : ESC\n\n");
		printf("\n\n\n");
		printf("���� : 2171210 A�� ������\n");
		if (_kbhit()) {
			startkey = _getch();
			if (startkey == 0x20) {
				break;
			}
			else if (startkey == 0x1b) {
				exit(0);
			}
			else if (startkey != 0x20)
				continue;
		}
	}
}

void item_effect() {

	int i;

	for (i = 0; i < MAXBULLET; i++) {
		if (((Bullet[i].x == t_x) && (Bullet[i].y == t_y)) || ((px == t_x) && (py == t_y))) {
			if (t_x != 0) {
				gotoxy(41, 1); textcolor(14, 0);
				printf("������ �߰�\r");
				p_life += 1;
				if (p_life > 5)
					p_life = 5;
				t_x = 0; t_y = 0;
			}
		}
		if (((Bullet[i].x == s_x) && (Bullet[i].y == s_y)) || ((px == s_x) && (py == s_y))) {
			if ((s_x != 0)) {
				gotoxy(41, 1); textcolor(9, 0);
				printf("���ݷ� ���\r");
				p_damage += 10;
				if (p_damage >= 50)
					p_damage = 50;
				s_x = 0; s_y = 0;
			}
		}
		if (((Bullet[i].x == e_x) && (Bullet[i].y == e_y)) || ((px == e_x) && (py == e_y))) {
			if (e_x != 0) {
				gotoxy(41, 1); textcolor(10, 0);
				printf("���ݷ� ����\r");
				m_damage += 100;
				if (m_damage >= 500)
					m_damage = 500;
				e_x = 0; e_y = 0;
			}
		}
		if (((Bullet[i].x == r_x) && (Bullet[i].y == r_y)) || ((px == r_x) && (py == r_y))) {
			if (r_x != 0) {
				gotoxy(41, 1); textcolor(12, 0);
				printf("���� ������\r");
				textcolor(12, 0);
				boss(bsels);
				textcolor(15, 0);
				random_damage = 1 + rand() % 3;
				switch (random_damage)
				{
				case 1:
					b_life -= 30;
					break;
				case 2:
					b_life -= 50;
					break;
				case 3:
					b_life -= 100;
					break;
				}
				r_x = 0; r_y = 0;
			}
		}
		if (((Bullet[i].x == d_x) && (Bullet[i].y == d_y)) || ((px == d_x) && (py == d_y))) {
			if (d_x != 0) {
				gotoxy(41, 1); textcolor(11, 0);
				printf("��� ȿ����\r");
				p_life += 1;
				if (p_life > 5)
					p_life = 5;
				p_damage += 10;
				if (p_damage >= 50)
					p_damage = 50;
				m_damage += 20;
				if (m_damage >= 100)
					m_damage = 100;
				random_damage = 1 + rand() % 3;
				switch (random_damage)
				{
				case 1:
					b_life -= 10;
					break;
				case 2:
					b_life -= 30;
					break;
				case 3:
					b_life -= 100;
					break;
				}
				d_x = 0; d_y = 0;
			}
		}
	}
}

void gameover() {
	int i;
	system("cls");
	draw_box(0, 0, WIDTH, HEIGHT);
	for (i = 1; i <= 15; i++) {
		draw_box2(i * 2, i, 88 - i * 2, 41 - i);
	}
	gotoxy(37, 17);
	printf("Game Over!");
	gotoxy(37, 18);
	printf("���� : %d", score);
	gotoxy(37, 20);
}

void gameclear() {
	int i;
	system("cls");
	draw_box(0, 0, WIDTH, HEIGHT);
	for (i = 1; i <= 15; i++) {
		textcolor(1 + rand() % 15, 0);
		draw_box2(i * 2, i, 88 - i * 2, 41 - i);
		Sleep(20);
	}
	textcolor(15, 0);
	gotoxy(37, 17);
	printf("Game Clear!");
	gotoxy(37, 18);
	printf("���� : %d", score);
	gotoxy(37, 20);
}

void DrawPlayer() {
	gotoxy(px, py);
	printf("X");
	life_damage = 0;
}

void ErasePlayer() {
	gotoxy(px, py); printf(BLANK);
}

void PlayerMove() {

	int i;

	if (GetAsyncKeyState(VK_LEFT) && px > 1)
	{
		ErasePlayer();
		px--;
		DrawPlayer();
	}
	else if (GetAsyncKeyState(VK_RIGHT) && px < 87)
	{
		ErasePlayer();
		px++;
		DrawPlayer();
	}
	else if (GetAsyncKeyState(VK_UP) && py > 10)
	{
		ErasePlayer();
		py--;
		DrawPlayer();
	}
	else if (GetAsyncKeyState(VK_DOWN) && py < 40)
	{
		ErasePlayer();
		py++;
		DrawPlayer();
	}
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case 0x20:
			for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) { ; }
			if (i != MAXBULLET)
			{
				Bullet[i].x = px;
				Bullet[i].y = py;
				Bullet[i].exist = TRUE;
			}
			break;
		case 'F':
			if (mx == -1)
			{
				mx = px;
				my = py;
			}
			break;
		case 'f':
			if (mx == -1)
			{
				mx = px;
				my = py;
			}
			break;
		case 'Q':
		case 'q':
			quit_end = 1;
			break;
		}
	}
}

void DrawBullet(int i)
{
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf("*");
}

void EraseBullet(int i)
{
	gotoxy(Bullet[i].x, Bullet[i].y); printf(BLANK);
}

void PlayerBullet()
{
	int i;

	for (i = 0; i < MAXBULLET; i++)
	{
		if (Bullet[i].exist == TRUE)
		{
			EraseBullet(i);
			if (Bullet[i].y == 3)
			{
				Bullet[i].exist = FALSE;
			}
			else
			{
				Bullet[i].y--;
				DrawBullet(i);
			}
		}
	}
}

void DrawMissile()
{

	gotoxy(mx - 1, my - 2); printf("��");
	gotoxy(mx - 1, my - 1); printf("||");
	gotoxy(mx - 1, my);     printf("||");

}

void EraseMissile()
{
	gotoxy(mx - 1, my - 2); printf("  ");
	gotoxy(mx - 1, my - 1); printf("  ");
	gotoxy(mx - 1, my);     printf("  ");
}

void PlayerMissile()
{
	if (mx != -1)
	{
		EraseMissile();
		if (my - 2 == 3)
		{
			mx = -1;
		}
		else
		{
			my--;
			DrawMissile();
		}
	}
}

void BossCrash()
{
	int i;

	for (i = 0; i < MAXBULLET; i++) {
		if ((bsels <= Bullet[i].x && Bullet[i].x <= bsels + 18) && (Bullet[i].y == 10)) {
			score += p_damage;
			b_life -= p_damage;
			damage_sign = 1;
		}
	}
	if ((bsels <= mx && mx <= bsels + 19) && (my == 12)) {
		score += m_damage;
		b_life -= m_damage;
		damage_sign = 1;
	}
}

void MakeEnemy(int shootx)
{
	int i;

	for (i = 3; i < 85; i++)
	{
		if (!Enemy[i].status)
		{
			Enemy[i].x = 3 + rand() % 83;
			Enemy[i].y = 11;
			Enemy[i].status = TRUE;
			return;
		}
	}
}

void MoveEnemy()
{
	int i;
	for (i = 3; i < 86; i++)
	{
		if (Enemy[i].status)
			Enemy[i].y++;
	}
}

void EndEnemy()
{
	int i;

	for (i = 3; i < 86; i++)
	{
		if (Enemy[i].y > 2 && (3 <= Enemy[i].x && Enemy[i].x <= 85)) {
			gotoxy(Enemy[i].x, Enemy[i].y - 1);
			printf(BLANK);
		}
		if (Enemy[i].status && Enemy[i].y == 40)
			Enemy[i].status = FALSE;
	}
}

void PlayerDamage()
{
	int i;
	for (i = 3; i < 86; i++)
	{
		if ((Enemy[i].y == py) && (Enemy[i].x == px)) {
			p_life -= 1;
			life_damage = 1;
		}
	}
}

void ShowEnemy()
{
	int i;
	for (i = 3; i < 85; i++)
	{
		if (Enemy[i].status)
		{
			gotoxy(Enemy[i].x, Enemy[i].y);
			printf("|");
		}
	}
}

void main()
{
	while (1)
	{
		sel = 'Y', ending = 0, b_life = 3000, remain_time = 100, quit_end = 0, score = 0, p_life = 5;
		px = 46, py = 32, bx = -1; by, mx = -1, my, p_damage = 10, damage_sign = 0, b_damage = 0, m_damage = 50;
		t_x = 0, t_y = 0, s_x = 0, s_y = 0, e_x = 0, e_y = 0, r_x = 0, r_y = 0, d_x = 0, d_y = 0;

		system("cls");
		removeCursor();
		system("color 0f");
		title_screen();
		init();
		system("cls");
		srand(time(NULL));
		start_time = time(NULL);
		last_remain_time = remain_time = time_out;
		show_time(remain_time);
		draw_box(0, 0, WIDTH, HEIGHT);
		while (1) {
			run_time = time(NULL) - start_time;
			if (damage_sign == 1)
				textcolor(4, 0);
			if ((run_time > 0) && (run_time % 3 == 0)) {

				int go_on;
				go_on = 1 + rand() % 2;
				if (bsels < 5)
					go_on = 1;
				if (bsels > 65)
					go_on = 2;
				switch (go_on)
				{
				case 1:
					bsels += 2;
					break;
				case 2:
					bsels -= 2;
					break;
				}
			}
			boss(bsels, move);
			textcolor(15, 0);
			enemy_generate = 1 + rand() % 5;
			if (remain_time <= 35)
				enemy_generate = 1 + rand() % 3;
			else if (remain_time <= 10)
				enemy_generate = 1 + rand() % 1;
			if (run_time > topaz_time && (run_time % 6 == 0)) {
				gotoxy(t_x, t_y); putchar(BLANK2);
				show_topaz();
				topaz_time = run_time;
			}
			if (run_time > sapphire_time && (run_time % 5 == 0)) {
				gotoxy(s_x, s_y); putchar(BLANK2);
				show_sapphire();
				sapphire_time = run_time;
			}
			if (run_time > emerald_time && (run_time % 7 == 0)) {
				gotoxy(e_x, e_y); putchar(BLANK2);
				show_emerald();
				emerald_time = run_time;
			}
			if (run_time > ruby_time && (run_time % 10 == 0)) {
				gotoxy(r_x, r_y); putchar(BLANK2);
				show_ruby();
				ruby_time = run_time;
			}
			if (run_time > diamond_time && (run_time % 5 == 0)) {
				gotoxy(d_x, d_y); putchar(BLANK2);
				show_diamond();
				diamond_time = run_time;
			}
			remain_time = time_out - run_time;
			if (remain_time < last_remain_time) {
				show_time(remain_time);
				last_remain_time = remain_time;
			}
			if ((remain_time == 0) || (p_life == 0)) {
				ending = 1;
				break;
			}
			textcolor(15, 6);
			if (life_damage == 1)
				textcolor(15, 4);
			if (p_life <= 1)
				textcolor(12, 7);
			gotoxy(2, 3); printf("�÷��̾� ������ : %d", p_life);
			textcolor(15, 3); gotoxy(23, 1); printf("���� : %d", score);
			textcolor(15, 4);
			if (b_life <= 300)
				textcolor(15, 9);
			gotoxy(67, 3); printf("���� ������ : %04d\r", b_life);
			textcolor(15, 0);

			DrawPlayer();
			PlayerMove();
			if (quit_end == 1) {
				ending = 1;
				break;
			}
			PlayerMissile();
			PlayerBullet();
			item_effect();
			BossCrash();
			if (enemy_generate == 1)
				MakeEnemy(bsels);
			MoveEnemy();
			EndEnemy();
			ShowEnemy();
			PlayerDamage();


			if (b_life <= 0) {
				ending = 2;
				break;
			}
			Sleep(Delay);
		}
		switch (ending)
		{
		case 1:
			gameover();
			Sleep(1000);

			printf("�絵�� : R");
			gotoxy(37, 21);
			printf("���� : ESC  ");
			while (1) {
				sel = _getch();
				if (sel == 'r' || sel == 'R') {
					break;
				}
				else if (sel == 0x1b)
					return;
				else {
					gotoxy(37, 23);
					printf("�����Ͽ� �ֽʽÿ�  ");
				}
			}
			break;
		case 2:
			gameclear();
			Sleep(1000);

			printf("�絵�� : R");
			gotoxy(37, 21);
			printf("���� : ESC  ");
			while (1) {
				sel = _getch();
				if (sel == 'r' || sel == 'R') {
					break;
				}
				else if (sel == 0x1b)
					return;
				else {
					gotoxy(37, 23);
					printf("�����Ͽ� �ֽʽÿ�  ");
				}
			}
			break;
		}
	}
}

#include "my_tank.h"
#include"bullet.h"
my_tank::my_tank(int x, int y, int direction, int HP, int buff, int kill_enemy)
	: Role(x, y, direction), HP(HP), buff(buff), kill_enemy(kill_enemy) {
	map[y / 40][x / 40] = 100;  // �ڵ�ͼ��ά�����б���ҷ�̹��λ��
}

void my_tank::reLive(int pos_x, int pos_y)
{
	this->x = pos_x;
	this->y = pos_y;
	this->buff = 0;
}
/*
	�������ƣ�move
	������void
	���ܣ�
		����̹�˵��ƶ���������Ұ��µļ��̰�����W��A��S��D������̹�˵ķ�����ƶ���
		�����ݷ������̹�˵����ꡣ
		��̹�˳����밴��ָ��һ����ǰ��Ϊ�յػ���������ߣ���̹���ƶ�����λ�ò�����Ƿ���������ߡ�
		�������밴��ָ��һ�£������̹�˷�������ƶ���
*/
void my_tank::move() {
	// �������W����̹�˳��������ƶ�
	if (GetAsyncKeyState('W') & 0x8000) {
		// �ж�̹�˵�ǰ�����Ƿ�Ϊ���ϣ�����ǣ����һ���ж��Ƿ���������ƶ�
		if (direction == 2 && (y - 40) >= 0 &&
			map[y / 40 - 1][x / 40] != 1 && map[y / 40 - 1][x / 40] != 2 && map[y / 40 - 1][x / 40] != 6 && map[y / 40 - 1][x / 40] != 101) {
			map[y / 40][x / 40] = 0;  // ��յ�ǰ��ͼ�ϵ�̹��λ�ñ��
			y -= 40;  // ����̹�˵������꣨�����ƶ���
			getBuff(x, y);  // ��鲢Ӧ���µ��������
			map[y / 40][x / 40] = 100;  // ����λ�ñ��̹��
		}
		else if (direction != 2) {
			// �����ǰ���������ϣ����������Ϊ����
			direction = 2;
		}
	}
	// ��������������ƶ���A: ��S: �£�D: �ң���ʵ�����������Ƶ��߼�
	// ����S�� �������ƶ���
	if (GetAsyncKeyState('S') & 0x8000) {
		if (direction == 3 && (y + 40) < 600 &&
			map[y / 40 + 1][x / 40] != 1 && map[y / 40 + 1][x / 40] != 2 && map[y / 40 + 1][x / 40] != 6 && map[y / 40 + 1][x / 40] != 101) {
			map[y / 40][x / 40] = 0;
			y += 40;
			getBuff(x, y);
			map[y / 40][x / 40] = 100;
		}
		else if (direction != 3) {
			direction = 3;
		}
	}
	// ʾ��������A���������ƶ���
	if (GetAsyncKeyState('A') & 0x8000) {
		if (direction == 0 && (x - 40) >= 0 &&
			map[y / 40][x / 40 - 1] != 1 && map[y / 40][x / 40 - 1] != 2 && map[y / 40][x / 40 - 1] != 6 && map[y / 40][x / 40 - 1] != 101) {
			map[y / 40][x / 40] = 0;
			x -= 40;
			getBuff(x, y);
			map[y / 40][x / 40] = 100;
		}
		else if (direction != 0) {
			direction = 0;
		}
	}



	// ʾ��������D���������ƶ���
	if (GetAsyncKeyState('D') & 0x8000) {
		if (direction == 1 && (x + 40) < 800 &&
			map[y / 40][x / 40 + 1] != 1 && map[y / 40][x / 40 + 1] != 2 && map[y / 40][x / 40 + 1] != 6 && map[y / 40][x / 40 + 1] != 101) {
			map[y / 40][x / 40] = 0;
			x += 40;
			getBuff(x, y);
			map[y / 40][x / 40] = 100;
		}
		else if (direction != 1) {
			direction = 1;
		}
	}
}

/*
	�������ƣ�shoot
	������
		bullets - �洢�ӵ���������������
	���ܣ�
		����Ұ��� 'J' ��ʱ������һ���ӵ�����ӵ� bullets �����С�
		����̹�˵�ǰ��buff״̬��buffֵ�������ɲ�ͬ���͵��ӵ���
		0��3 - ��ͨ�ӵ���1 - ������2 - ���⡣
		�ӵ��ĳ�ʼ�����λ��ȡ����̹�˵�ǰ�ķ����λ�á�
*/
int my_tank::shoot(vector<bullet>& bullets)
{
	if (GetAsyncKeyState('J') & 0x8000)
	{
		int bullet_type = (this->buff == 1) ? 1 : 0;  // ����buff�����ӵ����ͣ���ǰbuffЧ��Ϊ1ʱ���ӵ������Ϊ1-����
		int direction = this->direction;			  //�ӵ��ķ�����̹�˳���һ��
		//�ӵ������꣬1�ǵ�һ���ӵ������꣬2������ʱ�ڶ����ӵ�������
		int pos_x1, pos_x2;
		int pos_y1, pos_y2;

		//����̹�˵�ǰ�ķ����趨�ӵ���������ĳ�ʼ����
		switch (direction)
		{
		case 0://����
		{
			if (bullet_type == 1)//����ǵ���buff״̬
			{
				pos_x1 = x-20;
				pos_y1 = y + 10;
			}
			else
			{
				pos_x1 = x;
				pos_y1 = y + 18;
				pos_x2 = x - 8;
				pos_y2 = pos_y1;
			}
			break;
		}
		case 1://����
		{
			if (bullet_type == 1)//����ǵ���buff״̬
			{
				pos_x1 = x + 40;
				pos_y1 = y + 10;
			}
			else
			{
				pos_x1 = x + 36;
				pos_y1 = y + 18;
				pos_x2 = pos_x1 + 4;
				pos_y2 = pos_y1;
			}
			break;
		}
		case 2://����
		{
			if (bullet_type == 1)//����ǵ���buff״̬
			{
				pos_x1 = x + 10;
				pos_y1 = y - 20;
			}
			else
			{
				pos_x1 = x + 18;
				pos_y1 = y;
				pos_x2 = pos_x1;
				pos_y2 = pos_y1 - 8;
			}
			break;
		}
		case 3://����
		{
			if (bullet_type == 1)//����ǵ���buff״̬
			{
				pos_x1 = x + 10;
				pos_y1 = y + 40;
			}
			else
			{
				pos_x1 = x + 18;
				pos_y1 = y + 36;
				pos_x2 = pos_x1;
				pos_y2 = pos_y1 + 8;
			}
			break;
		}
		default:
			break;
		}
		if (this->buff == 2)//�����ǰbuff״̬Ϊ2-�����������������ӵ�
		{
			bullet bulletl(pos_x1, pos_y1, direction, 0, bullet_type);
			bullet bullet2(pos_x2, pos_y2, direction, 0, bullet_type);
			bullets.push_back(bulletl);  // �����ӵ�����������
			bullets.push_back(bullet2);  // �����ӵ�����������
		}
		else
		{
			bullet bulletl(pos_x1, pos_y1, direction, 0, bullet_type);
			bullets.push_back(bulletl);  // �����ӵ�����������
		}
		return 0;//�����ӵ��ɹ�
	}
	return 1;//�����ӵ�ʧ��
}

/*
	�������ƣ�getBuff
	������
		x - ��ǰ���ߵĺ�����
		y - ��ǰ���ߵ�������
	���ܣ�
		���̹�˵�ǰ����λ�õĵ�ͼ�������Ƿ���buff���ߣ�
		����У������̹�˵�buff״̬����ͬ�ĵ��߸��費ͬ��Ч����
		3 - ����buff��1 - ������2 - ���⣬5 - ���ƣ����Եֵ�һ���ӵ���������
*/
void my_tank::getBuff(int x, int y) {
	switch (map[y / 40][x / 40]) {
	case 3:
		buff = 1;  // ��ȡ����buff
		break;
	case 4:
		buff = 2;  // ��ȡ���⣨������buff
		break;
	case 5:
		buff = 3;  // ��ȡ����buff
		break;
	default:
		break;
	}
}

int& my_tank::currentBuff()
{
	return this->buff;
}

/*
	�������ƣ�getHP
	��������
	����ֵ��int& - ̹�˵ĵ�ǰHP����
	���ܣ�
		����̹�˵ĵ�ǰѪ��HP���Ա��������ط����ʻ��޸�Ѫ����
*/
int& my_tank::getHP() {
	return HP;
}

int& my_tank::getKill()
{
	return kill_enemy;
}

#include "enemy_tank.h"
#include"bullet.h"
//enemy_tank::enemy_tank() :Role(0, 0, 3), HP(1), buff(0), isLive(0) {}
enemy_tank::enemy_tank(int x, int y, int direction, int HP, int buff, int isLive) : Role(x, y, direction), HP(HP), buff(buff), isLive(isLive) 
{//���캯��
	map[y / 40][x / 40] = 101;  // �ڵ�ͼ��ά�����б�ǵз�̹��λ��
}
int enemy_tank::getIsLive()
{
	if (HP <= 0)
		isLive = 0;
	else
		isLive = 1;
	return isLive;
}
void enemy_tank::getBuff(int x, int y) {
	switch (map[y / 40][x / 40]) {
	case 3:
		buff = 1;  // ��ȡ����buff
		break;
	case 4:
		buff = 2;  // ��ȡ����buff
		break;
	case 5:
		buff = 3;  // ��ȡ����buff
		break;
	default:
		break;
	}
}
int& enemy_tank::currentBuff()
{
	return buff;
}
int& enemy_tank::getHP() {
	return HP;
}

void enemy_tank::move()
{
	//���жϵз�̹���Ƿ���
	if (getIsLive() == 0)
		return;
	if (direction == 2)//�����ǰ����Ϊ��
	{
		//��һ��λ�ò�Խ�磬��Ϊשǽ��ʯǽ�����ء��ҷ�̹�ˡ��з�̹�ˡ��ҷ������ʱ
		if ((y - 40) > 0 && map[(y-40) / 40][x / 40] !=1 && map[(y - 40) / 40][x / 40] !=2 && map[(y - 40) / 40][x / 40] != 6&& map[(y - 40) / 40][x / 40] !=100 && map[(y - 40) / 40][x / 40] != 101 && map[(y - 40) / 40][x / 40] != 7)
		{
			//��mapԭ����λ��ֵ����
			map[y / 40][x / 40] =0;
			y = y - 40;
			getBuff(x, y);  // ��鲢Ӧ���µ��������
			map[y / 40][x / 40] = 101;
		}
	}
	if (direction == 3)//�����ǰ����Ϊ��
	{
		//��һ��λ�ò�Խ�磬��Ϊשǽ��ʯǽ�����ء��ҷ�̹�ˡ��з�̹�ˡ��ҷ������ʱ
		if ((y + 40) < 600 && map[(y+40)/ 40][x / 40] !=1 && map[(y + 40) / 40][x / 40] !=2 && map[(y + 40) / 40][x / 40] !=6 && map[(y + 40) / 40][x / 40] !=100 && map[(y + 40) / 40][x / 40] != 101 && map[(y + 40) / 40][x / 40] != 7)
		{
			map[y / 40][x / 40] = 0;
			y = y + 40;
			getBuff(x, y);  // ��鲢Ӧ���µ��������
			map[y / 40][x / 40] = 101;
		}
			
	}
	if (direction == 0)//�����ǰ����Ϊ��
	{
		//��һ��λ�ò�Խ�磬��Ϊשǽ��ʯǽ�����ء��ҷ�̹�ˡ��з�̹�ˡ��ҷ������ʱ
		if ((x - 40) > 0 && map[y / 40 ][(x - 40)/40] !=1 && map[y / 40][(x - 40) / 40] !=2 && map[y / 40][(x - 40) / 40] !=6 && map[y / 40][(x - 40) / 40] !=100 && map[y / 40][(x - 40) / 40] != 101 && map[y / 40][(x - 40) / 40] != 7)
		{
			map[y / 40][x / 40] =0;
			x = x - 40;
			getBuff(x, y);  // ��鲢Ӧ���µ��������
			map[y / 40][x / 40] = 101;
		}

	}
	if (direction == 1)//�����ǰ����Ϊ��
	{
		//��һ��λ�ò�Խ�磬��Ϊשǽ��ʯǽ�����ء��ҷ�̹�ˡ��з�̹�ˡ��ҷ������ʱ
		if ((x + 40) < 800 && map[y / 40 ][(x + 40)/40] !=1 && map[y / 40][(x + 40) / 40] !=2 && map[y / 40][(x + 40) / 40] !=6 && map[y / 40][(x + 40) / 40] !=100 && map[y / 40][(x + 40) / 40] != 101 && map[y / 40][(x + 40) / 40] != 7)
		{
			map[y / 40][x / 40] = 0;
			x = x + 40;
			getBuff(x, y);  // ��鲢Ӧ���µ��������
			map[y / 40][x / 40] = 101;
		}
	}
}
void enemy_tank::shoot(vector<bullet>& bullets)
{
	//���жϵз�̹���Ƿ���
	if (getIsLive()==0)
		return;

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
		pos_x1 = x;
		pos_y1 = y + 18;
		pos_x2 = x - 8;
		pos_y2 = pos_y1;
		break;
	}
	case 1://����
	{
		pos_x1 = x + 36;
		pos_y1 = y + 18;
		pos_x2 = pos_x1 + 8;
		pos_y2 = pos_y1;
		break;
	}
	case 2://����
	{
		pos_x1 = x + 18;
		pos_y1 = y;
		pos_x2 = pos_x1;
		pos_y2 = pos_y1 - 8;
		break;
	}
	case 3://����
	{
		pos_x1 = x + 18;
		pos_y1 = y + 36;
		pos_x2 = pos_x1;
		pos_y2 = pos_y1 + 8;
		break;
	}
	default:
		break;
	}
	if (this->buff == 2)//�����ǰbuff״̬Ϊ2-�����������������ӵ�
	{
		bullet bulletl(pos_x1, pos_y1, direction, 1, bullet_type, 1);
		bullet bullet2(pos_x2, pos_y2, direction, 1, bullet_type, 1);
		bullets.push_back(bulletl);  // �����ӵ�����������
		bullets.push_back(bullet2);  // �����ӵ�����������
	}
	else
	{
		bullet bulletl(pos_x1, pos_y1, direction, 1, bullet_type, 1);
		bullets.push_back(bulletl);  // �����ӵ�����������
	}

}
int enemy_tank::turn(int x,int y)
{
	//�з�̹�����ҷ�̹�ˣ�����أ�����Է��������£������ң���
	mt19937 engine(random_device{}());//�������������
	uniform_int_distribution<int> distribution(0, 9);//����0-9���ȷֲ���������ֲ�
	int randomNumber = distribution(engine);//���������
	int dx = this->x - x;//��Ժ���λ��
	int dy = this->y - y;//�������λ��
	if (dx >= 0 && dy >= 0) 
	{//�з�̹�˸����ҷ�̹�˵�λ������ת���ҷ�̹����Եз�̹�˵�λ�÷�Ϊ���ϣ����£����ϣ����£����磺���£�����������ż���������Ϊ�ң���������Ϊ�£�ͬ�����߼�����
		if (randomNumber % 2 == 0) {//����
			direction = 0;
		}
		else {
			direction = 2;
		}
	}
	else if (dx >= 0 && dy < 0)
	{//����
		if (randomNumber % 2 == 0) {
			direction = 0;
		}
		else {
			direction = 3;
		}
	}
	else if (dx < 0 && dy >= 0)
	{//����
		if (randomNumber % 2 == 0) {
			direction = 1;
		}
		else {
			direction = 2;
		}
	}
	else if (dx < 0 && dy < 0)
	{//����
		if (randomNumber % 2 == 0) {
			direction = 1;
		}
		else {
			direction = 3;
		}
	}
	return direction;
}

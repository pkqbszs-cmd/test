#include "bullet.h"
bullet::bullet() :Role(0, 0, 0), kind(0), fireCome(0),isLive(0) {}
bullet::bullet(int x, int y, int direction,int fireCome, int kind, int isLive) :Role(x, y, direction),fireCome(fireCome), kind(kind), isLive(isLive){}
int& bullet::getIsLive()
{
	return isLive;
}
int& bullet::getKind()
{
	return kind;
}
void bullet::move(vector<enemy_tank>& enemies, my_tank& player,int pos_x,int pos_y)
{
	//�ӵ���һ��������
	int x1=x, y1=y;
	
	//���ݵ�ǰ����ȷ����һ��������
	if (direction == 0)//��
		x1 = x1 - 20;
	else if (direction == 1)//��
		x1 = x1 + 20;
	else if (direction == 2)//��
		y1 = y1 - 20;
	else if (direction == 3)//��
		y1 = y1 + 20;
	else return;
	//�����Ӧ���±�
	int index_i = y / 40, index_j = x / 40;
	int index_i1 = y1 / 40, index_j1 = x1 / 40;

	//���������ӵ�����ʧ
	if (x1 < 0 || x1 >= 800 || y1 < 0 || y1 >= 600)
	{
		isLive = 0;
		return;
	}

	//��ײ���
	//����
	if (map[index_i1][index_j1] == 6)
	{
		map[index_i1][index_j1] = 0;
		isLive = 0;
		return;
	}
	//ʯǽ
	else if (map[index_i1][index_j1] == 2)
	{
		isLive = 0;//����ʯǽֱ�����ӵ���ʧ
	}
	//ľǽ
	else if (map[index_i1][index_j1] == 1) {
		map[index_i1][index_j1] = 0;//����map��ֵ
		isLive = 0;
	}
	//���
	else if (map[index_i1][index_j1] == 100) {
		if (player.currentBuff() == 3)//�����ҵ�ǰ�ж���buff
		{
			isLive = 0;
			player.currentBuff() = 0;//�Ƴ�����buff
			//����ӵ��ǵ���,�����ֻ�ܵ�һ�Σ�����Ҫ�����һ��Ѫ
			if (kind == 1)
			{
				player.getHP() -= 1;
			}
			return;
		}
		//û�ж���buff��������Ѫ
		//����map��ֵΪ0,������ڳ�����λ���ϣ��򲻸ı������λ�õ�ֵ
		map[index_i1][index_j1] = (map[index_i1][index_j1]==7)?map[index_i1][index_j1]:0;
		player.getHP() -= (kind == 1) ? 2 : 1;
		player.reLive(pos_x, pos_y);//����ڻ�������
		isLive = 0;
	}
	//�л�,ֻ���ҷ��ӵ����ܻ�ɱ�з�̹��
	else if(map[index_i1][index_j1] == 101)
	{	
		for (auto& enemy : enemies) {
			if(enemy.x ==index_j1*40 &&enemy.y==index_i1*40 && fireCome==0)//��������[index_j1*40][index_i1*40]�ĵз�̹��,�����������ҷ����ӵ�
			{
				if (enemy.currentBuff() == 3)//����з�̹�˵�ǰ�ж���buff
				{
					isLive = 0;
					enemy.currentBuff() = 0;//�Ƴ�����buff
					//����ӵ��ǵ���,�����ֻ�ܵ�һ�Σ�����Ҫ�����һ��Ѫ
					if (kind == 1)
					{
						enemy.getHP() -= 1;
					}
					return;
				}
				//û�ж���buff��������Ѫ
				enemy.getHP() -= (kind == 1) ? 2 : 1;
				if (enemy.getIsLive() == 0)//���з�̹������ʱ
				{
					//�ӵз�̹���������Ƴ������ĵз�̹��
					enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
					player.getKill() += 1;
					//����map��ֵΪ0,����ڳ�����λ���ϣ��򲻸ı������λ�õ�ֵ
					map[index_i1][index_j1] = (map[index_i1][index_j1] == 7) ? map[index_i1][index_j1] : 0;
				}
				isLive = 0;
				return;
			}
			else if(enemy.x == index_j1 * 40 && enemy.y == index_i1 * 40 && fireCome == 1)//�������Եз����ӵ�����ֻ�ƶ��������ǵз�̹�ˣ�
			{
				x = x1;
				y = y1;
				return;
			}
		}
	}
	//����ӵ����������ƶ�
	else if(isLive==1)
	{
		x = x1;
		y = y1;
	}
}
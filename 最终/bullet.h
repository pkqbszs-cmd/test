#pragma once
#include"data.h"
#include"Role.h"
#include"my_tank.h"
#include"enemy_tank.h"
class bullet :public Role {
public:
	/*
		���ܣ�Ĭ�Ϲ��캯��
	*/
	bullet();
	/*
		���ܣ���ʼ���ӵ�
			  ���������Ը�ֵ
		������
			x:�ӵ��ĺ�����
			y:�ӵ���������
			direction���ӵ��ĳ���
			kind:�ӵ�����
			fireCome:�ӵ���Դ
			isLive:�ӵ����״̬
	*/
	bullet(int x, int y, int direction,int fireCome,int kind = 0, int isLive = 1);
	/*
		���ܣ������ӵ����ƶ�
			�����ӵ���ǰ�ĳ�����ǰ�ƶ�1�����أ�int x1=x+/-1����int y1=y+/-1;
			���ƶ�����ӵ���ľǽ��ײ�����ӵ���ľǽһ��ݻ�
			if(map[y1/40][x1/40]==1)
			{
				

			}
			���ƶ�����ӵ���ʯǽ��ײ���߳�����Ļ��Χ�����ӵ��ķ����ת
			���ƶ�����ӵ���л���ײ�����ӵ��ݻ٣��л�HP-1������ǵ�����HP-2��
			���ƶ�����ӵ��������ײ�����ӵ��ݻ٣����HP-1������ǵ�����HP-2��������ڻ�������
		������	
			pos_x:���صĺ�����
			pos_y:���ص�������
			enemies:����̹����
			player:�ҷ�̹��
		����ֵ��void
	*/
	void move(vector<enemy_tank>& enemies, my_tank& player, int pos_x, int pos_y);// �ӵ�����kind����ѡ����һ���˽�����ײ�ж�
	/*
		���ܣ������ӵ���ǰ���״̬
		������void
		����ֵ��int&:���״̬������
	*/
	int& getIsLive();
	/*
		���ܣ������ӵ�����
		������void
		����ֵ��int&:���������
	*/
	int& getKind();
	bool operator==(const bullet& other) const {
		// �Ƚ��߼���������Ҫ�Ƚ���س�Ա
		return this->x == other.x && this->y == other.y && this->direction == other.direction &&
			this->kind == other.kind && this->isLive == other.isLive  && this->fireCome == other.fireCome;
	}
private:
	int kind;//�ӵ����࣬0������ͨ�ӵ���1������
	int isLive;//�ӵ����״̬��0������ʧ��1������
	int fireCome;//�ӵ�����Դ��0���������ҷ���1�������Եз�
};

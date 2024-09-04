#pragma once
#include"data.h"
#include"Role.h"
class bullet;
class enemy_tank :public Role {
public:
	/*enemy_tank();*/
	/*
		�����ˣ�
		���ܣ���ʼ���з�̹�˵�����
		������
			x:�з�̹�˵ĺ�����
			y:�з�̹�˵�������
			direction:����
			HP:Ѫ��
			buff:��ǰ��buffЧ��
			isLive:�Ƿ���
				   0��������
				   1������
		����ֵ��void
	*/
	enemy_tank(int x, int y, int direction = 3, int HP = 1,int buff = 0, int isLive = 1);
	/*
		�����ˣ�
		���ܣ����Ƶз�̹�˵��ƶ�
			  �ƶ����ɣ�ÿ���ƶ�40����
			  ��ǰ��Ϊ�յأ������е��ߵĿյأ����������ƶ���ͬʱ������޴�������
			  ��ǰ��Ϊǽ���߽߱磬���ƶ�
		������void
		����ֵ��void
	*/
	void move();
	/*
		�����ˣ�
		���ܣ����Ƶз�̹�˵�ת��
			  ת����ɣ�ÿ����ת���򶼳���Ŀ�꣨x,y���Ĵ��·�����ת���������ת�������
			  ���磺��x,y���ڵз�̹�˵����½ǣ�����ת�ķ������һ�������
		������
			x:Ŀ��ĺ�����
			y:Ŀ���������
		����ֵ��void
	*/
	int turn(int x, int y);
	/*
		�����ˣ�
		���ܣ������ӵ�
			  ��buff==0��������ӵ�Ϊ��ͨ�ӵ�
			  ��buff==1��������ӵ�Ϊ����
			  ��buff==2��������ӵ�Ϊ���⣨������
			  ����̹�˵�ǰ�ĳ�������꣬���ӵ����費ͬ�ĳ��������
		������void
		����ֵ��void
	*/
	void shoot(vector<bullet>& bullets);
	/*
	�����ˣ�
	���ܣ����ص�ǰHP
	������void
	����ֵ��int&
	*/
	int& getHP();
	/*
	�����ˣ�
	���ܣ����buff
		  ���map[y/40][x/40]��buff����
		  ���ݴ�������buff�����࣬����̹�˲�ͬ��buffЧ��
		  ����̹�˵ĵ�ǰbuffЧ����1,2,3��������̹�˲�ͬ������
		  ����buff==1��������ӵ�Ϊ����
		  ��buff==2��������ӵ�Ϊ���⣨������
		  ��buff==3�����Եֵ�һ���ӵ��Ĺ�����
	������
		x:���ߺ�����
		y:����������
	����ֵ��void
	*/
	void getBuff(int x, int y);
	/*
	���ܣ���ȡ�з�̹�˵�ǰ��buff״̬
	������void
	����ֵ��
		int&:̹�˵�ǰ��buff״̬
	*/
	int& currentBuff();
	/*
		���ܣ��жϸõз�̹�˵�ǰ�Ƿ���
		����:void
		����ֵ:
			int:0��������
				1������
	*/
	int getIsLive();
	/*
		���ܣ����������==������remove
		������
			other:�з�̹�˵ĳ�����
		����ֵ��
			bool��other�͵�ǰ̹���Ƿ���ͬ��false����ͬ��true������ͬ
	*/
	bool operator==(const enemy_tank& other) const {
		// �Ƚ��߼���������Ҫ�Ƚ���س�Ա
		return this->x==other.x && this->y==other.y && this->direction==other.direction &&
			this->HP==other.HP && this->buff==other.buff && this->isLive==other.isLive;
	}
private:
	int HP;
	int buff;
	int isLive;
};

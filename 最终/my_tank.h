#pragma once
#include"data.h"
#include"Role.h"
class bullet;

class my_tank :public Role {
public:
	/*
		�����ˣ�
		���ܣ���ʼ���ҷ�̹�˵�����
		������
			x:������
			y:������
			direction:����
			HP:Ѫ��
			buff:����Ч��
	*/
	my_tank(int x, int y, int direction = 2, int HP = 3, int buff = 0,int kill_enemy=0);
	/*
		���ܣ�ʹ̹���ڻ�������
		������
			pos_x:���غ�����
			pos_y:����������
		����ֵ:void
	*/
	void reLive(int pos_x, int pos_y);
	/*
		�����ˣ�
		���ܣ�����̹�˵��ƶ�
			���ܼ��̵���Ϣ��wasd��
			�����յ��ļ�����Ϣ��ָ������̹�˵�ǰ����һ�£���ǰ��Ϊ�յأ�������buff�ĵط��������Ÿ÷����ƶ�40���أ�ͬʱ���ǰ������buff
			�����ܵ��ļ�����Ϣ��ָ������̹�˵�ǰ����һ�£��������̹�˵ķ���
			������Ϊ��
			if(map[y/40-1][x/40]==0||map[y/40-1][x/40]==3||map[y/40-1][x/40]==4||map[y/40-1][x/40]==5||direction==2||(y-40)>=0)
			{
				map[y/40][x/40]=0;
				y=y-40;
				getBuff(x,y);
				map[y/40][x/40]=100;
			}
			else if(direction!=2)
			{
				direction=2;
			}
		������void
		����ֵ��void
	*/
	void move();
	/*
		�����ˣ�
		���ܣ������ӵ�
			  ������ܵ�������Ϣ'j'��������һ���ӵ�
			  ��buff==0��3��������ӵ�Ϊ��ͨ�ӵ�
			  ��buff==1��������ӵ�Ϊ����
			  ��buff==2��������ӵ�Ϊ����
			  ����̹�˵�ǰ�ĳ�������꣬���ӵ����費ͬ�ĳ��������
		������void
		����ֵ��
			int:0������ɹ�
				1����û�з���
	*/
	int shoot(vector<bullet>& bullets);
	/*
		�����ˣ�
		���ܣ����buff
			  ���map[y/40][x/40]��buff����
			  ���ݴ�������buff�����࣬����̹�˲�ͬ��buffЧ��
			  ����̹�˵ĵ�ǰbuffЧ����1,2,3��������̹�˲�ͬ������
			  ��
			  ��buff==1��������ӵ�Ϊ����
			  ��buff==2��������ӵ�Ϊ����
			  ��buff==3����ҿ��Եֵ�һ���ӵ��Ĺ�����
		������
			x:���ߺ�����
			y:����������
		����ֵ��void
	*/
	void getBuff(int x, int y);
	/*
		���ܣ���⵱ǰbuff״̬
		������void
		����ֵ��
			int:��ǰ��buff״̬
	*/
	int& currentBuff();
	/*
		�����ˣ�
		���ܣ����ص�ǰHP
		������void
		����ֵ��int&
	*/
	int& getHP();
	/*
		���ܣ����ص�ǰɱ����
		������void
		����ֵ��int&
	*/
	int& getKill();
private:
	int HP;
	int buff;
	int kill_enemy;
};

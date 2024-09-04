#pragma once
#include"data.h"
#include"Role.h"
class bullet;

class my_tank :public Role {
public:
	/*
		负责人：
		功能：初始化我方坦克的属性
		参数：
			x:横坐标
			y:纵坐标
			direction:朝向
			HP:血量
			buff:道具效果
	*/
	my_tank(int x, int y, int direction = 2, int HP = 3, int buff = 0,int kill_enemy=0);
	/*
		功能：使坦克在基地重生
		参数：
			pos_x:基地横坐标
			pos_y:基地纵坐标
		返回值:void
	*/
	void reLive(int pos_x, int pos_y);
	/*
		负责人：
		功能：控制坦克的移动
			接受键盘的消息（wasd）
			若接收到的键盘消息所指方向与坦克当前方向一致，且前方为空地（或者有buff的地方），则朝着该方向移动40像素，同时检测前方有无buff
			若接受到的键盘消息所指方向与坦克当前方向不一致，则仅调整坦克的方向
			以向上为例
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
		参数：void
		返回值：void
	*/
	void move();
	/*
		负责人：
		功能：发射子弹
			  如果接受到键盘消息'j'，则生成一颗子弹
			  当buff==0或3，发射的子弹为普通子弹
			  当buff==1，发射的子弹为导弹
			  当buff==2，发射的子弹为两发
			  根据坦克当前的朝向和坐标，给子弹赋予不同的朝向和坐标
		参数：void
		返回值：
			int:0代表发射成功
				1代表没有发射
	*/
	int shoot(vector<bullet>& bullets);
	/*
		负责人：
		功能：获得buff
			  检测map[y/40][x/40]的buff种类
			  根据触碰到的buff的种类，赋予坦克不同的buff效果
			  根据坦克的当前buff效果（1,2,3），赋予坦克不同的增幅
			  （
			  当buff==1，发射的子弹为导弹
			  当buff==2，发射的子弹为激光
			  当buff==3，玩家可以抵挡一次子弹的攻击）
		参数：
			x:道具横坐标
			y:道具纵坐标
		返回值：void
	*/
	void getBuff(int x, int y);
	/*
		功能：检测当前buff状态
		参数：void
		返回值：
			int:当前的buff状态
	*/
	int& currentBuff();
	/*
		负责人：
		功能：返回当前HP
		参数：void
		返回值：int&
	*/
	int& getHP();
	/*
		功能：返回当前杀敌数
		参数：void
		返回值：int&
	*/
	int& getKill();
private:
	int HP;
	int buff;
	int kill_enemy;
};

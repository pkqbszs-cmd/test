#pragma once
#include"data.h"
#include"Role.h"
class bullet;
class enemy_tank :public Role {
public:
	/*enemy_tank();*/
	/*
		负责人：
		功能：初始化敌方坦克的属性
		参数：
			x:敌方坦克的横坐标
			y:敌方坦克的纵坐标
			direction:方向
			HP:血量
			buff:当前的buff效果
			isLive:是否存活
				   0代表死亡
				   1代表存活
		返回值：void
	*/
	enemy_tank(int x, int y, int direction = 3, int HP = 1,int buff = 0, int isLive = 1);
	/*
		负责人：
		功能：控制敌方坦克的移动
			  移动规律：每次移动40像素
			  若前方为空地（或者有道具的空地），则正常移动，同时检测有无触碰道具
			  若前方为墙或者边界，则不移动
		参数：void
		返回值：void
	*/
	void move();
	/*
		负责人：
		功能：控制敌方坦克的转向
			  转向规律：每次旋转方向都朝着目标（x,y）的大致方向旋转，具体的旋转方向随机
			  例如：（x,y）在敌方坦克的右下角，则旋转的方向向右或者向下
		参数：
			x:目标的横坐标
			y:目标的纵坐标
		返回值：void
	*/
	int turn(int x, int y);
	/*
		负责人：
		功能：发射子弹
			  当buff==0，发射的子弹为普通子弹
			  当buff==1，发射的子弹为导弹
			  当buff==2，发射的子弹为激光（连发）
			  根据坦克当前的朝向和坐标，给子弹赋予不同的朝向和坐标
		参数：void
		返回值：void
	*/
	void shoot(vector<bullet>& bullets);
	/*
	负责人：
	功能：返回当前HP
	参数：void
	返回值：int&
	*/
	int& getHP();
	/*
	负责人：
	功能：获得buff
		  检测map[y/40][x/40]的buff种类
		  根据触碰到的buff的种类，赋予坦克不同的buff效果
		  根据坦克的当前buff效果（1,2,3），赋予坦克不同的增幅
		  （当buff==1，发射的子弹为导弹
		  当buff==2，发射的子弹为激光（连发）
		  当buff==3，可以抵挡一次子弹的攻击）
	参数：
		x:道具横坐标
		y:道具纵坐标
	返回值：void
	*/
	void getBuff(int x, int y);
	/*
	功能：获取敌方坦克当前的buff状态
	参数：void
	返回值：
		int&:坦克当前的buff状态
	*/
	int& currentBuff();
	/*
		功能：判断该敌方坦克当前是否存活
		参数:void
		返回值:
			int:0代表死亡
				1代表存活
	*/
	int getIsLive();
	/*
		功能：重载运算符==，用于remove
		参数：
			other:敌方坦克的常引用
		返回值：
			bool：other和当前坦克是否相同，false代表不同，true代表相同
	*/
	bool operator==(const enemy_tank& other) const {
		// 比较逻辑，根据需要比较相关成员
		return this->x==other.x && this->y==other.y && this->direction==other.direction &&
			this->HP==other.HP && this->buff==other.buff && this->isLive==other.isLive;
	}
private:
	int HP;
	int buff;
	int isLive;
};

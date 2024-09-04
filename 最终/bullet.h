#pragma once
#include"data.h"
#include"Role.h"
#include"my_tank.h"
#include"enemy_tank.h"
class bullet :public Role {
public:
	/*
		功能：默认构造函数
	*/
	bullet();
	/*
		功能：初始化子弹
			  给各个属性赋值
		参数：
			x:子弹的横坐标
			y:子弹的纵坐标
			direction：子弹的朝向
			kind:子弹种类
			fireCome:子弹来源
			isLive:子弹存活状态
	*/
	bullet(int x, int y, int direction,int fireCome,int kind = 0, int isLive = 1);
	/*
		功能：控制子弹的移动
			根据子弹当前的朝向向前移动1个像素，int x1=x+/-1或者int y1=y+/-1;
			若移动后的子弹与木墙碰撞，则子弹和木墙一起摧毁
			if(map[y1/40][x1/40]==1)
			{
				

			}
			若移动后的子弹与石墙碰撞或者超出屏幕范围，则子弹的方向调转
			若移动后的子弹与敌机碰撞，则子弹摧毁，敌机HP-1（如果是导弹则HP-2）
			若移动后的子弹与玩家碰撞，则子弹摧毁，玩家HP-1（如果是导弹则HP-2），玩家在基地重生
		参数：	
			pos_x:基地的横坐标
			pos_y:基地的纵坐标
			enemies:敌人坦克组
			player:我方坦克
		返回值：void
	*/
	void move(vector<enemy_tank>& enemies, my_tank& player, int pos_x, int pos_y);// 子弹根据kind自行选择玩家或敌人进行碰撞判断
	/*
		功能：返回子弹当前存活状态
		参数：void
		返回值：int&:存活状态的引用
	*/
	int& getIsLive();
	/*
		功能：返回子弹种类
		参数：void
		返回值：int&:种类的引用
	*/
	int& getKind();
	bool operator==(const bullet& other) const {
		// 比较逻辑，根据需要比较相关成员
		return this->x == other.x && this->y == other.y && this->direction == other.direction &&
			this->kind == other.kind && this->isLive == other.isLive  && this->fireCome == other.fireCome;
	}
private:
	int kind;//子弹种类，0代表普通子弹，1代表导弹
	int isLive;//子弹存活状态，0代表消失，1代表存活
	int fireCome;//子弹的来源，0代表来自我方，1代表来自敌方
};

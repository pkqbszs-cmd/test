#include "my_tank.h"
#include"bullet.h"
my_tank::my_tank(int x, int y, int direction, int HP, int buff, int kill_enemy)
	: Role(x, y, direction), HP(HP), buff(buff), kill_enemy(kill_enemy) {
	map[y / 40][x / 40] = 100;  // 在地图二维数组中标记我方坦克位置
}

void my_tank::reLive(int pos_x, int pos_y)
{
	this->x = pos_x;
	this->y = pos_y;
	this->buff = 0;
}
/*
	函数名称：move
	参数：void
	功能：
		控制坦克的移动，根据玩家按下的键盘按键（W、A、S、D）决定坦克的方向和移动，
		并根据方向更新坦克的坐标。
		若坦克朝向与按键指向一致且前方为空地或有增益道具，则坦克移动到新位置并检测是否获得增益道具。
		若朝向与按键指向不一致，则调整坦克方向而不移动。
*/
void my_tank::move() {
	// 如果按下W键，坦克尝试向上移动
	if (GetAsyncKeyState('W') & 0x8000) {
		// 判断坦克当前方向是否为向上，如果是，则进一步判断是否可以向上移动
		if (direction == 2 && (y - 40) >= 0 &&
			map[y / 40 - 1][x / 40] != 1 && map[y / 40 - 1][x / 40] != 2 && map[y / 40 - 1][x / 40] != 6 && map[y / 40 - 1][x / 40] != 101) {
			map[y / 40][x / 40] = 0;  // 清空当前地图上的坦克位置标记
			y -= 40;  // 更新坦克的纵坐标（向上移动）
			getBuff(x, y);  // 检查并应用新的增益道具
			map[y / 40][x / 40] = 100;  // 在新位置标记坦克
		}
		else if (direction != 2) {
			// 如果当前方向不是向上，则调整方向为向上
			direction = 2;
		}
	}
	// 处理其他方向的移动（A: 左，S: 下，D: 右），实现与上述相似的逻辑
	// 处理S键 （向下移动）
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
	// 示例：处理A键（向左移动）
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



	// 示例：处理D键（向右移动）
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
	函数名称：shoot
	参数：
		bullets - 存储子弹的向量（容器）
	功能：
		当玩家按下 'J' 键时，生成一颗子弹并添加到 bullets 容器中。
		根据坦克当前的buff状态（buff值），生成不同类型的子弹。
		0或3 - 普通子弹，1 - 导弹，2 - 激光。
		子弹的初始方向和位置取决于坦克当前的方向和位置。
*/
int my_tank::shoot(vector<bullet>& bullets)
{
	if (GetAsyncKeyState('J') & 0x8000)
	{
		int bullet_type = (this->buff == 1) ? 1 : 0;  // 根据buff决定子弹类型，当前buff效果为1时，子弹种类变为1-导弹
		int direction = this->direction;			  //子弹的方向与坦克朝向一致
		//子弹的坐标，1是第一个子弹的坐标，2是连发时第二个子弹的坐标
		int pos_x1, pos_x2;
		int pos_y1, pos_y2;

		//根据坦克当前的方向设定子弹发射出来的初始坐标
		switch (direction)
		{
		case 0://向左
		{
			if (bullet_type == 1)//如果是导弹buff状态
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
		case 1://向右
		{
			if (bullet_type == 1)//如果是导弹buff状态
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
		case 2://向上
		{
			if (bullet_type == 1)//如果是导弹buff状态
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
		case 3://向下
		{
			if (bullet_type == 1)//如果是导弹buff状态
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
		if (this->buff == 2)//如果当前buff状态为2-连发，则生成两个子弹
		{
			bullet bulletl(pos_x1, pos_y1, direction, 0, bullet_type);
			bullet bullet2(pos_x2, pos_y2, direction, 0, bullet_type);
			bullets.push_back(bulletl);  // 生成子弹并加入容器
			bullets.push_back(bullet2);  // 生成子弹并加入容器
		}
		else
		{
			bullet bulletl(pos_x1, pos_y1, direction, 0, bullet_type);
			bullets.push_back(bulletl);  // 生成子弹并加入容器
		}
		return 0;//发射子弹成功
	}
	return 1;//发射子弹失败
}

/*
	函数名称：getBuff
	参数：
		x - 当前道具的横坐标
		y - 当前道具的纵坐标
	功能：
		检测坦克当前所在位置的地图格子中是否有buff道具，
		如果有，则更新坦克的buff状态。不同的道具赋予不同的效果：
		3 - 导弹buff，1 - 导弹，2 - 激光，5 - 盾牌（可以抵挡一次子弹攻击）。
*/
void my_tank::getBuff(int x, int y) {
	switch (map[y / 40][x / 40]) {
	case 3:
		buff = 1;  // 获取导弹buff
		break;
	case 4:
		buff = 2;  // 获取激光（连发）buff
		break;
	case 5:
		buff = 3;  // 获取盾牌buff
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
	函数名称：getHP
	参数：无
	返回值：int& - 坦克的当前HP引用
	功能：
		返回坦克的当前血量HP，以便于其他地方访问或修改血量。
*/
int& my_tank::getHP() {
	return HP;
}

int& my_tank::getKill()
{
	return kill_enemy;
}

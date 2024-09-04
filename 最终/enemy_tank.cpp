#include "enemy_tank.h"
#include"bullet.h"
//enemy_tank::enemy_tank() :Role(0, 0, 3), HP(1), buff(0), isLive(0) {}
enemy_tank::enemy_tank(int x, int y, int direction, int HP, int buff, int isLive) : Role(x, y, direction), HP(HP), buff(buff), isLive(isLive) 
{//构造函数
	map[y / 40][x / 40] = 101;  // 在地图二维数组中标记敌方坦克位置
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
		buff = 1;  // 获取导弹buff
		break;
	case 4:
		buff = 2;  // 获取激光buff
		break;
	case 5:
		buff = 3;  // 获取盾牌buff
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
	//先判断敌方坦克是否存活
	if (getIsLive() == 0)
		return;
	if (direction == 2)//如果当前朝向为上
	{
		//下一个位置不越界，不为砖墙、石墙、基地、我方坦克、敌方坦克、我方复活点时
		if ((y - 40) > 0 && map[(y-40) / 40][x / 40] !=1 && map[(y - 40) / 40][x / 40] !=2 && map[(y - 40) / 40][x / 40] != 6&& map[(y - 40) / 40][x / 40] !=100 && map[(y - 40) / 40][x / 40] != 101 && map[(y - 40) / 40][x / 40] != 7)
		{
			//将map原来的位置值更新
			map[y / 40][x / 40] =0;
			y = y - 40;
			getBuff(x, y);  // 检查并应用新的增益道具
			map[y / 40][x / 40] = 101;
		}
	}
	if (direction == 3)//如果当前朝向为下
	{
		//下一个位置不越界，不为砖墙、石墙、基地、我方坦克、敌方坦克、我方复活点时
		if ((y + 40) < 600 && map[(y+40)/ 40][x / 40] !=1 && map[(y + 40) / 40][x / 40] !=2 && map[(y + 40) / 40][x / 40] !=6 && map[(y + 40) / 40][x / 40] !=100 && map[(y + 40) / 40][x / 40] != 101 && map[(y + 40) / 40][x / 40] != 7)
		{
			map[y / 40][x / 40] = 0;
			y = y + 40;
			getBuff(x, y);  // 检查并应用新的增益道具
			map[y / 40][x / 40] = 101;
		}
			
	}
	if (direction == 0)//如果当前朝向为左
	{
		//下一个位置不越界，不为砖墙、石墙、基地、我方坦克、敌方坦克、我方复活点时
		if ((x - 40) > 0 && map[y / 40 ][(x - 40)/40] !=1 && map[y / 40][(x - 40) / 40] !=2 && map[y / 40][(x - 40) / 40] !=6 && map[y / 40][(x - 40) / 40] !=100 && map[y / 40][(x - 40) / 40] != 101 && map[y / 40][(x - 40) / 40] != 7)
		{
			map[y / 40][x / 40] =0;
			x = x - 40;
			getBuff(x, y);  // 检查并应用新的增益道具
			map[y / 40][x / 40] = 101;
		}

	}
	if (direction == 1)//如果当前朝向为右
	{
		//下一个位置不越界，不为砖墙、石墙、基地、我方坦克、敌方坦克、我方复活点时
		if ((x + 40) < 800 && map[y / 40 ][(x + 40)/40] !=1 && map[y / 40][(x + 40) / 40] !=2 && map[y / 40][(x + 40) / 40] !=6 && map[y / 40][(x + 40) / 40] !=100 && map[y / 40][(x + 40) / 40] != 101 && map[y / 40][(x + 40) / 40] != 7)
		{
			map[y / 40][x / 40] = 0;
			x = x + 40;
			getBuff(x, y);  // 检查并应用新的增益道具
			map[y / 40][x / 40] = 101;
		}
	}
}
void enemy_tank::shoot(vector<bullet>& bullets)
{
	//先判断敌方坦克是否存活
	if (getIsLive()==0)
		return;

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
		pos_x1 = x;
		pos_y1 = y + 18;
		pos_x2 = x - 8;
		pos_y2 = pos_y1;
		break;
	}
	case 1://向右
	{
		pos_x1 = x + 36;
		pos_y1 = y + 18;
		pos_x2 = pos_x1 + 8;
		pos_y2 = pos_y1;
		break;
	}
	case 2://向上
	{
		pos_x1 = x + 18;
		pos_y1 = y;
		pos_x2 = pos_x1;
		pos_y2 = pos_y1 - 8;
		break;
	}
	case 3://向下
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
	if (this->buff == 2)//如果当前buff状态为2-连发，则生成两个子弹
	{
		bullet bulletl(pos_x1, pos_y1, direction, 1, bullet_type, 1);
		bullet bullet2(pos_x2, pos_y2, direction, 1, bullet_type, 1);
		bullets.push_back(bulletl);  // 生成子弹并加入容器
		bullets.push_back(bullet2);  // 生成子弹并加入容器
	}
	else
	{
		bullet bulletl(pos_x1, pos_y1, direction, 1, bullet_type, 1);
		bullets.push_back(bulletl);  // 生成子弹并加入容器
	}

}
int enemy_tank::turn(int x,int y)
{
	//敌方坦克与我方坦克（或基地）的相对方向，先向下，向左，右，上
	mt19937 engine(random_device{}());//创建随机数引擎
	uniform_int_distribution<int> distribution(0, 9);//创建0-9均匀分布的随机数分布
	int randomNumber = distribution(engine);//生成随机数
	int dx = this->x - x;//相对横轴位置
	int dy = this->y - y;//相对纵轴位置
	if (dx >= 0 && dy >= 0) 
	{//敌方坦克根据我方坦克的位置做出转向，我方坦克相对敌方坦克的位置分为左上，左下，右上，右下，例如：右下，如果随机数是偶数，方向变为右，是奇数变为下，同样的逻辑处理
		if (randomNumber % 2 == 0) {//左上
			direction = 0;
		}
		else {
			direction = 2;
		}
	}
	else if (dx >= 0 && dy < 0)
	{//左下
		if (randomNumber % 2 == 0) {
			direction = 0;
		}
		else {
			direction = 3;
		}
	}
	else if (dx < 0 && dy >= 0)
	{//右上
		if (randomNumber % 2 == 0) {
			direction = 1;
		}
		else {
			direction = 2;
		}
	}
	else if (dx < 0 && dy < 0)
	{//右下
		if (randomNumber % 2 == 0) {
			direction = 1;
		}
		else {
			direction = 3;
		}
	}
	return direction;
}

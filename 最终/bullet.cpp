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
	//子弹下一步的坐标
	int x1=x, y1=y;
	
	//根据当前方向，确定下一步的坐标
	if (direction == 0)//左
		x1 = x1 - 20;
	else if (direction == 1)//右
		x1 = x1 + 20;
	else if (direction == 2)//上
		y1 = y1 - 20;
	else if (direction == 3)//下
		y1 = y1 + 20;
	else return;
	//坐标对应的下标
	int index_i = y / 40, index_j = x / 40;
	int index_i1 = y1 / 40, index_j1 = x1 / 40;

	//超出界限子弹就消失
	if (x1 < 0 || x1 >= 800 || y1 < 0 || y1 >= 600)
	{
		isLive = 0;
		return;
	}

	//碰撞检测
	//基地
	if (map[index_i1][index_j1] == 6)
	{
		map[index_i1][index_j1] = 0;
		isLive = 0;
		return;
	}
	//石墙
	else if (map[index_i1][index_j1] == 2)
	{
		isLive = 0;//碰到石墙直接让子弹消失
	}
	//木墙
	else if (map[index_i1][index_j1] == 1) {
		map[index_i1][index_j1] = 0;//更新map的值
		isLive = 0;
	}
	//玩家
	else if (map[index_i1][index_j1] == 100) {
		if (player.currentBuff() == 3)//如果玩家当前有盾牌buff
		{
			isLive = 0;
			player.currentBuff() = 0;//移除盾牌buff
			//如果子弹是导弹,则盾牌只能挡一次，还需要另外扣一滴血
			if (kind == 1)
			{
				player.getHP() -= 1;
			}
			return;
		}
		//没有盾牌buff则正常扣血
		//更新map的值为0,若玩家在出生地位置上，则不改变出生地位置的值
		map[index_i1][index_j1] = (map[index_i1][index_j1]==7)?map[index_i1][index_j1]:0;
		player.getHP() -= (kind == 1) ? 2 : 1;
		player.reLive(pos_x, pos_y);//玩家在基地重生
		isLive = 0;
	}
	//敌机,只有我方子弹才能击杀敌方坦克
	else if(map[index_i1][index_j1] == 101)
	{	
		for (auto& enemy : enemies) {
			if(enemy.x ==index_j1*40 &&enemy.y==index_i1*40 && fireCome==0)//找坐标在[index_j1*40][index_i1*40]的敌方坦克,并且是来自我方的子弹
			{
				if (enemy.currentBuff() == 3)//如果敌方坦克当前有盾牌buff
				{
					isLive = 0;
					enemy.currentBuff() = 0;//移除盾牌buff
					//如果子弹是导弹,则盾牌只能挡一次，还需要另外扣一滴血
					if (kind == 1)
					{
						enemy.getHP() -= 1;
					}
					return;
				}
				//没有盾牌buff则正常扣血
				enemy.getHP() -= (kind == 1) ? 2 : 1;
				if (enemy.getIsLive() == 0)//当敌方坦克死亡时
				{
					//从敌方坦克数组中移除死亡的敌方坦克
					enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
					player.getKill() += 1;
					//更新map的值为0,如果在出生地位置上，则不改变出生地位置的值
					map[index_i1][index_j1] = (map[index_i1][index_j1] == 7) ? map[index_i1][index_j1] : 0;
				}
				isLive = 0;
				return;
			}
			else if(enemy.x == index_j1 * 40 && enemy.y == index_i1 * 40 && fireCome == 1)//若是来自敌方的子弹，则只移动（不覆盖敌方坦克）
			{
				x = x1;
				y = y1;
				return;
			}
		}
	}
	//如果子弹存活，则正常移动
	else if(isLive==1)
	{
		x = x1;
		y = y1;
	}
}
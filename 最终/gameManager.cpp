#include "gameManager.h"
void gameManager::enemy_generate(vector<enemy_tank>& enemys, my_tank& player, int x, int y)
{

	if (pass == 1 || pass == 2 || pass == 3)//前三关场上最多可有3个敌方坦克
	{
		if (current_enemy < 3 && (player.getKill() + current_enemy) < total_enemy)
		{
			if (player.x == x && player.y == y)//当我方坦克在敌方坦克生成位置上时，不能生成敌方坦克
				return;
			else
			{
				enemy_tank enemy(x, y, 3, 1);//初始化并绘制出来一个敌方坦克，血量为1
				current_enemy += 1;				//场上坦克数加一
				enemys.push_back(enemy);		//并将其添加到敌方坦克组中
			}
		}
	}
	else
	{
		if (current_enemy < 5 && (player.getKill() + current_enemy) < total_enemy)
		{
			if (player.x == x && player.y == y)//当我方坦克在敌方坦克生成位置上时，不能生成敌方坦克
				return;
			else
			{
				enemy_tank enemy(x, y, 3, 2);//初始化并绘制出来一个敌方坦克，血量为2
				current_enemy += 1;				//场上坦克数加一
				enemys.push_back(enemy);		//并将其添加到敌方坦克组中
			}
		}
	}
	//只有当场上敌方坦克数量小于最大容许坦克数量，并且已击杀+场上敌方坦克数量<需要击杀的敌机总数时，才生成一个敌方坦克
	
}

void gameManager::buff_generate(int x, int y, int buff)
{
	//只有当场上的buff被拾取完后才会生成新的buff道具
	for (int row = 0; row < 15; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			if (map[row][col] == 3 || map[row][col] == 4 || map[row][col] == 5)//如果检测到buff存在
			{
				return;
			}
		}
	}
	map[y / 40][x / 40] = buff;
}


// 打印排行榜的函数
void gameManager::printRank()
{
	updateRank();
	while (true) {
		if (peekmessage(&msg, EX_MOUSE)) {} // 检测鼠标消息
		BeginBatchDraw(); // 开始批量绘图，提高绘图效率
		cleardevice();
		putimage(0, 0, &back_img[2]);
		// 打印"排行榜"标题
		int textWidth = 25, textHeight = 40; // 设置字体的宽度和高度
		settextstyle(textHeight, textWidth, "黑体"); // 设置字体样式为黑体
		settextcolor(BLACK); // 设置文字颜色为黑色
		const char* s = "排行榜"; // 定义显示的多字节字符文字
		int bgi = 10; // "排行榜"文字开始显示的纵坐标
		outtextxy(400 - textwidth(s) / 2, bgi, s); // 在图形窗口中间打印"排行榜"
		setlinecolor(BLACK); // 设置线条颜色为黑色

		// 绘制排行榜的背景框
		int Lft = 200, Top = bgi + 5 + textheight(s); // 设置排行榜背景框的左边和顶边坐标
		int WidthLen = 400, HeightLen = 400; // 设置排行榜背景框的宽度和高度
		rectangle(Lft, Top + HeightLen, Lft + WidthLen, Top); // 绘制背景框
		int cellWidth = 100, cellHeight = 40; // 设置每个单元格的宽度和高度
		setbkmode(TRANSPARENT); // 设置文字背景模式为透明
		textWidth = 20, textHeight = 30; // 重置文本格式
		settextstyle(textHeight, textWidth, "Tomas"); // 设置新的文本样式

		// 打印表头
		for (int j = 0; j < 4; j++) {
			int px = Lft + j * cellWidth, py = Top; // 计算每个表头文字的坐标
			switch (j) { // 根据列号输出相应的表头文字
			case 0:
				outtextxy(px, py, "Rank"); // 第一列表头为"Rank"
				break;
			case 1:
				outtextxy(px, py, "Name"); // 第二列表头为"Name"
				break;
			case 2:
				outtextxy(px, py, "Stars"); // 第三列表头为"Stars"
				break;
			case 3:
				outtextxy(px, py, "Time"); // 第四列表头为"Time"
				break;
			}
		}

		// 打印具体内容
		for (int i = 1; i <= 5; i++) {
			char rak[10],sta[10],tim[10]; // 使用多字节字符数组
			sprintf_s(rak, "%d", i); // 将排名数字转换为字符串
			sprintf_s(sta, "%d", users[i - 1].stars); // 将星星数转换为字符串
			sprintf_s(tim, "%d", users[i-1].time); // 时间暂时设置为100，这里可以根据实际数据修改

			for (int j = 0; j < 4; j++) { // 打印每个用户的详细信息
				int px = Lft + j * cellWidth, py = Top + i * cellHeight; // 计算每个单元格的左上角坐标
				rectangle(px, py + cellHeight, px + cellWidth, py); // 绘制单元格边框

				switch (j) { // 根据列号输出相应的用户信息
				case 0:
					outtextxy(px, py, rak); // 第一列显示排名
					break;
				case 1:
					outtextxy(px, py, users[i - 1].name.c_str()); // 第二列显示用户名
					break;
				case 2:
					outtextxy(px, py, sta); // 第三列显示星星数
					break;
				case 3:
					outtextxy(px, py, tim); // 第四列显示时间（假设时间为100）
					break;
				}
			}
		}

		// "返回主菜单"按钮的实现
		if (button(650, 50, 100, 50, "返回主菜单")) { // 如果点击了"返回主菜单"按钮
			cleardevice(); // 清屏，清除当前绘制内容
			flag = MENU; // 设置标志位为MENU，表示返回主菜单
			return; // 返回主菜单
		}

		FlushBatchDraw(); // 刷新批量绘图内容
		EndBatchDraw(); // 结束批量绘图
		msg.message = { 0 }; // 使得每次点击按钮只会响应一次
	}
}

// 从文件中读取用户数据的函数
void gameManager::readFile(const char* fileName)
{
	ifstream inFile; // 定义输入文件流对象
	inFile.open(fileName); // 打开文件
	if (!inFile.is_open()) throw out_of_range("File is not open"); // 检查文件是否成功打开

	//users.clear(); // 清空用户列表，避免重复添加数据
	//user nw; // 定义一个用户对象
	//while (!inFile.eof()) // 读取文件直到文件结束
	//{
	//	user nw; // 定义一个用户对象
	//	inFile >> nw.name >>nw.password>>nw.email>> nw.stars>>nw.time; // 从文件中读取用户名和星星数
	//	if (inFile) { // 检查是否成功读取数据
	//		users.push_back(nw); // 将读取的用户信息添加到用户列表中
	//	}
	//}
	user nw; // 定义一个用户对象
	while (inFile >> nw.name >> nw.password >> nw.email >> nw.stars >> nw.time) // 使用正确的读取方式
	{
		users.push_back(nw); // 将读取的用户信息添加到用户列表中
	}
	inFile.close(); // 关闭文件
}


// 将用户数据写入文件的函数
void gameManager::writeFile(const char* fileName)
{
	ofstream outFile; // 定义输出文件流对象
	outFile.open(fileName); // 打开文件
	if (!outFile.is_open()) throw out_of_range("File is not open"); // 检查文件是否成功打开
	for (int i = 0; i < users.size(); i++) // 遍历所有用户
	{
		outFile << users[i].name << ' ' << users[i].password << ' ' <<users[i].email << ' ' <<users[i].stars << ' ' <<users[i].time << ' ' << endl; // 将用户数据写入文件
	}
	outFile.close(); // 关闭文件
}

// 用户比较函数，用于排序
bool gameManager::rank_cmp(user a, user b)
{
	return (a.stars == b.stars)?(a.time<b.time):(a.stars>b.stars); // 比较两个用户的星星数，用于从大到小排序
}

// 更新排行榜的函数
void gameManager::updateRank()
{
	auto cmp = bind(&gameManager::rank_cmp, this, placeholders::_1, placeholders::_2);
	sort(users.begin(), users.end(), cmp); // 按星星数对用户列表进行排序
}
//创建新用户
void gameManager::insertNewUser(const user u)
{
	users.push_back(u); // 将新的用户添加到用户列表中
	auto cmp = bind(&gameManager::rank_cmp, this, placeholders::_1, placeholders::_2);
	sort(users.begin(), users.end(), cmp); // 按星星数对用户列表进行排序
}
void gameManager::pause()
{
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE|EX_KEY)) {}
		BeginBatchDraw();//使用双缓冲，防止闪屏
		cleardevice();
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "宋体");
		if (button(300, 100, 150, 50, "回到游戏") || (msg.message==WM_KEYDOWN && msg.vkcode==VK_ESCAPE))
		{
			cleardevice();//清屏
			msg.message = { 0 };
			return;

		}
		if (button(300, 300, 150, 50, "重新开始"))
		{
			flag = PASSCHOOSE;
			return;
		}
		if (button(300, 500, 150, 50, "返回主菜单"))
		{
			flag = MENU;
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}

void gameManager::init() {
	//数据初始化
	current_enemy = 0;
	time = 0;
	stars = 0;
	//根据当前的关卡数，将pass依次赋值给map
	switch (this->pass)
	{
	case 1:
	{
		total_enemy = 6;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				map[i][j] = pass1[i][j];
			}
		}
		break;
	}
	case 2:
	{
		total_enemy = 7;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				map[i][j] = pass2[i][j];
			}
		}
		break;
	}
	case 3:
	{
		total_enemy = 8;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				map[i][j] = pass3[i][j];
			}
		}
		break;
	}
	case 4:
	{
		total_enemy = 9;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				map[i][j] = pass4[i][j];
			}
		}
		break;
	}
	case 5:
	{
		total_enemy = 10;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				map[i][j] = pass5[i][j];
			}
		}
		break;
	}
	default:
		break;
	}

}
void gameManager::gameView()
{
	//初始化游戏地图
	init();
	//道具出现的位置、类型
	int buff_x, buff_y, buff_kind;
	//道具可能生成的坐标
	int buff_x1, buff_x2, buff_x3, buff_y1, buff_y2, buff_y3;
	//我方坦克出生地点
	int pos_x, pos_y;
	//我方基地的坐标
	int base_x, base_y;
	//敌方坦克的出现位置
	int enemy_x, enemy_y;
	//敌方坦克的出生位置
	int enemy_x1, enemy_y1;
	int enemy_x2, enemy_y2;
	int enemy_x3, enemy_y3;
	int enemy_x4, enemy_y4;
	int enemy_x5, enemy_y5;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//寻找道具生成点-3个
			if (map[i][j] == 3)
			{
				buff_x1 = j * 40;
				buff_y1 = i * 40;
				map[i][j] = 0;
			}
			if (map[i][j] == 4)
			{
				buff_x2 = j * 40;
				buff_y2 = i * 40;
				map[i][j] = 0;
			}
			if (map[i][j] == 5)
			{
				buff_x3 = j * 40;
				buff_y3 = i * 40;
				map[i][j] = 0;
			}
			//寻找基地坐标
			if (map[i][j] == 6)
			{
				base_x = j * 40;
				base_y = i * 40;
			}
			//寻找我方坦克出生点
			if (map[i][j] == 7)
			{
				pos_x = j * 40;
				pos_y = i * 40;
			}
			//寻找敌方坦克出生点-5个
			if (map[i][j] == 8)
			{
				enemy_x1 = j * 40;
				enemy_y1 = i * 40;
				map[i][j] = 0;
			}
			if (map[i][j] == 9)
			{
				enemy_x2 = j * 40;
				enemy_y2 = i * 40;
				map[i][j] = 0;
			}
			if (map[i][j] == 10)
			{
				enemy_x3 = j * 40;
				enemy_y3 = i * 40;
				map[i][j] = 0;
			}
			if (map[i][j] == 11)
			{
				enemy_x4 = j * 40;
				enemy_y4 = i * 40;
				map[i][j] = 0;
			}
			if (map[i][j] == 12)
			{
				enemy_x5 = j * 40;
				enemy_y5 = i * 40;
				map[i][j] = 0;
			}
		}
	}
	//定义我方坦克
	my_tank player(pos_x, pos_y);
	//定义我方子弹组
	vector<bullet> my_bullets;
	//定义敌方坦克组
	vector<enemy_tank> enemys;
	//定义敌方子弹组
	vector<bullet> enemy_bullets;

	int times = 0;//记录循环次数
	int shootTime = clock() - 500;//上次射击时间，控制距离上次射击0.5秒才能继续射击
	while (true)
	{
		draw(enemys, player, enemy_bullets, my_bullets);//绘制当前帧

		int starttime = clock();//本次循环开始时间

		//更新场上当前敌方坦克数量
		int enemyNum = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
				if (map[i][j] == 101)
					enemyNum += 1;
		}
		current_enemy = enemyNum;
		if (pass == 1 || pass == 2 || pass == 3)//前三关
		{
			//随机在三个敌方坦克出生点中的一个生成敌方坦克，随机在三个道具生成点的一个生成道具
			if (times % 3 == 0)
			{
				enemy_x = enemy_x1;
				enemy_y = enemy_y1;
				buff_x = buff_x1;
				buff_y = buff_y1;
				buff_kind = 3;
			}
			else if (times % 3 == 1)
			{
				enemy_x = enemy_x2;
				enemy_y = enemy_y2;
				buff_x = buff_x2;
				buff_y = buff_y2;
				buff_kind = 4;
			}
			else
			{
				enemy_x = enemy_x3;
				enemy_y = enemy_y3;
				buff_x = buff_x3;
				buff_y = buff_y3;
				buff_kind = 5;
			}
		}
		else if (pass == 4 || pass == 5)//4、5关
		{
			//随机五个个敌方坦克出生点中的一个生成敌方坦克，随机在三个道具生成点的一个生成道具
			if (times % 5 == 0)
			{
				enemy_x = enemy_x1;
				enemy_y = enemy_y1;
				buff_x = buff_x1;
				buff_y = buff_y1;
				buff_kind = 3;
			}
			else if (times % 5 == 1)
			{
				enemy_x = enemy_x2;
				enemy_y = enemy_y2;
				buff_x = buff_x2;
				buff_y = buff_y2;
				buff_kind = 4;
			}
			else if (times % 5 == 2)
			{
				enemy_x = enemy_x3;
				enemy_y = enemy_y3;
				buff_x = buff_x3;
				buff_y = buff_y3;
				buff_kind = 5;
			}
			else if (times % 5 == 3)
			{
				enemy_x = enemy_x4;
				enemy_y = enemy_y4;
				buff_x = buff_x1;
				buff_y = buff_y1;
				buff_kind = 5;
			}
			else if (times % 5 == 4)
			{
				enemy_x = enemy_x5;
				enemy_y = enemy_y5;
				buff_x = buff_x2;
				buff_y = buff_y2;
				buff_kind = 3;
			}
		}
		//生成敌方坦克
		enemy_generate(enemys, player, enemy_x, enemy_y);
		//生成道具
		if (time % 100 == 0)
			buff_generate(buff_x, buff_y, buff_kind);
		//控制存活的敌方坦克转向（每循环20次-2s转向一次，调用敌方坦克的turn()）
		if (times % 20 == 0)
		{
			for (int i = 0; i < enemys.size(); i++)
			{
				if (i <= enemys.size() / 2)//一半敌机朝着玩家转弯
				{
					enemys[i].turn(player.x, player.y);
				}

				else//另一半敌机朝着基地转弯
				{
					enemys[i].turn(base_x, base_y);
				}
			}
		}
		//控制存活的敌方坦克移动（每循环5次-0.5s移动一次，调用敌方坦克的move()）
		if (times % 5 == 0)
		{
			for (auto& i : enemys)
			{
				i.move();
			}
		}

		//控制存活的敌方坦克射击（每循环50次-2.5s射击一次，调用敌方坦克的shoot()）
		if (times % 50 == 0)
		{
			for (auto& i : enemys)
			{
				i.shoot(enemy_bullets);
			}
		}
		//玩家移动、射击（调用我方坦克的move()）
		player.move();

		if (clock() - shootTime >= 500)//距离上次发射子弹每过0.5秒才能继续发射
		{
			//本次成功发射子弹
			if (player.shoot(my_bullets) == 0)
			{
				shootTime = clock();//更新发射子弹的时间
			}
		}
		//子弹移动（每次循环调用子弹的move()）
		//我方子弹移动
		for (auto& my_bullet : my_bullets)
		{
			//移除消失的子弹
			if (my_bullet.getIsLive() == 0)
			{
				my_bullets.erase(remove(my_bullets.begin(), my_bullets.end(), my_bullet), my_bullets.end());
			}
			//存活的子弹继续移动
			if (my_bullet.getIsLive() == 1)
			{
				//每个子弹进行各自的移动，并判断碰撞情况
				my_bullet.move(enemys, player, pos_x, pos_y);
			}
		}
		//敌方子弹移动
		for (auto& enemy_bullet : enemy_bullets)
		{
			//移除消失的子弹
			if (enemy_bullet.getIsLive() == 0)
			{
				enemy_bullets.erase(remove(enemy_bullets.begin(), enemy_bullets.end(), enemy_bullet), enemy_bullets.end());
			}
			//存活的子弹继续移动
			if (enemy_bullet.getIsLive() == 1)//如果子弹存活
			{
				//每个子弹进行各自的移动，并判断碰撞情况
				enemy_bullet.move(enemys, player, pos_x, pos_y);
			}
		}
		/*
		判断胜负（调用win_or_lose）
		如果胜利调用胜利界面
		如果失败调用失败界面
		*/
		int win = win_or_lose(player);
		if (win == 0)//游戏胜利
		{
			//通过不同的关卡给不同的星星数
			switch (pass)
			{
			case 1:
				stars = 1;
				break;
			case 2:
				stars = 2;
				break;
			case 3:
				stars = 3;
				break;
			case 4:
				stars = 4;
				break;
			case 5:
				stars = 5;
				break;
			default:
				break;
			}
			//更新users数据，(stars,time)并写入保存文件中
			for (auto& user : users)
			{
				if (user.name == userName)
				{
					user.stars += stars;
					user.time = user.time+this->time/1000;
					break;
				}
			}
			//调用update更新users容器
			updateRank();
			//调用writeFile更新文件内容
			writeFile("userInfo.txt");
			flag = WINSHOW;
			break;
		}
		else if (win == 1)
		{
			flag = LOSESHOW;
			break;
		}
		times++;
		time = time + (clock() - starttime) + 100;//计时器累加:(原来的时间+循环一次的时间+sleep的时间)/1000=秒
		//检测是否按暂停键P
		if (peekmessage(&msg,EX_KEY))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE)
				{
					msg.message = { 0 };
					pause();
				}
			}
			
			//当从暂停界面出来后，如果页面状态改变，则退出游戏界面
			if (flag != GAMEVIEW)
				break;
		}


	}
}

void gameManager::draw(vector<enemy_tank>& enemies, my_tank& player, vector<bullet>& enemy_bullets, vector<bullet>& my_bullets)
{
	BeginBatchDraw();//双缓冲绘图，防止闪屏
	cleardevice();
	//根据map[i][j]的值，在不同的方块绘制不同的图像
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 0)//空地
			{
				setfillcolor(BLACK);
				solidrectangle(j * 40, i * 40, (j + 1) * 40, (i + 1) * 40);
			}
			else if (map[i][j] == 1)//木墙
				putimage(j * 40, i * 40, &woodWall_img);
			else if (map[i][j] == 2)//石墙
				putimage(j * 40, i * 40, &stoneWall_img);
			else if (map[i][j] == 3)//导弹
				putimage(j * 40, i * 40, &buff_img[0]);
			else if (map[i][j] == 4)//激光
				putimage(j * 40, i * 40, &buff_img[1]);
			else if (map[i][j] == 5)//盾牌
				putimage(j * 40, i * 40, &buff_img[2]);
			else if (map[i][j] == 6)//基地
				putimage(j * 40, i * 40, &base_img);
		}
	}
	//绘制敌方坦克-不依赖map
	for (auto& enemy : enemies)
	{
		if(pass==1||pass==2||pass==3)
		putimage(enemy.x, enemy.y, &enemy_tank_img[0][enemy.direction]);
		else
		putimage(enemy.x, enemy.y, &enemy_tank_img[1][enemy.direction]);
	}
	//绘制我方坦克-不依赖map
	putimage(player.x, player.y, &my_tank_img[selectedSkin][player.direction]);
	//绘制敌方子弹-不依赖map
	for (auto& enemy_bullet : enemy_bullets)
	{
		//注意敌方子弹无法杀死敌方坦克
		//当敌方子弹穿过敌方坦克时敌方子弹被隐藏
		if (map[enemy_bullet.y / 40][enemy_bullet.x / 40] == 101)
			continue;
		else//其余情况子弹存活时正常绘制
			putimage(enemy_bullet.x, enemy_bullet.y, &bullet_img[enemy_bullet.getKind()]);
	}
	//绘制我方子弹-不依赖map
	for (auto& my_bullet : my_bullets)
	{
		putimage(my_bullet.x, my_bullet.y, &bullet_img[my_bullet.getKind()]);
	}
	//FlushBatchDraw();
	Sleep(100);
	EndBatchDraw();
}
void gameManager::winShow()
{
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE)) {}
		BeginBatchDraw();//使用双缓冲，防止闪屏
		cleardevice();
		putimage(0, 0, &back_img[4]);
		int time_s = time / 1000 % 60;//秒
		int time_min = time / 1000 / 60;//分
		string time_str = to_string(time_min) + "min" + ":" + to_string(time_s) + "s";
		string stars_str = to_string(stars);
		settextcolor(RGB(164, 141, 45));
		settextstyle(50, 0, "宋体");
		outtextxy(250, 50, "恭喜闯关成功");
		outtextxy(100, 150, "总共用时：");
		outtextxy(350, 150, time_str.c_str());
		outtextxy(100, 250, "奖励星星：");
		outtextxy(350, 250, stars_str.c_str());
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "宋体");
		if (button(100, 400, 150, 50, "下一关"))
		{
			pass = (pass + 1) % 5;
			cleardevice();//清屏
			flag = GAMEVIEW;
			return;

		}
		if (button(400, 400, 150, 50, "再来一局"))
		{
			cleardevice();//清屏，一般每次绘制完一帧的图片都要进行清屏
			flag = GAMEVIEW;
			return;
		}
		if (button(500, 500, 150, 50, "返回主菜单"))
		{
			cleardevice();//清屏，一般每次绘制完一帧的图片都要进行清屏
			flag = MENU;
			return;
		}
		//FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}


}
void gameManager::loseShow()
{
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE)) {}//接收鼠标消息
		BeginBatchDraw();//双缓冲绘图
		cleardevice();
		putimage(0, 0, &back_img[4]);
		//设置字体
		settextcolor(RGB(164, 141, 45));
		settextstyle(50, 0, "宋体");
		outtextxy(150, 50, "闯关失败，请再接再厉");
		settextcolor(BLACK);
		settextstyle(30, 0, "宋体");
		//绘制按钮并判断是否按下
		if (button(300, 200, 150, 50, "再来一局"))
		{
			cleardevice();//清屏
			flag = GAMEVIEW;
			break;
		}
		if (button(300, 400, 150, 50, "返回主菜单"))
		{
			cleardevice();//清屏
			flag = MENU;
			break;
		}
		//FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
int gameManager::win_or_lose(my_tank& player)
{
	int baseLive = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 6)
				baseLive = 1;
		}
	}
	if (player.getHP() <= 0 || baseLive == 0)
		return 1;
	else if (player.getKill() == total_enemy && player.getHP() > 0)
		return 0;
	else
		return 2;
}



bool gameManager::inArea(int mx, int my, int x, int y, int w, int h)
{
	if (mx > x && mx<x + w && my>y && my < y + h)
		return true;
	else return false;
}
bool gameManager::button(int x, int y, int w, int h, const char* str)
{
	// 判断按钮的外观颜色
	if (inArea(msg.x, msg.y, x, y, w, h))
		setfillcolor(RGB(93, 107, 153)); // 鼠标在按钮上
	else
		setfillcolor(RGB(231, 232, 233)); // 鼠标不在按钮上

	fillroundrect(x, y, x + w, y + h, 5, 5); // 绘制圆角矩形按钮

	settextcolor(BLACK); // 文本颜色
	settextstyle(20, 0, "宋体");
	setbkmode(TRANSPARENT); // 透明背景

	// 计算文本位置，使其在按钮中心
	int vSpace = (w - textwidth(str)) / 2;
	int hSpace = (h - textheight(str)) / 2;
	outtextxy(x + vSpace, y + hSpace, str);

	// 判断是否点击
	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		msg.message = 0;
		return true; // 按钮被点击
	}
	return false; // 按钮未被点击
}

void gameManager::drawText(int x, int y, int size, const char* text) {
	// 设置文字大小
	settextstyle(size, 0, "微软雅黑");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, text);
}


void gameManager::drawSkinPage(int& selectedSkin) {
	while (true) {
		peekmessage(&msg, EX_MOUSE);
		BeginBatchDraw();
		cleardevice();  // 清除屏幕，准备重新绘制
		//setbkcolor(WHITE);
		putimage(0, 0, &back_img[6]);
		settextcolor(BLACK);
		BeginBatchDraw();

		// 绘制皮肤和 BUFF 区域
		rectangle(270, 150, 470, 300);  // 坦克皮肤区域框
		outtextxy(320, 225, "坦克皮肤");

		//rectangle(520, 200, 600, 240);  // BUFF 区域框
		//outtextxy(540, 210, "BUFF");
		// 绘制选中的皮肤图片
		switch (selectedSkin) {
		case 0:
			putimage(270, 150, &skin[0]);  // 显示皮肤1图片
			break;
		case 1:
			putimage(270, 150, &skin[1]);  // 显示皮肤2图片
			break;
		case 2:
			putimage(270, 150, &skin[2]);  // 显示皮肤3图片
			break;
		default:
			break;
		}

		// 使用 button 函数绘制按钮并检测点击
		if (button(520, 200, 100, 50, "BUFF")) {
			flag = BUFF;
			return;
		}
		if (button(150, 400, 100, 50, "皮肤1")) {
			selectedSkin = 0;  // 选择皮肤1
		}

		if (button(325, 400, 100, 50, "皮肤2")) {
			selectedSkin = 1;  // 选择皮肤2
		}

		if (button(500, 400, 100, 50, "皮肤3")) {
			selectedSkin = 2;  // 选择皮肤3
		}

		if (button(650, 500, 50, 50, "返回")) {
			// 返回按钮被点击，执行返回操作
			flag = MENU;
			return;
		}

		// 刷新屏幕显示
		//FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}

void gameManager::menu()
{
	while (true)
	{
		peekmessage(&msg, EX_MOUSE);       //接收鼠标消息
		BeginBatchDraw();
		cleardevice();

		putimage(0, 0, &back_img[1]);

		if (button(350, 25, 100, 70, "进入游戏"))
			flag = PASSCHOOSE;
		if (button(350, 105, 100, 70, "新手指南"))
			flag = GUIDE;
		if (button(350, 185, 100, 70, "星星排行榜"))
			flag = RANKLIST;
		if (button(350, 265, 100, 70, "装扮库"))
			flag = CHANGESTYLE;
		if (button(350, 345, 100, 70, "设置"))
			flag = SET;
		if (button(350, 425, 100, 70, "团队介绍"))
			flag = MEMBERINFO;
		if (button(350, 505, 100, 70, "退出游戏"))
			exit(0);

		FlushBatchDraw();
		EndBatchDraw();
		msg.message = {0};
		if (flag != MENU)
			break;
	}
}

void gameManager::passChoose()
{

	while (true) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &back_img[5]);
		putimage(70, 200, &pass_img[0]);
		putimage(210, 200, &pass_img[1]);
		putimage(350, 200, &pass_img[2]);
		putimage(490, 200, &pass_img[3]);
		putimage(630, 200, &pass_img[4]);
		if (peekmessage(&msg, EX_MOUSE)) {}
		BeginBatchDraw();
		if (button(27, 16, 50, 33, "设置"))
		{
			flag = SET;
			return;
		}
		if (button(80, 400, 80, 30, "1"))
		{
			pass = 1;
			flag = GAMEVIEW;
			return;
		}
		if (button(220, 400, 80, 30, "2"))
		{
			pass = 2;
			flag = GAMEVIEW;
			return;
		}
		if (button(360, 400, 80, 30, "3"))
		{
			pass = 3;
			flag = GAMEVIEW;
			return;
		}
		if (button(500, 400, 80, 30, "4"))
		{
			pass = 4;
			flag = GAMEVIEW;
			return;
		}
		if (button(640, 400, 80, 30, "5"))
		{
			pass = 5;
			flag = GAMEVIEW;
			return;
		}
		if (button(650, 550, 150, 50, "返回主菜单")) // 如果点击了"返回主菜单"按钮
		{
			flag = MENU; // 设置标志位为MENU，表示返回主菜单
			return; // 返回主菜单
		}

		//FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };//使得每次点击按钮只会响应一次
	}
}
void gameManager::buff()
{
	while (true) {
		peekmessage(&msg, EX_MOUSE);

		BeginBatchDraw();
		setbkcolor(WHITE);
		settextcolor(BLACK);
		cleardevice();  // 清除屏幕，准备重新绘制


		// 绘制皮肤和 BUFF 区域
		// 绘制选中的皮肤图片
		switch (selectedBuff) {
		case 0:
			putimage(270, 150, &show_buff_img[0]);  // 显示Buff1图片
			break;
		case 1:
			putimage(270, 150, &show_buff_img[1]);  // 显示Buff2图片
			break;
		case 2:
			putimage(270, 150, &show_buff_img[2]);  // 显示Buff3图片
			break;
		default:
			break;
		}

		// 使用 button 函数绘制按钮并检测点击
		if (button(150, 400, 100, 50, "Buff1")) {
			selectedBuff = 0;  // 选择Buff1
		}
		if (button(325, 400, 100, 50, "Buff2")) {
			selectedBuff = 1;  // 选择Buff2
		}
		if (button(500, 400, 100, 50, "Buff3")) {
			selectedBuff = 2;  // 选择Buff3
		}
		if (button(650, 500, 150, 50, "返回主菜单")) {
			// 返回按钮被点击，执行返回操作
			cout << "返回按钮被点击" << endl;
			flag = MENU; //是返回到选择皮肤页面的话改一下
			return;
		}

		// 刷新屏幕显示
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
void gameManager::memberInfor()
{
	while (true) {
		BeginBatchDraw(); // 开始批量绘图，提高绘图效率
		//setbkcolor(WHITE); // 设置背景颜色为白色
		cleardevice(); // 清除设备内容
		putimage(0, 0, &back_img[7]);

		//团队介绍：
		int titleWidth = 20, titleHeight = 33;
		settextstyle(titleHeight, titleWidth, "宋体");
		settextcolor(BLACK);
		int bgi_x = 50, bgi_y = 40;
		outtextxy(bgi_x, bgi_y, "团队介绍：");
		int cx = bgi_x, cy = bgi_y + 5 + titleHeight; //内容开始的坐标
		int contentWidth = 13, contentHeight = 21;
		settextstyle(contentHeight, contentWidth, "宋体");
		settextcolor(GREEN);
		string contents[9] = {
			"组长_清淤：负责排行榜界面，团队介绍界面，新手指南界面",
			"副组长_十里：十里：游戏子弹，设置界面，团队介绍",
			"技术官1_大帅：框架设计，流程图设计，游戏内的运行逻辑",
			"技术官2_皮卡丘：游戏外逻辑代码整合修改，解决难点和bug",
			"技术官3_蓦然回首：游戏关卡地图以及所使用道具和图片的绘制",
			"产品经理1_至善：至善：需求、原型图，登录注册、忘记密码界面",
			"产品经理2_一枝鱼：需求文档，敌方坦克",
			"监督官_GO：按钮的绘制 主菜单和新手指南界面",
			"信息官_XY："
		};
		for (int i = 0; i < 9; i++)
		{
			outtextxy(cx, cy, contents[i].c_str());
			cy += contentHeight + 10;
		}

		// "返回主菜单"按钮的实现
		if (peekmessage(&msg, EX_MOUSE)) {} // 检测鼠标消息
		if (button(650, 550, 100, 50, "返回主菜单")) // 如果点击了"返回主菜单"按钮
		{
			//cleardevice(); // 清屏，清除当前绘制内容
			flag = MENU; // 设置标志位为MENU，表示返回主菜单
			return; // 返回主菜单
		}

		FlushBatchDraw(); // 刷新批量绘图内容
		EndBatchDraw(); // 结束批量绘图
		msg.message = { 0 }; // 重置消息对象
	}
}
void gameManager::controller() {
	while (1) {
		switch (flag) {
		case PASSCHOOSE:
			passChoose();
			break;
		case SIGNIN:
			signIn();
			break;
		case LOGIN:
			logIn();
			break;
		case FINDPASSWORD:
			forgetPassword();
			break;
		case FINDPASSWORD2:
			forgetPassword2();
			break;
		case MENU:
			cleardevice();
			menu();
			break;
		case CHANGESTYLE:
			drawSkinPage(selectedSkin);
			break;
		case RANKLIST:
			printRank();
			break;
		case MEMBERINFO:
			memberInfor();
			break;
		case SET:
			set();
			break;
		case GAMEVIEW:
			cleardevice();
			gameView();
			break;
		case LOSESHOW:
			cleardevice();
			loseShow();
			break;
		case WINSHOW:
			cleardevice();
			winShow();
			break;
		case GUIDE:
			cleardevice();
			guide();
			break;
		case BUFF:
			buff();
			break;
		case OVER:
			exit(0);
		}

		// 检查用户按下 ESC 键退出程序
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 27) break; // 按下 ESC 键退出程序
		}
	}
}
void gameManager::guide()
{
	while (true) {
		BeginBatchDraw(); // 开始批量绘图，提高绘图效率
		//setbkcolor(WHITE); // 设置背景颜色为白色
		cleardevice(); // 清除设备内容
		putimage(0, 0, &back_img[3]);
		//按键介绍
		int titleWidth = 20, titleHeight = 33; //my_titile文字的宽和高
		settextstyle(titleHeight, titleWidth, "黑体"); //设置标题文字样式
		settextcolor(BLACK); //设置文字颜色
		string my_title = "按键介绍:"; //标题
		int title_x = 50, title_y = 50; //my_title开始的x,y坐标
		outtextxy(title_x, title_y, my_title.c_str());
		//按键介绍内容
		string introduce1 = "WASD分别表示上左下右，J表示攻击，Esc键表示暂停/回到游戏";
		int content_x = title_x, content_y = title_y + titleHeight;
		int contentWidth = 13, contentHeight = 21; //内容文字的宽和高
		settextstyle(contentHeight, contentWidth, "黑体"); //设置标题文字样式
		settextcolor(GREEN);
		outtextxy(content_x, content_y, introduce1.c_str());

		//Buff介绍
		my_title = "Buff介绍:";
		title_y += titleWidth + textheight(introduce1.c_str()) + 70;
		settextstyle(titleHeight, titleWidth, "黑体"); //设置标题文字样式
		settextcolor(BLACK); //设置文字颜色
		outtextxy(title_x, title_y, my_title.c_str());
		string introduce2 = "玩家触碰不同的补给可以获得不同的Buff效果：";
		string introduce3 = "炸弹：子弹变大，伤害变高";
		string introduce4 = "护罩：10秒内不死";
		content_x = title_x, content_y = title_y + titleHeight;
		settextstyle(contentHeight, contentWidth, "黑体"); //设置标题文字样式
		settextcolor(GREEN); //设置文字颜色
		outtextxy(content_x, content_y, introduce2.c_str()); //打印第一行
		content_y += contentHeight;
		outtextxy(content_x, content_y, introduce3.c_str());//打印第二行
		content_y += contentHeight;
		outtextxy(content_x, content_y, introduce4.c_str()); //打印第三行
		content_y += contentHeight + 70;
		outtextxy(content_x, content_y, "未完待续。。。我们还会回来的"); //打印第三行

		// "返回主菜单"按钮的实现
		if (peekmessage(&msg, EX_MOUSE)) {} // 检测鼠标消息
		if (button(650, 550, 100, 50, "返回主菜单")) // 如果点击了"返回主菜单"按钮
		{
			flag = MENU; // 设置标志位为MENU，表示返回主菜单
			return; // 返回主菜单
		}

		FlushBatchDraw(); // 刷新批量绘图内容
		EndBatchDraw(); // 结束批量绘图
		msg.message = { 0 }; // 重置消息对象
	}
}
void gameManager::loadSources()
{
	loadimage(&skin[0], "图片资源/tankStyle1.jpg", 200, 200); // 加载皮肤1图片
	loadimage(&skin[1], "图片资源/tankStyle2.jpg"); // 加载皮肤2图片
	loadimage(&skin[2], "图片资源/tankStyle3.jpg"); // 加载皮肤3图片

	loadimage(&my_tank_img[0][0], "图片资源/tankStyle1_left.jpg", 40, 40);
	loadimage(&my_tank_img[0][1], "图片资源/tankStyle1_right.jpg", 40, 40);
	loadimage(&my_tank_img[0][2], "图片资源/tankStyle1.jpg", 40, 40);
	loadimage(&my_tank_img[0][3], "图片资源/tankStyle1_down.jpg", 40, 40);

	loadimage(&my_tank_img[1][0], "图片资源/tankStyle2_left.jpg", 40, 40);
	loadimage(&my_tank_img[1][1], "图片资源/tankStyle2_right.jpg", 40, 40);
	loadimage(&my_tank_img[1][2], "图片资源/tankStyle2.jpg", 40, 40);
	loadimage(&my_tank_img[1][3], "图片资源/tankStyle2_down.jpg", 40, 40);

	loadimage(&my_tank_img[2][0], "图片资源/tankStyle3_left.jpg", 40, 40);
	loadimage(&my_tank_img[2][1], "图片资源/tankStyle3_right.jpg", 40, 40);
	loadimage(&my_tank_img[2][2], "图片资源/tankStyle3.jpg", 40, 40);
	loadimage(&my_tank_img[2][3], "图片资源/tankStyle3_down.jpg", 40, 40);

	loadimage(&enemy_tank_img[0][0], "图片资源/敌方坦克左.jpg", 40, 40);
	loadimage(&enemy_tank_img[0][1], "图片资源/敌方坦克右.jpg", 40, 40);
	loadimage(&enemy_tank_img[0][2], "图片资源/敌方坦克上.jpg", 40, 40);
	loadimage(&enemy_tank_img[0][3], "图片资源/敌方坦克下.jpg", 40, 40);

	loadimage(&enemy_tank_img[1][0], "图片资源/我方坦克左.jpg", 40, 40);
	loadimage(&enemy_tank_img[1][1], "图片资源/我方坦克右.jpg", 40, 40);
	loadimage(&enemy_tank_img[1][2], "图片资源/我方坦克上.jpg", 40, 40);
	loadimage(&enemy_tank_img[1][3], "图片资源/我方坦克下.jpg", 40, 40);

	loadimage(&buff_img[0], "图片资源/导弹.jpg", 40, 40);
	loadimage(&buff_img[1], "图片资源/激光.jpg", 40, 40);
	loadimage(&buff_img[2], "图片资源/盾牌.jpg", 40, 40);
	loadimage(&bullet_img[0], "图片资源/子弹.jpg", 4, 4);
	loadimage(&bullet_img[1], "图片资源/子弹.jpg", 20, 20);
	loadimage(&woodWall_img, "图片资源/砖墙.jpg", 40, 40);
	loadimage(&stoneWall_img, "图片资源/石墙.jpg", 40, 40);
	loadimage(&base_img, "图片资源/基地.jpg", 40, 40);
	loadimage(&bg, "图片资源/坦克大战2.jpg", 800, 600);
	loadimage(&img_set, "图片资源/设置.jpg", 800, 600);

	loadimage(&show_buff_img[0], "图片资源/导弹.jpg", 200, 200);
	loadimage(&show_buff_img[1], "图片资源/激光.jpg", 200, 200);
	loadimage(&show_buff_img[2], "图片资源/盾牌.jpg", 200, 200);

	loadimage(&pass_img[0], "图片资源/关卡-1.jpg", 100, 100);
	loadimage(&pass_img[1], "图片资源/关卡-2.jpg", 100, 100);
	loadimage(&pass_img[2], "图片资源/关卡-3.jpg", 100, 100);
	loadimage(&pass_img[3], "图片资源/关卡-4.jpg", 100, 100);
	loadimage(&pass_img[4], "图片资源/关卡-5.jpg", 100, 100);

	loadimage(&back_img[0], "图片资源/登录注册背景图.jpg", 800, 600);
	loadimage(&back_img[1], "图片资源/主菜单背景图2.jpg", 800, 600);
	loadimage(&back_img[2], "图片资源/排行榜背景图.jpg", 800, 600);
	loadimage(&back_img[3], "图片资源/新手指南背景图.jpg", 800, 600);
	loadimage(&back_img[4], "图片资源/胜利失败背景图.jpg", 800, 600);
	loadimage(&back_img[5], "图片资源/选关界面背景图.jpg", 800, 600);
	loadimage(&back_img[6], "图片资源/装扮库背景图.jpg", 800, 600);
	loadimage(&back_img[7], "图片资源/团队介绍背景图.jpg", 800, 600);

	mciSendString("open AllAboutThatGuitar.mp3", 0, 0, 0);
	//mciSendString("play AllAboutThatGuitar.mp3", 0, 0, 0);
	readFile("userInfo.txt");

}

void gameManager::set() {
	int sliderX = 200;//滑块（初始）位置
	static double volume = 50;//音量百分百比
	bool lbutton_down = false;//按钮是否按下

	ExMessage msg = { 0 };
	while (1) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img_set);
		setfillcolor(WHITE);
		rectangle(175, 105, 525, 125);
		setfillcolor(BLUE);
		fillrectangle(175, 105, sliderX, 125);
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN) {
				int x1 = msg.x, y1 = msg.y;
				if (x1 >= 0 && x1 <= 90 && y1 >= 0 && y1 <= 40) {
					flag = MENU;
					cout << "主菜单" << endl;
					break;
				}
				else if (x1 >= 700 && x1 <= 800 && y1 >= 0 && y1 <= 60) {

					exit(0);
				}
				else if (x1 >= 630 && x1 <= 770 && y1 >= 400 && y1 <= 460) {
					flag = MENU;
					break;
				}
			}
			if (msg.message == WM_LBUTTONDOWN)
				lbutton_down = true;
			if (msg.message == WM_LBUTTONUP)
				lbutton_down = false;
			if (lbutton_down)
			{
				int x = msg.x, y = msg.y;
				if (x >= 175 && x <= 525 && y >= 105 && y <= 125)
				{
					int x = msg.x;
					sliderX = x;
					volume = (sliderX - 175) / static_cast<double>(350);
					setVolume(volume, "AllAboutThatGuitar.mp3");
				}
			}
		}
		FlushBatchDraw();
		EndBatchDraw();
	}
}

//调节音量的函数
void gameManager::setVolume(double volume_persent, const string& musicPath) {
	// 限制音量范围在 0 到 100 之间
	if (volume_persent < 0) volume_persent = 0;
	if (volume_persent > 1) volume_persent = 1;
	// 打开音频设备
	mciSendString("open new type waveaudio alias myaudio", NULL, 0, NULL);
	// 设置音量
	string command = "setaudio " + musicPath + " volume to " + to_string(static_cast<int>(volume_persent * 1000));
	mciSendString(command.data(), NULL, 0, NULL);
	// 关闭音频设备
	string s = "play " + musicPath + " repeat";
	mciSendString(s.data(), NULL, 0, NULL);
	//mciSendString("stop myaudio", NULL, 0, NULL);
}

// 打印登录界面的函数
void gameManager::logIn()
{
	char username[30] = ""; // 假设用户名最多30字符
	char password[30] = ""; // 假设密码最多30字符
	int userIndex = 0;
	int passIndex = 0;
	bool isPasswordInput = false; // 用于区分当前是输入用户名还是密码
	bool isTypingUsername = true; // 当前是否在输入用户名
	bool haveUser = true;//判断是否存在该用户
	bool passwordRight = true;//判断用户输入的密码是否正确
	// 定义输入框区域
	int usernameInputX = 260, usernameInputY = 200;
	int passwordInputX = 260, passwordInputY = 250;
	int inputWidth = 300, inputHeight = 30;

	while (true)
	{
		if (peekmessage(&msg))
		{
			// 处理鼠标点击事件
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= usernameInputX && msg.x <= usernameInputX + inputWidth &&
					msg.y >= usernameInputY && msg.y <= usernameInputY + inputHeight)
				{
					isTypingUsername = true;
				}
				else if (msg.x >= passwordInputX && msg.x <= passwordInputX + inputWidth &&
					msg.y >= passwordInputY && msg.y <= passwordInputY + inputHeight)
				{
					isTypingUsername = false;
				}
			}

			// 处理键盘事件
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isTypingUsername) // 用户名输入
				{
					if (ch == '\b' && userIndex > 0) // 退格键
					{
						username[--userIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && userIndex < 29) // 可显示字符
					{
						username[userIndex++] = ch;
						username[userIndex] = '\0';
					}
				}
				else // 密码输入
				{
					if (ch == '\b' && passIndex > 0) // 退格键
					{
						password[--passIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && passIndex < 29) // 可显示字符
					{
						password[passIndex++] = ch;
						password[passIndex] = '\0';
					}
				}
			}
		}


		// 开始绘制
		BeginBatchDraw();
		cleardevice(); // 清屏
		//绘制背景图片
		putimage(0, 0, &back_img[0]);
		//设置字体
		settextcolor(RGB(164, 141, 45));
		//setbkcolor(WHITE);
		settextstyle(30, 0, "微软雅黑");
		drawText(160, 200, 30, "账号：");
		drawText(160, 250, 30, "密码：");

		// 绘制输入框
		setfillcolor(RGB(231, 232, 233));
		fillrectangle(usernameInputX, usernameInputY, usernameInputX + inputWidth, usernameInputY + inputHeight);
		fillrectangle(passwordInputX, passwordInputY, passwordInputX + inputWidth, passwordInputY + inputHeight);

		// 显示实时输入的账号和密码（密码用星号显示）
		drawText(usernameInputX, usernameInputY, 30, username);
		drawText(passwordInputX, passwordInputY, 30, std::string(passIndex, '*').c_str());

		// 按钮逻辑
		if (button(300, 320, 200, 60, "登录"))
		{
			//检查账号密码是否匹配
			for (auto& user : users)
			{
				if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.password.c_str(), password) == 0)
				{
					userName = username;
					flag = MENU;  // 如果正常登录跳转至主菜单
					cleardevice(); // 清屏
					haveUser = true;
					passwordRight = true;
					return;
				}
				else if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.password.c_str(), password) != 0)
				{
					//提示密码不正确，需要重新输入密码
					haveUser = true;
					passwordRight = false;
					break;
				}
				else
					haveUser = false;
			}
		}
		if(!passwordRight)
			drawText(260, 290, 25, "密码错误");
		if (!haveUser)//如果没有该用户，提示用户不存在
			drawText(260, 290, 25, "用户不存在");
		if (button(2, 2, 100, 50, "设置"))
		{
			flag = SET;
			cleardevice(); // 清屏
			return;
		}
		if (button(700, 0, 98, 50, "退出"))
		{
			closegraph(); // 关闭图形窗口
			exit(0);
			return; // 结束程序
		}
		if (button(620, 420, 100, 40, "忘记密码"))
		{
			flag = FINDPASSWORD;
			cleardevice(); // 清屏
			return;
		}
		if (button(140, 420, 60, 40, "注册"))
		{
			flag = SIGNIN; // 注册界面
			cleardevice(); // 清屏
			return;
		}

		//FlushBatchDraw();
		EndBatchDraw();
	}
}


// 打印注册界面的函数
void gameManager::signIn()
{
	char username[30] = ""; // 假设用户名最多30字符
	char password[30] = ""; // 假设密码最多30字符
	char email[30] = "";//邮箱
	int userIndex = 0;
	int passIndex = 0;
	int emailIndex = 0;
	bool isInputUsernam = false;
	bool isInputPassword = false;
	bool isInputEmail = false;
	bool haveUser = false;
	bool allFilled = true;//判断是否有没有填写的信息
	//定义输入框区域
	int usernameInputX = 280, usernameInputY = 160;
	int passwordInputX = 280, passwordInputY = 200;
	int emailInputX = 280, emailInputY = 240;
	int inputWidth = 300, inputHeight = 30;
	while (true)
	{
		if (peekmessage(&msg))
		{
			// 处理鼠标点击事件
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= usernameInputX && msg.x <= usernameInputX + inputWidth &&
					msg.y >= usernameInputY && msg.y <= usernameInputY + inputHeight)
				{
					isInputUsernam = true;
					isInputEmail = false;
					isInputPassword = false;
				}
				else if (msg.x >= passwordInputX && msg.x <= passwordInputX + inputWidth &&
					msg.y >= passwordInputY && msg.y <= passwordInputY + inputHeight)
				{
					isInputPassword = true;
					isInputEmail = false;
					isInputUsernam = false;
				}
				else if (msg.x >= emailInputX && msg.x <= emailInputX + inputWidth &&
					msg.y >= emailInputY && msg.y <= emailInputY + inputHeight)
				{
					isInputEmail = true;
					isInputPassword = false;
					isInputUsernam = false;
				}
			}

			// 处理键盘事件
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isInputUsernam) // 用户名输入
				{
					if (ch == '\b' && userIndex > 0) // 退格键
					{
						username[--userIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && userIndex < 29) // 可显示字符
					{
						username[userIndex++] = ch;
						username[userIndex] = '\0';
					}
				}
				else if(isInputPassword)// 密码输入
				{
					if (ch == '\b' && passIndex > 0) // 退格键
					{
						password[--passIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && passIndex < 29) // 可显示字符
					{
						password[passIndex++] = ch;
						password[passIndex] = '\0';
					}
				}
				else if (isInputEmail)
				{
					if (ch == '\b' && emailIndex > 0) // 退格键
					{
						email[--emailIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && emailIndex < 29) // 可显示字符
					{
						email[emailIndex++] = ch;
						email[emailIndex] = '\0';
					}
				}
			}
		}
		//开始绘制
		BeginBatchDraw();//使用双缓冲，防止闪屏
		cleardevice();
		putimage(0, 0, &back_img[0]);
		settextcolor(RGB(164, 141, 45));
		setbkcolor(WHITE);
		settextstyle(30, 0, "宋体");
		drawText(180, 160, 35, "账号：");
		drawText(180, 200, 35, "密码：");
		drawText(180, 240, 35, "邮箱：");   //此处进行了调整！！！！

		//绘制输入框
		setfillcolor(RGB(231, 232, 233));
		fillrectangle(usernameInputX, usernameInputY, usernameInputX + inputWidth, usernameInputY + inputHeight);
		fillrectangle(passwordInputX, passwordInputY, passwordInputX + inputWidth, passwordInputY + inputHeight);
		fillrectangle(emailInputX, emailInputY, emailInputX + inputWidth, emailInputY + inputHeight);

		// 显示实时输入的账号和密码（密码用星号显示）
		drawText(usernameInputX, usernameInputY, 30, username);
		drawText(passwordInputX, passwordInputY, 30, password);
		drawText(emailInputX, emailInputY, 30, email);
		// 注册界面的按钮
		if (button(300, 320, 200, 60, "创建"))
		{
			
			if (strcmp(username,"")==0 || strcmp(password, "") == 0 || strcmp(email, "") == 0)
			{
				allFilled = false;
			}
			else
			{
				//先检查用户是否已经存在
				for (auto& user : users)
				{
					if (strcmp(user.name.c_str(), username) == 0)
					{
						haveUser = true;
						break;
					}
					else
						haveUser = false;
						
				}
				if (!haveUser)
				{
					user u;
					u.name = username;
					u.email = email;
					u.password = password;
					u.stars = 0;
					u.time = 0;
					insertNewUser(u);//添加到users组中
					writeFile("userInfo.txt");//更新文件内容
					flag = LOGIN;	// 返回登录界面
					return;
				}
					
				
			}
			
		}
		if(haveUser)
			drawText(280, 280, 25, "用户已存在");;
		if (!allFilled)
			drawText(280, 280, 25, "请将信息填写完整");
		if (button(620, 420, 100, 40, "返回"))
		{
			flag = LOGIN;	// 返回登录界面
			return;
		}
		if (button(2, 2, 100, 50, "设置"))
		{
			flag = SET;			// 切换到设置状态
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
// 打印忘记密码界面1的函数
void gameManager::forgetPassword()
{
	char username[30] = ""; // 假设用户名最多30字符
	char email[30] = "";
	int userIndex = 0;
	int emailIndex = 0;
	bool isInputName = false; 
	bool isInputEmail = false; 
	bool haveUser = true;
	bool emailRight = true;

	// 定义输入框区域
	int usernameInputX = 260, usernameInputY = 200;
	int emailInputX = 260, emailInputY = 250;
	int inputWidth = 300, inputHeight = 30;
	while (true)
	{
		if (peekmessage(&msg))
		{
			// 处理鼠标点击事件
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= usernameInputX && msg.x <= usernameInputX + inputWidth &&
					msg.y >= usernameInputY && msg.y <= usernameInputY + inputHeight)
				{
					isInputName = true;
					isInputEmail = false;
				}
				else if (msg.x >= emailInputX && msg.x <= emailInputX + inputWidth &&
					msg.y >= emailInputY && msg.y <= emailInputY + inputHeight)
				{
					isInputEmail = true;
					isInputName = false;
				}
			}

			// 处理键盘事件
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isInputName) // 用户名输入
				{
					if (ch == '\b' && userIndex > 0) // 退格键
					{
						username[--userIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && userIndex < 29) // 可显示字符
					{
						username[userIndex++] = ch;
						username[userIndex] = '\0';
					}
				}
				else if(isInputEmail)// 邮箱输入
				{
					if (ch == '\b' && emailIndex > 0) // 退格键
					{
						email[--emailIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && emailIndex < 29) // 可显示字符
					{
						email[emailIndex++] = ch;
						email[emailIndex] = '\0';
					}
				}
			}
		}
		BeginBatchDraw();//使用双缓冲，防止闪屏
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "宋体");
		setbkcolor(WHITE);
		cleardevice();
		putimage(0, 0, &back_img[0]);
		BeginBatchDraw(); // 开始批量绘图，提高绘图效率
		drawText(160, 200, 30, "账号：");
		drawText(160, 250, 30, "邮箱：");


		// 绘制输入框
		setfillcolor(RGB(231, 232, 233));
		solidrectangle(usernameInputX, usernameInputY, usernameInputX + inputWidth, usernameInputY + inputHeight);
		solidrectangle(emailInputX, emailInputY, emailInputX + inputWidth, emailInputY + inputHeight);

		// 显示实时输入的账号和邮箱
		drawText(usernameInputX, usernameInputY, 30, username);
		drawText(emailInputX, emailInputY, 30, email);
		// 找回密码第一步的按钮
		if (button(300, 320, 200, 60, "找回"))
		{
			
			for (auto& user : users)
			{
				if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.email.c_str(), email) == 0)//账号邮箱匹配
				{
					userName = username;
					haveUser = true;
					flag = FINDPASSWORD2; // 如果账号和邮箱相匹配的话切换到找回密码第二步
					return;
				}
				else if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.email.c_str(), email) != 0)//邮箱不对
				{
					haveUser = true;
					emailRight = false;
					break;
				}
				else
					haveUser = false;
			}
			
		}
		if (!haveUser)
			drawText(260, 290, 25, "用户不存在");
		if(!emailRight)
			drawText(260, 290, 25, "邮箱不存在");
		if (button(620, 420, 100, 40, "返回"))
		{
			flag = LOGIN; // 返回登录界面
			return;
		}
		if (button(2, 2, 100, 50, "设置"))
		{
			flag = SET;			// 切换到设置状态
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
// 打印忘记密码界面2的函数
void gameManager::forgetPassword2()
{
	char password[30] = ""; // 假设密码最多30字符
	char password_sure[30] = ""; 
	int passIndex = 0;
	int pass_sureIndex = 0;
	bool isPasswordInput = false; 
	bool isPass_sureInput= false; 
	bool twoPasswordSame = true;//判断两次密码输入是否一致

	// 定义输入框区域
	int passwordInputX = 260, passwordInputY = 200;
	int pass_sureInputX = 260, pass_sureInputY = 250;
	int inputWidth = 300, inputHeight = 30;
	while (true)
	{
		if (peekmessage(&msg))
		{
			// 处理鼠标点击事件
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= passwordInputX && msg.x <= passwordInputX + inputWidth &&
					msg.y >= passwordInputY && msg.y <= passwordInputY + inputHeight)
				{
					isPasswordInput = true;
					isPass_sureInput = false;
				}
				else if (msg.x >= pass_sureInputX && msg.x <= pass_sureInputX + inputWidth &&
					msg.y >= pass_sureInputY && msg.y <= pass_sureInputY + inputHeight)
				{
					isPass_sureInput = true;
					isPasswordInput = false;
				}
			}

			// 处理键盘事件
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isPasswordInput) // 密码输入
				{
					if (ch == '\b' && passIndex > 0) // 退格键
					{
						password[--passIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && passIndex < 29) // 可显示字符
					{
						password[passIndex++] = ch;
						password[passIndex] = '\0';
					}
				}
				else if(isPass_sureInput)// 确认密码输入
				{
					if (ch == '\b' && pass_sureIndex > 0) // 退格键
					{
						password_sure[--pass_sureIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && pass_sureIndex < 29) // 可显示字符
					{
						password_sure[pass_sureIndex++] = ch;
						password_sure[pass_sureIndex] = '\0';
					}
				}
			}
		}
		BeginBatchDraw();//使用双缓冲，防止闪屏
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "宋体");
		setbkcolor(WHITE);
		cleardevice();
		putimage(0, 0, &back_img[0]);
		drawText(300, 80, 40, "请重新设置密码");
		drawText(160, 200, 30, "新密码：");
		drawText(160, 250, 30, "确认密码：");

		// 绘制输入框
		setfillcolor(RGB(231, 232, 233));
		solidrectangle(passwordInputX, passwordInputY, passwordInputX + inputWidth, passwordInputY + inputHeight);
		solidrectangle(pass_sureInputX, pass_sureInputY, pass_sureInputX + inputWidth, pass_sureInputY + inputHeight);

		// 显示实时输入的密码和确认密码（密码用星号显示）
		drawText(passwordInputX, passwordInputY, 30, std::string(passIndex, '*').c_str());
		drawText(pass_sureInputX, pass_sureInputY, 30, std::string(pass_sureIndex, '*').c_str());
		// 找回密码第二步的按钮
		if (button(300, 320, 200, 60, "确定"))
		{
			for (auto& user : users)
			{
				if (strcmp(user.name.c_str(),userName.c_str())==0 && strcmp(password, password_sure) == 0)
				{
					twoPasswordSame = true;
					user.password = string(password);
					writeFile("userInfo.txt");
					flag = LOGIN; // 返回登录界面
					return;
				}
				else
				{
					twoPasswordSame = false;
				}
			}
			
		}
		if (!twoPasswordSame)
			drawText(260, 290, 25, "两次密码输入不一致");
		if (button(620, 420, 100, 40, "返回"))
		{
			flag = FINDPASSWORD; // 返回忘记密码第一个界面
			return;
		}
		if (button(2, 2, 100, 50, "设置"))
		{
			flag = SET;			// 切换到设置状态
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}

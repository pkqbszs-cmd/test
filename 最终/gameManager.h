#pragma once
#include"data.h"
#include"bullet.h"
class gameManager {
public:

	/**********************************游戏逻辑部分***********************************/
	/*
		负责人：D
		功能：初始化地图和数据

			  根据当前的关卡数，绘制不同的地图
			  switch(pass)
			  {
				case 1:
					将pass1逐元素赋值给map
					break;
				case 2:
				case 3:
				case 4:
				case 5:
			  }
		参数：void
		返回值：void
	*/
	void init();

	/*
	功能：暂停界面
		  可以返回到游戏也可以回到主菜单
		  根据原型图设计
	参数：void
	返回值：void
*/
	void pause();
	/*
	负责人：I
	功能：打印胜利/失败界面
		  安装原型图设计
	参数：void
	返回值：void
*/
	void winShow();
	void loseShow();

	/*
	负责人：I(难点)
	功能：控制游戏界面的运行
		  初始化游戏地图
		  init(pass);
		  打印地图界面（调用draw()）
		  定义我方坦克并
		  定义我方子弹组
		  定义敌方坦克组
		  定义敌方子弹组
		  int times=0;//记录循环次数
		  while(true)
		  {
			
			控制存活的敌方坦克转向（每循环200次转向一次，调用敌方坦克的turn()）
			控制存活的敌方坦克移动（每循环20次移动一次，调用敌方坦克的move()）
			控制存活的敌方坦克射击（每循环200次射击一次，调用敌方坦克的shoot()）
			玩家移动、射击（调用我方坦克的move()）
			子弹移动（每次循环调用子弹的move()）

			判断胜负（调用win_or_lose）
			如果胜利调用胜利界面
			如果失败调用失败界面
			times++;

			暂停判断
		  }
	参数：void
	返回值：void
*/
	void gameView();
	/*
		功能：绘制游戏界面的一帧
		参数：
			enemies:游戏内的敌人组
			player:游戏内的我方坦克
			enemy_bullets:敌方子弹组
			my_bullets:我方子弹组
		返回值：void
	*/
	void draw(vector<enemy_tank>& enemies, my_tank& player, vector<bullet>& enemy_bullets, vector<bullet>& my_bullets);

	/*
	功能：根据当前场上的敌方坦克数量判断是否需要继续生成敌方坦克
		  当场上敌方坦克小于三个且消灭的敌方坦克数小于本关最大敌方坦克数目时，在敌方坦克出生点（可能不止一个，随机选一个）生成一个敌方坦克
	参数：
		enemies:游戏内的敌人组
		player:游戏内的我方坦克
		x:生成位置的横坐标
		y:生成位置的纵坐标
	*/
	void enemy_generate(vector<enemy_tank>& enemys, my_tank& player, int x, int y);
	/*
	功能：生成buff道具
	参数：
		x:buff生成位置的横坐标
		y:buff生成位置的纵坐标
		buff:buff的种类
	*/
	void buff_generate(int x, int y, int buff);

	/*
	负责人：I
	功能：判断当前游戏是否胜利或者是否失败
		  所有的敌机坦克都死亡且玩家的HP>0
		  玩家HP<=0,失败
	参数：void
	返回值：
		int:
			0表示胜利，1表示失败，2表示未分胜负
*/
	int win_or_lose(my_tank& player);



	/****************************************游戏外逻辑和页面处理*************************************************/
	/*
		功能：装扮库
		参数：
			selectedSkin:
		返回值:void
	*/
	void drawSkinPage(int& selectedSkin);

	/*
		负责人：E
		功能：打印主菜单
			  打印按钮：
				进入游戏，如果点击则进入关卡选择界面
				新手指南，如果点击则进入新手指南界面
				星星排行榜，如果点击则进入星星排行榜界面
				装扮库，如果点击则进入装扮库界面
				设置，如果点击则进入设置界面
				团队介绍，如果点击则进入团队介绍界面
				退出游戏，如果点击则退出程序
	*/
	void menu();
	/*
		负责人：E
		功能：打印选关界面
			  参照原型图设计界面
			  点击某个关卡后进入相应的游戏界面
		参数：void
		返回值：void
	*/
	void passChoose();
	void buff();
	/*
		负责人：E
		功能：打印新手指南界面
		参数：void
		返回值：void
	*/
	void guide();
	/*
		负责人：F
		功能：打印星星排行榜
		参数：void
		返回值：void
	*/
	void printRank();
	/*
		负责人：F
		功能：读取文件流
		参数：fileName
		返回值：vector<user>
	*/
	void readFile(const char* fileName);
	/*
		负责人：F
		功能：写入文件
		参数：
			fileName:文件名
		返回值：void
	*/
	void writeFile(const char* fileName);
	/*
		负责人：F
		功能：更新排行榜
		参数：
			u:变动的用户
		返回值：void
	*/
	bool rank_cmp(user a, user b);
	void updateRank();
	void insertNewUser(const user u);
	/*
		负责人：G
		功能：登录注册忘记密码界面
			  根据原型图设计
	*/
	void signIn();
	void logIn();
	void forgetPassword();
	void forgetPassword2();

	/*
		功能：模式选择界面
			  可以跳转到关卡选择界面
			  根据原型图设计
		参数：void
		返回值：void
	*/
	void chooseMode();
	/*
		功能：将游戏所需要的图片资源和文件资源加载进来
	*/
	void loadSources();

	/*
		负责人：A
		功能：设计界面
			  可以调节音量、更改按键设置，根据原型图设计
		参数：void
		返回值：void
	*/
	void set();
	void setVolume(double volume_persent, const string& musicPath);
	/*
		负责人：A
		功能：团队介绍
			  根据原型图设计
		参数：void
		返回值：void
	*/
	void memberInfor();



	/**********************************************控制整个游戏主循环*****************************************************/
	void controller();


	/***********************************************小组件***************************************************/
	/*
	负责人：E
	功能：判断当前某个点是否在指定区域
	参数：
		mx:该点的横坐标
		my:该点的纵坐标
		x:区域的左上角点横坐标
		y:区域的左上角点纵坐标
		w:区域的宽度
		h:区域的高度
	返回值：
		bool:
			true表示该点在指定区域
			false表示该点不在指定区域
*/
	bool inArea(int mx, int my, int x, int y, int w, int h);
	/*
		负责人：E
		功能：绘制按钮并判断鼠标有无点击该按钮
			  当鼠标悬浮在按钮上时，高亮按钮（setfillcolor(RGB( , , ))）
			  否则按照默认颜色正常显示按钮，（setfillcolor(RGB( , , ))）
			  绘制按钮，fillroundrect(x,y,x+w,y+h,5,5);
			  绘制按钮的文本，outtextxy( , ,str);
			  判断按钮是否被点击
		参数：
			x:按钮的左上角点横坐标
			y:按钮的左上角点纵坐标
			w:按钮的宽度
			h:按钮的高度
			str:按钮中的文本
	*/
	bool button(int x, int y, int w, int h, const char* str);
	/*
		功能：在(x,y)绘制大小为size的文本text
	*/
	void drawText(int x, int y, int size, const char* text);

private:
	int pass = 5;//当前选择的关卡数，默认为第一关
	int current_enemy = 0;
	int total_enemy = 6;
	int kill_enemy = 0;
	int time = 0;//本次闯关用时
	int stars = 0;//本关奖励的星星数
	string userName;
	// 当前页面状态
	GameState flag = LOGIN;
	//定义消息结构体变量
	ExMessage msg = { 0 };
};
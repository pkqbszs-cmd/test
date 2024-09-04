#pragma once
#include"data.h"
#include"bullet.h"
class gameManager {
public:

	/**********************************��Ϸ�߼�����***********************************/
	/*
		�����ˣ�D
		���ܣ���ʼ����ͼ������

			  ���ݵ�ǰ�Ĺؿ��������Ʋ�ͬ�ĵ�ͼ
			  switch(pass)
			  {
				case 1:
					��pass1��Ԫ�ظ�ֵ��map
					break;
				case 2:
				case 3:
				case 4:
				case 5:
			  }
		������void
		����ֵ��void
	*/
	void init();

	/*
	���ܣ���ͣ����
		  ���Է��ص���ϷҲ���Իص����˵�
		  ����ԭ��ͼ���
	������void
	����ֵ��void
*/
	void pause();
	/*
	�����ˣ�I
	���ܣ���ӡʤ��/ʧ�ܽ���
		  ��װԭ��ͼ���
	������void
	����ֵ��void
*/
	void winShow();
	void loseShow();

	/*
	�����ˣ�I(�ѵ�)
	���ܣ�������Ϸ���������
		  ��ʼ����Ϸ��ͼ
		  init(pass);
		  ��ӡ��ͼ���棨����draw()��
		  �����ҷ�̹�˲�
		  �����ҷ��ӵ���
		  ����з�̹����
		  ����з��ӵ���
		  int times=0;//��¼ѭ������
		  while(true)
		  {
			
			���ƴ��ĵз�̹��ת��ÿѭ��200��ת��һ�Σ����õз�̹�˵�turn()��
			���ƴ��ĵз�̹���ƶ���ÿѭ��20���ƶ�һ�Σ����õз�̹�˵�move()��
			���ƴ��ĵз�̹�������ÿѭ��200�����һ�Σ����õз�̹�˵�shoot()��
			����ƶ�������������ҷ�̹�˵�move()��
			�ӵ��ƶ���ÿ��ѭ�������ӵ���move()��

			�ж�ʤ��������win_or_lose��
			���ʤ������ʤ������
			���ʧ�ܵ���ʧ�ܽ���
			times++;

			��ͣ�ж�
		  }
	������void
	����ֵ��void
*/
	void gameView();
	/*
		���ܣ�������Ϸ�����һ֡
		������
			enemies:��Ϸ�ڵĵ�����
			player:��Ϸ�ڵ��ҷ�̹��
			enemy_bullets:�з��ӵ���
			my_bullets:�ҷ��ӵ���
		����ֵ��void
	*/
	void draw(vector<enemy_tank>& enemies, my_tank& player, vector<bullet>& enemy_bullets, vector<bullet>& my_bullets);

	/*
	���ܣ����ݵ�ǰ���ϵĵз�̹�������ж��Ƿ���Ҫ�������ɵз�̹��
		  �����ϵз�̹��С������������ĵз�̹����С�ڱ������з�̹����Ŀʱ���ڵз�̹�˳����㣨���ܲ�ֹһ�������ѡһ��������һ���з�̹��
	������
		enemies:��Ϸ�ڵĵ�����
		player:��Ϸ�ڵ��ҷ�̹��
		x:����λ�õĺ�����
		y:����λ�õ�������
	*/
	void enemy_generate(vector<enemy_tank>& enemys, my_tank& player, int x, int y);
	/*
	���ܣ�����buff����
	������
		x:buff����λ�õĺ�����
		y:buff����λ�õ�������
		buff:buff������
	*/
	void buff_generate(int x, int y, int buff);

	/*
	�����ˣ�I
	���ܣ��жϵ�ǰ��Ϸ�Ƿ�ʤ�������Ƿ�ʧ��
		  ���еĵл�̹�˶���������ҵ�HP>0
		  ���HP<=0,ʧ��
	������void
	����ֵ��
		int:
			0��ʾʤ����1��ʾʧ�ܣ�2��ʾδ��ʤ��
*/
	int win_or_lose(my_tank& player);



	/****************************************��Ϸ���߼���ҳ�洦��*************************************************/
	/*
		���ܣ�װ���
		������
			selectedSkin:
		����ֵ:void
	*/
	void drawSkinPage(int& selectedSkin);

	/*
		�����ˣ�E
		���ܣ���ӡ���˵�
			  ��ӡ��ť��
				������Ϸ�������������ؿ�ѡ�����
				����ָ�ϣ����������������ָ�Ͻ���
				�������а�������������������а����
				װ��⣬�����������װ������
				���ã���������������ý���
				�Ŷӽ��ܣ�������������Ŷӽ��ܽ���
				�˳���Ϸ�����������˳�����
	*/
	void menu();
	/*
		�����ˣ�E
		���ܣ���ӡѡ�ؽ���
			  ����ԭ��ͼ��ƽ���
			  ���ĳ���ؿ��������Ӧ����Ϸ����
		������void
		����ֵ��void
	*/
	void passChoose();
	void buff();
	/*
		�����ˣ�E
		���ܣ���ӡ����ָ�Ͻ���
		������void
		����ֵ��void
	*/
	void guide();
	/*
		�����ˣ�F
		���ܣ���ӡ�������а�
		������void
		����ֵ��void
	*/
	void printRank();
	/*
		�����ˣ�F
		���ܣ���ȡ�ļ���
		������fileName
		����ֵ��vector<user>
	*/
	void readFile(const char* fileName);
	/*
		�����ˣ�F
		���ܣ�д���ļ�
		������
			fileName:�ļ���
		����ֵ��void
	*/
	void writeFile(const char* fileName);
	/*
		�����ˣ�F
		���ܣ��������а�
		������
			u:�䶯���û�
		����ֵ��void
	*/
	bool rank_cmp(user a, user b);
	void updateRank();
	void insertNewUser(const user u);
	/*
		�����ˣ�G
		���ܣ���¼ע�������������
			  ����ԭ��ͼ���
	*/
	void signIn();
	void logIn();
	void forgetPassword();
	void forgetPassword2();

	/*
		���ܣ�ģʽѡ�����
			  ������ת���ؿ�ѡ�����
			  ����ԭ��ͼ���
		������void
		����ֵ��void
	*/
	void chooseMode();
	/*
		���ܣ�����Ϸ����Ҫ��ͼƬ��Դ���ļ���Դ���ؽ���
	*/
	void loadSources();

	/*
		�����ˣ�A
		���ܣ���ƽ���
			  ���Ե������������İ������ã�����ԭ��ͼ���
		������void
		����ֵ��void
	*/
	void set();
	void setVolume(double volume_persent, const string& musicPath);
	/*
		�����ˣ�A
		���ܣ��Ŷӽ���
			  ����ԭ��ͼ���
		������void
		����ֵ��void
	*/
	void memberInfor();



	/**********************************************����������Ϸ��ѭ��*****************************************************/
	void controller();


	/***********************************************С���***************************************************/
	/*
	�����ˣ�E
	���ܣ��жϵ�ǰĳ�����Ƿ���ָ������
	������
		mx:�õ�ĺ�����
		my:�õ��������
		x:��������Ͻǵ������
		y:��������Ͻǵ�������
		w:����Ŀ��
		h:����ĸ߶�
	����ֵ��
		bool:
			true��ʾ�õ���ָ������
			false��ʾ�õ㲻��ָ������
*/
	bool inArea(int mx, int my, int x, int y, int w, int h);
	/*
		�����ˣ�E
		���ܣ����ư�ť���ж�������޵���ð�ť
			  ����������ڰ�ť��ʱ��������ť��setfillcolor(RGB( , , ))��
			  ������Ĭ����ɫ������ʾ��ť����setfillcolor(RGB( , , ))��
			  ���ư�ť��fillroundrect(x,y,x+w,y+h,5,5);
			  ���ư�ť���ı���outtextxy( , ,str);
			  �жϰ�ť�Ƿ񱻵��
		������
			x:��ť�����Ͻǵ������
			y:��ť�����Ͻǵ�������
			w:��ť�Ŀ��
			h:��ť�ĸ߶�
			str:��ť�е��ı�
	*/
	bool button(int x, int y, int w, int h, const char* str);
	/*
		���ܣ���(x,y)���ƴ�СΪsize���ı�text
	*/
	void drawText(int x, int y, int size, const char* text);

private:
	int pass = 5;//��ǰѡ��Ĺؿ�����Ĭ��Ϊ��һ��
	int current_enemy = 0;
	int total_enemy = 6;
	int kill_enemy = 0;
	int time = 0;//���δ�����ʱ
	int stars = 0;//���ؽ�����������
	string userName;
	// ��ǰҳ��״̬
	GameState flag = LOGIN;
	//������Ϣ�ṹ�����
	ExMessage msg = { 0 };
};
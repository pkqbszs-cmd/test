#include "gameManager.h"
void gameManager::enemy_generate(vector<enemy_tank>& enemys, my_tank& player, int x, int y)
{

	if (pass == 1 || pass == 2 || pass == 3)//ǰ���س���������3���з�̹��
	{
		if (current_enemy < 3 && (player.getKill() + current_enemy) < total_enemy)
		{
			if (player.x == x && player.y == y)//���ҷ�̹���ڵз�̹������λ����ʱ���������ɵз�̹��
				return;
			else
			{
				enemy_tank enemy(x, y, 3, 1);//��ʼ�������Ƴ���һ���з�̹�ˣ�Ѫ��Ϊ1
				current_enemy += 1;				//����̹������һ
				enemys.push_back(enemy);		//��������ӵ��з�̹������
			}
		}
	}
	else
	{
		if (current_enemy < 5 && (player.getKill() + current_enemy) < total_enemy)
		{
			if (player.x == x && player.y == y)//���ҷ�̹���ڵз�̹������λ����ʱ���������ɵз�̹��
				return;
			else
			{
				enemy_tank enemy(x, y, 3, 2);//��ʼ�������Ƴ���һ���з�̹�ˣ�Ѫ��Ϊ2
				current_enemy += 1;				//����̹������һ
				enemys.push_back(enemy);		//��������ӵ��з�̹������
			}
		}
	}
	//ֻ�е����ϵз�̹������С���������̹�������������ѻ�ɱ+���ϵз�̹������<��Ҫ��ɱ�ĵл�����ʱ��������һ���з�̹��
	
}

void gameManager::buff_generate(int x, int y, int buff)
{
	//ֻ�е����ϵ�buff��ʰȡ���Ż������µ�buff����
	for (int row = 0; row < 15; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			if (map[row][col] == 3 || map[row][col] == 4 || map[row][col] == 5)//�����⵽buff����
			{
				return;
			}
		}
	}
	map[y / 40][x / 40] = buff;
}


// ��ӡ���а�ĺ���
void gameManager::printRank()
{
	updateRank();
	while (true) {
		if (peekmessage(&msg, EX_MOUSE)) {} // ��������Ϣ
		BeginBatchDraw(); // ��ʼ������ͼ����߻�ͼЧ��
		cleardevice();
		putimage(0, 0, &back_img[2]);
		// ��ӡ"���а�"����
		int textWidth = 25, textHeight = 40; // ��������Ŀ�Ⱥ͸߶�
		settextstyle(textHeight, textWidth, "����"); // ����������ʽΪ����
		settextcolor(BLACK); // ����������ɫΪ��ɫ
		const char* s = "���а�"; // ������ʾ�Ķ��ֽ��ַ�����
		int bgi = 10; // "���а�"���ֿ�ʼ��ʾ��������
		outtextxy(400 - textwidth(s) / 2, bgi, s); // ��ͼ�δ����м��ӡ"���а�"
		setlinecolor(BLACK); // ����������ɫΪ��ɫ

		// �������а�ı�����
		int Lft = 200, Top = bgi + 5 + textheight(s); // �������а񱳾������ߺͶ�������
		int WidthLen = 400, HeightLen = 400; // �������а񱳾���Ŀ�Ⱥ͸߶�
		rectangle(Lft, Top + HeightLen, Lft + WidthLen, Top); // ���Ʊ�����
		int cellWidth = 100, cellHeight = 40; // ����ÿ����Ԫ��Ŀ�Ⱥ͸߶�
		setbkmode(TRANSPARENT); // �������ֱ���ģʽΪ͸��
		textWidth = 20, textHeight = 30; // �����ı���ʽ
		settextstyle(textHeight, textWidth, "Tomas"); // �����µ��ı���ʽ

		// ��ӡ��ͷ
		for (int j = 0; j < 4; j++) {
			int px = Lft + j * cellWidth, py = Top; // ����ÿ����ͷ���ֵ�����
			switch (j) { // �����к������Ӧ�ı�ͷ����
			case 0:
				outtextxy(px, py, "Rank"); // ��һ�б�ͷΪ"Rank"
				break;
			case 1:
				outtextxy(px, py, "Name"); // �ڶ��б�ͷΪ"Name"
				break;
			case 2:
				outtextxy(px, py, "Stars"); // �����б�ͷΪ"Stars"
				break;
			case 3:
				outtextxy(px, py, "Time"); // �����б�ͷΪ"Time"
				break;
			}
		}

		// ��ӡ��������
		for (int i = 1; i <= 5; i++) {
			char rak[10],sta[10],tim[10]; // ʹ�ö��ֽ��ַ�����
			sprintf_s(rak, "%d", i); // ����������ת��Ϊ�ַ���
			sprintf_s(sta, "%d", users[i - 1].stars); // ��������ת��Ϊ�ַ���
			sprintf_s(tim, "%d", users[i-1].time); // ʱ����ʱ����Ϊ100��������Ը���ʵ�������޸�

			for (int j = 0; j < 4; j++) { // ��ӡÿ���û�����ϸ��Ϣ
				int px = Lft + j * cellWidth, py = Top + i * cellHeight; // ����ÿ����Ԫ������Ͻ�����
				rectangle(px, py + cellHeight, px + cellWidth, py); // ���Ƶ�Ԫ��߿�

				switch (j) { // �����к������Ӧ���û���Ϣ
				case 0:
					outtextxy(px, py, rak); // ��һ����ʾ����
					break;
				case 1:
					outtextxy(px, py, users[i - 1].name.c_str()); // �ڶ�����ʾ�û���
					break;
				case 2:
					outtextxy(px, py, sta); // ��������ʾ������
					break;
				case 3:
					outtextxy(px, py, tim); // ��������ʾʱ�䣨����ʱ��Ϊ100��
					break;
				}
			}
		}

		// "�������˵�"��ť��ʵ��
		if (button(650, 50, 100, 50, "�������˵�")) { // ��������"�������˵�"��ť
			cleardevice(); // �����������ǰ��������
			flag = MENU; // ���ñ�־λΪMENU����ʾ�������˵�
			return; // �������˵�
		}

		FlushBatchDraw(); // ˢ��������ͼ����
		EndBatchDraw(); // ����������ͼ
		msg.message = { 0 }; // ʹ��ÿ�ε����ťֻ����Ӧһ��
	}
}

// ���ļ��ж�ȡ�û����ݵĺ���
void gameManager::readFile(const char* fileName)
{
	ifstream inFile; // ���������ļ�������
	inFile.open(fileName); // ���ļ�
	if (!inFile.is_open()) throw out_of_range("File is not open"); // ����ļ��Ƿ�ɹ���

	//users.clear(); // ����û��б������ظ��������
	//user nw; // ����һ���û�����
	//while (!inFile.eof()) // ��ȡ�ļ�ֱ���ļ�����
	//{
	//	user nw; // ����һ���û�����
	//	inFile >> nw.name >>nw.password>>nw.email>> nw.stars>>nw.time; // ���ļ��ж�ȡ�û�����������
	//	if (inFile) { // ����Ƿ�ɹ���ȡ����
	//		users.push_back(nw); // ����ȡ���û���Ϣ��ӵ��û��б���
	//	}
	//}
	user nw; // ����һ���û�����
	while (inFile >> nw.name >> nw.password >> nw.email >> nw.stars >> nw.time) // ʹ����ȷ�Ķ�ȡ��ʽ
	{
		users.push_back(nw); // ����ȡ���û���Ϣ��ӵ��û��б���
	}
	inFile.close(); // �ر��ļ�
}


// ���û�����д���ļ��ĺ���
void gameManager::writeFile(const char* fileName)
{
	ofstream outFile; // ��������ļ�������
	outFile.open(fileName); // ���ļ�
	if (!outFile.is_open()) throw out_of_range("File is not open"); // ����ļ��Ƿ�ɹ���
	for (int i = 0; i < users.size(); i++) // ���������û�
	{
		outFile << users[i].name << ' ' << users[i].password << ' ' <<users[i].email << ' ' <<users[i].stars << ' ' <<users[i].time << ' ' << endl; // ���û�����д���ļ�
	}
	outFile.close(); // �ر��ļ�
}

// �û��ȽϺ�������������
bool gameManager::rank_cmp(user a, user b)
{
	return (a.stars == b.stars)?(a.time<b.time):(a.stars>b.stars); // �Ƚ������û��������������ڴӴ�С����
}

// �������а�ĺ���
void gameManager::updateRank()
{
	auto cmp = bind(&gameManager::rank_cmp, this, placeholders::_1, placeholders::_2);
	sort(users.begin(), users.end(), cmp); // �����������û��б��������
}
//�������û�
void gameManager::insertNewUser(const user u)
{
	users.push_back(u); // ���µ��û���ӵ��û��б���
	auto cmp = bind(&gameManager::rank_cmp, this, placeholders::_1, placeholders::_2);
	sort(users.begin(), users.end(), cmp); // �����������û��б��������
}
void gameManager::pause()
{
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE|EX_KEY)) {}
		BeginBatchDraw();//ʹ��˫���壬��ֹ����
		cleardevice();
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "����");
		if (button(300, 100, 150, 50, "�ص���Ϸ") || (msg.message==WM_KEYDOWN && msg.vkcode==VK_ESCAPE))
		{
			cleardevice();//����
			msg.message = { 0 };
			return;

		}
		if (button(300, 300, 150, 50, "���¿�ʼ"))
		{
			flag = PASSCHOOSE;
			return;
		}
		if (button(300, 500, 150, 50, "�������˵�"))
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
	//���ݳ�ʼ��
	current_enemy = 0;
	time = 0;
	stars = 0;
	//���ݵ�ǰ�Ĺؿ�������pass���θ�ֵ��map
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
	//��ʼ����Ϸ��ͼ
	init();
	//���߳��ֵ�λ�á�����
	int buff_x, buff_y, buff_kind;
	//���߿������ɵ�����
	int buff_x1, buff_x2, buff_x3, buff_y1, buff_y2, buff_y3;
	//�ҷ�̹�˳����ص�
	int pos_x, pos_y;
	//�ҷ����ص�����
	int base_x, base_y;
	//�з�̹�˵ĳ���λ��
	int enemy_x, enemy_y;
	//�з�̹�˵ĳ���λ��
	int enemy_x1, enemy_y1;
	int enemy_x2, enemy_y2;
	int enemy_x3, enemy_y3;
	int enemy_x4, enemy_y4;
	int enemy_x5, enemy_y5;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//Ѱ�ҵ������ɵ�-3��
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
			//Ѱ�һ�������
			if (map[i][j] == 6)
			{
				base_x = j * 40;
				base_y = i * 40;
			}
			//Ѱ���ҷ�̹�˳�����
			if (map[i][j] == 7)
			{
				pos_x = j * 40;
				pos_y = i * 40;
			}
			//Ѱ�ҵз�̹�˳�����-5��
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
	//�����ҷ�̹��
	my_tank player(pos_x, pos_y);
	//�����ҷ��ӵ���
	vector<bullet> my_bullets;
	//����з�̹����
	vector<enemy_tank> enemys;
	//����з��ӵ���
	vector<bullet> enemy_bullets;

	int times = 0;//��¼ѭ������
	int shootTime = clock() - 500;//�ϴ����ʱ�䣬���ƾ����ϴ����0.5����ܼ������
	while (true)
	{
		draw(enemys, player, enemy_bullets, my_bullets);//���Ƶ�ǰ֡

		int starttime = clock();//����ѭ����ʼʱ��

		//���³��ϵ�ǰ�з�̹������
		int enemyNum = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
				if (map[i][j] == 101)
					enemyNum += 1;
		}
		current_enemy = enemyNum;
		if (pass == 1 || pass == 2 || pass == 3)//ǰ����
		{
			//����������з�̹�˳������е�һ�����ɵз�̹�ˣ�����������������ɵ��һ�����ɵ���
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
		else if (pass == 4 || pass == 5)//4��5��
		{
			//���������з�̹�˳������е�һ�����ɵз�̹�ˣ�����������������ɵ��һ�����ɵ���
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
		//���ɵз�̹��
		enemy_generate(enemys, player, enemy_x, enemy_y);
		//���ɵ���
		if (time % 100 == 0)
			buff_generate(buff_x, buff_y, buff_kind);
		//���ƴ��ĵз�̹��ת��ÿѭ��20��-2sת��һ�Σ����õз�̹�˵�turn()��
		if (times % 20 == 0)
		{
			for (int i = 0; i < enemys.size(); i++)
			{
				if (i <= enemys.size() / 2)//һ��л��������ת��
				{
					enemys[i].turn(player.x, player.y);
				}

				else//��һ��л����Ż���ת��
				{
					enemys[i].turn(base_x, base_y);
				}
			}
		}
		//���ƴ��ĵз�̹���ƶ���ÿѭ��5��-0.5s�ƶ�һ�Σ����õз�̹�˵�move()��
		if (times % 5 == 0)
		{
			for (auto& i : enemys)
			{
				i.move();
			}
		}

		//���ƴ��ĵз�̹�������ÿѭ��50��-2.5s���һ�Σ����õз�̹�˵�shoot()��
		if (times % 50 == 0)
		{
			for (auto& i : enemys)
			{
				i.shoot(enemy_bullets);
			}
		}
		//����ƶ�������������ҷ�̹�˵�move()��
		player.move();

		if (clock() - shootTime >= 500)//�����ϴη����ӵ�ÿ��0.5����ܼ�������
		{
			//���γɹ������ӵ�
			if (player.shoot(my_bullets) == 0)
			{
				shootTime = clock();//���·����ӵ���ʱ��
			}
		}
		//�ӵ��ƶ���ÿ��ѭ�������ӵ���move()��
		//�ҷ��ӵ��ƶ�
		for (auto& my_bullet : my_bullets)
		{
			//�Ƴ���ʧ���ӵ�
			if (my_bullet.getIsLive() == 0)
			{
				my_bullets.erase(remove(my_bullets.begin(), my_bullets.end(), my_bullet), my_bullets.end());
			}
			//�����ӵ������ƶ�
			if (my_bullet.getIsLive() == 1)
			{
				//ÿ���ӵ����и��Ե��ƶ������ж���ײ���
				my_bullet.move(enemys, player, pos_x, pos_y);
			}
		}
		//�з��ӵ��ƶ�
		for (auto& enemy_bullet : enemy_bullets)
		{
			//�Ƴ���ʧ���ӵ�
			if (enemy_bullet.getIsLive() == 0)
			{
				enemy_bullets.erase(remove(enemy_bullets.begin(), enemy_bullets.end(), enemy_bullet), enemy_bullets.end());
			}
			//�����ӵ������ƶ�
			if (enemy_bullet.getIsLive() == 1)//����ӵ����
			{
				//ÿ���ӵ����и��Ե��ƶ������ж���ײ���
				enemy_bullet.move(enemys, player, pos_x, pos_y);
			}
		}
		/*
		�ж�ʤ��������win_or_lose��
		���ʤ������ʤ������
		���ʧ�ܵ���ʧ�ܽ���
		*/
		int win = win_or_lose(player);
		if (win == 0)//��Ϸʤ��
		{
			//ͨ����ͬ�Ĺؿ�����ͬ��������
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
			//����users���ݣ�(stars,time)��д�뱣���ļ���
			for (auto& user : users)
			{
				if (user.name == userName)
				{
					user.stars += stars;
					user.time = user.time+this->time/1000;
					break;
				}
			}
			//����update����users����
			updateRank();
			//����writeFile�����ļ�����
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
		time = time + (clock() - starttime) + 100;//��ʱ���ۼ�:(ԭ����ʱ��+ѭ��һ�ε�ʱ��+sleep��ʱ��)/1000=��
		//����Ƿ���ͣ��P
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
			
			//������ͣ������������ҳ��״̬�ı䣬���˳���Ϸ����
			if (flag != GAMEVIEW)
				break;
		}


	}
}

void gameManager::draw(vector<enemy_tank>& enemies, my_tank& player, vector<bullet>& enemy_bullets, vector<bullet>& my_bullets)
{
	BeginBatchDraw();//˫�����ͼ����ֹ����
	cleardevice();
	//����map[i][j]��ֵ���ڲ�ͬ�ķ�����Ʋ�ͬ��ͼ��
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 0)//�յ�
			{
				setfillcolor(BLACK);
				solidrectangle(j * 40, i * 40, (j + 1) * 40, (i + 1) * 40);
			}
			else if (map[i][j] == 1)//ľǽ
				putimage(j * 40, i * 40, &woodWall_img);
			else if (map[i][j] == 2)//ʯǽ
				putimage(j * 40, i * 40, &stoneWall_img);
			else if (map[i][j] == 3)//����
				putimage(j * 40, i * 40, &buff_img[0]);
			else if (map[i][j] == 4)//����
				putimage(j * 40, i * 40, &buff_img[1]);
			else if (map[i][j] == 5)//����
				putimage(j * 40, i * 40, &buff_img[2]);
			else if (map[i][j] == 6)//����
				putimage(j * 40, i * 40, &base_img);
		}
	}
	//���Ƶз�̹��-������map
	for (auto& enemy : enemies)
	{
		if(pass==1||pass==2||pass==3)
		putimage(enemy.x, enemy.y, &enemy_tank_img[0][enemy.direction]);
		else
		putimage(enemy.x, enemy.y, &enemy_tank_img[1][enemy.direction]);
	}
	//�����ҷ�̹��-������map
	putimage(player.x, player.y, &my_tank_img[selectedSkin][player.direction]);
	//���Ƶз��ӵ�-������map
	for (auto& enemy_bullet : enemy_bullets)
	{
		//ע��з��ӵ��޷�ɱ���з�̹��
		//���з��ӵ������з�̹��ʱ�з��ӵ�������
		if (map[enemy_bullet.y / 40][enemy_bullet.x / 40] == 101)
			continue;
		else//��������ӵ����ʱ��������
			putimage(enemy_bullet.x, enemy_bullet.y, &bullet_img[enemy_bullet.getKind()]);
	}
	//�����ҷ��ӵ�-������map
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
		BeginBatchDraw();//ʹ��˫���壬��ֹ����
		cleardevice();
		putimage(0, 0, &back_img[4]);
		int time_s = time / 1000 % 60;//��
		int time_min = time / 1000 / 60;//��
		string time_str = to_string(time_min) + "min" + ":" + to_string(time_s) + "s";
		string stars_str = to_string(stars);
		settextcolor(RGB(164, 141, 45));
		settextstyle(50, 0, "����");
		outtextxy(250, 50, "��ϲ���سɹ�");
		outtextxy(100, 150, "�ܹ���ʱ��");
		outtextxy(350, 150, time_str.c_str());
		outtextxy(100, 250, "�������ǣ�");
		outtextxy(350, 250, stars_str.c_str());
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "����");
		if (button(100, 400, 150, 50, "��һ��"))
		{
			pass = (pass + 1) % 5;
			cleardevice();//����
			flag = GAMEVIEW;
			return;

		}
		if (button(400, 400, 150, 50, "����һ��"))
		{
			cleardevice();//������һ��ÿ�λ�����һ֡��ͼƬ��Ҫ��������
			flag = GAMEVIEW;
			return;
		}
		if (button(500, 500, 150, 50, "�������˵�"))
		{
			cleardevice();//������һ��ÿ�λ�����һ֡��ͼƬ��Ҫ��������
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
		if (peekmessage(&msg, EX_MOUSE)) {}//���������Ϣ
		BeginBatchDraw();//˫�����ͼ
		cleardevice();
		putimage(0, 0, &back_img[4]);
		//��������
		settextcolor(RGB(164, 141, 45));
		settextstyle(50, 0, "����");
		outtextxy(150, 50, "����ʧ�ܣ����ٽ�����");
		settextcolor(BLACK);
		settextstyle(30, 0, "����");
		//���ư�ť���ж��Ƿ���
		if (button(300, 200, 150, 50, "����һ��"))
		{
			cleardevice();//����
			flag = GAMEVIEW;
			break;
		}
		if (button(300, 400, 150, 50, "�������˵�"))
		{
			cleardevice();//����
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
	// �жϰ�ť�������ɫ
	if (inArea(msg.x, msg.y, x, y, w, h))
		setfillcolor(RGB(93, 107, 153)); // ����ڰ�ť��
	else
		setfillcolor(RGB(231, 232, 233)); // ��겻�ڰ�ť��

	fillroundrect(x, y, x + w, y + h, 5, 5); // ����Բ�Ǿ��ΰ�ť

	settextcolor(BLACK); // �ı���ɫ
	settextstyle(20, 0, "����");
	setbkmode(TRANSPARENT); // ͸������

	// �����ı�λ�ã�ʹ���ڰ�ť����
	int vSpace = (w - textwidth(str)) / 2;
	int hSpace = (h - textheight(str)) / 2;
	outtextxy(x + vSpace, y + hSpace, str);

	// �ж��Ƿ���
	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		msg.message = 0;
		return true; // ��ť�����
	}
	return false; // ��ťδ�����
}

void gameManager::drawText(int x, int y, int size, const char* text) {
	// �������ִ�С
	settextstyle(size, 0, "΢���ź�");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, text);
}


void gameManager::drawSkinPage(int& selectedSkin) {
	while (true) {
		peekmessage(&msg, EX_MOUSE);
		BeginBatchDraw();
		cleardevice();  // �����Ļ��׼�����»���
		//setbkcolor(WHITE);
		putimage(0, 0, &back_img[6]);
		settextcolor(BLACK);
		BeginBatchDraw();

		// ����Ƥ���� BUFF ����
		rectangle(270, 150, 470, 300);  // ̹��Ƥ�������
		outtextxy(320, 225, "̹��Ƥ��");

		//rectangle(520, 200, 600, 240);  // BUFF �����
		//outtextxy(540, 210, "BUFF");
		// ����ѡ�е�Ƥ��ͼƬ
		switch (selectedSkin) {
		case 0:
			putimage(270, 150, &skin[0]);  // ��ʾƤ��1ͼƬ
			break;
		case 1:
			putimage(270, 150, &skin[1]);  // ��ʾƤ��2ͼƬ
			break;
		case 2:
			putimage(270, 150, &skin[2]);  // ��ʾƤ��3ͼƬ
			break;
		default:
			break;
		}

		// ʹ�� button �������ư�ť�������
		if (button(520, 200, 100, 50, "BUFF")) {
			flag = BUFF;
			return;
		}
		if (button(150, 400, 100, 50, "Ƥ��1")) {
			selectedSkin = 0;  // ѡ��Ƥ��1
		}

		if (button(325, 400, 100, 50, "Ƥ��2")) {
			selectedSkin = 1;  // ѡ��Ƥ��2
		}

		if (button(500, 400, 100, 50, "Ƥ��3")) {
			selectedSkin = 2;  // ѡ��Ƥ��3
		}

		if (button(650, 500, 50, 50, "����")) {
			// ���ذ�ť�������ִ�з��ز���
			flag = MENU;
			return;
		}

		// ˢ����Ļ��ʾ
		//FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}

void gameManager::menu()
{
	while (true)
	{
		peekmessage(&msg, EX_MOUSE);       //���������Ϣ
		BeginBatchDraw();
		cleardevice();

		putimage(0, 0, &back_img[1]);

		if (button(350, 25, 100, 70, "������Ϸ"))
			flag = PASSCHOOSE;
		if (button(350, 105, 100, 70, "����ָ��"))
			flag = GUIDE;
		if (button(350, 185, 100, 70, "�������а�"))
			flag = RANKLIST;
		if (button(350, 265, 100, 70, "װ���"))
			flag = CHANGESTYLE;
		if (button(350, 345, 100, 70, "����"))
			flag = SET;
		if (button(350, 425, 100, 70, "�Ŷӽ���"))
			flag = MEMBERINFO;
		if (button(350, 505, 100, 70, "�˳���Ϸ"))
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
		if (button(27, 16, 50, 33, "����"))
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
		if (button(650, 550, 150, 50, "�������˵�")) // ��������"�������˵�"��ť
		{
			flag = MENU; // ���ñ�־λΪMENU����ʾ�������˵�
			return; // �������˵�
		}

		//FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };//ʹ��ÿ�ε����ťֻ����Ӧһ��
	}
}
void gameManager::buff()
{
	while (true) {
		peekmessage(&msg, EX_MOUSE);

		BeginBatchDraw();
		setbkcolor(WHITE);
		settextcolor(BLACK);
		cleardevice();  // �����Ļ��׼�����»���


		// ����Ƥ���� BUFF ����
		// ����ѡ�е�Ƥ��ͼƬ
		switch (selectedBuff) {
		case 0:
			putimage(270, 150, &show_buff_img[0]);  // ��ʾBuff1ͼƬ
			break;
		case 1:
			putimage(270, 150, &show_buff_img[1]);  // ��ʾBuff2ͼƬ
			break;
		case 2:
			putimage(270, 150, &show_buff_img[2]);  // ��ʾBuff3ͼƬ
			break;
		default:
			break;
		}

		// ʹ�� button �������ư�ť�������
		if (button(150, 400, 100, 50, "Buff1")) {
			selectedBuff = 0;  // ѡ��Buff1
		}
		if (button(325, 400, 100, 50, "Buff2")) {
			selectedBuff = 1;  // ѡ��Buff2
		}
		if (button(500, 400, 100, 50, "Buff3")) {
			selectedBuff = 2;  // ѡ��Buff3
		}
		if (button(650, 500, 150, 50, "�������˵�")) {
			// ���ذ�ť�������ִ�з��ز���
			cout << "���ذ�ť�����" << endl;
			flag = MENU; //�Ƿ��ص�ѡ��Ƥ��ҳ��Ļ���һ��
			return;
		}

		// ˢ����Ļ��ʾ
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
void gameManager::memberInfor()
{
	while (true) {
		BeginBatchDraw(); // ��ʼ������ͼ����߻�ͼЧ��
		//setbkcolor(WHITE); // ���ñ�����ɫΪ��ɫ
		cleardevice(); // ����豸����
		putimage(0, 0, &back_img[7]);

		//�Ŷӽ��ܣ�
		int titleWidth = 20, titleHeight = 33;
		settextstyle(titleHeight, titleWidth, "����");
		settextcolor(BLACK);
		int bgi_x = 50, bgi_y = 40;
		outtextxy(bgi_x, bgi_y, "�Ŷӽ��ܣ�");
		int cx = bgi_x, cy = bgi_y + 5 + titleHeight; //���ݿ�ʼ������
		int contentWidth = 13, contentHeight = 21;
		settextstyle(contentHeight, contentWidth, "����");
		settextcolor(GREEN);
		string contents[9] = {
			"�鳤_���٣��������а���棬�Ŷӽ��ܽ��棬����ָ�Ͻ���",
			"���鳤_ʮ�ʮ���Ϸ�ӵ������ý��棬�Ŷӽ���",
			"������1_��˧�������ƣ�����ͼ��ƣ���Ϸ�ڵ������߼�",
			"������2_Ƥ������Ϸ���߼����������޸ģ�����ѵ��bug",
			"������3_��Ȼ���ף���Ϸ�ؿ���ͼ�Լ���ʹ�õ��ߺ�ͼƬ�Ļ���",
			"��Ʒ����1_���ƣ����ƣ�����ԭ��ͼ����¼ע�ᡢ�����������",
			"��Ʒ����2_һ֦�㣺�����ĵ����з�̹��",
			"�ල��_GO����ť�Ļ��� ���˵�������ָ�Ͻ���",
			"��Ϣ��_XY��"
		};
		for (int i = 0; i < 9; i++)
		{
			outtextxy(cx, cy, contents[i].c_str());
			cy += contentHeight + 10;
		}

		// "�������˵�"��ť��ʵ��
		if (peekmessage(&msg, EX_MOUSE)) {} // ��������Ϣ
		if (button(650, 550, 100, 50, "�������˵�")) // ��������"�������˵�"��ť
		{
			//cleardevice(); // �����������ǰ��������
			flag = MENU; // ���ñ�־λΪMENU����ʾ�������˵�
			return; // �������˵�
		}

		FlushBatchDraw(); // ˢ��������ͼ����
		EndBatchDraw(); // ����������ͼ
		msg.message = { 0 }; // ������Ϣ����
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

		// ����û����� ESC ���˳�����
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 27) break; // ���� ESC ���˳�����
		}
	}
}
void gameManager::guide()
{
	while (true) {
		BeginBatchDraw(); // ��ʼ������ͼ����߻�ͼЧ��
		//setbkcolor(WHITE); // ���ñ�����ɫΪ��ɫ
		cleardevice(); // ����豸����
		putimage(0, 0, &back_img[3]);
		//��������
		int titleWidth = 20, titleHeight = 33; //my_titile���ֵĿ�͸�
		settextstyle(titleHeight, titleWidth, "����"); //���ñ���������ʽ
		settextcolor(BLACK); //����������ɫ
		string my_title = "��������:"; //����
		int title_x = 50, title_y = 50; //my_title��ʼ��x,y����
		outtextxy(title_x, title_y, my_title.c_str());
		//������������
		string introduce1 = "WASD�ֱ��ʾ�������ң�J��ʾ������Esc����ʾ��ͣ/�ص���Ϸ";
		int content_x = title_x, content_y = title_y + titleHeight;
		int contentWidth = 13, contentHeight = 21; //�������ֵĿ�͸�
		settextstyle(contentHeight, contentWidth, "����"); //���ñ���������ʽ
		settextcolor(GREEN);
		outtextxy(content_x, content_y, introduce1.c_str());

		//Buff����
		my_title = "Buff����:";
		title_y += titleWidth + textheight(introduce1.c_str()) + 70;
		settextstyle(titleHeight, titleWidth, "����"); //���ñ���������ʽ
		settextcolor(BLACK); //����������ɫ
		outtextxy(title_x, title_y, my_title.c_str());
		string introduce2 = "��Ҵ�����ͬ�Ĳ������Ի�ò�ͬ��BuffЧ����";
		string introduce3 = "ը�����ӵ�����˺����";
		string introduce4 = "���֣�10���ڲ���";
		content_x = title_x, content_y = title_y + titleHeight;
		settextstyle(contentHeight, contentWidth, "����"); //���ñ���������ʽ
		settextcolor(GREEN); //����������ɫ
		outtextxy(content_x, content_y, introduce2.c_str()); //��ӡ��һ��
		content_y += contentHeight;
		outtextxy(content_x, content_y, introduce3.c_str());//��ӡ�ڶ���
		content_y += contentHeight;
		outtextxy(content_x, content_y, introduce4.c_str()); //��ӡ������
		content_y += contentHeight + 70;
		outtextxy(content_x, content_y, "δ��������������ǻ��������"); //��ӡ������

		// "�������˵�"��ť��ʵ��
		if (peekmessage(&msg, EX_MOUSE)) {} // ��������Ϣ
		if (button(650, 550, 100, 50, "�������˵�")) // ��������"�������˵�"��ť
		{
			flag = MENU; // ���ñ�־λΪMENU����ʾ�������˵�
			return; // �������˵�
		}

		FlushBatchDraw(); // ˢ��������ͼ����
		EndBatchDraw(); // ����������ͼ
		msg.message = { 0 }; // ������Ϣ����
	}
}
void gameManager::loadSources()
{
	loadimage(&skin[0], "ͼƬ��Դ/tankStyle1.jpg", 200, 200); // ����Ƥ��1ͼƬ
	loadimage(&skin[1], "ͼƬ��Դ/tankStyle2.jpg"); // ����Ƥ��2ͼƬ
	loadimage(&skin[2], "ͼƬ��Դ/tankStyle3.jpg"); // ����Ƥ��3ͼƬ

	loadimage(&my_tank_img[0][0], "ͼƬ��Դ/tankStyle1_left.jpg", 40, 40);
	loadimage(&my_tank_img[0][1], "ͼƬ��Դ/tankStyle1_right.jpg", 40, 40);
	loadimage(&my_tank_img[0][2], "ͼƬ��Դ/tankStyle1.jpg", 40, 40);
	loadimage(&my_tank_img[0][3], "ͼƬ��Դ/tankStyle1_down.jpg", 40, 40);

	loadimage(&my_tank_img[1][0], "ͼƬ��Դ/tankStyle2_left.jpg", 40, 40);
	loadimage(&my_tank_img[1][1], "ͼƬ��Դ/tankStyle2_right.jpg", 40, 40);
	loadimage(&my_tank_img[1][2], "ͼƬ��Դ/tankStyle2.jpg", 40, 40);
	loadimage(&my_tank_img[1][3], "ͼƬ��Դ/tankStyle2_down.jpg", 40, 40);

	loadimage(&my_tank_img[2][0], "ͼƬ��Դ/tankStyle3_left.jpg", 40, 40);
	loadimage(&my_tank_img[2][1], "ͼƬ��Դ/tankStyle3_right.jpg", 40, 40);
	loadimage(&my_tank_img[2][2], "ͼƬ��Դ/tankStyle3.jpg", 40, 40);
	loadimage(&my_tank_img[2][3], "ͼƬ��Դ/tankStyle3_down.jpg", 40, 40);

	loadimage(&enemy_tank_img[0][0], "ͼƬ��Դ/�з�̹����.jpg", 40, 40);
	loadimage(&enemy_tank_img[0][1], "ͼƬ��Դ/�з�̹����.jpg", 40, 40);
	loadimage(&enemy_tank_img[0][2], "ͼƬ��Դ/�з�̹����.jpg", 40, 40);
	loadimage(&enemy_tank_img[0][3], "ͼƬ��Դ/�з�̹����.jpg", 40, 40);

	loadimage(&enemy_tank_img[1][0], "ͼƬ��Դ/�ҷ�̹����.jpg", 40, 40);
	loadimage(&enemy_tank_img[1][1], "ͼƬ��Դ/�ҷ�̹����.jpg", 40, 40);
	loadimage(&enemy_tank_img[1][2], "ͼƬ��Դ/�ҷ�̹����.jpg", 40, 40);
	loadimage(&enemy_tank_img[1][3], "ͼƬ��Դ/�ҷ�̹����.jpg", 40, 40);

	loadimage(&buff_img[0], "ͼƬ��Դ/����.jpg", 40, 40);
	loadimage(&buff_img[1], "ͼƬ��Դ/����.jpg", 40, 40);
	loadimage(&buff_img[2], "ͼƬ��Դ/����.jpg", 40, 40);
	loadimage(&bullet_img[0], "ͼƬ��Դ/�ӵ�.jpg", 4, 4);
	loadimage(&bullet_img[1], "ͼƬ��Դ/�ӵ�.jpg", 20, 20);
	loadimage(&woodWall_img, "ͼƬ��Դ/שǽ.jpg", 40, 40);
	loadimage(&stoneWall_img, "ͼƬ��Դ/ʯǽ.jpg", 40, 40);
	loadimage(&base_img, "ͼƬ��Դ/����.jpg", 40, 40);
	loadimage(&bg, "ͼƬ��Դ/̹�˴�ս2.jpg", 800, 600);
	loadimage(&img_set, "ͼƬ��Դ/����.jpg", 800, 600);

	loadimage(&show_buff_img[0], "ͼƬ��Դ/����.jpg", 200, 200);
	loadimage(&show_buff_img[1], "ͼƬ��Դ/����.jpg", 200, 200);
	loadimage(&show_buff_img[2], "ͼƬ��Դ/����.jpg", 200, 200);

	loadimage(&pass_img[0], "ͼƬ��Դ/�ؿ�-1.jpg", 100, 100);
	loadimage(&pass_img[1], "ͼƬ��Դ/�ؿ�-2.jpg", 100, 100);
	loadimage(&pass_img[2], "ͼƬ��Դ/�ؿ�-3.jpg", 100, 100);
	loadimage(&pass_img[3], "ͼƬ��Դ/�ؿ�-4.jpg", 100, 100);
	loadimage(&pass_img[4], "ͼƬ��Դ/�ؿ�-5.jpg", 100, 100);

	loadimage(&back_img[0], "ͼƬ��Դ/��¼ע�ᱳ��ͼ.jpg", 800, 600);
	loadimage(&back_img[1], "ͼƬ��Դ/���˵�����ͼ2.jpg", 800, 600);
	loadimage(&back_img[2], "ͼƬ��Դ/���а񱳾�ͼ.jpg", 800, 600);
	loadimage(&back_img[3], "ͼƬ��Դ/����ָ�ϱ���ͼ.jpg", 800, 600);
	loadimage(&back_img[4], "ͼƬ��Դ/ʤ��ʧ�ܱ���ͼ.jpg", 800, 600);
	loadimage(&back_img[5], "ͼƬ��Դ/ѡ�ؽ��汳��ͼ.jpg", 800, 600);
	loadimage(&back_img[6], "ͼƬ��Դ/װ��ⱳ��ͼ.jpg", 800, 600);
	loadimage(&back_img[7], "ͼƬ��Դ/�Ŷӽ��ܱ���ͼ.jpg", 800, 600);

	mciSendString("open AllAboutThatGuitar.mp3", 0, 0, 0);
	//mciSendString("play AllAboutThatGuitar.mp3", 0, 0, 0);
	readFile("userInfo.txt");

}

void gameManager::set() {
	int sliderX = 200;//���飨��ʼ��λ��
	static double volume = 50;//�����ٷְٱ�
	bool lbutton_down = false;//��ť�Ƿ���

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
					cout << "���˵�" << endl;
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

//���������ĺ���
void gameManager::setVolume(double volume_persent, const string& musicPath) {
	// ����������Χ�� 0 �� 100 ֮��
	if (volume_persent < 0) volume_persent = 0;
	if (volume_persent > 1) volume_persent = 1;
	// ����Ƶ�豸
	mciSendString("open new type waveaudio alias myaudio", NULL, 0, NULL);
	// ��������
	string command = "setaudio " + musicPath + " volume to " + to_string(static_cast<int>(volume_persent * 1000));
	mciSendString(command.data(), NULL, 0, NULL);
	// �ر���Ƶ�豸
	string s = "play " + musicPath + " repeat";
	mciSendString(s.data(), NULL, 0, NULL);
	//mciSendString("stop myaudio", NULL, 0, NULL);
}

// ��ӡ��¼����ĺ���
void gameManager::logIn()
{
	char username[30] = ""; // �����û������30�ַ�
	char password[30] = ""; // �����������30�ַ�
	int userIndex = 0;
	int passIndex = 0;
	bool isPasswordInput = false; // �������ֵ�ǰ�������û�����������
	bool isTypingUsername = true; // ��ǰ�Ƿ��������û���
	bool haveUser = true;//�ж��Ƿ���ڸ��û�
	bool passwordRight = true;//�ж��û�����������Ƿ���ȷ
	// �������������
	int usernameInputX = 260, usernameInputY = 200;
	int passwordInputX = 260, passwordInputY = 250;
	int inputWidth = 300, inputHeight = 30;

	while (true)
	{
		if (peekmessage(&msg))
		{
			// ����������¼�
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

			// ��������¼�
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isTypingUsername) // �û�������
				{
					if (ch == '\b' && userIndex > 0) // �˸��
					{
						username[--userIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && userIndex < 29) // ����ʾ�ַ�
					{
						username[userIndex++] = ch;
						username[userIndex] = '\0';
					}
				}
				else // ��������
				{
					if (ch == '\b' && passIndex > 0) // �˸��
					{
						password[--passIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && passIndex < 29) // ����ʾ�ַ�
					{
						password[passIndex++] = ch;
						password[passIndex] = '\0';
					}
				}
			}
		}


		// ��ʼ����
		BeginBatchDraw();
		cleardevice(); // ����
		//���Ʊ���ͼƬ
		putimage(0, 0, &back_img[0]);
		//��������
		settextcolor(RGB(164, 141, 45));
		//setbkcolor(WHITE);
		settextstyle(30, 0, "΢���ź�");
		drawText(160, 200, 30, "�˺ţ�");
		drawText(160, 250, 30, "���룺");

		// ���������
		setfillcolor(RGB(231, 232, 233));
		fillrectangle(usernameInputX, usernameInputY, usernameInputX + inputWidth, usernameInputY + inputHeight);
		fillrectangle(passwordInputX, passwordInputY, passwordInputX + inputWidth, passwordInputY + inputHeight);

		// ��ʾʵʱ������˺ź����루�������Ǻ���ʾ��
		drawText(usernameInputX, usernameInputY, 30, username);
		drawText(passwordInputX, passwordInputY, 30, std::string(passIndex, '*').c_str());

		// ��ť�߼�
		if (button(300, 320, 200, 60, "��¼"))
		{
			//����˺������Ƿ�ƥ��
			for (auto& user : users)
			{
				if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.password.c_str(), password) == 0)
				{
					userName = username;
					flag = MENU;  // ���������¼��ת�����˵�
					cleardevice(); // ����
					haveUser = true;
					passwordRight = true;
					return;
				}
				else if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.password.c_str(), password) != 0)
				{
					//��ʾ���벻��ȷ����Ҫ������������
					haveUser = true;
					passwordRight = false;
					break;
				}
				else
					haveUser = false;
			}
		}
		if(!passwordRight)
			drawText(260, 290, 25, "�������");
		if (!haveUser)//���û�и��û�����ʾ�û�������
			drawText(260, 290, 25, "�û�������");
		if (button(2, 2, 100, 50, "����"))
		{
			flag = SET;
			cleardevice(); // ����
			return;
		}
		if (button(700, 0, 98, 50, "�˳�"))
		{
			closegraph(); // �ر�ͼ�δ���
			exit(0);
			return; // ��������
		}
		if (button(620, 420, 100, 40, "��������"))
		{
			flag = FINDPASSWORD;
			cleardevice(); // ����
			return;
		}
		if (button(140, 420, 60, 40, "ע��"))
		{
			flag = SIGNIN; // ע�����
			cleardevice(); // ����
			return;
		}

		//FlushBatchDraw();
		EndBatchDraw();
	}
}


// ��ӡע�����ĺ���
void gameManager::signIn()
{
	char username[30] = ""; // �����û������30�ַ�
	char password[30] = ""; // �����������30�ַ�
	char email[30] = "";//����
	int userIndex = 0;
	int passIndex = 0;
	int emailIndex = 0;
	bool isInputUsernam = false;
	bool isInputPassword = false;
	bool isInputEmail = false;
	bool haveUser = false;
	bool allFilled = true;//�ж��Ƿ���û����д����Ϣ
	//�������������
	int usernameInputX = 280, usernameInputY = 160;
	int passwordInputX = 280, passwordInputY = 200;
	int emailInputX = 280, emailInputY = 240;
	int inputWidth = 300, inputHeight = 30;
	while (true)
	{
		if (peekmessage(&msg))
		{
			// ����������¼�
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

			// ��������¼�
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isInputUsernam) // �û�������
				{
					if (ch == '\b' && userIndex > 0) // �˸��
					{
						username[--userIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && userIndex < 29) // ����ʾ�ַ�
					{
						username[userIndex++] = ch;
						username[userIndex] = '\0';
					}
				}
				else if(isInputPassword)// ��������
				{
					if (ch == '\b' && passIndex > 0) // �˸��
					{
						password[--passIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && passIndex < 29) // ����ʾ�ַ�
					{
						password[passIndex++] = ch;
						password[passIndex] = '\0';
					}
				}
				else if (isInputEmail)
				{
					if (ch == '\b' && emailIndex > 0) // �˸��
					{
						email[--emailIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && emailIndex < 29) // ����ʾ�ַ�
					{
						email[emailIndex++] = ch;
						email[emailIndex] = '\0';
					}
				}
			}
		}
		//��ʼ����
		BeginBatchDraw();//ʹ��˫���壬��ֹ����
		cleardevice();
		putimage(0, 0, &back_img[0]);
		settextcolor(RGB(164, 141, 45));
		setbkcolor(WHITE);
		settextstyle(30, 0, "����");
		drawText(180, 160, 35, "�˺ţ�");
		drawText(180, 200, 35, "���룺");
		drawText(180, 240, 35, "���䣺");   //�˴������˵�����������

		//���������
		setfillcolor(RGB(231, 232, 233));
		fillrectangle(usernameInputX, usernameInputY, usernameInputX + inputWidth, usernameInputY + inputHeight);
		fillrectangle(passwordInputX, passwordInputY, passwordInputX + inputWidth, passwordInputY + inputHeight);
		fillrectangle(emailInputX, emailInputY, emailInputX + inputWidth, emailInputY + inputHeight);

		// ��ʾʵʱ������˺ź����루�������Ǻ���ʾ��
		drawText(usernameInputX, usernameInputY, 30, username);
		drawText(passwordInputX, passwordInputY, 30, password);
		drawText(emailInputX, emailInputY, 30, email);
		// ע�����İ�ť
		if (button(300, 320, 200, 60, "����"))
		{
			
			if (strcmp(username,"")==0 || strcmp(password, "") == 0 || strcmp(email, "") == 0)
			{
				allFilled = false;
			}
			else
			{
				//�ȼ���û��Ƿ��Ѿ�����
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
					insertNewUser(u);//��ӵ�users����
					writeFile("userInfo.txt");//�����ļ�����
					flag = LOGIN;	// ���ص�¼����
					return;
				}
					
				
			}
			
		}
		if(haveUser)
			drawText(280, 280, 25, "�û��Ѵ���");;
		if (!allFilled)
			drawText(280, 280, 25, "�뽫��Ϣ��д����");
		if (button(620, 420, 100, 40, "����"))
		{
			flag = LOGIN;	// ���ص�¼����
			return;
		}
		if (button(2, 2, 100, 50, "����"))
		{
			flag = SET;			// �л�������״̬
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
// ��ӡ�����������1�ĺ���
void gameManager::forgetPassword()
{
	char username[30] = ""; // �����û������30�ַ�
	char email[30] = "";
	int userIndex = 0;
	int emailIndex = 0;
	bool isInputName = false; 
	bool isInputEmail = false; 
	bool haveUser = true;
	bool emailRight = true;

	// �������������
	int usernameInputX = 260, usernameInputY = 200;
	int emailInputX = 260, emailInputY = 250;
	int inputWidth = 300, inputHeight = 30;
	while (true)
	{
		if (peekmessage(&msg))
		{
			// ����������¼�
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

			// ��������¼�
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isInputName) // �û�������
				{
					if (ch == '\b' && userIndex > 0) // �˸��
					{
						username[--userIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && userIndex < 29) // ����ʾ�ַ�
					{
						username[userIndex++] = ch;
						username[userIndex] = '\0';
					}
				}
				else if(isInputEmail)// ��������
				{
					if (ch == '\b' && emailIndex > 0) // �˸��
					{
						email[--emailIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && emailIndex < 29) // ����ʾ�ַ�
					{
						email[emailIndex++] = ch;
						email[emailIndex] = '\0';
					}
				}
			}
		}
		BeginBatchDraw();//ʹ��˫���壬��ֹ����
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "����");
		setbkcolor(WHITE);
		cleardevice();
		putimage(0, 0, &back_img[0]);
		BeginBatchDraw(); // ��ʼ������ͼ����߻�ͼЧ��
		drawText(160, 200, 30, "�˺ţ�");
		drawText(160, 250, 30, "���䣺");


		// ���������
		setfillcolor(RGB(231, 232, 233));
		solidrectangle(usernameInputX, usernameInputY, usernameInputX + inputWidth, usernameInputY + inputHeight);
		solidrectangle(emailInputX, emailInputY, emailInputX + inputWidth, emailInputY + inputHeight);

		// ��ʾʵʱ������˺ź�����
		drawText(usernameInputX, usernameInputY, 30, username);
		drawText(emailInputX, emailInputY, 30, email);
		// �һ������һ���İ�ť
		if (button(300, 320, 200, 60, "�һ�"))
		{
			
			for (auto& user : users)
			{
				if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.email.c_str(), email) == 0)//�˺�����ƥ��
				{
					userName = username;
					haveUser = true;
					flag = FINDPASSWORD2; // ����˺ź�������ƥ��Ļ��л����һ�����ڶ���
					return;
				}
				else if (strcmp(user.name.c_str(), username) == 0 && strcmp(user.email.c_str(), email) != 0)//���䲻��
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
			drawText(260, 290, 25, "�û�������");
		if(!emailRight)
			drawText(260, 290, 25, "���䲻����");
		if (button(620, 420, 100, 40, "����"))
		{
			flag = LOGIN; // ���ص�¼����
			return;
		}
		if (button(2, 2, 100, 50, "����"))
		{
			flag = SET;			// �л�������״̬
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}
// ��ӡ�����������2�ĺ���
void gameManager::forgetPassword2()
{
	char password[30] = ""; // �����������30�ַ�
	char password_sure[30] = ""; 
	int passIndex = 0;
	int pass_sureIndex = 0;
	bool isPasswordInput = false; 
	bool isPass_sureInput= false; 
	bool twoPasswordSame = true;//�ж��������������Ƿ�һ��

	// �������������
	int passwordInputX = 260, passwordInputY = 200;
	int pass_sureInputX = 260, pass_sureInputY = 250;
	int inputWidth = 300, inputHeight = 30;
	while (true)
	{
		if (peekmessage(&msg))
		{
			// ����������¼�
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

			// ��������¼�
			if (msg.message == WM_CHAR)
			{
				char ch = msg.ch;
				if (isPasswordInput) // ��������
				{
					if (ch == '\b' && passIndex > 0) // �˸��
					{
						password[--passIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && passIndex < 29) // ����ʾ�ַ�
					{
						password[passIndex++] = ch;
						password[passIndex] = '\0';
					}
				}
				else if(isPass_sureInput)// ȷ����������
				{
					if (ch == '\b' && pass_sureIndex > 0) // �˸��
					{
						password_sure[--pass_sureIndex] = '\0';
					}
					else if (ch >= 32 && ch <= 126 && pass_sureIndex < 29) // ����ʾ�ַ�
					{
						password_sure[pass_sureIndex++] = ch;
						password_sure[pass_sureIndex] = '\0';
					}
				}
			}
		}
		BeginBatchDraw();//ʹ��˫���壬��ֹ����
		settextcolor(RGB(164, 141, 45));
		settextstyle(30, 0, "����");
		setbkcolor(WHITE);
		cleardevice();
		putimage(0, 0, &back_img[0]);
		drawText(300, 80, 40, "��������������");
		drawText(160, 200, 30, "�����룺");
		drawText(160, 250, 30, "ȷ�����룺");

		// ���������
		setfillcolor(RGB(231, 232, 233));
		solidrectangle(passwordInputX, passwordInputY, passwordInputX + inputWidth, passwordInputY + inputHeight);
		solidrectangle(pass_sureInputX, pass_sureInputY, pass_sureInputX + inputWidth, pass_sureInputY + inputHeight);

		// ��ʾʵʱ����������ȷ�����루�������Ǻ���ʾ��
		drawText(passwordInputX, passwordInputY, 30, std::string(passIndex, '*').c_str());
		drawText(pass_sureInputX, pass_sureInputY, 30, std::string(pass_sureIndex, '*').c_str());
		// �һ�����ڶ����İ�ť
		if (button(300, 320, 200, 60, "ȷ��"))
		{
			for (auto& user : users)
			{
				if (strcmp(user.name.c_str(),userName.c_str())==0 && strcmp(password, password_sure) == 0)
				{
					twoPasswordSame = true;
					user.password = string(password);
					writeFile("userInfo.txt");
					flag = LOGIN; // ���ص�¼����
					return;
				}
				else
				{
					twoPasswordSame = false;
				}
			}
			
		}
		if (!twoPasswordSame)
			drawText(260, 290, 25, "�����������벻һ��");
		if (button(620, 420, 100, 40, "����"))
		{
			flag = FINDPASSWORD; // �������������һ������
			return;
		}
		if (button(2, 2, 100, 50, "����"))
		{
			flag = SET;			// �л�������״̬
			return;
		}
		FlushBatchDraw();
		EndBatchDraw();
		msg.message = { 0 };
	}
}

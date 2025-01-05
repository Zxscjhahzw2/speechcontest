#include<iostream>
using namespace std;
#include"speechmanager.h"


int main() {
	//创建管理类对象
	SpeechManager speech;
	int choice;

	//for (map<int, Speaker>::iterator it = speech.m_speaker.begin(); it != speech.m_speaker.end(); it++) {

	//	cout << "选手编号：" << it->first << "姓名：" << it->second.m_name << "成绩：" << it->second.m_score[0] << endl;
	//}

	while (1)
	{
		speech.show_menu();
		cout << "请输入你的选择:" << endl;
		cin >> choice;
		switch (choice)
		{
			case 1://开始比赛
				speech.startspeech();
				break;
			case 2://查看往届记录
				speech.loadRecord();
				break;
			case 3://清空比赛记录
				speech.clear();
				break;
			case 4:
				break;
			case 0://推出系统
				speech.exit_menu();
				break;
			default:
				system("cls");//清屏
				break;
		}
		system("pause");
		system("cls");//清屏

	}






	system("pause");
	return 0;
}
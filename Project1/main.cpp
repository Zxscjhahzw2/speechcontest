#include<iostream>
using namespace std;
#include"speechmanager.h"


int main() {
	//�������������
	SpeechManager speech;
	int choice;

	//for (map<int, Speaker>::iterator it = speech.m_speaker.begin(); it != speech.m_speaker.end(); it++) {

	//	cout << "ѡ�ֱ�ţ�" << it->first << "������" << it->second.m_name << "�ɼ���" << it->second.m_score[0] << endl;
	//}

	while (1)
	{
		speech.show_menu();
		cout << "���������ѡ��:" << endl;
		cin >> choice;
		switch (choice)
		{
			case 1://��ʼ����
				speech.startspeech();
				break;
			case 2://�鿴�����¼
				speech.loadRecord();
				break;
			case 3://��ձ�����¼
				speech.clear();
				break;
			case 4:
				break;
			case 0://�Ƴ�ϵͳ
				speech.exit_menu();
				break;
			default:
				system("cls");//����
				break;
		}
		system("pause");
		system("cls");//����

	}






	system("pause");
	return 0;
}
#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<ctime>
#include<functional>
#include<fstream>

//����ݽ�������
class SpeechManager {

public:

	//���캯��
	SpeechManager();

	//��ʾ�˵�
	void show_menu();

	//�˳��˵�
	void exit_menu();

	//��������
	~SpeechManager();

	//��ʼ������������
	void init_speech();

	//����12��ѡ��
	void creat12();
	
	//����ȫ���̿��ƺ���
	void startspeech();

	//��ǩ����
	void speechdraw();

	//����
	void contest();

	//��ʾ�÷�
	void showscore();

	//����
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool file_isempty;

	//��������¼
	map<int, vector<string>>m_record;

	//���
	void clear();

	//��Ա����
	//�����һ��ѡ�ֱ������
	vector<int>v1;
	//��һ�ֽ���ѡ�ֱ��
	vector<int>v2;
	//ʤ��ǰ����ѡ�ֱ������
	vector<int>vvictory;
	//��ű���Լ�����ѡ������
	map<int, Speaker>m_speaker;
	//��ű�������
	int m_index;
	
};
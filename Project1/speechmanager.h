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

//设计演讲管理类
class SpeechManager {

public:

	//构造函数
	SpeechManager();

	//显示菜单
	void show_menu();

	//退出菜单
	void exit_menu();

	//析构函数
	~SpeechManager();

	//初始化容器和属性
	void init_speech();

	//创建12名选手
	void creat12();
	
	//比赛全流程控制函数
	void startspeech();

	//抽签函数
	void speechdraw();

	//比赛
	void contest();

	//显示得分
	void showscore();

	//保存
	void saveRecord();

	//读取记录
	void loadRecord();

	//判断文件是否为空
	bool file_isempty;

	//存放往届记录
	map<int, vector<string>>m_record;

	//清空
	void clear();

	//成员属性
	//保存第一轮选手编号容器
	vector<int>v1;
	//第一轮晋级选手编号
	vector<int>v2;
	//胜出前三名选手编号容器
	vector<int>vvictory;
	//存放编号以及具体选手容器
	map<int, Speaker>m_speaker;
	//存放比赛论述
	int m_index;
	
};
#include"speechmanager.h"

//构造函数
SpeechManager::SpeechManager() {
	this->init_speech();
	this->creat12();
}

void SpeechManager::creat12() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++) {
		string name = "选手";
		name += nameseed[i];
		//创建具体选手
		Speaker speaker;
		speaker.m_name = name;

		for (int j = 0; j < 2; j++) {
			speaker.m_score[j] = 0;//两轮分数置为0
		}
		//创建选手编号添加到v1容器
		this->v1.push_back(i + 10001);
		//添加map
		this->m_speaker.insert(make_pair(i + 10001, speaker));
	}
}



//展示菜单
void SpeechManager::show_menu() {
	cout << "****************************************" << endl;
	cout << "***********欢迎参加演讲比赛*************" << endl;
	cout << "***********1.开始演讲比赛***************" << endl;
	cout << "***********2.查看往届记录***************" << endl;
	cout << "***********3.清空比赛记录***************" << endl;
	cout << "***********0.推出比赛程序***************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

//退出c菜单
void SpeechManager::exit_menu() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::init_speech() {
	this->v1.clear();
	this->v2.clear();
	this->vvictory.clear();
	this->m_speaker.clear();

	this->m_index = 1;
}

void SpeechManager::startspeech() {
	//第一轮比赛开始
	//1.抽签
	this->speechdraw();
	//2.比赛
	this->contest();
	//3.显示晋级结果
	this->showscore();
	//第二轮开始
	this->m_index++;
	//1.抽签
	speechdraw();
	//2.比赛
	contest();
	//3.显示最终结果
	showscore();
	//4.保存分数到文件
	this->saveRecord();

	cout << "比赛结束" << endl;
	system("pause");
	system("cls");

}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {

		this->file_isempty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {

		cout << "文件为空" << endl;
		this->file_isempty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->file_isempty = false;
	ifs.putback(ch);
	string data;

	while (ifs>>data)
	{
		//cout << data << endl;
		vector<string>v;//存放6个string字符串
		int pos = -1;//查到,
		int start = 0;
		int index = 0;
		while(true){
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}

				string temp = data.substr(start, pos - start);
				cout << temp << endl;
				v.push_back(temp);
				start = pos + 1;


		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++) {
		cout << it->first << "冠军编号：" << it->second[0] << "分数" << it->second[1] << endl;
	}
}

void SpeechManager::clear() {
	ofstream ofs("speech.csv", ios::trunc);
	ofs.close();
}


void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // 用输出的方式打开文件 -- 写文件

	// 将每个人数据写入到文件中
	for (vector<int>::iterator it = vvictory.begin(); it != vvictory.end(); it++)
	{
		ofs << *it << ","
			<< m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	// 关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;
}


void SpeechManager::showscore() {

	cout << "-------------第" << this->m_index << "轮晋级结果如下----------" << endl;
	vector<int>v;
	if (this->m_index == 1) {

		v = v2;
	}
	else
	{
		v = vvictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号：" << *it << "姓名:" << this->m_speaker[*it].m_name << "平均分为：" << m_speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_menu();
}

void SpeechManager::contest() {
	cout << "第" << this->m_index << "轮比赛正式开始" << endl;

	//分组容器创建
	multimap<double, int, greater<double>> groupscore;
	int num = 0;//用于记录人员个数，6人一组

	vector<int>v_src;//比赛选手容器
	if (this->m_index == 1) {
		v_src = v1;
	}
	else {
		v_src = v2;
	}
	srand(time(0));
	//遍历所有选手
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++) {
		//评委打分
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {

			double score = (rand() % 401 + 600 )/ 10.f;
			//cout << score<< " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();//去除高低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();//平均分

		//cout <<"编号："<<*it<<"姓名:"<<this->m_speaker[*it].m_name << "平均分为：" << avg << endl;
		//将平均分放入map
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		//将打分数据放到临时容器中
		groupscore.insert(make_pair(avg, *it));
		//每六人取前三
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次:" << endl;
			for (multimap<double, int>::iterator it = groupscore.begin(); it != groupscore.end(); it++) {
				cout << "编号：" << it->second << "姓名:" << this->m_speaker[it->second].m_name<< "平均分为：" << m_speaker[it->second].m_score[this->m_index-1] << endl;
			}

			 //取走前三
			int count = 0;
			for (multimap<double, int>::iterator it = groupscore.begin(); it != groupscore.end()&&count<3; it++,count++) {
				if (this->m_index == 1) {
					v2.push_back(it->second);
				}
				else {
					vvictory.push_back(it->second);
				}
			}

			groupscore.clear();
		}
	}

	cout << "第" << this->m_index << "轮比赛完成" << endl;
	system("pause");
}

void SpeechManager::speechdraw() {
	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	cout << "-------------------" << endl;
	cout << "抽签后顺序如下:" << endl;
	
	if (this->m_index == 1) {
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout<<*it<<" ";
		}
		cout << endl;
	}
	else {
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
	system("pause");
	cout << endl;
}

//析构函数
SpeechManager::~SpeechManager() {


}
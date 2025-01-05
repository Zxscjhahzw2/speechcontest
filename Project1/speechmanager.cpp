#include"speechmanager.h"

//���캯��
SpeechManager::SpeechManager() {
	this->init_speech();
	this->creat12();
}

void SpeechManager::creat12() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++) {
		string name = "ѡ��";
		name += nameseed[i];
		//��������ѡ��
		Speaker speaker;
		speaker.m_name = name;

		for (int j = 0; j < 2; j++) {
			speaker.m_score[j] = 0;//���ַ�����Ϊ0
		}
		//����ѡ�ֱ�����ӵ�v1����
		this->v1.push_back(i + 10001);
		//����map
		this->m_speaker.insert(make_pair(i + 10001, speaker));
	}
}



//չʾ�˵�
void SpeechManager::show_menu() {
	cout << "****************************************" << endl;
	cout << "***********��ӭ�μ��ݽ�����*************" << endl;
	cout << "***********1.��ʼ�ݽ�����***************" << endl;
	cout << "***********2.�鿴�����¼***************" << endl;
	cout << "***********3.��ձ�����¼***************" << endl;
	cout << "***********0.�Ƴ���������***************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

//�˳�c�˵�
void SpeechManager::exit_menu() {
	cout << "��ӭ�´�ʹ��" << endl;
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
	//��һ�ֱ�����ʼ
	//1.��ǩ
	this->speechdraw();
	//2.����
	this->contest();
	//3.��ʾ�������
	this->showscore();
	//�ڶ��ֿ�ʼ
	this->m_index++;
	//1.��ǩ
	speechdraw();
	//2.����
	contest();
	//3.��ʾ���ս��
	showscore();
	//4.����������ļ�
	this->saveRecord();

	cout << "��������" << endl;
	system("pause");
	system("cls");

}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {

		this->file_isempty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {

		cout << "�ļ�Ϊ��" << endl;
		this->file_isempty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->file_isempty = false;
	ifs.putback(ch);
	string data;

	while (ifs>>data)
	{
		//cout << data << endl;
		vector<string>v;//���6��string�ַ���
		int pos = -1;//�鵽,
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
		cout << it->first << "�ھ���ţ�" << it->second[0] << "����" << it->second[1] << endl;
	}
}

void SpeechManager::clear() {
	ofstream ofs("speech.csv", ios::trunc);
	ofs.close();
}


void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // ������ķ�ʽ���ļ� -- д�ļ�

	// ��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = vvictory.begin(); it != vvictory.end(); it++)
	{
		ofs << *it << ","
			<< m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	// �ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;
}


void SpeechManager::showscore() {

	cout << "-------------��" << this->m_index << "�ֽ����������----------" << endl;
	vector<int>v;
	if (this->m_index == 1) {

		v = v2;
	}
	else
	{
		v = vvictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "��ţ�" << *it << "����:" << this->m_speaker[*it].m_name << "ƽ����Ϊ��" << m_speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_menu();
}

void SpeechManager::contest() {
	cout << "��" << this->m_index << "�ֱ�����ʽ��ʼ" << endl;

	//������������
	multimap<double, int, greater<double>> groupscore;
	int num = 0;//���ڼ�¼��Ա������6��һ��

	vector<int>v_src;//����ѡ������
	if (this->m_index == 1) {
		v_src = v1;
	}
	else {
		v_src = v2;
	}
	srand(time(0));
	//��������ѡ��
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++) {
		//��ί���
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {

			double score = (rand() % 401 + 600 )/ 10.f;
			//cout << score<< " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();//ȥ���ߵͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();//ƽ����

		//cout <<"��ţ�"<<*it<<"����:"<<this->m_speaker[*it].m_name << "ƽ����Ϊ��" << avg << endl;
		//��ƽ���ַ���map
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		//��������ݷŵ���ʱ������
		groupscore.insert(make_pair(avg, *it));
		//ÿ����ȡǰ��
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С���������:" << endl;
			for (multimap<double, int>::iterator it = groupscore.begin(); it != groupscore.end(); it++) {
				cout << "��ţ�" << it->second << "����:" << this->m_speaker[it->second].m_name<< "ƽ����Ϊ��" << m_speaker[it->second].m_score[this->m_index-1] << endl;
			}

			 //ȡ��ǰ��
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

	cout << "��" << this->m_index << "�ֱ������" << endl;
	system("pause");
}

void SpeechManager::speechdraw() {
	cout << "��" << this->m_index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------" << endl;
	cout << "��ǩ��˳������:" << endl;
	
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

//��������
SpeechManager::~SpeechManager() {


}
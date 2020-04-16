#include <iostream>
#include <string>
#include <io.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std;

class HomeworkInfo
{
public:
	string _student_name;
	string _date;
};

class HomeworkStatistic
{
private:
	map<string, unordered_set<string>> _files_of_date;			 //关键字为日期
	unordered_map<string, unordered_set<string>> _files_of_name; //关键字为人名
	unordered_set<string> _nameinfo;
	unordered_map<string, int> _finished_date;
	unordered_map<string, int> _finished_student;

private:
	class AutoRelease
	{
	public:
		AutoRelease() {}
		~AutoRelease()
		{
			if (_pInstance)
				delete _pInstance;
		}
	};

private:
	HomeworkStatistic() {}
	~HomeworkStatistic() {}
	static HomeworkStatistic* _pInstance;
	static AutoRelease _ar;

public:
	unordered_set<string> _file_path;
	vector<string> _files_of_error;

public:
	static HomeworkStatistic* getInstance()
	{
		if (_pInstance == nullptr)
			_pInstance = new HomeworkStatistic();
		return _pInstance;
	}

public:
	HomeworkInfo preprogress(const char* filename);
	void show_file_path();
	void initialized_finished_student();
	void load_nameinfo();
	void load_file_path();
	bool islegal_date(string& date);			   //简单判断日期是否合法
	void files_read(string path, string exd = ""); //(path,exd): path->文件夹路径; exd->文件名后缀 （默认为""，读取所有后缀）
	void read();
	void show_error();
	void add_path();
	void clear_file(const string& filename);
	bool is_path_avaliable(const string& path);

public:
	void Show_Menu();
	void Show_Menu_0();

public:
	void func1_set_path();
	void func2_show_someone();
	void func3_show_someday();
	void func4_show_error();
	void func5_store();
	void func6_clear();
	void func0_exit();
};
HomeworkStatistic* HomeworkStatistic::_pInstance = nullptr;

void HomeworkStatistic::show_file_path()
{
	cout << "loading...\n";
	for (auto& x : _file_path)
	{
		cout << x << endl;
	}
	cout << endl;
}
void HomeworkStatistic::initialized_finished_student()
{
	for (auto& x : _nameinfo)
		_finished_student[x] = 0;
}
void HomeworkStatistic::load_nameinfo()
{
	_nameinfo = {
		"张浩宇", "谢剑峰", "汪寿安", "刘爽", "高成", "孟康", "元美金", "杨云钊", "唐希茁", "刘嘉林", "燕凯宏", "张晟源", "余中杰", "魏泽宇", "柏玮琦", "于艳帆", "赵昊", "王慧", "陈争光", "郑旭哲", "余俊达", "卢小金", "李建刚", "王宇宸", "王梦娇", "陈希磊", "罗梽轩", "谢坤", "蔡凌霄", "乔晶点", "汪冰青", "丁超", "王子淞", "蔡子超", "肖文彬", "王一焜", "张凡", "刘洋", "肖纵", "陈昊", "左晓倩", "毛自翔", "邓雄腾", "陈卓", "王月", "令初宇", "韩超", "吴克东", "张璇", "陈星怡", "李经纬", "王乐", "叶晶涌", "刘磊", "李智", "阮旭东", "乐鑫", "张馨支", "师与", "杨环宇", "刘宗林", "李俊强", "刁虹尹", "吴国民", "王政御", "张玮轩", "龚斌", "胡恒源", "刘坤", "陈威", "江俊杰", "陈彦龙", "吴昊坤", "陈思逸", "刘子涵", "杜杰", "申双美", "高颖", "李婉蓉" };
}
void HomeworkStatistic::load_file_path()
{
	string filename = "filepath.txt";
	ifstream ifs(filename);
	if (!ifs)
	{
		cerr << "ifstream open file " << filename << " error\n";
		return;
	}
	string line;
	while (getline(ifs, line), !ifs.eof())
	{
		//cout << name << endl;
		if(is_path_avaliable(line))
			_file_path.insert(line);
		else {
			cerr << "loading " << line << " failed!" << endl << "[errorinfo]path does not exist! " << endl << endl;
		}
	}
	ifs.close();
}
bool HomeworkStatistic::islegal_date(string& date) //简单判断日期是否合法
{
	if (date.size() != 8)
		return false;
	else if (date.substr(0, 4) != "2020" && date.substr(0, 4) != "2019")
		return false;
	return true;
}
HomeworkInfo HomeworkStatistic::preprogress(const char* filename)
{
	HomeworkInfo temp;
	for (size_t idx = 0; idx < strlen(filename); ++idx)
	{
		if (filename[idx] >= '0' && filename[idx] <= '9')
			temp._date.push_back(filename[idx]);
		else if ((int)filename[idx] < -1) //判断是否是汉字 汉字的编码值为0x80—0xFE，强制类型转换为int（补码）后小于-1
		{
			temp._student_name += filename[idx];
			temp._student_name += filename[++idx];
		}
	}
	return temp;
}
void HomeworkStatistic::files_read(string path, string exd) //(path,exd): path->文件夹路径; exd->文件名后缀 （默认为""，读取所有后缀）
{
	long hFile = 0;				 //文件句柄
	struct _finddata_t fileinfo; //文件信息 _finddata_t为存储文件信息的结构体
	string pathName, exdName;
	if (0 != strcmp(exd.c_str(), ""))
		exdName = "\\*." + exd;
	else
		exdName = "\\*";
	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR)) //目录
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					HomeworkStatistic::files_read(pathName.assign(path).append("\\").append(fileinfo.name), exd); //递归读取
			}
			else //file
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					HomeworkInfo temp = preprogress(fileinfo.name); //预处理
					if (islegal_date(temp._date))					//日期合法
					{
						_finished_date[temp._date] = 0;
						_files_of_date[temp._date].insert(temp._student_name);
						_files_of_name[temp._student_name].insert(temp._date);
					}
					else //日期非法
					{
						_files_of_error.push_back(fileinfo.name);
					}
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
void HomeworkStatistic::read()
{
	for (auto& x : _file_path)
		files_read(x);
}

void HomeworkStatistic::show_error()
{
	for (auto& x : _files_of_error)
	{
		cout << x << endl;
	}
}

void HomeworkStatistic::Show_Menu()
{
	cout << "****************************************************************" << endl;
	cout << "*********  Welcome to use homework statistics system!  *********" << endl;
	cout << "*****************  0.  exit system     *************************" << endl;
	cout << "*****************  1.  set file path   *************************" << endl;
	cout << "*****************  2.  show someone's  *************************" << endl;
	cout << "*****************  3.  show someday's  *************************" << endl;
	cout << "*****************  4.  show error info *************************" << endl;
	cout << "*****************  5.  record to local *************************" << endl;
	cout << "*****************  6.  clear file      *************************" << endl;
	cout << "****************************************************************" << endl;
	cout << endl;
}
void HomeworkStatistic::Show_Menu_0()
{
	cout << "****************************************************************" << endl;
	cout << "******************     set file path          ******************" << endl;
	cout << "******************  0.  return to main menu   ******************" << endl;
	cout << "******************  1.  add directory         ******************" << endl;
	cout << "******************  2.  clear                 ******************" << endl;
	cout << "****************************************************************" << endl
		<< endl;
}

void HomeworkStatistic::add_path()
{
	string path_temp;
	cout << "please input the path you want to traverse: "
		<< "Example  C:\\Users\\frank\\Desktop\\homework" << endl;
	cin >> path_temp;
	if (!is_path_avaliable(path_temp))
		cerr << "the specified directory doesn't exist. please try again!\n";
	else
	{
		ofstream fout("filepath.txt", std::ios::app);
		fout << path_temp << endl;
		cout << "add_directory done! \n\n";
		fout.close();
	}
}

void HomeworkStatistic::clear_file(const string& filename)
{
	fstream file(filename, ios::out);
	file.close();
}

bool HomeworkStatistic::is_path_avaliable(const string& path)
{
	struct _finddata_t fileinfo;
	if (_findfirst(path.c_str(), &fileinfo) == -1)
		return false;
	else
		return true;
}

//unordered_set<string> _file_path;
void HomeworkStatistic::func1_set_path()
{
	int choice = 0;
	while (true)
	{
		system("cls");
		Show_Menu_0();

		cout << "input your choice: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			return;
		case 1:
			add_path();
			break;
		case 2:
			clear_file("filepath.txt");
			_file_path.clear();
			cout << "clear_directory done\n\n";
			break;
		default:
			break;
		}
		system("pause");
	}
}

void HomeworkStatistic::func2_show_someone()
{
	unordered_set<string>::iterator iter1;
	unordered_map<string, unordered_set<string>>::iterator iter2;
	string name;
	while (true)
	{
		cout << "input a student name: ";
		while (cin >> name)
		{
			if (name == "exit")
				return;
			iter1 = _nameinfo.find(name);
			if (iter1 == _nameinfo.end())
				cout << "this student doesn't exist, please input again or input exit to leave" << endl;
			else
				break;
		}

		iter2 = _files_of_name.find(*iter1);
		cout << "student: " << name << endl;
		cout << "finished_dates are as follows: " << endl;
		if (iter2 != _files_of_name.end())
		{
			int count = 0;
			for (auto& x : iter2->second)
			{
				_finished_date[x] = 1;
				cout << x << "  ";
				++count;
				if (count % 8 == 0)
					cout << endl;
			}
			cout << endl;
		}
		cout << "unfinished_dates or unrecognized_dates are as follows: " << endl;
		int count = 0;
		for (auto& x : _finished_date)
		{
			if (x.second == 0)
			{
				cout << x.first << " ";
				++count;
				if (count % 8 == 0)
					cout << endl;
			}
		}
		cout << endl << endl;
		cout << "input exit to leave or any other keys to continue\n";
		string temp;
		if (cin >> temp, temp == "exit")
			break;
	}
}

void HomeworkStatistic::func3_show_someday()
{
	initialized_finished_student();
	map<string, unordered_set<string>>::iterator iter1;
	string date;
	while (true)
	{
		cout << "input a date: ";
		while (cin >> date)
		{
			if (date == "exit")
				return;
			iter1 = _files_of_date.find(date);
			if (iter1 == _files_of_date.end())
				cout << "this date doesn't exist, please input again or input exit to leave" << endl;
			else
				break;
		}
		cout << "date: " << date << endl;
		cout << "finished_students are as follows: " << endl;
		int count = 0;
		for (auto& x : iter1->second)
		{
			_finished_student[x] = 1;
			cout << x << "  ";
			++count;
			if (count % 8 == 0)
				cout << endl;
		}
		cout << endl;
		cout << "unfinished_students or unrecognized_students are as follows: " << endl;
		count = 0;
		for (auto& y : _finished_student)
		{
			if (y.second == 0)
			{
				cout << y.first << " ";
				++count;
				if (count % 8 == 0)
					cout << endl;
			}
		}
		cout << endl
			<< endl;
		cout << "input exit to leave or any other keys to continue\n";
		string temp;
		if (cin >> temp, temp == "exit")
			break;
	}
}

void HomeworkStatistic::func4_show_error()
{
	for (auto& x : _files_of_error)
		cout << x << endl;
	system("pause");
}

void HomeworkStatistic::func5_store()
{
	ofstream fout("homework_statistics.txt");
	map<string, unordered_set<string>>::iterator iter;
	for (auto& x : _files_of_date)
	{
		initialized_finished_student();
		fout << x.first << " : " << endl
			<< "finished_students : \n";
		for (auto& y : x.second)
		{
			_finished_student[y] = 1;
			fout << y << ",";
		}
		fout << endl
			<< "unfinished_students : \n";
		for (auto& z : _finished_student)
		{
			if (z.second == 0)
			{
				fout << z.first << ",";
			}
		}
		fout << endl
			<< endl;
	}
	fout << "unrecognized_files : " << endl;
	for (auto& t : _files_of_error)
	{
		fout << t << endl;
	}
	fout << endl;
	fout.close();
	cout << "homework_statistics_store done !" << endl;
	system("start homework_statistics.txt");
	system("pause");
}

void HomeworkStatistic::func6_clear()
{
	clear_file("homework_statistics.txt");
	cout << "homework_statistics_clear done !" << endl;
	system("pause");
}

void HomeworkStatistic::func0_exit()
{
	cout << "Welcome to use again!" << endl;
	system("pause");
	exit(0);
}

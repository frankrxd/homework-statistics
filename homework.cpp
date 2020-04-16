/*
 * @Author: frank
 * @Date: 2020-01-15 20:23:42
 * @LastEditTime : 2020-01-15 20:26:34
 * @LastEditors  : Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \homework_statistics\homework.cpp
 */
#include "homework.h"

int main()
{
	HomeworkStatistic* p = HomeworkStatistic::getInstance();
	HomeworkStatistic::getInstance()->_files_of_error.clear();
	HomeworkStatistic::getInstance()->load_file_path();
	HomeworkStatistic::getInstance()->load_nameinfo();
	HomeworkStatistic::getInstance()->read();
	HomeworkStatistic::getInstance()->show_file_path();
	cout << "load_files finished!" <<endl<< endl;
	int choice = 0;
	while (true)
	{ 
		
		HomeworkStatistic::getInstance()->Show_Menu();
		//HomeworkStatistic::getInstance()->load_file_path();
		//HomeworkStatistic::getInstance()->load_nameinfo();
		//HomeworkStatistic::getInstance()->read();
		cout << "input your choice: " << endl;

		
		cin >> choice;
		switch (choice)
		{
		case 1: //路径
			HomeworkStatistic::getInstance()->func1_set_path();

			HomeworkStatistic::getInstance()->_files_of_error.clear();
			HomeworkStatistic::getInstance()->load_file_path();
			HomeworkStatistic::getInstance()->load_nameinfo();
			HomeworkStatistic::getInstance()->read();
			HomeworkStatistic::getInstance()->show_file_path();
			system("pause");
			
			break;
		case 2: //某人
			HomeworkStatistic::getInstance()->func2_show_someone();
			break;
		case 3: //某天
			HomeworkStatistic::getInstance()->func3_show_someday();
			break;
		case 4: //错误
			HomeworkStatistic::getInstance()->func4_show_error();
			break;
		case 5: //存储
			HomeworkStatistic::getInstance()->func5_store();
			break;
		case 6: //清空
			HomeworkStatistic::getInstance()->func6_clear();
			break;
		case 0: //结束
			HomeworkStatistic::getInstance()->func0_exit();
			break;
		default:
			system("cls"); //清屏
			break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}

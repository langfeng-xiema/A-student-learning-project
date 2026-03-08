#define _CRT_SECURE_NO_WARNINGS
#include "workerManager.h"

WorkerManager::WorkerManager() {
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//文件为空
		cout << "文件为空" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，并记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//存放数据
	this->init_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++) {
		cout << " 职工编号： "<< this->m_EmpArray[i]->m_Id
			<< " 姓名：  " << this->m_EmpArray[i]->m_name
			<< " 部门编号： " << this->m_EmpArray[i]->m_Id << endl;
	}*/
}

//统计文件中人数
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		//统计人数
		num++;
	}
	return num;
}
WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
void WorkerManager::Show_Meau() {
	cout << "*************************************************" << endl;
	cout << "***************欢迎使用职工管理系统**************" << endl;
	cout << "*******************0.退出管理程序****************" << endl;
	cout << "*******************1.增加职工信息****************" << endl;
	cout << "*******************2.显示职工信息****************" << endl;
	cout << "*******************3.删除离职职工****************" << endl;
	cout << "*******************4.修改职工信息****************" << endl;
	cout << "*******************5.查找职工信息****************" << endl;
	cout << "*******************6.按照编号排序****************" << endl;
	cout << "*******************7.清空所有文档****************" << endl;
	cout << "*************************************************" << endl;
	cout << "*************************************************" << endl;
	cout << endl;
}
void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}
//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量" << endl;
	int addNum = 0;//保存用户输入数量
	cin >> addNum;

	if (addNum > 0) {
		//添加
		//计算空间大小
		int newSize = this->m_EmpNum + addNum;//新空间大小=原来记录人数+新增人数
		Worker** newspace = new Worker * [newSize];
		//将原来空间下的数据拷贝到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newspace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建的职工指针保存到数组中
			newspace[this->m_EmpNum + i] = worker;
		}
		//释放原有的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newspace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空
		this->m_FileIsEmpty = false;

		//保存数据到文件中
		this->save();

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else {
		cout << "数据有误";
	}
	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}
//初始化职工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}
//显示职工
void WorkerManager::Show_Emp() {
	//判断文件是否为空
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		//按照职工编号删除
		cout << "请输入想要删除职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) {
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			//同步数据到文件
			this->save();
			cout << "删除成功" << endl;
		}
		else {
			cout << "删除失败，未找到职工" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}
//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入修改职工编号："<<endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) {
			//查找到职工
			delete this->m_EmpArray[ret];

			int newID = 0;;
			string newname = " ";
			int dSelet = 0;

			cout << "查找：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newID;
			cout << "请输入新职工姓名：" << endl;
			cin >> newname;
			cout << "请输入新职工岗位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelet;

			Worker* worker = NULL;
			switch (dSelet) {
			default:
				break;
			case 1:
				worker = new Employee(newID, newname,dSelet);
				break;
			case 2:
				worker = new Manager(newID, newname, dSelet);
				break;
			case 3:
				worker = new Boss(newID, newname, dSelet);
				break;
			}
			//更新数据
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			//保存
			this->save();
		}
		else {
			cout << "修改失败,查无此人" << endl;
		}
	}
	//清屏
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;

		int select;
		cin >> select;

		if (select == 1) {
			//按照编号
			int id;
			cout << "请输入查找的职工的编号" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1) {
				cout << "找到职工，该职工信息如下" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "查无此人"<<endl;
			}
		}
		else if(select == 2){
			//按照姓名
			string name;
			cout << "请输入查找的姓名" << endl;
			cin >> name;

			//加入一个判断是否查到的标志
			bool flag = false;

			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_name == name) {
					cout << "查找成功,职工编号为"
						<<this->m_EmpArray[i]->m_Id
						<<"号，信息如下" << endl;
					flag = true;

					this->m_EmpArray[i]->showInfo();
					
				}
			}
			if (flag = false) {
				cout << "查无此人" << endl;
			}
		}
		else {
			cout << "输入错误" << endl;
		}
	}
	//清屏
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id) {
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}
//按照编号排序
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1.按照职工号进行升序" << endl;
		cout << "1.按照职工号进行降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;//声明最小值或最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) {
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {//降序
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			//判断最开始的最小值或最大值是不是计算的最小值或最大值，如果不是交换数据
			if (i != minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功！结果为：" << endl;
		this->save();//保存
		this->Show_Emp();
	}
}
//清空文件
void WorkerManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL) {
			//删除堆区每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				m_EmpArray[i] = NULL;
			}
			//删除堆区数组
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功!" << endl;
	}
	system("pause");
	system("cls");
}

//写入文档
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME,ios::out);//用输出的方式打开文件 -- 写文件

	//将每个人的数据写入文件
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_name<<"  "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}
#define _CRT_SECURE_NO_WARNINGS
#include "manager.h"

//构造函数
Manager::Manager(int id, string name, int did) {
	this->m_Id = id;
	this->m_name = name;
	this->m_DeptId = did;
}
//显示个人信息
void Manager::showInfo() {
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责：完成老板交给的任务，并下发任务给普通员工"
		<< endl;
}
//获取岗位名称
string Manager::getDeptName() {
	return string("经理");
}
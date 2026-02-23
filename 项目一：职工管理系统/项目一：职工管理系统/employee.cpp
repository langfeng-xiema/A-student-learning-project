#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "employee.h"
//构造函数
Employee::Employee(int id, string name, int did) {
	this->m_Id = id;
	this->m_name = name;
	this->m_DeptId = did;
}
//显示个人信息
void Employee::showInfo() {
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务"
		<<endl;
}
//获取岗位名称
string Employee::getDeptName() {
	return string("员工");
}
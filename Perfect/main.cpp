/*
 * main.cpp
 *
 *  Created on: 2019��12��12��
 *      Author: poplarli
 */


#include <iostream>
#include "Perfect.h"

//�����ʾ���塣����������ת��
const int Animal::cn;

int main(){

	std::string s;
	//Ϊë���������õ���process(std::string&& s)
	logAndProcess(s);
	logAndProcess(std::move(s));

	auto && a1 = s;
	auto && a2 = std::move(s);

	//�������õ��βα����ݸ���������ʱ������Ҫ��std::forward



	Person p1("lp");
	Person p2(2);
	p1.printPerson();
	p2.printPerson();

	short idx = 1;
	//Person p3(idx);	//���벻�� stringû��short�βεĹ��캯��


	logAndAdd("zz");
	logAndAdd(std::string("pt"));
	logAndAdd(2);
	logAndAdd(idx);
	for(auto i : st){
		std::cout << i << " ";
	}
	std::cout << std::endl;

	Animal ani1("pp");
	Animal ani2(ani1);

	Animal ani3(2);
	Animal ani4(idx);

	static_assert(std::is_constructible<std::string, const char*>::value, "can not construct");

	std::cout << "cn = " << Animal::cn << std::endl;

	return 0;
}


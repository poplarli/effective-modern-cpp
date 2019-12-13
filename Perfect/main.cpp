/*
 * main.cpp
 *
 *  Created on: 2019年12月12日
 *      Author: poplarli
 */


#include <iostream>
#include "Perfect.h"

//最好显示定义。有利于完美转发
const int Animal::cn;

int main(){

	std::string s;
	//为毛两个都调用的是process(std::string&& s)
	logAndProcess(s);
	logAndProcess(std::move(s));

	auto && a1 = s;
	auto && a2 = std::move(s);

	//万能引用的形参被传递给其他函数时，我们要做std::forward



	Person p1("lp");
	Person p2(2);
	p1.printPerson();
	p2.printPerson();

	short idx = 1;
	//Person p3(idx);	//编译不过 string没有short形参的构造函数


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


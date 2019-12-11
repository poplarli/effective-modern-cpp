/*
 * main.cpp
 *
 *  Created on: 2019年12月11日
 *      Author: poplarli
 */



#include <iostream>
#include <memory>
#include "SmartPointer.h"
#include "Store.h"

int main(){

	std::unique_ptr<Widget> up(new Widget());
	std::cout << up->a << std::endl;
	//unique_ptr可以转换为shared_ptr
	std::shared_ptr<Widget> sp(std::move(up));
	std::cout << sp->a << std::endl;

	auto pa = makeAnimal();


	std::shared_ptr<Person> spe = Person::makePerson("lala");
	std::vector<std::shared_ptr<Person>> vec;
	spe->f1(vec);

	{
		std::shared_ptr<Person> sp1 = getPerson("ly");
		std::shared_ptr<Person> sp2 = getPerson("ly");
	}

	std::shared_ptr<Person> sp3 = getPerson("ly");


	//make系列操作只分配一次内存，用于要管理的对象和控制块。
	//使用make生成的对象内存，需要shared_ptr和weak_ptr都析构的时候才释放。而直接使用构造函数生成的对象内存在shared_ptr全部析构的时候就释放，控制块的内存等到weak_ptr全部析构的时候释放。
	//make系列的完美转发，是采用圆括号的。
	std::shared_ptr<std::vector<int>> sv = std::make_shared<std::vector<int>>(3,10);

	auto il = {3, 10};
	std::shared_ptr<std::vector<int>> sv2 = std::make_shared<std::vector<int>>(il);
	std::cout << sv->size() << " " << sv2->size() << std::endl;


	Store st;
	Store st2(std::move(st));

	return 0;

}

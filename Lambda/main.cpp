/*
 * main.cpp
 *
 *  Created on: 2019年12月13日
 *      Author: poplarli
 */


#include <iostream>
#include <memory>
#include "lambda.h"

Widget::FilterContainer Widget::vec;

int main(){

	{
		std::unique_ptr<Widget> up1 = std::make_unique<Widget>(2);
		std::unique_ptr<Widget> up2 = std::make_unique<Widget>(3);
		up1->addFilter();
		up2->addFilter();
	}

	for(auto& func : Widget::vec){
		std::cout << func(100) << std::endl;
	}


	auto f = [pw = std::make_unique<Widget>(5)]{
		pw->print();
	};
	f();

	auto f2 = std::bind([](const std::unique_ptr<Widget>& pw){
		pw->print();
	}, std::make_unique<Widget>());
	f2();

	auto f3 = [](auto&& ... params){
		//泛型lambda的完美转发
		test(std::forward<decltype(params)>(params)...);
	};
	f3("hello", "world");

	int low = 0;
	int high = 100;
	auto comp = [low, high](auto m){
		return m > low && m < high;
	};
	std::cout << comp(5) << " " << comp(200) << std::endl;

	return 0;
}


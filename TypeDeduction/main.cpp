/*
 * main.cpp
 *
 *  Created on: 2019年12月9日
 *      Author: poplarli
 */

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include "type_deduction.h"

int main(){

	int arr[] = {1,2,3,4,5};
	std::cout << arrSize(arr) << std::endl;

	auto x = {1, 2, 3};
	//func({1});	//编译失败
	std::for_each(x.begin(), x.end(), [](int i){std::cout << i << std::endl;});

	std::vector<int> v;
	auto resetV = [&v](const auto& newValue){
		v = newValue;
	};

	//resetV({1,2,3}); 使用大括号将使用模板推导，编译不过。
	std::vector<int> v2 = {5,6,7};
	resetV(v2);

	//vector初始化为initializer_list
	std::initializer_list<int> ilst = {7,8,9};
	std::vector<int> v3 = ilst;

	//查看型别推导结果的方法
	const int answer = 42;
	auto y = answer;
	auto z = &answer;
	std::cout << typeid(y).name() << std::endl;
	std::cout << typeid(z).name() << std::endl;

	//有时候type::name函数返回的并不准确，因为其忽略了引用、const和volatile特性。
	//使用boost::typeindex::type_id_with_cvr可以解决这个问题。
	const int * pi = nullptr;
	func3(pi);

	std::vector<bool> bvec = {true, false, false};
	using boost::typeindex::type_id_with_cvr;
	std::cout << type_id_with_cvr<decltype(bvec[1])>().pretty_name() << std::endl;

 	return 0;
}


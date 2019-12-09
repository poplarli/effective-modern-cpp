/*
 * main.cpp
 *
 *  Created on: 2019年12月9日
 *      Author: poplarli
 */

#include "auto.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>
#include <algorithm>
#include <boost/type_index.hpp>

int main(){

	std::vector<int> v = {1,3,5,7,9};
	dwim(v.begin(), v.end());

	//这里的key是const，写起来容易出错。
	std::unordered_map<std::string, int> ump = {{"xm", 1}, {"xw", 2}};
	for(std::pair<const std::string, int>& i : ump){
		i.second = 100;
	}
	std::for_each(ump.begin(), ump.end(), [](auto& i){std::cout << i.first << " " << i.second << std::endl;});
	//使用auto，简单不易错，i绑定到ump的元素上
	for(auto & i : ump){
		i.second = 200;
	}
	std::for_each(ump.begin(), ump.end(), [](auto& i){std::cout << i.first << " " << i.second << std::endl;});

	std::vector<bool> v2 = {1,0,1,0,1,1,1};
	for(auto i : v2){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	using boost::typeindex::type_id_with_cvr;
	std::cout << type_id_with_cvr<decltype(v2[4])>().pretty_name() << std::endl;

	//显示指明意在创建一个型别有异于初始化表达式的变量
	auto x = static_cast<bool>(v2[4]);
	std::cout << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl;

	//显示指明我想要转换为int
	std::vector<double> v3 = {0.1,0.5,0.9,0.6};
	auto d = static_cast<int>(v3.size() * v3[2]);

	return 0;

}



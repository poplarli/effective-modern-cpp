/*
 * main.cpp
 *
 *  Created on: 2019Äê12ÔÂ14ÈÕ
 *      Author: poplarli
 */


#include <iostream>
#include <string>
#include <vector>

int main(){

	std::vector<std::string> vec;
	vec.emplace_back(10,'a');

	for(const auto& i : vec){
		std::cout << i << std::endl;
	}

	return 0;
}


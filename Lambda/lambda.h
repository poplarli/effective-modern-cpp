/*
 * lambda.h
 *
 *  Created on: 2019年12月13日
 *      Author: poplarli
 */

#ifndef LAMBDA_LAMBDA_H_
#define LAMBDA_LAMBDA_H_

#include <vector>
#include <algorithm>
#include <functional>

class Widget{

public:
	using FilterContainer = std::vector<std::function<bool (int)>>;
	Widget(int d = 1) : divisor(d){

	}
	void addFilter() const{
		//广义捕获。如果仅仅捕获this，那么可能会导致空悬指针的问题。
		Widget::vec.emplace_back([divisor=divisor](int value){
			return value % divisor == 0;
		});
	}

	void print() const{
		std::cout << "divisor = " << divisor<< std::endl;
	}

public:
	static FilterContainer vec;
private:
	int divisor{1};
};

void test(std::string s1, std::string s2){
	std::cout << s1 << " " << s2 << std::endl;
}


#endif /* LAMBDA_LAMBDA_H_ */

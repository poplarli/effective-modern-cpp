/*
 * Perfect.h
 *
 *  Created on: 2019年12月12日
 *      Author: poplarli
 */

#ifndef PERFECT_PERFECT_H_
#define PERFECT_PERFECT_H_

#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <set>

void process(const std::string& s){
	std::cout << "call process(const std::string& s)" << std::endl;
}

void process(std::string&& s){
	std::cout << "call process(std::string&& s)" << std::endl;
}


std::string getNameFromIdx(int idx){

	static std::map<int, std::string> mp = {{1,"ly"}, {2, "pc"}};
	auto iter = mp.find(idx);
	if(iter != mp.end()){
		return iter->second;
	}
	return "unkown";
}


//万能引用
template<typename T>
void logAndProcess(T&& param){
	auto now = std::chrono::system_clock::now();
	std::cout << "call logAndProcess" << std::endl;
	//所有参数都是左值。所以param是个左值，即使它绑定到右值。
	//当param是由右值初始化的时候，std::forward会进行强制类型转换。
	process(std::forward<std::string>(param));
}

std::set<std::string> st;


template<typename T>
void logAndAdd(T&& param);

template<typename T>
void logAndAddImpl(T&& param, std::true_type){
	std::cout << "call true" << std::endl;
	logAndAdd(getNameFromIdx(param));

}

template<typename T>
void logAndAddImpl(T&& param, std::false_type){

	std::cout << "call false" << std::endl;
	st.emplace(std::forward<T>(param));

}

//标签分派
template<typename T>
void logAndAdd(T&& param){
	//因为如果param是左值，T会被推导成引用类型。所以下面加上了remove_reference_t去除引用，要不然is_integral的结果会很奇怪(int& 不是 int)。
	logAndAddImpl(std::forward<T>(param), std::is_integral<std::remove_reference_t<T>>());

}


class Person{


public:
	//完美转发构造函数
	template<typename T>
	Person(T&& param) : name_(std::forward<T>(param)){
	}

	Person(int idx) : name_(getNameFromIdx(idx)){
	}

	void printPerson(){
		std::cout << "my name is " << name_ << std::endl;
	}

private:
	std::string name_;
};

class Animal{

public:
	//使用enable_if 舍弃掉Animal继承链上所有类型的形参的实例版本以及形参为int的版本
	template<typename T, typename = std::enable_if_t<!std::is_base_of<Animal, std::decay_t<T>>::value && !std::is_integral<std::remove_reference_t<T>>::value>>
	Animal(T&& name) : name_(std::forward<T>(name)){
		std::cout << "call <>" << std::endl;
	}


	Animal(const Animal& rhs) : name_(rhs.name_){
		std::cout << "call Animal copy" << std::endl;
	}

	Animal(int idx) : name_(getNameFromIdx(idx)){
		std::cout << "call Animal int" << std::endl;
	}

	static const int cn = 100;

private:
	std::string name_;

};

#endif /* PERFECT_PERFECT_H_ */

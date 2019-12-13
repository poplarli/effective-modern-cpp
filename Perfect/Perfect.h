/*
 * Perfect.h
 *
 *  Created on: 2019��12��12��
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


//��������
template<typename T>
void logAndProcess(T&& param){
	auto now = std::chrono::system_clock::now();
	std::cout << "call logAndProcess" << std::endl;
	//���в���������ֵ������param�Ǹ���ֵ����ʹ���󶨵���ֵ��
	//��param������ֵ��ʼ����ʱ��std::forward�����ǿ������ת����
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

//��ǩ����
template<typename T>
void logAndAdd(T&& param){
	//��Ϊ���param����ֵ��T�ᱻ�Ƶ����������͡��������������remove_reference_tȥ�����ã�Ҫ��Ȼis_integral�Ľ��������(int& ���� int)��
	logAndAddImpl(std::forward<T>(param), std::is_integral<std::remove_reference_t<T>>());

}


class Person{


public:
	//����ת�����캯��
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
	//ʹ��enable_if ������Animal�̳������������͵��βε�ʵ���汾�Լ��β�Ϊint�İ汾
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

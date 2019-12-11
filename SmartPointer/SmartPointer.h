/*
 * SmartPointer.h
 *
 *  Created on: 2019��12��11��
 *      Author: poplarli
 */

#ifndef SMARTPOINTER_SMARTPOINTER_H_
#define SMARTPOINTER_SMARTPOINTER_H_

#include <vector>
#include <string>
#include <memory>
#include <map>

class Widget{

public:
	int a {10};
};

class Animal{

public:
	virtual ~Animal() = default;
	virtual void func() = 0;
};

class Pig : public Animal{
public:
	void func(){
		std::cout << "i am pig" << std::endl;
	}
};

class Dog : public Animal{
public:
	void func(){
		std::cout << "i am dog" << std::endl;
	}
};

template <typename... Ts>
auto makeAnimal(Ts... params){
	//Ĭ��������������£�unique_ptr����ָ���С��ͬ
	//ʹ�ú���ָ����Ϊ��������������һ�������ֳ�
	//ʹ�ÿղ����lambda���ʽ������ָ���С��ͬ��
	auto delAnimal = [](Animal* pa){
		pa->func();
		delete pa;
	};

	std::unique_ptr<Animal, decltype(delAnimal)> up(nullptr, delAnimal);
	if(0){
		up.reset(new Pig());
	}else{
		up.reset(new Dog());
	}

	return up;
}

class Person : public std::enable_shared_from_this<Person>{

public:

	//ʹ��shared_from_this������Ҫ��ָ��this�Ŀ��ƿ顣
	//����һ��ѹ��캯������Ϊprivate��ʹ��factory�������ɶ���
	static std::shared_ptr<Person> makePerson(std::string name){
		return std::shared_ptr<Person>(new Person(name));
	}

	~Person(){
		std::cout << "call ~Person() name = " << name_ << std::endl;
	}


	void f1(std::vector<std::shared_ptr<Person>>& vec){
		vec.emplace_back(shared_from_this());
		std::cout << name_ << " call f1" << std::endl;
	}

	void f2(){
		std::cout << name_ << " call f2" << std::endl;
	}

private:
	Person(std::string name) : name_(name){
		std::cout << "make Person " << name << std::endl;
	}

	std::string name_;
};

std::shared_ptr<Person> getPerson(std::string s){

	static std::map<std::string, std::weak_ptr<Person>> mp;
	auto objptr = mp[s].lock();
	if(!objptr){
		objptr = Person::makePerson(s);
		mp[s] = objptr;
	}

	return objptr;
}


#endif /* SMARTPOINTER_SMARTPOINTER_H_ */

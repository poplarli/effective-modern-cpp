/*
 * main.cpp
 *
 *  Created on: 2019��12��11��
 *      Author: poplarli
 */



#include <iostream>
#include <memory>
#include "SmartPointer.h"
#include "Store.h"

int main(){

	std::unique_ptr<Widget> up(new Widget());
	std::cout << up->a << std::endl;
	//unique_ptr����ת��Ϊshared_ptr
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


	//makeϵ�в���ֻ����һ���ڴ棬����Ҫ����Ķ���Ϳ��ƿ顣
	//ʹ��make���ɵĶ����ڴ棬��Ҫshared_ptr��weak_ptr��������ʱ����ͷš���ֱ��ʹ�ù��캯�����ɵĶ����ڴ���shared_ptrȫ��������ʱ����ͷţ����ƿ���ڴ�ȵ�weak_ptrȫ��������ʱ���ͷš�
	//makeϵ�е�����ת�����ǲ���Բ���ŵġ�
	std::shared_ptr<std::vector<int>> sv = std::make_shared<std::vector<int>>(3,10);

	auto il = {3, 10};
	std::shared_ptr<std::vector<int>> sv2 = std::make_shared<std::vector<int>>(il);
	std::cout << sv->size() << " " << sv2->size() << std::endl;


	Store st;
	Store st2(std::move(st));

	return 0;

}

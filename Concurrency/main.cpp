/*
 * main.cpp
 *
 *  Created on: 2019��12��13��
 *      Author: poplarli
 */


#include <iostream>
#include <thread>
#include <future>
#include <unistd.h>
#include "Concurrency.h"

namespace{

	int func(){
		//sleep(3);
		std::cout << "call func" << std::endl;
		return 109;
	}

	template<typename F, typename... Ts>
	auto realAsync(F&& f, Ts&&... args){
		return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(args)...);
	}

	int func2(){
		int i = 0;
		while(i < 10){
			std::cout << ++i << std::endl;
			sleep(1);
		}
		return 0;
	}
};

int main(){

	//�����ʱ��Ӧ��ѡ������������ƣ����ǻ����̵߳���ơ�
	auto fu = std::async(std::launch::deferred, func);

	//sleep(1);
	std::cout << "123" << std::endl;

	//std::cout << fu.get() << std::endl;


	int cnt = 0;
	using namespace std::literals;
	while(cnt++ < 1 && fu.wait_for(500ms) != std::future_status::ready){
		std::cout << "wait " << cnt << "times" << std::endl;
	}

	realAsync(func);


	//std::thread t(func2);	//�����ӵ�thread���������ǻ���ֹ���̡�
	//ʹ��RAII��������thread����������ʱ�����д�����join�ػ���detach�ء�
	//ThreadRAII tr(std::thread(func2), ThreadRAII::DtorAction::join);
	ThreadRAII tr(std::thread(func2), ThreadRAII::DtorAction::detach);
	std::cout << "main end" << std::endl;

	return 0;
};




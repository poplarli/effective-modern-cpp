/*
 * main.cpp
 *
 *  Created on: 2019年12月13日
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

	//大多数时候，应该选择基于任务的设计，而非基于线程的设计。
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


	//std::thread t(func2);	//可连接的thread对象析构是会终止进程。
	//使用RAII技术，在thread对象析构的时候，自行处理。是join呢还是detach呢。
	//ThreadRAII tr(std::thread(func2), ThreadRAII::DtorAction::join);
	ThreadRAII tr(std::thread(func2), ThreadRAII::DtorAction::detach);
	std::cout << "main end" << std::endl;

	return 0;
};




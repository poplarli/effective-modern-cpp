/*
 * Concurrency.h
 *
 *  Created on: 2019Äê12ÔÂ13ÈÕ
 *      Author: poplarli
 */

#ifndef CONCURRENCY_H_
#define CONCURRENCY_H_

#include <future>

class ThreadRAII{

public:
	enum class DtorAction{ join, detach };

	ThreadRAII(std::thread&& t, DtorAction a) : action(a), t(std::move(t)){

	}

	~ThreadRAII(){
		if(t.joinable()){
			if(action == DtorAction::join){
				t.join();
			}else{
				t.detach();
			}
		}
	}

	ThreadRAII(ThreadRAII&&) = default;
	ThreadRAII& operator=(ThreadRAII&&) = default;

private:
	DtorAction action;
	std::thread t;
};



#endif /* CONCURRENCY_H_ */

/*
 * auto.h
 *
 *  Created on: 2019��12��9��
 *      Author: poplarli
 */

#ifndef AUTO_AUTO_H_
#define AUTO_AUTO_H_

#include <iostream>
#include <functional>
#include <iterator>

//ʹ��auto�ô���డ

template<typename It>
void dwim(It b, It e){
	while(b != e){
		typename std::iterator_traits<It>::value_type val = *b;
		std::cout << val << " ";
		auto val2 = *b;		//��
		std::cout << val << " ";
		++b;
	}
	std::cout << std::endl;


}



#endif /* AUTO_AUTO_H_ */

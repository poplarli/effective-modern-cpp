/*
 * main.cpp
 *
 *  Created on: 2019��12��9��
 *      Author: poplarli
 */

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include "type_deduction.h"

int main(){

	int arr[] = {1,2,3,4,5};
	std::cout << arrSize(arr) << std::endl;

	auto x = {1, 2, 3};
	//func({1});	//����ʧ��
	std::for_each(x.begin(), x.end(), [](int i){std::cout << i << std::endl;});

	std::vector<int> v;
	auto resetV = [&v](const auto& newValue){
		v = newValue;
	};

	//resetV({1,2,3}); ʹ�ô����Ž�ʹ��ģ���Ƶ������벻����
	std::vector<int> v2 = {5,6,7};
	resetV(v2);

	//vector��ʼ��Ϊinitializer_list
	std::initializer_list<int> ilst = {7,8,9};
	std::vector<int> v3 = ilst;

	//�鿴�ͱ��Ƶ�����ķ���
	const int answer = 42;
	auto y = answer;
	auto z = &answer;
	std::cout << typeid(y).name() << std::endl;
	std::cout << typeid(z).name() << std::endl;

	//��ʱ��type::name�������صĲ���׼ȷ����Ϊ����������á�const��volatile���ԡ�
	//ʹ��boost::typeindex::type_id_with_cvr���Խ��������⡣
	const int * pi = nullptr;
	func3(pi);

	std::vector<bool> bvec = {true, false, false};
	using boost::typeindex::type_id_with_cvr;
	std::cout << type_id_with_cvr<decltype(bvec[1])>().pretty_name() << std::endl;

 	return 0;
}


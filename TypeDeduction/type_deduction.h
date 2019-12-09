/*
 * type_deduction.h
 *
 *  Created on: 2019��12��9��
 *      Author: poplarli
 */

#ifndef TYPE_DEDUCTION_H_
#define TYPE_DEDUCTION_H_

#include <iostream>
#include <boost/type_index.hpp>


//ģ�尴ֵ����ʱ������ʵ�ν��ᱻ�Ƶ�Ϊָ�����͡�
template<typename T>
void func(T x){
}

//ģ�尴���ô���ʱ������ʵ�ν��ᱻ�Ƶ�Ϊ�������͡�
template<typename T>
void func2(T& x){
}

//�����ڼ��Գ�����ʽ��������ߴ�
template<typename T, std::size_t N>
constexpr std::size_t arrSize(T (&) [N]) noexcept{
	return N;
}

//auto�ͱ��Ƶ���ģ���ͱ��Ƶ�ʮ�����ơ�auto��ӦT�����������Ͷ�Ӧ�βε�paramType
//���ڴ����ų�ʼ��ʽ�Ĵ���ʽ����auto�ͱ��Ƶ���ģ���ͱ��Ƶ���Ψһ��֮ͬ����
//������auto�����ı���ʹ�ô����ų�ʼ�����ʽ���г�ʼ��ʱ���Ƶ�������std::initializer_list��һ��ʵ���ͱ𡣵������Ӧ��ģ�崫��һ��ͬ���ĳ�ʼ�����ʽ���ͱ��Ƶ���ʧ�ܣ����벻ͨ����

//���ں�������ֵ����lambda���ʽ��ʹ��auto��������ʹ��ģ���ͱ��Ƶ�������auto�ͱ��Ƶ�����������Щ�����ʹ�ô������ǲ��еġ�
//auto createList(){
//	return {1,2,3};
//}




class TD;


template<typename T>
void func3(const T& param){

	//����ʵ��const int*���ͣ���ӡPKi��PKi
	std::cout << typeid(T).name() << std::endl;
	std::cout << typeid(param).name() << std::endl;

	//��ӡint const*��int const* const&
	using boost::typeindex::type_id_with_cvr;
	std::cout << type_id_with_cvr<T>().pretty_name() << std::endl;
	std::cout << type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}


#endif /* TYPE_DEDUCTION_H_ */

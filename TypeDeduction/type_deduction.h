/*
 * type_deduction.h
 *
 *  Created on: 2019年12月9日
 *      Author: poplarli
 */

#ifndef TYPE_DEDUCTION_H_
#define TYPE_DEDUCTION_H_

#include <iostream>
#include <boost/type_index.hpp>


//模板按值传递时，数组实参将会被推导为指针类型。
template<typename T>
void func(T x){
}

//模板按引用传递时，数组实参将会被推导为数组类型。
template<typename T>
void func2(T& x){
}

//编译期间以常量形式返回数组尺寸
template<typename T, std::size_t N>
constexpr std::size_t arrSize(T (&) [N]) noexcept{
	return N;
}

//auto型别推导和模板型别推导十分类似。auto对应T，变量的类型对应形参的paramType
//对于大括号初始化式的处理方式，是auto型别推导和模板型别推导的唯一不同之处。
//当采用auto声明的变量使用大括号初始化表达式进行初始化时，推导出的是std::initializer_list的一个实例型别。但是向对应的模板传入一个同样的初始化表达式，型别推导会失败，编译不通过。

//对于函数返回值或者lambda表达式中使用auto，这是在使用模板型别推导而不是auto型别推导。所以在这些情况下使用大括号是不行的。
//auto createList(){
//	return {1,2,3};
//}




class TD;


template<typename T>
void func3(const T& param){

	//对于实参const int*类型，打印PKi、PKi
	std::cout << typeid(T).name() << std::endl;
	std::cout << typeid(param).name() << std::endl;

	//打印int const*、int const* const&
	using boost::typeindex::type_id_with_cvr;
	std::cout << type_id_with_cvr<T>().pretty_name() << std::endl;
	std::cout << type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}


#endif /* TYPE_DEDUCTION_H_ */

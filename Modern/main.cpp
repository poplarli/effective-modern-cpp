/*
 * main.cpp
 *
 *  Created on: 2019年12月10日
 *      Author: poplarli
 */



#include <iostream>
#include <typeinfo>
#include <vector>
#include <type_traits>
#include <list>
#include "modern.h"

int main(){

	//采用大括号初始化来调用没有形参的构造函数。但是如果这样写Widget w1(),就会有问题。因为这声明了一个函数。
	Widget w2{};
	w2.f();

	//int a = {1.1};	编译不过，大括号初始化可以阻止隐式窄化类型转换。
	int b = 1.2;
	int c(1.3);

	auto d = {3};
	std::cout << typeid(d).name() << std::endl;

	//会优先选择initialized_list参数的构造函数。
	Widget w3{1,false};

	//编译不过，因为还是会选择initialized_list参数的构造函数，但是存在double->int的窄化转换。
	//Widget w4{1.1,false};

	//对于既有默认构造函数，又有initialized_list参数的构造函数，这里调用的是默认构造函数。
	Widget w1;
	//下面是调用initialized_list参数的构造函数
	Widget w4({});
	Widget w5{{}};

	//这俩完全不一样
	std::vector<int> v1(2,3);
	std::vector<int> v2{2,3};
	printVec(std::move(v1));	//3 3
	printVec(std::move(v2));	//2 3

	doSomeWork<std::vector<int>>(2,3);

	std::mutex m1;
	//lockAndCall(f1, m1, 0);	//编译不过，could not convert ‘ptr’ from ‘int’ to ‘std::shared_ptr<Widget>’
	lockAndCall(f1, m1, nullptr);

	f1(0);	//这里可以调用。
	std::shared_ptr<int> sp = 0; //这里可以调用。


	std::cout << std::is_same<Widget, std::remove_const_t<const Widget>>::value << std::endl;

	//typedef不支持模板，别名声明支持
	MyList<int> lst;
	MyList2<int>::type lst2;

	//限定范围的枚举类型
	enum class Color{RED, BLUE, GREEN};
	auto m = Color::RED;
	//double r = m + 1.0;	//编译不过，限定作用域的枚举类型不能隐式转换路径
	double r = static_cast<double>(m) + 1.0;

	using UserInfo = std::tuple<std::string, int, int>;
	UserInfo u{"pp", 31, 175};
	std::cout << "age = "<< std::get<1>(u) << std::endl;
	//这里使用非限定枚举要方便些。
	enum User {NAME, AGE, HEIGHT};
	std::cout << "name = "<< std::get<User::NAME>(u) << std::endl;
	//使用限定枚举
	enum class User2 : long long {NAME, AGE, HEIGHT};
	std::cout << "height = " << std::get<toUType(User2::HEIGHT)>(u) << std::endl;

	//underlying_type_t返回枚举类的底层类型
	std::cout << std::is_same<int, std::underlying_type_t<User2>>::value << std::endl;			//false
	std::cout << std::is_same<long long, std::underlying_type_t<User2>>::value << std::endl;	//true

	makeWidget().doWork();

	//调用右值引用，data()返回右值，从而调用vector的移动构造函数。
	W::DataType vec1 = makeW().data();
	//调用左值引用，调用vector的复制构造函数
	W w;
	W::DataType vec2 = w.data();


	//C++11下，能使用const_iterator就使用
	auto it = std::cbegin(v1);
	//在最通用的代码里，优先选用非成员函数版本的begin、end、rbegin、rend等
	int arr[] = {3,7,9};
	int* bn  = std::begin(arr);
	int* ed  = std::end(arr);
	auto func = [](int* b, int* e){while(b != e){
		std::cout << *b << " ";
		++b;
	};};
	func(bn, ed);

	int arr2[] = {2,3,4};
	std::swap(arr, arr2);

	int x = 2;
	int y = 3;
	std::swap(x, y);


	//constexpr是const，const不是constexpr。
	//对于要求编译期间常量的语境，只能是constexpr
	const auto var = x;
	//std::array<int, var> data; //编译不过 the value of ‘var’ is not usable in a constant expression
	//constexpr auto var2 = y; //编译不过 the value of ‘y’ is not usable in a constant expression
	constexpr auto var3 = 10;
	std::array<int, var3> data2;

	//constexptr函数可以用在编译器常量的语境下，前提是传给constexptr函数的实参是编译器常量。如果不是，那么编译失败。
	std::array<int, add(2,3)> data3; //add函数前面的constexpr表示如果实参是编译期间常量，那么add返回结果可以当做编译期间常量。
	//std::array<int, add(x,y)> data4; 编译不过

	//如果传入constexptr函数的参数在编译器未知，那么和普通函数无异
	add(x,y);	//执行期间被调用


	Point pt;
	pt.func();
	pt.func();
	std::cout << pt.callCnt() << std::endl;

	pt.foo();

	//Point pt2 = pt; 编译不过 因为mutex和atomic对象都不能复制。除非显示定义复制构造函数
	Point pt2(std::move(pt));

	MapTool mt1;
	MapTool mt2(std::move(mt1));
	mt2.printMap();

	MMMM mm1;
	MMMM mm2(std::move(mm1));
	return 0;
}


/*
 * modern.h
 *
 *  Created on: 2019年12月10日
 *      Author: poplarli
 */

#ifndef MODERN_MODERN_H_
#define MODERN_MODERN_H_

#include <iostream>
#include <algorithm>
#include <memory>
#include <mutex>
#include <atomic>
#include <type_traits>
#include <unordered_map>

//使用using声明
template<typename T>
using MyList = std::list<T>;

//使用typedef
template<typename T>
struct MyList2{
	typedef std::list<T> type;
};

//非限定作用域枚举的前置声明,需要声明底层类型。
enum E1 : int;
//限定作用域的枚举，默认底层是int
enum class E2;

template<typename T>
class A{
	//这里必须加typename
	typedef typename MyList2<T>::type wtype;
private:
	wtype w;
	MyList<T> l;	//使用方便
	E1 a;
	E2 b;
};

class Widget{

public:
	Widget() = default;
	Widget(int a, bool b){
		std::cout << "call Widget(int a, bool b)" << std::endl;
	}

	Widget(std::initializer_list<int> il){
		std::cout << "call Widget(std::initializer_list<long double> il)" << std::endl;
	}

	static void f(){
		std::cout << "call f()" << std::endl;
	}

	//&引用饰词 左值调用
	void doWork() &{
		std::cout << "call doWork() &" << std::endl;
	}

	//&&引用饰词 右值调用
	void doWork() &&{
		std::cout << "call doWork() &&" << std::endl;
	}

private:
	int a_{1};		//大括号初始化默认值
	bool b_{false};

};

Widget makeWidget(){
	return *(new Widget());
}


template<typename T>
void printVec(std::vector<T>&& v){

	std::for_each(v.begin(), v.end(), [](const T& x){std::cout << x << " ";});
	std::cout << std::endl;

}

template<typename T, typename... TS>
void doSomeWork(TS&&... param){
	std::cout << "call doSomeWork" << std::endl;
	T localObj1(std::forward<TS>(param)...);
	for(auto i : localObj1){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	T localObj2{std::forward<TS>(param)...};
	for(auto i : localObj2){
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

//0和NULL具有整型型别，不具备指针型别。
//nullptr不具有整型型别，可以把它想象成任意型别的指针。
//使用空指针请使用nullptr
int f1(std::shared_ptr<Widget> spw){
	typedef typename std::remove_reference<Widget&>::type type;
	using type2 = std::remove_reference_t<Widget&>;
	return 0;
}

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mx, PtrType ptr){

	using MuxGuard = std::lock_guard<std::mutex>;
	MuxGuard g(mx);
	return func(ptr);
}

template<typename T>
constexpr auto toUType(T e) noexcept{
	return static_cast<typename std::underlying_type_t<T>>(e);
}

//优先使用删除函数，而非private为定义函数
class D{

public:
	//使用delete代替private的函数声明，来阻止复制和赋值操作符的调用。
	//使用public可以从编译信息中得到较好的错误信息。
	D(const D&) = delete;
	D& operator=(const D&) = delete;

	template<typename T>
	void func(T param){}
};

//使用delete来删除类内部的模板特化，这个使用private函数做不了。
template<>
void D::func(void*) = delete;

template<typename T>
void func2(T param){}

//使用delete来删除模板具现
template<>
void func2(int) = delete;
template<>
void func2(double) = delete;

//使用delete来防止调用luck(int)时，由double或者bool引发的隐式转换。为我们想要滤掉的型别创建重载版本。
//尽管重载版本不可使用，但是还是程序的一部分。因此在重载决议的时候还是会被纳入考量。
void luck(int);
void luck(double) = delete;
void luck(bool) = delete;

class Base{
public:
	virtual ~Base(){};
	virtual void mf1() const{};
	virtual void mf2(int x){};
};

class Derived : public Base{
public:
	void mf1() const override{

	};
	virtual void mf2(int x) override{};
	//virtual void mf3(int x) override{};		//编译不过 因为Base没有mf3
};

class W{

public:
	using DataType = std::vector<int>;

	DataType& data() &{
		return vec;
	}

	DataType data() &&{
		return std::move(vec);
	}
private:
	DataType vec;
};

W makeW(){
	return W();
}

constexpr int add(int base, int exp) noexcept{
	//如果在函数中调用了非constexpr函数，那么该函数将是普通函数。
	//Widget w;
	//w.doWork();

	//constexpr函数中不允许有IO
	//std::cout << "123";
	return base + exp;
}


class Point{

public:

	Point() = default;
	//Point(const Point& ){}
	Point(Point&& ){}

	int callCnt() const{
		return cnt;
	}

	void func() const{

		++cnt;
		std::cout << "call func" <<std::endl;
	}

	double foo() const{
		//使用lock_guard对象管理互斥量
		//构造加锁，析构解锁
		std::lock_guard<std::mutex> g(mx);
		if(!flag){
			pi = 3.14;
			flag = true;
		}
		return pi;
	}

private:
	mutable std::atomic<int> cnt {0};	//对于当个变量的内存操作，可以使用atomic变量，比互斥量提供更好的性能

	mutable std::mutex mx;				//声明为mutable 因为加锁解锁都不是const函数所为
	mutable bool flag {false};
	mutable double pi {0};
};

class MapTool{

public:
	MapTool() = default;
	~MapTool() = default;
	MapTool(const MapTool& rhs){
		std::cout << "call copy cstr" << std::endl;
		ump = rhs.ump;
	}
	//显示定义析构或复制，就不会自动生成移动操作。
	MapTool(MapTool && rhs)  = default;

	void printMap(){
		//lambda表达式里面如果要访问其他成员，需要capture this指针
		std::for_each(std::begin(ump), std::end(ump), [this](const std::pair<std::string, int>& m){std::cout << m.first << " " << m.second << " " << a <<std::endl;});
	}

private:
	int a {1000};
	//具备移动操作。
	std::unordered_map<std::string, int> ump {{"ly", 100}, {"pp", 200}};
};

class MMMM{

public:
	MMMM() = default;
	//按成员移动：把std::move应用于每个移动源对象，返回值用于函数重载决议，来决定是移动还是复制。支持移动的成员就移动，不支持的就复制。
	MMMM(MMMM&& rhs) = default;
private:
	MapTool mt;
};




#endif /* MODERN_MODERN_H_ */

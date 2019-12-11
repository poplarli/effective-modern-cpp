/*
 * modern.h
 *
 *  Created on: 2019��12��10��
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

//ʹ��using����
template<typename T>
using MyList = std::list<T>;

//ʹ��typedef
template<typename T>
struct MyList2{
	typedef std::list<T> type;
};

//���޶�������ö�ٵ�ǰ������,��Ҫ�����ײ����͡�
enum E1 : int;
//�޶��������ö�٣�Ĭ�ϵײ���int
enum class E2;

template<typename T>
class A{
	//��������typename
	typedef typename MyList2<T>::type wtype;
private:
	wtype w;
	MyList<T> l;	//ʹ�÷���
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

	//&�����δ� ��ֵ����
	void doWork() &{
		std::cout << "call doWork() &" << std::endl;
	}

	//&&�����δ� ��ֵ����
	void doWork() &&{
		std::cout << "call doWork() &&" << std::endl;
	}

private:
	int a_{1};		//�����ų�ʼ��Ĭ��ֵ
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

//0��NULL���������ͱ𣬲��߱�ָ���ͱ�
//nullptr�����������ͱ𣬿��԰�������������ͱ��ָ�롣
//ʹ�ÿ�ָ����ʹ��nullptr
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

//����ʹ��ɾ������������privateΪ���庯��
class D{

public:
	//ʹ��delete����private�ĺ�������������ֹ���ƺ͸�ֵ�������ĵ��á�
	//ʹ��public���Դӱ�����Ϣ�еõ��ϺõĴ�����Ϣ��
	D(const D&) = delete;
	D& operator=(const D&) = delete;

	template<typename T>
	void func(T param){}
};

//ʹ��delete��ɾ�����ڲ���ģ���ػ������ʹ��private���������ˡ�
template<>
void D::func(void*) = delete;

template<typename T>
void func2(T param){}

//ʹ��delete��ɾ��ģ�����
template<>
void func2(int) = delete;
template<>
void func2(double) = delete;

//ʹ��delete����ֹ����luck(int)ʱ����double����bool��������ʽת����Ϊ������Ҫ�˵����ͱ𴴽����ذ汾��
//�������ذ汾����ʹ�ã����ǻ��ǳ����һ���֡���������ؾ����ʱ���ǻᱻ���뿼����
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
	//virtual void mf3(int x) override{};		//���벻�� ��ΪBaseû��mf3
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
	//����ں����е����˷�constexpr��������ô�ú���������ͨ������
	//Widget w;
	//w.doWork();

	//constexpr�����в�������IO
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
		//ʹ��lock_guard�����������
		//�����������������
		std::lock_guard<std::mutex> g(mx);
		if(!flag){
			pi = 3.14;
			flag = true;
		}
		return pi;
	}

private:
	mutable std::atomic<int> cnt {0};	//���ڵ����������ڴ����������ʹ��atomic�������Ȼ������ṩ���õ�����

	mutable std::mutex mx;				//����Ϊmutable ��Ϊ��������������const������Ϊ
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
	//��ʾ�����������ƣ��Ͳ����Զ������ƶ�������
	MapTool(MapTool && rhs)  = default;

	void printMap(){
		//lambda���ʽ�������Ҫ����������Ա����Ҫcapture thisָ��
		std::for_each(std::begin(ump), std::end(ump), [this](const std::pair<std::string, int>& m){std::cout << m.first << " " << m.second << " " << a <<std::endl;});
	}

private:
	int a {1000};
	//�߱��ƶ�������
	std::unordered_map<std::string, int> ump {{"ly", 100}, {"pp", 200}};
};

class MMMM{

public:
	MMMM() = default;
	//����Ա�ƶ�����std::moveӦ����ÿ���ƶ�Դ���󣬷���ֵ���ں������ؾ��飬���������ƶ����Ǹ��ơ�֧���ƶ��ĳ�Ա���ƶ�����֧�ֵľ͸��ơ�
	MMMM(MMMM&& rhs) = default;
private:
	MapTool mt;
};




#endif /* MODERN_MODERN_H_ */

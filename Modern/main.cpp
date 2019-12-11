/*
 * main.cpp
 *
 *  Created on: 2019��12��10��
 *      Author: poplarli
 */



#include <iostream>
#include <typeinfo>
#include <vector>
#include <type_traits>
#include <list>
#include "modern.h"

int main(){

	//���ô����ų�ʼ��������û���βεĹ��캯���������������дWidget w1(),�ͻ������⡣��Ϊ��������һ��������
	Widget w2{};
	w2.f();

	//int a = {1.1};	���벻���������ų�ʼ��������ֹ��ʽխ������ת����
	int b = 1.2;
	int c(1.3);

	auto d = {3};
	std::cout << typeid(d).name() << std::endl;

	//������ѡ��initialized_list�����Ĺ��캯����
	Widget w3{1,false};

	//���벻������Ϊ���ǻ�ѡ��initialized_list�����Ĺ��캯�������Ǵ���double->int��խ��ת����
	//Widget w4{1.1,false};

	//���ڼ���Ĭ�Ϲ��캯��������initialized_list�����Ĺ��캯����������õ���Ĭ�Ϲ��캯����
	Widget w1;
	//�����ǵ���initialized_list�����Ĺ��캯��
	Widget w4({});
	Widget w5{{}};

	//������ȫ��һ��
	std::vector<int> v1(2,3);
	std::vector<int> v2{2,3};
	printVec(std::move(v1));	//3 3
	printVec(std::move(v2));	//2 3

	doSomeWork<std::vector<int>>(2,3);

	std::mutex m1;
	//lockAndCall(f1, m1, 0);	//���벻����could not convert ��ptr�� from ��int�� to ��std::shared_ptr<Widget>��
	lockAndCall(f1, m1, nullptr);

	f1(0);	//������Ե��á�
	std::shared_ptr<int> sp = 0; //������Ե��á�


	std::cout << std::is_same<Widget, std::remove_const_t<const Widget>>::value << std::endl;

	//typedef��֧��ģ�壬��������֧��
	MyList<int> lst;
	MyList2<int>::type lst2;

	//�޶���Χ��ö������
	enum class Color{RED, BLUE, GREEN};
	auto m = Color::RED;
	//double r = m + 1.0;	//���벻�����޶��������ö�����Ͳ�����ʽת��·��
	double r = static_cast<double>(m) + 1.0;

	using UserInfo = std::tuple<std::string, int, int>;
	UserInfo u{"pp", 31, 175};
	std::cout << "age = "<< std::get<1>(u) << std::endl;
	//����ʹ�÷��޶�ö��Ҫ����Щ��
	enum User {NAME, AGE, HEIGHT};
	std::cout << "name = "<< std::get<User::NAME>(u) << std::endl;
	//ʹ���޶�ö��
	enum class User2 : long long {NAME, AGE, HEIGHT};
	std::cout << "height = " << std::get<toUType(User2::HEIGHT)>(u) << std::endl;

	//underlying_type_t����ö����ĵײ�����
	std::cout << std::is_same<int, std::underlying_type_t<User2>>::value << std::endl;			//false
	std::cout << std::is_same<long long, std::underlying_type_t<User2>>::value << std::endl;	//true

	makeWidget().doWork();

	//������ֵ���ã�data()������ֵ���Ӷ�����vector���ƶ����캯����
	W::DataType vec1 = makeW().data();
	//������ֵ���ã�����vector�ĸ��ƹ��캯��
	W w;
	W::DataType vec2 = w.data();


	//C++11�£���ʹ��const_iterator��ʹ��
	auto it = std::cbegin(v1);
	//����ͨ�õĴ��������ѡ�÷ǳ�Ա�����汾��begin��end��rbegin��rend��
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


	//constexpr��const��const����constexpr��
	//����Ҫ������ڼ䳣�����ﾳ��ֻ����constexpr
	const auto var = x;
	//std::array<int, var> data; //���벻�� the value of ��var�� is not usable in a constant expression
	//constexpr auto var2 = y; //���벻�� the value of ��y�� is not usable in a constant expression
	constexpr auto var3 = 10;
	std::array<int, var3> data2;

	//constexptr�����������ڱ������������ﾳ�£�ǰ���Ǵ���constexptr������ʵ���Ǳ�����������������ǣ���ô����ʧ�ܡ�
	std::array<int, add(2,3)> data3; //add����ǰ���constexpr��ʾ���ʵ���Ǳ����ڼ䳣������ôadd���ؽ�����Ե��������ڼ䳣����
	//std::array<int, add(x,y)> data4; ���벻��

	//�������constexptr�����Ĳ����ڱ�����δ֪����ô����ͨ��������
	add(x,y);	//ִ���ڼ䱻����


	Point pt;
	pt.func();
	pt.func();
	std::cout << pt.callCnt() << std::endl;

	pt.foo();

	//Point pt2 = pt; ���벻�� ��Ϊmutex��atomic���󶼲��ܸ��ơ�������ʾ���帴�ƹ��캯��
	Point pt2(std::move(pt));

	MapTool mt1;
	MapTool mt2(std::move(mt1));
	mt2.printMap();

	MMMM mm1;
	MMMM mm2(std::move(mm1));
	return 0;
}


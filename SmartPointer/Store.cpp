/*
 * Store.cpp
 *
 *  Created on: 2019Äê12ÔÂ11ÈÕ
 *      Author: poplarli
 */

#include "Store.h"
#include <string>


struct Store::Food{
	std::string name_;
	double price;
};

Store::Store() : pf(std::make_unique<Food>()){
}

Store::~Store() = default;

Store::Store(Store&& rhs) = default;
Store& Store::operator=(Store&& rhs) = default;

Store::Store(const Store& rhs) : pf(std::make_unique<Food>(*rhs.pf)){

}

Store& Store::operator=(const Store& rhs){
	*pf = *rhs.pf;
	return *this;
}

/*
 * Store.h
 *
 *  Created on: 2019Äê12ÔÂ11ÈÕ
 *      Author: poplarli
 */

#ifndef SMARTPOINTER_STORE_H_
#define SMARTPOINTER_STORE_H_

#include <iostream>
#include <memory>


class Store{

public:
	Store();
	~Store();
	Store(const Store&);
	Store& operator=(const Store& rhs);
	Store(Store&& rhs);
	Store& operator=(Store&& rhs);

private:
	struct Food;
	std::unique_ptr<Food> pf;
};




#endif /* SMARTPOINTER_STORE_H_ */

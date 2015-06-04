#ifndef FunctionHashTable_H__
#define FunctionHashTable_H__

/*!
 * \file FunctionHashTable.h
 *
 * \author CHE
 * \date 五月 2015
 *
 * 存放函数指针的hashtable，专用
 */
#include "NetCommunicationProtocol.h"
#include <initializer_list>
#include <QVector>
#include <QPair>
using std::initializer_list;
template<typename _Key, typename _Value>
class FunctionHashTable
{
public:
	typedef _Key key_type;
	typedef _Value value_type;
	typedef QPair<key_type, value_type> il_type;
	FunctionHashTable(initializer_list<il_type> il){
		_Mem.resize(net::MAX_PROTOCOL);
		for each(auto val in il){
			_Mem.insert(val.first, val.second);
		}
	}

	const value_type& operator[](key_type key)const throw(){
		return _Mem.at(key);
	}
private:
	QVector<value_type> _Mem;
};
#endif // FunctionHashTable_H__

#ifndef Range_H__
#define Range_H__

/*!
 * \file Range.h
 *
 * \author CHE
 * \date ÁùÔÂ 2015
 *
 * Range
 */

#include "Packet.h"

class Range;
Q_DECLARE_METATYPE(Range);
class Range :public AbstractParseJson
{
	Q_OBJECT
public:
	Range() :left(0), right(0){}
	Range(int l, int r) :left(l), right(r){}
	Range(const Range &other) : left(other.left), right(other.right){}
	operator QVariant()const{
		return QVariant::fromValue(*this);
	}
	~Range(){}
	QT_MOC_MINE_DEFINITION(int, left, Left);
	QT_MOC_MINE_DEFINITION(int, right, Right);
};

#endif // Range_H__

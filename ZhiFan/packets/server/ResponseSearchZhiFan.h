#ifndef ResponseSearchZhiFan_H__
#define ResponseSearchZhiFan_H__

/*!
 * \file ResponseSearchZhiFan.h
 *
 * \author CHE
 * \date ÁùÔÂ 2015
 *
 * ResponseSearchZhiFan
 */
#include "ResponseGetZhiFanPublishPageOfRange.h"
class ResponseSearchZhiFanPacket : public ResponseGetZhiFanPublishPageOfRangePacket
{
	Q_OBJECT
public:
	ResponseSearchZhiFanPacket(net::NetCommunicationProtocol _protocol = net::ResponseSearchZhiFan) :ResponseGetZhiFanPublishPageOfRangePacket(_protocol){}
};
#endif // ResponseSearchZhiFan_H__

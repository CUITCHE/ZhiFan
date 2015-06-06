#ifndef ResponseGetOneZhiFanPublish_H__
#define ResponseGetOneZhiFanPublish_H__

/*!
 * \file ResponseGetOneZhiFanPublish.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * For：获取知返的详细内容（详细）：GetOneZhiFanPublish：ResponseGetOneZhiFanPublish

 */
#include "ZhiFanPublishOne.h"

class ResponseGetOneZhiFanPublishPacket : public ZhiFanPublishOnePacket
{
	Q_OBJECT
public:
	ResponseGetOneZhiFanPublishPacket(){}
	~ResponseGetOneZhiFanPublishPacket()override{}
};

#endif // ResponseGetOneZhiFanPublish_H__

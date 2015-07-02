#ifndef Error_H__
#define Error_H__

/*!
 * \file Error.h
 *
 * \author CHE
 * \date ���� 2015
 *
 * �����࣬�����˷���˵����д���
 */
class Error
{
public:
	void operator=(QString val);
	void operator=(unsigned int errNum);
	operator int()const;
	operator QString()const;
	Error(){}
	~Error(){}
private:
	QString errorMsg;
	unsigned int errNum;
};
#endif // Error_H__

#ifndef Error_H__
#define Error_H__

/*!
 * \file Error.h
 *
 * \author CHE
 * \date 五月 2015
 *
 * 错误类，定义了服务端的所有错误
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

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
	void operator=(int val);
	void setProtocol(unsigned int p);
	unsigned int getProtocol()const;
	operator int()const;
	Error();
	~Error(){}
private:
	int error;
	unsigned int operatorProtocol;
};
#endif // Error_H__

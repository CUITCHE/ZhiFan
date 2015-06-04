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

enum Errors : unsigned int{
	//存在error，但不知道是什么错误
	ExistsError,
	//没有错误
	NoError,
	//登陆：被拒绝
	LoginReject,
	//注册：帐号已存在
	RegAccountExisted,
	//注册：失败
	RegFailed
};


class Error
{
public:
	void operator=(Errors e);
	void setProtocol(unsigned int p);
	unsigned int getProtocol()const;
	operator Errors()const;
	Error();
	~Error(){}
private:
	mutable Errors error;
	unsigned int operatorProtocol;
};
#endif // Error_H__

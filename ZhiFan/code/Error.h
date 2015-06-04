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

enum Errors : unsigned int{
	//����error������֪����ʲô����
	ExistsError,
	//û�д���
	NoError,
	//��½�����ܾ�
	LoginReject,
	//ע�᣺�ʺ��Ѵ���
	RegAccountExisted,
	//ע�᣺ʧ��
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

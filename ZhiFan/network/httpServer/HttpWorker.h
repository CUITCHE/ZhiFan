#ifndef HTTPWORKER_H
#define HTTPWORKER_H
/*!
 * \file HttpWorker.h
 *
 * \author CHE
 * \date 七月 2015
 *
 * 处理http请求
 */
#include <QObject>

class HttpWorkerPrivate;

__interface IHttpHtml
{
	/*
	@brief 用户中心页面，第一个tab页
	*/
	void userCenter();

	/*
	@brief 帐号管理界面
	*/
	void accountMananger();

	/*
	@brief 通知中心
	*/
	void noticeCenter();

	/*
	@brief 我发布的知返
	*/
	void myPublished();

	/*
	@brief 我参与过的知返（回答过的，点赞过的）
	*/
	void myJoined();
};

class HttpWorker : public QObject, public IHttpHtml
{
	Q_OBJECT

public:
	HttpWorker(QObject *parent = 0);
	~HttpWorker();

	/*
	 @brief 传入的是HttpRequestParser类型的指针，是已经做过分析的HttpRequestParser
	*/
	void setObject(QObject *object);

	/*
	 @brief 做生成任务，将生成的字符串返回
	*/
	void getResponseString(QByteArray &out);
protected:
	HttpWorkerPrivate *const d_ptr;
	/*
	@brief 用户中心页面，第一个tab页
	*/
	void userCenter();

	/*
	@brief 分发任务
	*/
	void dispatch();

	/*
	@brief 帐号管理界面
	*/
	void accountMananger();

	/*
	@brief 通知中心
	*/
	void noticeCenter();

	/*
	@brief 我发布的知返
	*/
	void myPublished();

	/*
	@brief 我参与过的知返（回答过的，点赞过的）
	*/
	void myJoined();
private:
	Q_DECLARE_PRIVATE(HttpWorker);
	/*
	@brief 帐号验证，先验证帐号是否在线，在验证token是否正确
	@return 成功返回true
	*/
	bool accountVerification(const QString &userid, const QString &token);

	/*
	@brief 写403 Forbidden
	*/
	void write403();

	/*
	@brief 写404 Not Found html
	*/
	void write404();

	/*
	@brief 发送文件
	*/
	void writeFile(const QString &path);
};

#endif // HTTPWORKER_H

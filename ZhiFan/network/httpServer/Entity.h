#ifndef Entity_H__
#define Entity_H__

/*!
 * \file Entity.h
 *
 * \author CHE
 * \date 六月 2015
 *
 * 实体基类，
 * 子类需要重写update函数，并调用基类的update函数，实体类才能正常运行
 * isVaild：可以根据需求，选择重写。
 */
#include "defs.h"
#include <QString>
#include <QDateTime>
#include <QMutex>
class Packet;
class Entity
{
public:
#define __lock__ Q_lock(mtx)
public:
	Entity();
	virtual ~Entity();

	void update(const Packet *pck);

	//记录此实体生成时间
	ENTITY_MEMBER_DEFINITION(QTime, generatedTime);
protected:
	//子类需重写这个函数
	virtual void update_impl(const Packet *pck) = 0;

	//子类自行控制，实体过期时间，默认是15分钟过期
	//If it needs not update, it will return true
	virtual bool isVaild(const QTime& other);

	//每当更新实体数据的时候，需要调用此函数
	void updateTime();
protected:
	QMutex* mtx;
};

#define ENTITY_CLASS_DEFINITION_BEGIN(Class)\
	class Class: public Entity{\
	public:Class(){} ~##Class()override{}\
	void update_impl(const Packet *pck)override;
#define ENTITY_CLASS_DEFINITION_END };
#endif // Entity_H__

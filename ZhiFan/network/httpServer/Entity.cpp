#include "stdafx.h"
#include "Entity.h"
using namespace std;

Entity::Entity()
	:mtx(new QMutex)
	, _generatedTime()
{
}

Entity::~Entity()
{
	delete mtx;
}

void Entity::update(const Packet *pck)
{
	if (!this->isVaild(QTime::currentTime())){
		updateTime();
		this->update_impl(pck);
	}
}

void Entity::updateTime()
{
	_generatedTime = QTime::currentTime();
}

bool Entity::isVaild(const QTime& other)
{
	const int vaildSecs = 15 * 60;
	return _generatedTime.secsTo(other) < vaildSecs;
}
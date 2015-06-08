#include "stdafx.h"
#include "AbstractParseJson.h"
#include "ZhiFanPublishBriefOne.h"
#include "Range.h"
#include <QJsonDocument>
template<class T>
void ComplexToQVariant(const T &toConvert, QVariant &result){
	QVariantMap data = toConvert.read();
	result = data;
}

template<class T>
void ComplexListToQVariantList(const QList<T> &toConvert, QList<QVariant> &result){
	QVariant tmp;
	for (const T& val : toConvert){
		ComplexToQVariant(val, tmp);
		result.push_back(tmp);
	}
}

template<class T>
void QVariantToComplex(const QVariant &toConver, T &object){
	QVariantMap data = toConver.toMap();
	object.write(data);
}

template<class T>
void QVariantListToComplexList(const QList<QVariant> &toConvert, QList<T> &object){
	T tmp;
	for (const auto &val : toConvert){
		QVariantToComplex(val, tmp);
		object.push_back(tmp);
	}
}

AbstractParseJson::AbstractParseJson(QObject *parent)
	: QObject(parent){}
AbstractParseJson::AbstractParseJson(const AbstractParseJson&){}
AbstractParseJson &AbstractParseJson::operator =(const AbstractParseJson &){return *this;}
AbstractParseJson::~AbstractParseJson(){}

void AbstractParseJson::qobject2qvariant(QVariantMap &variant)const
{
	const QObject *object = dynamic_cast<const QObject *>(this);

	const QMetaObject *metaobject = object->metaObject();
	int count = metaobject->propertyCount();
	for (int i = 1; i < count; ++i){
		QMetaProperty metaProperty = metaobject->property(i);
		const char *name = metaProperty.name();
		QVariant value = object->property(name);
		QVariant::Type type = metaProperty.type();
		if (!value.canConvert(type)){
			QString typeName = metaProperty.typeName();
			if (typeName.compare("QList<ZhiFanPublishBriefOnePacket>") == 0){
				QList<ZhiFanPublishBriefOnePacket> data = value.value<QList<ZhiFanPublishBriefOnePacket>>();
				QList<QVariant> tmp;
				ComplexListToQVariantList(data, tmp);
				value = tmp;
			}
			else if (typeName.compare("Range") == 0){
				Range data = value.value<Range>();
				QVariant tmp;
				ComplexToQVariant(data, tmp);
				value = tmp;
			}
		}
		//qDebug() << value;
		variant[QLatin1String(name)] = value;
	}
}

void AbstractParseJson::qvariant2qobject(const QVariantMap &variant)
{
	QObject *object = dynamic_cast <QObject *>(this);
	const QMetaObject *metaobject = object->metaObject();
	QVariantMap::const_iterator iter = variant.constBegin();
	int index = -1;
	while (iter != variant.end()){
		index = metaobject->indexOfProperty(iter.key().toLatin1());
		if (index < 0){
			++iter;
			continue;
		}
		QMetaProperty metaProperty = metaobject->property(index);
		QVariant::Type type = metaProperty.type();
		QVariant v(iter.value());
		if (v.canConvert(type)){
			v.convert(type);
			metaProperty.write(object, v);
		}
		else if (QString(QLatin1String("QVariant")).compare(QLatin1String(metaProperty.typeName())) == 0){
			metaProperty.write(object, v);
		}
		else{
			QString typeName = metaProperty.typeName();
			if (typeName.compare("QList<ZhiFanPublishBriefOnePacket>") == 0){
				QList<QVariant> data = v.toList();
				QList<ZhiFanPublishBriefOnePacket> tmp;
				QVariantListToComplexList(data, tmp);
				metaProperty.write(object, QVariant::fromValue(tmp));
			}
			else if (typeName.compare("Range") == 0){
				QVariant data = v;
				Range tmp;
				QVariantToComplex(data, tmp);
				metaProperty.write(object,tmp);
			}
		}
		++iter;
	}
}

QVariant AbstractParseJson::getValue(const char *key) const
{
	return this->property(key);
}

void AbstractParseJson::setValue(const char *key, const QVariant &val)
{
	this->setProperty(key, val);
}

void AbstractParseJson::write(const QVariantMap &val)
{
	this->qvariant2qobject(val);
}

QVariantMap AbstractParseJson::read()const
{
	QVariantMap data;
	this->qobject2qvariant(data);
	return data;
}

QByteArray AbstractParseJson::toJson(QJsonDocument::JsonFormat format /*= QJsonDocument::JsonFormat::Indented*/) const
{
	auto mapdata = read();
	QJsonDocument json = QJsonDocument::fromVariant(mapdata);
	return json.toJson(format);
}


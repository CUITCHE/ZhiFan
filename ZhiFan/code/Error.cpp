#include "stdafx.h"
#include "Error.h"

Error::Error()
	:error(0)
{

}

void Error::setProtocol(unsigned int p)
{
	operatorProtocol = p;
}

unsigned int Error::getProtocol() const
{
	return operatorProtocol;
}

Error::operator int() const
{
	return error;
}

void Error::operator=(int val)
{
	error = val;
}

#include "stdafx.h"
#include "Error.h"


void Error::operator=(unsigned int errNum)
{
	this->errNum = errNum;
}

Error::operator int() const
{
	return errNum;
}

void Error::operator=(QString val)
{
	errorMsg = val;
}

Error::operator QString() const
{
	return errorMsg;
}

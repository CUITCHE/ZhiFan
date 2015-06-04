#include "Error.h"

Error::Error()
	:error(NoError)
{

}

Error::operator Errors() const
{
	return error;
}

void Error::operator=(Errors e)
{
	error = e;
}

void Error::setProtocol(unsigned int p)
{
	operatorProtocol = p;
}

unsigned int Error::getProtocol() const
{
	return operatorProtocol;
}

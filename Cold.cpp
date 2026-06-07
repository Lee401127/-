#include "Cold.h"

int Cold::getElderid() const
{
	return this->elder_id;
}

void Cold::setElderid(int elderid)
{
	this->elder_id = elderid;
}

string Cold::getUserphone() const
{
	return user_phone;
}


void Cold::setUserphone(string userphone)
{
	user_phone = userphone;
}


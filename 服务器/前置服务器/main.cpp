#include<iostream>
#include "CEpollServer.h"

using namespace std;


int main()
{


	CEpollServer epollserver(10086);
	epollserver.EpollStart();




	return 0;








}
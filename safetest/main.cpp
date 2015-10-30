#include "SafeApplication.h"

int main()
{
	SafeApplication SafeApp;
	SafeApp.init();
	SafeApp.play();
	SafeApp.term();
	return 0;
}
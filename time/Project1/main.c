#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
	char current_time[30] = {0}, *p;
	time_t time_second;
	struct tm* utc_time;

	time(&time_second);
	p = current_time;
	p = ctime(&time_second);
	printf("Current time(local): %s\n",p);

	utc_time = gmtime(&time_second);
	time_t UTC = mktime(utc_time);
	p = ctime(&UTC);
	printf("Current time(UTC): %s\n",p);
	return 0;
}

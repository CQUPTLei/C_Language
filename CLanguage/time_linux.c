#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int main() {
    struct timeval current_time;
    struct tm set_time ={ 0, 0, 0, 1, 0, 120, },*diff_readable;
    char time_str[30], *p;

    if (gettimeofday(&current_time, NULL) == 0) {
        p = ctime(&current_time.tv_sec);
        printf("Current time is %s", p); // 注意这里的字符串本来就是以换行符结尾的
        printf("It has passed %ld seconds %ld microseconds since 1970-1-1\n", current_time.tv_sec, current_time.tv_usec);
    } else {
        perror("gettimeofday");
    }

    time_t set_t = mktime(&set_time);
    printf("I set a time: %s", asctime(&set_time));

    double diff = difftime(current_time.tv_sec, set_t);
    printf("Time diff between current time and set time  is %ld seconds\n",(long)(diff));

    time_t diff_time = (time_t)diff;
    diff_readable = gmtime(&diff_time);
    printf("Transform to be readable :%d yesrs %d months %d days %d hours\n",
           diff_readable->tm_year-70, diff_readable->tm_mon+1,
           diff_readable->tm_mday, diff_readable->tm_hour);

    return 0;
}

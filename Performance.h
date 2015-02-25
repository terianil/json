#include <sys/time.h>
#include <sys/resource.h>

// zajętość pamięci w KB
long GetMemorySize()
{
    long rss = 0L;
    FILE* fp = NULL;
    if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL )
        return (size_t)0L;		/* Can't open? */
    if ( fscanf( fp, "%*s%ld", &rss ) != 1 )
    {
        fclose( fp );
        return (size_t)0L;		/* Can't read? */
    }
    fclose( fp );

    return ((size_t)rss * (size_t)sysconf( _SC_PAGESIZE))/1024;
}

timespec Time()
{
    timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);

    return time;
}

timespec TimeDiff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}
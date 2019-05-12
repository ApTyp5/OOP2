#include "exception.h"
#include "stdio.h"
#include <sstream>


Exception::Exception(const time_t time,
                     const char *className,
                     const char *method,
                     const char *extra_mess,
                     const char *addInfo):
    time(time),
    className(className),
    method(method),
    extra_mess(extra_mess),
    additionInfo(addInfo)
{}

const char *Exception::what() const noexcept
{
    size_t bufsize = 100;
    char *buf = new char [bufsize];

    struct tm *time_struct = localtime(&time);

    size_t len = strftime(buf, bufsize, "%d.%m.%Y\t%H:%M:%S\t", time_struct);
    snprintf(buf + len, bufsize - len, "%s\t%s\t%s\t%s\n",
             className, method, extra_mess, additionInfo);

    return buf;
}


out_of_range::out_of_range(const time_t time,
                           const char *className,
                           const char *method,
                           const char *addInfo):
    Exception (time, className, method, "out of range", addInfo){}

alloc_err::alloc_err(const time_t time,
                     const char *className,
                     const char *method,
                     const char *addInfo):
    Exception (time, className, method, "alloc_err", addInfo){}

wrong_sizes::wrong_sizes(const time_t time,
                     const char *className,
                     const char *method,
                     const char *addInfo):
    Exception (time, className, method, "wrong sizes", addInfo){}

damaged_iter::damaged_iter(const time_t time,
                           const char *className,
                           const char *method,
                           const char *addInfo):
    Exception (time, className, method, "damaged iterator", addInfo){}

bad_ptr::bad_ptr(const time_t time,
                 const char *className,
                 const char *method,
                 const char *addInfo):
    Exception (time, className, method, "bad_ptr", addInfo){}

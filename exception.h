#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <time.h>


class Exception : public std::exception
{
public:
    Exception(const time_t time,
              const char *className,
              const char *method,
              const char *extra_mess,
              const char *addInfo = nullptr);

    const char *what() const noexcept override;

protected:
    const time_t time;
    const char *className;
    const char *method;
    const char *extra_mess;
    const char *additionInfo;
};

class out_of_range : public Exception
{
public:
    out_of_range(const time_t time,
                 const char *className,
                 const char *method,
                 const char *addInfo = nullptr);
};


class alloc_err : public Exception
{
public:
    alloc_err(const time_t time,
              const char *className,
              const char *method,
              const char *addInfo = nullptr);
};

class wrong_sizes : public Exception
{
public:
    wrong_sizes(const time_t time,
                const char *className,
                const char *method,
                const char *addInfo = nullptr);
};

class damaged_iter : public Exception
{
public:
    damaged_iter(const time_t time,
                 const char *className,
                 const char *method,
                 const char *addInfo = nullptr);
};

class bad_ptr :public Exception
{
public:
    bad_ptr(const time_t time,
            const char *className,
            const char *method,
            const char *addInfo = nullptr);
};

#endif // EXCEPTION_H

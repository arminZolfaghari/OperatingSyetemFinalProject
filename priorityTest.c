#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int main()
{
    int a = 4;
    int res = setPriority(a);
    printf(1, "%d\n\n\n", res);

    return 0;
}
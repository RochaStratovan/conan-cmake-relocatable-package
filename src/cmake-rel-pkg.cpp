#include <stdio.h>


// This is silly stuff just to illustrate a difference in the code
//
// Also, I think these are Visual Studio specific defines. Probably not
// portable.
#ifdef _DEBUG
    #define MSG_STR "DEBUG"
#else
    #define MSG_STR "NOT-DEBUG"
#endif   

void simple(void)
{
    printf("This is %s mode.\n", MSG_STR);
}

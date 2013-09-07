#include <sys/mman.h>
#include <stdio.h>
 
unsigned int arrCode[9] = {
    0x90909090, //NOP
    0x90909090,
    0x90909090,
    0x90909090,
    0x90909090,
    0x90909090,
    0x90909090,
    0x90909090,
    0x895590c3 //ret
};
 
int main()
{
    char *arrCodeBuff = (char *) &arrCode;
    printf("arrCodeBuff=%lx arrCode=%lx \n", arrCodeBuff, arrCode);
 
    arrCodeBuff = (char *)  ((int) arrCodeBuff / 4096 * 4096);  // align with page(4k)
    printf("arrCodeBuff=%lx arrCode=%lx \n", arrCodeBuff, arrCode);
 
    void (*fun)(void) = (void(*)(void)) arrCode;
    printf("start, %lx - %lx\n", &arrCode, arrCode);
//    mprotect(arrCodeBuff, 8192, PROT_READ | PROT_WRITE | PROT_EXEC);
    fun();
 
    printf("end\n");
    return 0;
}
/* 
$ ./a.out 
arrCodeBuff=804a040 arrCode=804a040 
arrCodeBuff=804a000 arrCode=804a040 
start, 804a040 - 804a040
end
 
 
如果mprotect那行被注释掉，则输出如下：
$ ./a.out 
arrCodeBuff=804a040 arrCode=804a040 
arrCodeBuff=804a000 arrCode=804a040 
start, 804a040 - 804a040
Segmentation fault (core dumped)
 
 */

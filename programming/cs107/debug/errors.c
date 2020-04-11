#include <stdio.h>
#include <stdlib.h>

/**
 * Segmentation fault demo. It often occurs when dereferencing a bad pointer,
 * such like NULL pointer.
 */
void segmentation_fault_demo()
{
    void *addr = NULL;
    int a = *(int *)addr;
    printf("a = %d\n", a);
}

/**
 * Bus error demo. It often happens when the memory is not aligned with the
 *  specific data type.
 * Derived from https://www.geeksforgeeks.org/segmentation-fault-sigsegv-vs-bus-error-sigbus/.
 */
void bus_error_demo()
{
#if defined(__GNUC__) 
# if defined(__i386__) 
    /* Enable Alignment Checking on x86 */
    __asm__("pushf\norl $0x40000,(%esp)\npopf"); 
# elif defined(__x86_64__)  
     /* Enable Alignment Checking on x86_64 */
    __asm__("pushf\norl $0x40000,(%rsp)\npopf"); 
# endif 
#endif 
    
    /* malloc() always provides aligned memory */
    char *cptr = malloc(sizeof(int) + 1); 
      
    /* Increment the pointer by one, making it 
       misaligned */
    int *iptr = (int *) ++cptr; 
  
    /* Dereference it as an int pointer, causing 
       an unaligned access */
    *iptr = 42; 
  
    /* Following accesses will also result in  
       sigbus error. 
       short *sptr; 
       int    i; 
  
       sptr = (short *)&i; 
  
       // For all odd value increments, it will 
       // result in sigbus. 
       sptr = (short *)(((char *)sptr) + 1); 
       *sptr = 100;    */
}

int main(int argc, char *argv[])
{
    // segmentation_fault_demo();
    // bus_error_demo();
    return 0;
}
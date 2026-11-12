#include <stddef.h>

/* The lab applications do not use libc. Keep the minimal startup dependency
 * required by the CMSIS vector template and aggregate initialization. */
void *memset(void *destination, int value, size_t count)
{
    unsigned char *bytes = (unsigned char *)destination;
    while (count--) *bytes++ = (unsigned char)value;
    return destination;
}

void __libc_init_array(void)
{
    /* No C++ constructors or application init arrays are used in these labs. */
}

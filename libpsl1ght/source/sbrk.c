#include <psl1ght/lv2.h>
#include <sys/reent.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>

// 64kb page allocations
//#define PAGE_SIZE		0x10000
//#define PAGE_SIZE_FLAG	0x200

// 1mb page allocations
#define PAGE_SIZE		0x100000
#define PAGE_SIZE_FLAG	0x400

#define ROUND_UP(p, round) \
	((p + round - 1) & ~(round - 1))

// Here's a very lazy and lossy sbrk. It's made of fail, but I'm lazy.
static char* current_mem = 0;
static char* end_mem = 0;

#if 0
caddr_t psl1ght_sbrk_r(struct _reent* r, ptrdiff_t increment)
{
    static int one = 1;

    if(one) {
        one = 0;
        size_t allocsize = ROUND_UP(200*1024*1024, PAGE_SIZE);
        u32 taddr = 0;

       
        if (Lv2Syscall3(348, allocsize, PAGE_SIZE_FLAG, (u64)&taddr)) {
            r->_errno = ENOMEM;
            return (void*)-1;
        }

        char* addr = (char*)(u64)taddr;
	    
		current_mem = addr;
	    end_mem = addr + allocsize;
   }


    if(current_mem + increment > end_mem) return (void*)-1;
    char* ret = current_mem;
	current_mem += increment;
    
    return  ret;
}

#endif

#define MAX_PAGES 16

static struct {
    char *start;
    char *end;
} pages[MAX_PAGES];



caddr_t psl1ght_sbrk_r(struct _reent* r, ptrdiff_t increment)
{
    static int one = 1;
    int n, m;
    char * ret;

    // initialize

    if(one) {
        one = 0;
        size_t allocsize = ROUND_UP(MAX_PAGES*1024*1024, PAGE_SIZE);
        u32 taddr = 0;

        for(n = 0; n < MAX_PAGES; n++) pages[n].start = pages[n].end = NULL;

        if (Lv2Syscall3(348, allocsize, PAGE_SIZE_FLAG, (u64)&taddr)) {
            r->_errno = ENOMEM;
            return (void*)-1;
        }

        char* addr = (char*)(u64)taddr;
	    
		current_mem = pages[0].start = addr;
	    end_mem = pages[0].end = addr + allocsize;
    }
    
   
    if(increment > 0) {

        // find current page
        for(n = 0; n < MAX_PAGES; n++) {
            if(current_mem >= pages[n].start  && current_mem < pages[n].end) break;
        }
     
        // if not found or page minor...
        if(n == MAX_PAGES || (current_mem + increment) > pages[n].end) {

            // test in the next pages
            if(n < (MAX_PAGES-1)) {
                for(m = n + 1; m < MAX_PAGES; m++) {
                    if(pages[m].start != NULL && (pages[m].start + increment) <= pages[m].end) break;
                }
                
                if(m < MAX_PAGES) {
                    current_mem = pages[m].start;
                    goto return_ok;
                }
            }

            size_t allocsize = ROUND_UP(increment, MAX_PAGES*1024*1024);
            u32 taddr = 0;

            if (Lv2Syscall3(348, allocsize, PAGE_SIZE_FLAG, (u64)&taddr)) {
                r->_errno = ENOMEM;
                return (void*)-1;
            }

            char* addr = (char*)(u64)taddr;

            // error if addr < end_mem

            if(end_mem > addr) {
                r->_errno = ENOMEM;
                return (void*)-1;
            }
            
            end_mem = addr + allocsize;

            // test for increase the page
            if(n != MAX_PAGES && pages[n].end == addr) {
                pages[n].end += allocsize;
            } else {

                // test empty page
                for(n = 0; n < MAX_PAGES; n++) if(pages[n].start == NULL) break;

                if(n == MAX_PAGES) {
                    r->_errno = ENOMEM;
                    return (void*)-1;
                }

                
                pages[n].start = addr;
                pages[n].end = addr + allocsize;

                current_mem = pages[n].start;
            }
        }
        
       
    } else if(increment < 0){
            
        buclea:

        // find current page
        for(n = 0; n < MAX_PAGES; n++) {
            if(current_mem >= pages[n].start && current_mem < pages[n].end) break;
        }

        if(n != MAX_PAGES) {
           
            if(pages[n].start > (current_mem + increment)) {

                if(pages[n].start == current_mem) {

                    n--;

                    if(n >= 0) {

                        int incre = (int) (pages[n].end - pages[n].start);
                        
                        // skip pages if increment is very big
                        if(incre < -increment) {increment +=  incre; current_mem = pages[n].start; goto buclea;}

                        if(pages[n].start >= pages[n].end + increment) {ret= current_mem; current_mem = pages[n].end + increment; return ret;}
                    }
       
                }
            } else goto return_ok;
        }
        
        
        r->_errno = ENOMEM;
        return (void*)-1;
    }
        
return_ok:

    ret = current_mem;
	current_mem += increment;
    
    return  ret;
}

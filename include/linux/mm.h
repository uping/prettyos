#include "asm-i386/page.h"
#ifndef __LINUX_LIST_H
#define __LINUX_LIST_H 
#include "list.h"
#endif

extern long memory_end; 
extern long main_memory_start;
extern long main_memory_end;
extern long memory_size;
extern long buffer_memory_start;
extern long buffer_memory_end;

extern struct page *mem_map;

extern int nr_swap_pages;
extern int nr_free_pages;

int alloc_mem(int pid,int memsize);
void init_mem(unsigned long start_mem,unsigned long end_mem);
int get_limit(struct descriptor *dp);
int get_base(struct descriptor *dp);

struct page
{
		struct list_head list;
		struct address_space *mapping;
		unsigned long index;
		struct page *next_hash;
		int count;
		unsigned long flags;
		struct list_head lru;
		wait_queue_head_t wait;
		struct buffer_head *buffers;
		struct zone_struct *zone;

};


#define oom() ({ panic ("memory fatal error!\n");})

#define  GFP_BUFFER 	0x001
#define  GFP_USER 		0x001
#define  GFP_ATOMIC 	0x002
#define  GFP_KERNEL 	0x003


extern void free_pages(unsigned long addr, unsigned long order);
extern unsigned long paging_init(unsigned long start_mem, unsigned long end_mem);
extern inline unsigned long get_free_page(int priority);
extern int zeromap_page_range(unsigned long address, unsigned long size, pgprot_t prot);

#define free_page(addr) 	free_pages((addr), 0)
#define MAP_NR(addr) 		(((unsigned long) addr) >> PAGE_SHIFT)


#define NR_MEM_LISTS 	6
/*
 * 1 page  1024
 * 2 pages 518
 * 3 pages 256 
 * 4 pages 128 
 * 5 pages 64 
 * 6 pages 32 
 *
 * */

struct mem_list 
{
	struct mem_list *next;
	struct mem_list *prev;
};

extern struct mem_list free_mem_list[NR_MEM_LISTS];
extern unsigned char * free_mem_map[NR_MEM_LISTS];


struct vm_area_struct 
{
		unsigned long vm_start;
		unsigned long vm_end;
		struct task_struct *vm_task;

		pgprot_t vm_page_prot;
		short vm_avl_height;
		unsigned short vm_flags;
		
		struct vm_area_struct *vm_avl_left;	
		struct vm_area_struct *vm_avl_right;	

		struct vm_area_struct *vm_next;	

		struct vm_area_struct *vm_next_share;	
		struct vm_area_struct *vm_prev_share;	

		struct vm_operation_struct *vm_ops;

		unsigned long vm_offset;
		struct 	m_inode *vm_inode;
		unsigned long 	vm_pte; //shared mem;
};

struct vm_operation_struct
{
		void (*open) (struct vm_area_struct *vma);
		void (*close) (struct vm_area_struct *vma);
		void (*unmap)(struct vm_area_struct *area, unsigned long, size_t);
};


#define 	VM_READ 		0x0001
#define 	VM_WRITE 		0x0002
#define 	VM_EXEC 		0x0004
#define 	VM_SHARED 		0x0008

#define 	VM_MAYREAD 		0x0010
#define 	VM_MAYWRITE 	0x0020
#define 	VM_MAYEXEC 		0x0040
#define 	VM_MAYSHARE 	0x0080

#define 	VM_GROWSDOWN 	0x0100
#define 	VM_GROWSUP 		0x0200
#define 	VM_SHM 			0x0400
#define 	VM_DENYWRITE 	0x0800

#define 	VM_EXECUTABLE  	0X1000
#define 	VM_STACK_FLAGS 	0x0177


extern unsigned long __get_free_pages(int priority, unsigned long gfporder);
#define  	__get_free_page(priority) 		__get_free_pages((priority),0)

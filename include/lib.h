#include "boot.h" 
//       klib.asm 
extern void     out_byte(t_port port, t_8 value);
t_8      		in_byte(t_port port);
extern void     disable_int();
extern void     enable_int();
extern void     disp_str(char * info);
// void     disp_int(int i);
extern void     disp_color_str(char * info, int color);
extern void     clear_screen();
//       tlib.c 
t_bool   		is_alphanumeric(char ch);
extern void     delay(int time);
extern void     itoa(char* str, int num);
extern void     disp_int(int input);

//       misc.c 
extern void     spin(char *str);
extern void     assertion_failure(char *exp,char *file,char *base_file,int line);
/*
extern int 		strncmp(char *str1,char *str2,int len);
extern int 		strncpy(char *dest,char *src,int pos,int size);
extern int 		strcpy(char *dst, char *src);
extern int 		strcmp(char *str1,char *str2);

*/

extern void 	get_boot_params(struct boot_params *bp);
extern int 		get_kernel_map(unsigned int * base, unsigned int * limit);

extern int 		phys_copy(char * dst, char * src,int size);
extern int 		u_phys_copy(unsigned char * dst, unsigned char * src,int size);
#define 		memncpy(d,s,l) do{u_phys_copy(d,s,l);}while(0)
extern int 		memcmp(char *dst, char *src,int len);
extern int 		memset(char *dst, char ch,int len);
extern int 		strlen(char *str);

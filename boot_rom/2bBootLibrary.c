
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************

	2003-01-12 andy@warmcat.com  Created from other files, enhanced malloc
	                             greatly so it is more like a stdc one

*/
#include "2bload.h"


void * memcpy(void *dest, const void *src,  size_t size) {

	BYTE * pb=(BYTE *)src, *pbd=(BYTE *)dest;
	while(size--) *pbd++=*pb++;
	return dest;
}


int strlen(const char * sz) { 
	int n=0; while(sz[n]) n++; 
	return n; 
	}


void * memset(void *dest, int data,  size_t size) {
//    bprintf("memset(0x%x,0x%x,0x%x);\n", dest, data, size);
    __asm__ __volatile__ (
              "    push %%eax    \n"
              "    push %%edi    \n"
              "    push %%ecx    \n"
              "    mov %0, %%edi \n"
              "    mov %1, %%eax \n"
              "    mov %2, %%ecx \n"
              "    shr $2, %%ecx \n"
              "    rep stosl     \n"
              "    pop %%ecx     \n"
              "    pop %%edi     \n"
              "    pop %%eax     \n"
              : : "S" (dest), "%eax" (data), "c" (size)
		);
	return dest;
}

int _memcmp(const BYTE *pb, const BYTE *pb1, int n) {
	while(n--) { if(*pb++ != *pb1++) return 1; }
	return 0;
}

	// this is the memory managemnt struct stored behind every allocation






char * strcpy(char *sz, const char *szc)
{
	char *szStart=sz;
	while(*szc) *sz++=*szc++;
	*sz='\0';
	return szStart;
}

char * _strncpy(char *sz, const char *szc, int nLenMax)
{
	char *szStart=sz;
	while((*szc) && (nLenMax--)) *sz++=*szc++;
	*sz='\0';
	return szStart;
}


int _strncmp(const char *sz1, const char *sz2, int nMax) {

	while((*sz1) && (*sz2) && nMax--) {
		if(*sz1 != *sz2) return (*sz1 - *sz2);
		sz1++; sz2++;
	}
	if(nMax==0) return 0;
	if((*sz1) || (*sz2)) return 0;
	return 0; // used up nMax
}



char *strrchr0(char *string, char ch) {
        char *ptr = string;
	while(*ptr != 0) {
		if(*ptr == ch) {
			return ptr;
		} else {
			ptr++;
		}
	}
	return NULL;
}
#include "boot.h"
#include "video.h"
#include "memory_layout.h"
#include <shared.h>
#include <filesys.h>
#include "rc4.h"
#include "sha1.h"
#include "BootFATX.h"
#include "xbox.h"
#include "BootFlash.h"
#include "cpu.h"

void BootFromCD(void) {
	CONFIGENTRY config;
	BootLoadConfigCD(&config);
	ExittoLinux(&config);
}

void BootFromFATX(void) {
	CONFIGENTRY config;
	BootLoadConfigFATX(&config);
	ExittoLinux(&config);
}

//More grub bits
unsigned long saved_drive;
unsigned long saved_partition;
grub_error_t errnum;
unsigned long boot_drive;

extern unsigned long current_drive;

void BootFromNative(void) {
	CONFIGENTRY config;
	//This stuff is needed to keep the grub FS code happy.
	char szGrub[256+4];
	int menu=0,selected=0;
	
	//Making this another global isn't brilliant, but until I pass member data sensibly
	//to these functions, it will do.
	extern int nActivePartitionIndex;

	memset(szGrub,0x00,sizeof(szGrub));
	szGrub[0]=0xff;
	szGrub[1]=0xff;
	szGrub[2]=nActivePartitionIndex;
	szGrub[3]=0x00;
	errnum=0;
	boot_drive=0;
	saved_drive=0;
	saved_partition=0x0001ffff;
	buf_drive=-1;
	current_partition=0x0001ffff;
	current_drive=0xff;
	buf_drive=-1;
	fsys_type = NUM_FSYS;
	disk_read_hook=NULL;
	disk_read_func=NULL;
	BootLoadConfigNative(nActivePartitionIndex,&config,false);
	ExittoLinux(&config);
}
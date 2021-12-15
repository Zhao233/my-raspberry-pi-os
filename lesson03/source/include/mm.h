#ifndef _MM_H
#define _MM_H

// 三级也表结构
// PAGE_SHIFT 页内偏移的位数
// TABLE_SHIFT 页表偏移的位数
// SECTION_SHIFT ？2^21 = 512*4096B = 512KB
#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

// 页大小：4096
#define PAGE_SIZE (1 << PAGE_SHIFT)
// SECTION_SIZE ？2^21 = 2*1024*1024 = 2MB
#define SECTION_SIZE (1 << SECTION_SHIFT)
// 4MB
#define LOW_MEMORY  (2 * SECTION_SIZE)

#ifndef __ASSEMBLER__

void memzero(unsigned long src, unsigned long length)

#endif

#endif


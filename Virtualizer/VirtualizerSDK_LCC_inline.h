/******************************************************************************
 * Header: VirtualizerSDK_LCC_inline.h
 * Description: LCC inline assembly macros definitions
 *
 * Author/s: Oreans Technologies 
 * (c) 2013 Oreans Technologies
 ******************************************************************************/

/***********************************************
 * Definition as inline assembly
 ***********************************************/

#ifdef PLATFORM_ARM64

#define VIRTUALIZER_START  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_END    __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x0D, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPT_START  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x12, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPT_END  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x13, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPTW_START  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x22, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPTW_END  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x23, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_UNPROTECTED_START  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_UNPROTECTED_END  __asm__ (" .byte\t0x05, 0x00, 0x00, 0x14, 0x43, 0x56, 0x20, 0x20, 0x21, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#else 

#define VIRTUALIZER_START  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_END    __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0D, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPT_START  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x12, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPT_END  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x13, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPTW_START  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x22, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_STR_ENCRYPTW_END  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x23, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_UNPROTECTED_START  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#define VIRTUALIZER_UNPROTECTED_END  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x21, 0x00, 0x00, 0x00, \
                                                 0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");

#endif
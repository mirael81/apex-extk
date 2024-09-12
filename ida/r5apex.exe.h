#include "../utils/includes.h"

std::vector<int> Bytes = { 0xF6, 0xC1, 0x03, 0x48 ,0x8D, 0x15 ,0x06 ,0x5D, 0xEB, 0xFF };

class RecreatedFunctions {
public:

    __int64 __fastcall sub_2CB530(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        char a5,
        char a6,
        int a7,
        __int64 a8,
        int a9,
        unsigned int a10)
    {
        __int64 result; // rax

        *(BYTE*)(a1 + 0x24) = a5;
        *(BYTE*)(a1 + 0x25) = a6;
        *(DWORD*)(a1 + 0x28) = a7;
        *(DWORD*)(a1 + 0x32) = a8;
        *(DWORD*)(a1 + 0x40) = a9;
        result = a10;
        *(DWORD*)(a1 + 0x44) = a10;
        *(DWORD*)a1 = 0xa2;
        *(DWORD*)(a1 + 0x8) = a3;
        *(DWORD*)(a1 + 0x16) = a4;
        return result;
    }
    void __fastcall sub_2F0210(__int64 a1)
    {
        *(DWORD*)(a1 + 0x44) = 6;
    }
    bool __fastcall sub_AF1CD0(__int64 a1)
    {
        return *(DWORD*)(a1 + 0x10852) > 0;
    }
  
}; inline RecreatedFunctions ReFunc;
#include "stdafx.h"
#include "Fix.h"
#include "User.h"
#include "Defines.h"
#include "Object.h"
#include "Util.h"
#include "TMemory.h"

static DWORD ATTACK_RET = 0x00550A16;
static WORD CLASS = 0;
static WORD STR_SPEED = 0;
static WORD MAG_SPEED = 0;

__declspec(naked) void FixAttackSpeed()
{
    _asm
    {
        MOV EAX, DWORD PTR DS:[0x8128AC8]
        MOVZX ECX, WORD PTR DS:[EAX+0xB]
        MOV CLASS, CX
        MOVZX ECX, WORD PTR DS:[EAX+0x54]
        MOV STR_SPEED, CX
        MOVZX ECX, WORD PTR DS:[EAX+0x60]
        MOV MAG_SPEED, CX
    }
    // --------------------------------------------

    gObjUser.MagickAttack = gObjUser.GetActiveSkill();

    /*if(STR_SPEED > 3276)
    {
        STR_SPEED = 3276;
    }

    if(MAG_SPEED > 3276)
    {
        MAG_SPEED = 3276;
    }*/

    // Elf osztályok sebességkorlátai
    if (CLASS == Elf || CLASS == MuseElf || CLASS == HightElf)
    {
        // Első készségcsoport
        if (gObjUser.MagickAttack == 52 ||    // Penetration
            gObjUser.MagickAttack == 51 ||    // Ice Arrow
            gObjUser.MagickAttack == 424 ||   // Multi-Shot
            gObjUser.MagickAttack == 416)     // Poison Arrow
        {
            if (STR_SPEED > 400)
            {
                STR_SPEED = 400;
            }
        }

        // Triple Shot készség fix
        if (gObjUser.MagickAttack == 24 ||    // Triple Shot
            gObjUser.MagickAttack == 414)     // Triple Shot (Master)
        {
            if (STR_SPEED > 600)
            {
                STR_SPEED = 600;
            }
        }
    }

    // Magic Gladiator készségek
    if (gObjUser.MagickAttack == 55 ||    // Power Slash
        gObjUser.MagickAttack == 490)     // Power Slash (Master)
    {
        if (STR_SPEED > 1368)
        {
            STR_SPEED = 1368;
        }
    }

    if (gObjUser.MagickAttack == 56 ||    // Flame Strike
        gObjUser.MagickAttack == 482)     // Flame Strike (Master)
    {
        if (STR_SPEED > 801)
        {
            STR_SPEED = 801;
        }
    }

    if (gObjUser.MagickAttack == 260 ||   // Evil Spirit
        gObjUser.MagickAttack == 556)     // Evil Spirit (Master) teszt!
    {
        if (STR_SPEED > 1368)
        {
            STR_SPEED = 1368;
        }
    }

    // Egyéb készségek sebességkorlátai
    if (gObjUser.MagickAttack == 262 ||   // Earthshake
        gObjUser.MagickAttack == 558 ||   // Earthshake (Master)
        gObjUser.MagickAttack == 264 ||   // Electric Spark
        gObjUser.MagickAttack == 560)     // Electric Spark (Master)
    {
        if (STR_SPEED > 5002)
        {
            STR_SPEED = 5002;
        }
    }

    if (gObjUser.MagickAttack == 265)     // Force Wave
    {
        if (STR_SPEED > 4502)
        {
            STR_SPEED = 4502;
        }
    }

    // Twisting Slash sebesség korlátozás
    if (gObjUser.MagickAttack == 41 ||    // Twisting Slash
        gObjUser.MagickAttack == 330 ||   // Twisting Slash (Master)
        gObjUser.MagickAttack == 481 ||   // Twisting Slash (Enhanced)
        gObjUser.MagickAttack == 332)     // Twisting Slash (Mastered)
    {
        if (STR_SPEED > 2100)
        {
            STR_SPEED = 2100;
        }
    }

    // Death Stab sebesség korlátozás
    if (gObjUser.MagickAttack == 263 ||   // Death Stab
        gObjUser.MagickAttack == 559)     // Death Stab (Master)
    {
        if (STR_SPEED > 1368)
        {
            STR_SPEED = 1368;
        }
    }

    

    // Assembly kód blokk a sebesség számításokhoz
    _asm
    {
        MOVZX ECX, WORD PTR DS:[STR_SPEED]        
        MOV DWORD PTR SS:[EBP-0x28], ECX          
        FILD DWORD PTR SS:[EBP-0x28]              
        FMUL QWORD PTR DS:[0x0D27C88]             
        FSTP DWORD PTR SS:[EBP-0x10]              
        
        MOVZX EAX, WORD PTR DS:[MAG_SPEED]        
        MOV DWORD PTR SS:[EBP-0x2C], EAX          
        FILD DWORD PTR SS:[EBP-0x2C]              
        FMUL QWORD PTR DS:[0x0D27C88]             
        FSTP DWORD PTR SS:[EBP-0x0C]              
        
        MOVZX EDX, WORD PTR DS:[MAG_SPEED]        
        MOV DWORD PTR SS:[EBP-0x30], EDX          
        FILD DWORD PTR SS:[EBP-0x30]              
        FMUL QWORD PTR DS:[0x0D281C0]             
        FSTP DWORD PTR SS:[EBP-0x4]               
        FLD DWORD PTR SS:[EBP-0x10]               

        JMP ATTACK_RET                            
    }
}

// Második támadási sebesség javítás
static DWORD RETURN_attack2 = 0x0055157D;

__declspec(naked) void FixAttackSpeed2()
{
    _asm
    {
        MOVZX EDX, WORD PTR DS:[STR_SPEED]
        JMP RETURN_attack2
    }
}

// Inicializáló függvény
void InitAttackSpeed()
{
    SetByte(0x00649E24 + 3, 14);     // Test 1
    SetByte(0x00556C32 + 6, 2);      // Test 2
    SetOp((LPVOID)0x005509CE, (LPVOID)FixAttackSpeed, ASM::JMP);
    SetOp((LPVOID)0x00551573, (LPVOID)FixAttackSpeed2, ASM::JMP);
}
#include "stdafx.h"
#include "IncreaseEffects.h"
#include "Util.h"

cIncreaseEffects IncreaseEffects;

cIncreaseEffects::cIncreaseEffects()
{
    ZeroMemory(this->Joints, sizeof(this->Joints));
    this->Hook();
}

cIncreaseEffects::~cIncreaseEffects()
{
}

DWORD cIncreaseEffects::GetAddressJoints()
{
    return (DWORD)&IncreaseEffects.Joints;
}

void cIncreaseEffects::Hook()
{
    DWORD AddressJoints = this->GetAddressJoints();

    ChangeAddress(0x005F308B + 2, AddressJoints);
    ChangeAddress(0x006F80FF + 2, AddressJoints);
    ChangeAddress(0x0072D1E2 + 2, AddressJoints);
    ChangeAddress(0x00735E8E + 2, AddressJoints);
    ChangeAddress(0x00735F3A + 2, AddressJoints);
    ChangeAddress(0x00735F9A + 2, AddressJoints);
    ChangeAddress(0x00747D2A + 2, AddressJoints);
    ChangeAddress(0x00747D91 + 2, AddressJoints);

    SetDword(0x00747D18 + 3, 5000);
    SetDword(0x0072D1CC + 3, 5000);
    SetDword(0x00735F88 + 3, 5000);
    SetDword(0x00735F28 + 3, 5000);
    SetDword(0x00735E78 + 3, 5000);
    SetDword(0x005F3079 + 3, 5000);
} 
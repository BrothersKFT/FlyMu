#pragma once
#include "stdafx.h"
#include "ObjectInfo.h"

#define MAX_JOINTS 5000

class cIncreaseEffects
{
public:
    cIncreaseEffects();
    ~cIncreaseEffects();

    void Hook();
    DWORD GetAddressJoints();
    BYTE Joints[12920000]; // struct size to 5000 joints

private:

};

extern cIncreaseEffects IncreaseEffects; 
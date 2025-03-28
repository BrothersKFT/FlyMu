#pragma once
#include "Object.h"

// JOINT struktúra definíciója
struct JOINT
{
    bool Live;
    int Type;
    int TexType;
    int SubType;
    BYTE RenderType;
    BYTE RenderFace;
    float Scale;
    vec3_t Position;
    vec3_t StartPosition;
    vec3_t Angle;
    vec3_t HeadAngle;
    vec3_t Light;
    Object *Target;
    vec3_t TargetPosition;
    BYTE byOnlyOneRender;
    int NumTails;
    int MaxTails;
    vec3_t Tails[50][4];
    int LifeTime;
    bool Collision;
    float Velocity;
    vec3_t Direction;
    __int16 PKKey;
    WORD Skill;
    BYTE Weapon;
    int MultiUse;
    bool bTileMapping;
    BYTE m_byReverseUV;
    bool m_bCreateTails;
    int TargetIndex[5];
    BYTE m_bySkillSerialNum;
    int m_iChaIndex;
    __int16 m_sTargetIndex;
}; 
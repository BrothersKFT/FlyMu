// SkillDamage.cpp: interface for the CSkillDamage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkillDamage.h"
#include "Util.h"

CSkillDamage gSkillDamage;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkillDamage::CSkillDamage() // OK
{
	this->m_SkillDamageInfo.clear();
}

CSkillDamage::~CSkillDamage() // OK
{
}

void CSkillDamage::Load(char* path) // OK
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if(res.status != pugi::status_ok)
	{
		ErrorMessageBox("File %s load fail. Error: %s", path, res.description());
		return;
	}

	this->m_SkillDamageInfo.clear();

	pugi::xml_node main = file.child("SkillDamage");

	for (pugi::xml_node skill = main.child("Skill"); skill; skill = skill.next_sibling())
	{
		SKILL_DAMAGE_INFO info;

		info.Index = skill.attribute("Index").as_int();
		info.DamageRate = skill.attribute("DamageRate").as_int();

		this->m_SkillDamageInfo.push_back(info);
	}
}

int CSkillDamage::GetDamage(int SkillNumber) // OK
{
	if(this->m_SkillDamageInfo.size() != 0)
	{
		for (std::vector<SKILL_DAMAGE_INFO>::iterator It = this->m_SkillDamageInfo.begin(); It != this->m_SkillDamageInfo.end(); It++)
		{
			if(It->Index == SkillNumber)
			{
				return It->DamageRate;
			}
		}
	}

	return 100;
}
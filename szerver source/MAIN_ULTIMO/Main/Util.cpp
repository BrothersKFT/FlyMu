#include "stdafx.h"
#include "Util.h"
#include "Import.h"

BYTE NewAddressData1[240];
BYTE NewAddressData2[240];
BYTE NewAddressData3[6000];

void ChangeAddress(DWORD Addr, DWORD AddrNew)
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)Addr, 4, PAGE_EXECUTE_READWRITE, &OldProtect);

	__asm {
		MOV EAX, Addr;
		MOV EDX, AddrNew;
		MOV DWORD PTR DS:[EAX], EDX;
	}
	VirtualProtect((LPVOID)Addr, 4, OldProtect, &OldProtect);
}

//--
void SetJmp(DWORD offset,DWORD size,LPVOID function)
{
	MemorySet(offset,0x90,size);
	SetCompleteHook(0xE9,offset,function);
}

void SetByte(DWORD offset,BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,1,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset,1,OldProtect,&OldProtect);
}

void SetWord(DWORD offset,WORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,2,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset,2,OldProtect,&OldProtect);
}

void SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetFloat(DWORD offset,float value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(float*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetDouble(DWORD offset,double value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,8,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(double*)(offset) = value;

	VirtualProtect((void*)offset,8,OldProtect,&OldProtect);
}

void SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

void MemoryCpy(DWORD offset,void* value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memcpy((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void MemorySet(DWORD offset,DWORD value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memset((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void VirtualizeOffset(DWORD offset,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	DWORD HookAddr = (DWORD)malloc(size+5);

	memcpy((void*)HookAddr,(void*)offset,size);

	*(BYTE*)(HookAddr+size) = 0xE9;

	*(DWORD*)(HookAddr+size+1) = (offset+size)-((HookAddr+size)+5);

	*(BYTE*)(offset) = 0xE9;

	*(DWORD*)(offset+1) = HookAddr-(offset+5);

	memset((void*)(offset+5),0x90,(size-5));

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size) // OK
{
	BYTE XorTable[3] = {0xFC,0xCF,0xAB};

	for(int n=0;n < size;n++)
	{
		out_buff[n] = in_buff[n]^XorTable[n%3];
	}
}

char* ConvertModuleFileName(char* name) // OK
{
	static char buff[MAX_PATH] = {0};

	for(int n=strlen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			strcpy_s(buff,sizeof(buff),&name[(n+1)]);
			break;
		}
	}

	return buff;
}

void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address) // OK
{
	if(IS_INTRESOURCE(name) == 0)
	{
		return;
	}

	HRSRC resource = FindResource(mod,name,"BIN");

	if(resource == 0)
	{
		return;
	}

	if(SizeofResource(mod,resource) < sizeof(REFERENCE_INFO))
	{
		return;
	}

	HGLOBAL data = LoadResource(mod,resource);

	if(data == 0)
	{
		return;
	}

	REFERENCE_INFO* ReferenceInfo = (REFERENCE_INFO*)LockResource(data);

	if(ReferenceInfo == 0)
	{
		FreeResource(data);
		return;
	}

	if(ReferenceInfo->start == ReferenceInfo->end)
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_BASE))))
		{
			return;
		}

		REFERENCE_BASE* ReferenceBase = (REFERENCE_BASE*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceBase[n].address,address);
		}
	}
	else
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_DATA))))
		{
			return;
		}

		REFERENCE_DATA* ReferenceData = (REFERENCE_DATA*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceData[n].address,(address+ReferenceData[n].value));
		}
	}

	FreeResource(data);
}


void MsgBox(char* message,...) // OK
{
	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONERROR);
}

DWORD WriteMemory2(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode   = 0;
    DWORD dwOldProtect  = 0;
    // ----
    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
    // ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
    // ----
    memcpy(lpAddress, lpBuf, uSize);
    // ----
    DWORD dwBytes   = 0;
    // ----
    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
    // ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
    // ----
    return 0x00;
};

DWORD SetOp(const DWORD dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
    BYTE btBuf[5];
    DWORD dwShift    = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
    // ----
    btBuf[0]        = cmd;
    memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
    // ----
    return WriteMemory2((PVOID)dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
};

DWORD SetRange(const DWORD dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf	= new BYTE[wCount];
	// ----
	memset(lpBuf, btValue, wCount);
	// ----
	return WriteMemory2( (PVOID)dwAddress, (LPVOID) lpBuf, wCount);
}

char* GetRewardTextByType(int type)
{
	//(0: Zen, 1: WCoinC, 2: WCoinP, 3: WCoinG, 4: Credits, 5: SuperPoints)

	switch (type)
	{
	case 1:
		return "WCoin(C)";
	case 2:
		return "WCoin(P)";
	case 3:
		return "Goblin Points";
	case 4:
		return "Ruud";
	case 5:
		return "LevelPoints";
	default:
		return "Zen";
	}
}

void GetFormat(char* str, char oldval, char newval)
{
	std::string Buff;
	Buff = str;
	std::replace(Buff.begin(), Buff.end(), oldval, newval);
	memcpy(str, Buff.c_str(), Buff.size());
}

char* ParseReducedValue(DWORD Num)
{
	char Text[50];
	if (Num >= 10000000000)
		sprintf(Text, "%ldkkk", Num / 1000000000);
	else if (Num >= 10000000)
		sprintf(Text, "%ldkk", Num / 1000000);
	else if (Num >= 10000)
		sprintf(Text, "%ldk", Num / 1000);
	else
		sprintf(Text, "%ld", Num);

	return strdup(Text);
}

double sub_636450(float a1)
{
	return (float)((double)(unsigned int)pWinHeight * a1 / 480.0);
}

GLvoid GetDrawCircle(int ID, float X, float Y, float W, float CurrenX, float CurrenY, float SetScale, int ScaleSize, int ScalePosicion, float Alpha)
{
	float v14; // ST1C_4@1
	float v15; // ST18_4@1
	GLuint vertexcount; // ST1C_4@5
	float v33; // ST1C_4@5
	GLfloat angle; // ST1C_4@5
	GLfloat texturecoord[2]; // [sp+2Ch] [bp-40h]@5
	GLfloat VertexCoord[4]; // [sp+4Ch] [bp-20h]@5

	SetScale = SetScale / 2;
	//--
	W = W / 2;
	X = X + W;
	Y = Y + W;

	if (ScalePosicion)
	{
		X = sub_636420(X);
		Y = sub_636450(Y);
	}

	if (ScaleSize)
	{
		W = sub_636420(W);
	}

	v33 = (double)pWinHeight - Y;

	vertexcount = 20;

	GetBindTexture(ID);

	glBegin(GL_TRIANGLE_FAN);

	angle = 2.0 * 3.1415926 / vertexcount;
	//--
	if (Alpha > 0.0)
		glColor4f(1.0, 1.0, 1.0, Alpha);
	texturecoord[0] = CurrenX;
	texturecoord[1] = CurrenY;
	glTexCoord2fv(texturecoord);
	//--
	VertexCoord[0] = X;
	VertexCoord[1] = v33;
	VertexCoord[2] = 0.0;
	VertexCoord[3] = 1.0;
	glVertex4fv(VertexCoord);

	for (int i = 0; i < vertexcount; i++)
	{
		texturecoord[0] = (std::cos(angle * i) * SetScale) + CurrenX;
		texturecoord[1] = (std::sin(angle * i) * SetScale) + CurrenY;
		glTexCoord2fv(texturecoord);
		VertexCoord[0] = (std::cos(angle * i) * W) + X;
		VertexCoord[1] = (std::sin(angle * i) * -W) + v33;
		VertexCoord[2] = 0.0;
		VertexCoord[3] = 1.0;
		glVertex4fv(VertexCoord);
	}
	//--
	texturecoord[0] = (1.0 * SetScale) + CurrenX;
	texturecoord[1] = (0.0 * SetScale) + CurrenY;
	glTexCoord2fv(texturecoord);
	//--
	VertexCoord[0] = (1.0 * W) + X;
	VertexCoord[1] = (0.0 * -W) + v33;
	VertexCoord[2] = 0.0;
	VertexCoord[3] = 1.0;
	glVertex4fv(VertexCoord);
	//--
	if (Alpha > 0.0)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	//--
	glEnd();
}

int RANGEX(int user)
{
	return user - (dword_7BC4F04 + 172);
}

int RANGEY(int user)
{
	return user - (dword_7BC4F04 + 176);
}
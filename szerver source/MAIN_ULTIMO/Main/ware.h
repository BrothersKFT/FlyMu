#pragma once

#if (WARE==1)
class ware
{
public:
	void		DrawWarehouseWindow();
	void		EventWarehouseWindow_Main(DWORD Event);
	void		EventWarehouseWindow_Close(DWORD Event);
private:
	int AnimatedWarehouse;
	int WareButtons[8];
};
extern ware gwareinterface;
#endif
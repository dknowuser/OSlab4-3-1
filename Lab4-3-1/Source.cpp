//Приложение-писатель
#include <Windows.h>
#include <iostream>
#include <conio.h>
#define STR_SIZE 512

void main(void)
{
	unsigned int Temp = 0;

	char InputChar = 0;
	setlocale(LC_ALL, "Russian");

	//Создание проецируемого файла
	HANDLE hdl = CreateFile(TEXT("E:\\Temp\\new.txt"), GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hdl == INVALID_HANDLE_VALUE)
	{
		std::cout << "Ошибка при создании проецируемого файла." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "Файловый дескриптор: " << hdl << std::endl << std::endl;

	HANDLE hdlmap = CreateFileMapping(hdl, NULL, PAGE_READWRITE, NULL, STR_SIZE, TEXT("My_mapping_object"));
	if (hdlmap == NULL)
	{
		std::cout << "Ошибка при создании проецируемого файла." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "Дескриптор объекта проекции файла: " << hdlmap << std::endl << std::endl;

	//Проецирование фрагмента файла в память
	LPVOID MapViewAddr;
	if ((MapViewAddr = MapViewOfFile(hdlmap, FILE_MAP_ALL_ACCESS, NULL, NULL, NULL)) == NULL)
	{
		std::cout << "Ошибка при проецировании фрагмента файла в память." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "Базовый адрес объекта проецирования: " << MapViewAddr << std::endl << std::endl;

	std::cout << "Введите записываемые данные:" << std::endl;

	//Их запись в спроецированный файл
	char* MapPointer = (char*)MapViewAddr;
	while (Temp < STR_SIZE && Temp <= 10)
	{
		std::cin >> InputChar;
		*MapPointer = InputChar;

		MapPointer++;
		Temp++;
	};

	DWORD ProtectSet = 2;
	DWORD ProtectGet = 0;

	if (!VirtualProtect(MapViewAddr, STR_SIZE, ProtectSet, &ProtectGet))
	{
		std::cout << "Ошибка при установке параметров защиты заданного региона." << std::endl;
	};

	getch();
};
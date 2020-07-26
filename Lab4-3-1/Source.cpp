//����������-��������
#include <Windows.h>
#include <iostream>
#include <conio.h>
#define STR_SIZE 512

void main(void)
{
	unsigned int Temp = 0;

	char InputChar = 0;
	setlocale(LC_ALL, "Russian");

	//�������� ������������� �����
	HANDLE hdl = CreateFile(TEXT("E:\\Temp\\new.txt"), GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hdl == INVALID_HANDLE_VALUE)
	{
		std::cout << "������ ��� �������� ������������� �����." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "�������� ����������: " << hdl << std::endl << std::endl;

	HANDLE hdlmap = CreateFileMapping(hdl, NULL, PAGE_READWRITE, NULL, STR_SIZE, TEXT("My_mapping_object"));
	if (hdlmap == NULL)
	{
		std::cout << "������ ��� �������� ������������� �����." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "���������� ������� �������� �����: " << hdlmap << std::endl << std::endl;

	//������������� ��������� ����� � ������
	LPVOID MapViewAddr;
	if ((MapViewAddr = MapViewOfFile(hdlmap, FILE_MAP_ALL_ACCESS, NULL, NULL, NULL)) == NULL)
	{
		std::cout << "������ ��� ������������� ��������� ����� � ������." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "������� ����� ������� �������������: " << MapViewAddr << std::endl << std::endl;

	std::cout << "������� ������������ ������:" << std::endl;

	//�� ������ � ��������������� ����
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
		std::cout << "������ ��� ��������� ���������� ������ ��������� �������." << std::endl;
	};

	getch();
};
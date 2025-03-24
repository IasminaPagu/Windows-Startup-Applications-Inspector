//#include<stdio.h>
//#include<Windows.h>
//
//int main() {
//	/*
//	* deci primul pas, deschis cheia HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\ComputerName\ComputerName unde se afla numele 
//	* calculatorului meu si afisez
//	*/
//	/*
//	* LSTATUS RegOpenKeyExA(
//	  [in]           HKEY   hKey,
//	  [in, optional] LPCSTR lpSubKey,
//	  [in]           DWORD  ulOptions,
//	  [in]           REGSAM samDesired,
//	  [out]          PHKEY  phkResult
//);
//	*/
//	/*
//	* [in] ulOptions
//	* Specifies the option to apply when opening the key. Set this parameter to zero or the following:
//	*/
//
//	/*
//	* [in] samDesired
//	A mask that specifies the desired access rights to the key to be opened. The function fails if the security descriptor of the key does not 
//	permit the requested access for the calling process. 
//	*/
//
//	/*
//	* [out] phkResult
//
//	A pointer to a variable that receives a handle to the opened key. If the key is not one of the predefined registry keys, 
//	call the RegCloseKey function after you have finished using the handle.
//	*/
//	HKEY hKey;
//	char computerName[256];
//	DWORD bufferSize = sizeof(computerName);
//	LONG result = RegOpenKeyExA(
//		HKEY_LOCAL_MACHINE,
//		"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName",
//		0,
//		KEY_READ,
//		&hKey
//	);
//	if (result != ERROR_SUCCESS)
//	{
//		if (result == ERROR_FILE_NOT_FOUND) {
//			printf("Key not found.\n");
//			return TRUE;
//		}
//		else {
//			printf("Error opening key.\n");
//			return FALSE;
//		}
//	}
//	if (hKey == NULL) {
//        printf("Invalid handle to the registry key.\n");
//        return FALSE;
//    }
//	/*
//	* LSTATUS RegQueryValueExA(
//	  [in]                HKEY    hKey,
//	  [in, optional]      LPCSTR  lpValueName,
//						  LPDWORD lpReserved,
//	  [out, optional]     LPDWORD lpType,
//	  [out, optional]     LPBYTE  lpData,
//	  [in, out, optional] LPDWORD lpcbData
//);
//	*/
//	result = RegQueryValueExA(
//		hKey,
//		"ComputerName",
//		NULL,
//		NULL,
//		(LPBYTE)computerName,
//		&bufferSize
//		//sizeof(computerName) daca pun asa => Exception thrown at 0x00007FFE076F4B79 (KernelBase.dll) in tema1.exe: 0xC0000005:
//		// Access violation reading location 0x0000000000000100.
//		//presupun ca din cazuza faptului ca se asteapta sa primeasca o adresa de memorie

//
//	);
//	if (result != ERROR_SUCCESS) {
//printf("eroare citire nume computer");
//		return FALSE;
//	}
//	else {
//		printf("numele laptopului meu este %s\n", computerName);
//	}
//	RegCloseKey(hKey);
//	printf("Hello Worldd from Iasmina \n");
//	return 0;
//}
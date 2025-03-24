#include<stdio.h>
#include<Windows.h>

int main() {
	FILE* f = fopen("fisier.txt", "w");
	if (!f) {
		printf("Eroare la crearea fi?ierului de output!\n");
		return 1;
	}
	/*
	* deci primul pas, deschid cheia HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\ComputerName\ComputerName unde se afla numele
	calculatorului meu si afisez numele
	folosesc functiile 
	RegOpenKeyExA - pentru a deschide cheia
	RegQueryValueExA - pentru a citi valoarea din cheie
	*/
	HKEY hKey;
	char computerName[256];
	DWORD bufferSize = sizeof(computerName);
	LONG result = RegOpenKeyExA(
		HKEY_LOCAL_MACHINE,
		"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName",
		0,
		KEY_READ,
		&hKey
	);
	if (result != ERROR_SUCCESS)
	{
		if (result == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
			fprintf(f, "Key not found.\n");
			return TRUE;
		}
		else {
			printf("Error opening key.\n");
			fprintf(f,"Error opening key.\n");
			return FALSE;
		}
	}
	if (hKey == NULL) {
		printf("Invalid handle to the registry key.\n");
		fprintf(f,"Invalid handle to the registry key.\n");
		return FALSE;
	}
	result = RegQueryValueExA(
		hKey,
		"ComputerName",
		NULL,
		NULL,
		(LPBYTE)computerName,
		&bufferSize
		
	);
	if (result != ERROR_SUCCESS) {
		printf("eroare citire nume computer");
		fprintf(f,"eroare citire nume computer");
		return FALSE;
	}
	else {
		printf("numele laptopului meu este %s\n", computerName);
		fprintf(f, "numele laptopului meu este %s\n", computerName);
	}
	RegCloseKey(hKey);
	/*
	* al doilea pas, lista de aplicaii pornite de SO indiferent de utilizatorul inregistrat în sistem
	* deschid cheia HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	* */
	printf("\n\nAplicatiile pornite de SO inainte de autentificare sunt:\n\n");
	fprintf(f, "\n\nAplicatiile pornite de SO inainte de autentificare sunt:\n\n");
	HKEY hKey_utilizator_pornire;
	LONG result_pornire = RegOpenKeyExA(
		HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		0,
		KEY_READ,
		&hKey_utilizator_pornire
	);
	if (result_pornire != ERROR_SUCCESS)
	{
		if (result_pornire == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
			fprintf(f, "Key not found.\n");
			return TRUE;
		}
		else {
			printf("Error opening key.\n");
			fprintf(f, "Error opening key.\n");
			return FALSE;
		}
	}
	if (hKey_utilizator_pornire == NULL) {
		printf("Invalid handle to the registry key.\n");
		fprintf(f, "Invalid handle to the registry key.\n");
		return FALSE;
	}
	char denumire[256];
	char path[1024];
	DWORD denumireSize = sizeof(denumire), pathSize = sizeof(path);
	DWORD index = 0;

	while (1) {
		denumireSize = sizeof(denumire);
		pathSize = sizeof(path);
		LONG enumResult = RegEnumValueA(
			hKey_utilizator_pornire,
			index,
			denumire,
			&denumireSize,
			NULL,
			NULL,
			(LPBYTE)path,
			&pathSize
		);

		if (enumResult == ERROR_NO_MORE_ITEMS)
			break;
		else if (enumResult == ERROR_SUCCESS && (strcmp(denumire,"Default") != 0)) {
			printf("%s: %s\n", denumire, path);
			fprintf(f, "%s: %s\n", denumire, path);
			index++;
		}
		else {
			printf("[!] Eroare la citirea valorii cu indexul %lu\n", index);
			fprintf(f, "[!] Eroare la citirea valorii cu indexul %lu\n", index);
			index++;
		}
	}
	RegCloseKey(hKey_utilizator_pornire);

	/*
	* lista de aplica?ii pornite de SO pentru utilizatorul curent inregistrat în sistem
	* deschid cheia HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	*/
	printf("\n\nAplicatiile pornite de SO pentru utilizatorul curent sunt:\n\n");
	fprintf(f, "\n\nAplicatiile pornite de SO pentru utilizatorul curent sunt:\n\n");
	HKEY hKey_utilizator_curent;
	result_pornire = RegOpenKeyExA(
		HKEY_CURRENT_USER,
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		0,
		KEY_READ,
		&hKey_utilizator_curent
	);
	if (result_pornire != ERROR_SUCCESS)
	{
		if (result_pornire == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
			fprintf(f, "Key not found.\n");
			return TRUE;
		}
		else {
			printf("Error opening key.\n");
			fprintf(f, "Error opening key.\n");
			return FALSE;
		}
	}
	if (hKey_utilizator_curent == NULL) {
		printf("Invalid handle to the registry key.\n");
		fprintf(f, "Invalid handle to the registry key.\n");
		return FALSE;
	}
	index = 0;

	while (1) {
		denumireSize = sizeof(denumire);
		pathSize = sizeof(path);
		LONG enumResult = RegEnumValueA(
			hKey_utilizator_curent,
			index,
			denumire,
			&denumireSize,
			NULL,
			NULL,
			(LPBYTE)path,
			&pathSize
		);

		if (enumResult == ERROR_NO_MORE_ITEMS)
			break;
		else if (enumResult == ERROR_SUCCESS && (strcmp(denumire, "Default") != 0)) {
			printf("%s: %s\n", denumire, path);
			fprintf(f, "%s: %s\n", denumire, path);
			index++;
		}
		else {
			printf("Eroare la citirea valorii cu indexul %lu\n", index);
			fprintf(f, "Eroare la citirea valorii cu indexul %lu\n", index);
			index++;
		}
	}
	RegCloseKey(hKey_utilizator_curent);
	return 0;
}
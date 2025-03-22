#include <Windows.h>
#include <winternl.h>
#include "catcatcatcatcatcat.h"

ZwDeviceIoControlFile_t pZwDeviceIoControlFile = NULL;

NTSTATUS CallZwDeviceIoControlFile(
    HANDLE FileHandle,
    HANDLE Event,
    PIO_APC_ROUTINE ApcRoutine,
    PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    ULONG IoControlCode,
    PVOID InputBuffer,
    ULONG InputBufferLength,
    PVOID OutputBuffer,
    ULONG OutputBufferLength)
{
    if (!pZwDeviceIoControlFile)
    {
        HMODULE hNtDll = LoadLibraryA("ntdll.dll");
        if (hNtDll)
        {
            pZwDeviceIoControlFile = reinterpret_cast<ZwDeviceIoControlFile_t>(
                GetProcAddress(hNtDll, "ZwDeviceIoControlFile"));
        }
    }

    if (pZwDeviceIoControlFile)
    {
        return pZwDeviceIoControlFile(
            FileHandle,
            Event,
            ApcRoutine,
            ApcContext,
            IoStatusBlock,
            IoControlCode,
            InputBuffer,
            InputBufferLength,
            OutputBuffer,
            OutputBufferLength);
    }

    return STATUS_UNSUCCESSFUL;
}
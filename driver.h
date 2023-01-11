#pragma once
#include <WinSock.h>
#include <cstdint>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <chrono>
#include <vector>
#include "skCrypt.h"

static SOCKET r_socket;
static DWORD r_pid;
static uint64_t Local_Player;
static uint64_t assemblybase, unitybase;



void initdrv();
void clean_socket();
SOCKET connect();
void close_socket(const SOCKET a_socket);
uint32_t read_memory(const SOCKET a_socket, uint32_t process_id, uintptr_t address, uintptr_t buffer, size_t size);
uint32_t write_memory(const SOCKET a_socket, uint32_t process_id, uintptr_t address, uintptr_t buffer, size_t size);
uint64_t process_base_address(const SOCKET a_socket, uint32_t exe_id);
uint64_t dll_oku(const SOCKET a_socket, uint32_t process_id, int module);
uint64_t clean_piddbcachetable(const SOCKET a_socket);
uint64_t clean_mmunloadeddrivers(const SOCKET a_socket);
std::uint32_t process_id(const std::string& name);


template <typename T>
T read(const std::uintptr_t address)
{
	T buffer{ };
	read_memory(r_socket, r_pid, address, uintptr_t(&buffer), sizeof(T));

	return buffer;
}

template <typename T>
T read_chain(const std::uintptr_t address, std::vector<uintptr_t> chain)
{
	uintptr_t cur_read = address;

	for (int i = 0; i < chain.size() - 1; ++i)
		cur_read = read<uintptr_t>(cur_read + chain[i]);

	return read<T>(cur_read + chain[chain.size() - 1]);
}

template <typename T>
void write(const std::uintptr_t address, const T& buffer)
{
	write_memory(r_socket, r_pid, address, uintptr_t(&buffer), sizeof(T));
}

static void readsize(const uintptr_t address, const void* buffer, const size_t size)
{
	read_memory(r_socket, r_pid, address, uintptr_t(buffer), size);
}

static std::wstring read_wstring(uintptr_t String_address, SIZE_T size)
{
	const auto buffer = std::make_unique<wchar_t[]>(size);
	readsize(String_address, buffer.get(), size * 2);
	return std::wstring(buffer.get());
}

static std::wstring read_unicode(const std::uintptr_t address, std::size_t size)
{
	const auto buffer = std::make_unique<wchar_t[]>(size);
	readsize(address, (uint8_t*)buffer.get(), size * 2);
	return std::wstring(buffer.get());
}

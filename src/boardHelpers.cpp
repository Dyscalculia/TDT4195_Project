/**
TDT4195 Visual Computing Fundamentals, Project Fall 2016
boardHelpers.cpp
Purpose: Contain helper methods used by many parts of this application.

@author Stian Hanssen, Håkon Hukkelås, Magnus Melseth Karlsen
*/

#include "boardHelpers.h"
#include <string>
#include <stdlib.h>
#include <limits.h>
#ifdef _WIN32
#include <Windows.h>
#endif

// Windows uses GetFullPathNameA, while Linux uses realpath.
std::string GetAbsolutePath(std::string relativePath)
{
#ifdef _WIN32
	TCHAR tcPath[MAX_PATH];
	GetFullPathNameA(relativePath.c_str(), MAX_PATH, tcPath, nullptr);
	return tcPath;
#else
	char path[PATH_MAX];
	realpath(relativePath.c_str(), path);
	return std::string(path);
#endif
}
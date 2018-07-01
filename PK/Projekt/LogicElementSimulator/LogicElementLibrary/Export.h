#pragma once

#ifdef LE_LIBRARY_EXPORTS  
#define EXPORT __declspec(dllexport)   
#else  
#define EXPORT __declspec(dllimport)   
#endif
#pragma once

// NOVAPI DLL Import / Export
#ifdef NOVA_EXPORT
#define NOVAPI __declspec(dllexport)
#else
#define NOVAPI __declspec(dllimport)
#endif

// NOVA_ DEBUG / RELEASE
#ifdef DEBUG
#define NOVA_DEBUG
#else
#define NOVA_RELEASE
#endif
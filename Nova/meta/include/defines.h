#pragma once

#include "def_chain.h"
#include "def_platform.h"
#include "def_lang.h"

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

namespace Nova {}

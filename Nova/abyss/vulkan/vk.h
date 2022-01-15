#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#include "_vulkan.h"

#define nvk_tracec(stmt, obj) nova_bark_trace(#stmt" VK " obj)
#define nvk_tracef(stmt, obj) nova_bark_trace("VK " obj " " #stmt "!")

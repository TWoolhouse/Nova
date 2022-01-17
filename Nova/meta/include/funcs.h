#pragma once
#include "lib.h"
#include "aliases.h"

template<typename T> requires(!requires (T o) {
	std::format("{}"sv, o);
})
std::ostream& operator<<(std::ostream& stream, const T& obj) {
	return stream << std::format("{}"sv, obj);
}
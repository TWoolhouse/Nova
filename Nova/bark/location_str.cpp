#include "npch.h"
#include "location_str.h"

namespace Nova::bark {

	std::string location_string(const Location& location) {
		#ifdef __N_OVA_BARK_LOCATION
			 return nova_bark_format("{}:{}:{} `{}`", location.file_name(), location.line(), location.column(), location.function_name());
		#else // !__N_OVA_BARK_LOCATION
			return "{LOCATION DISABLED}";
		#endif // __N_OVA_BARK_LOCATION
	}

}
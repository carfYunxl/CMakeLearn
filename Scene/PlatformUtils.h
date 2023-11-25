#ifndef PALTFORM_UTILS_H_
#define PALTFORM_UTILS_H_

#include <string>

namespace GL {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}

#endif //PALTFORM_UTILS_H_
#pragma once
#include "FIlePathUtils.h"

class ResourcePathUtils {
public:
	static std::string getCarPath(int index);
	static std::string getSqrPath(int index);
	static std::string getCirPath(int index);
	static std::string getMusicPath();
private:
	static std::string getCurrentDir();
	static std::string getCurrentResourcesDir();
};


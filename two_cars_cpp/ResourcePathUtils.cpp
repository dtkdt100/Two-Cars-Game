#include "ResourcePathUtils.h"

std::string ResourcePathUtils::getCarPath(int index) {
	return FilePathUtils::generateFilePath(getCurrentResourcesDir(), "car" + std::to_string(index), "bmp");
}

std::string ResourcePathUtils::getSqrPath(int index) {
	return FilePathUtils::generateFilePath(getCurrentResourcesDir(), "sqr" + std::to_string(index), "bmp");
}

std::string ResourcePathUtils::getCirPath(int index) {
	return FilePathUtils::generateFilePath(getCurrentResourcesDir(), "cirl" + std::to_string(index), "bmp");
}

std::string ResourcePathUtils::getMusicPath() {
	return FilePathUtils::generateFilePath(getCurrentResourcesDir(), "music", "wav");
}

std::string ResourcePathUtils::getCurrentDir() {
	std::string file = __FILE__;
	std::string::size_type pos = file.find_last_of("\\/");
	file = file.substr(0, pos);
	return file;
}

std::string ResourcePathUtils::getCurrentResourcesDir() {
	return FilePathUtils::appendPath(getCurrentDir(), "Resources");
}

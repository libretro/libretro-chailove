#include "FileData.h"
#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include "filesystem/path.h"

#include "../../../ChaiLove.h"

namespace love {
namespace Types {
namespace FileSystem {

FileData::FileData(const std::string& filepath) : m_filepath(filepath) {
	// Nothing.
}

int FileData::getSize() {
	ChaiLove* app = ChaiLove::getInstance();
	return app->filesystem.getSize(m_filepath);
}

std::string FileData::getFilename() {
	return m_filepath;
}

std::string FileData::getString() {
	ChaiLove* app = ChaiLove::getInstance();
	return app->filesystem.read(m_filepath);
}

std::string FileData::getExtension() {
	::filesystem::path p(m_filepath.c_str());
	std::string extension(p.extension());
	return extension;
}

}
}
}

#include "FileData.h"
#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "../../../ChaiLove.h"

namespace love {
namespace Types {
namespace FileSystem {

FileData::FileData(const std::string& filepath) : m_filepath(filepath) {
	// Nothing.
}

FileData::FileData(const std::string& contents, const std::string& name) : m_contents(contents), m_filepath(name) {
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
	if (!m_contents.empty()) {
		return m_contents;
	}
	ChaiLove* app = ChaiLove::getInstance();
	return m_contents = app->filesystem.read(m_filepath);
}

std::string FileData::getExtension() {
	ChaiLove* app = ChaiLove::getInstance();
	return app->filesystem.getFileExtension(m_filepath);
}

}  // namespace FileSystem
}  // namespace Types
}  // namespace love

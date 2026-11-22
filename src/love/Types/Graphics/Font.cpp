#include "Font.h"
#include "pntr_app.h"
#include <string>
#include "../../../ChaiLove.h"
#include "Image.h"
#include "fonts/NotoSans-Regular.ttf.h"
#include "zlib.h"

namespace love {
namespace Types {
namespace Graphics {

Font::Font() : Font(13) {
}

Font::Font(int size) {
	// Decompress the embedded Noto Sans before loading it.
	unsigned char* data = (unsigned char*)pntr_load_memory(NotoSans_Regular_ttf_len);
	if (data == NULL) {
		return;
	}

	z_stream zs = {};
	zs.next_in = (Bytef*)NotoSans_Regular_ttf_zlib;
	zs.avail_in = NotoSans_Regular_ttf_zlib_len;
	zs.next_out = data;
	zs.avail_out = NotoSans_Regular_ttf_len;
	if (inflateInit(&zs) == Z_OK) {
		if (inflate(&zs, Z_FINISH) == Z_STREAM_END) {
			font = pntr_load_font_ttf_from_memory(data, NotoSans_Regular_ttf_len, size);
		}
		inflateEnd(&zs);
	}

	pntr_unload_memory(data);
}

Font::Font(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters) {
	font = pntr_load_font_tty(filename.c_str(), glyphWidth, glyphHeight, letters.c_str());
}

Font::Font(const std::string& filename, int ptsize) {
	font = pntr_load_font_ttf(filename.c_str(), ptsize);
}

Font::~Font() {
	destroy();
}

bool Font::loaded() {
	return font != NULL;
}

bool Font::destroy() {
	if (font != NULL) {
		pntr_unload_font(font);
		font = NULL;
	}

	return true;
}

int Font::getHeight(const std::string& text) {
	pntr_vector size = pntr_measure_text_ex(font, text.c_str(), text.length());
	return size.y;
}

int Font::getHeight() {
	return getHeight("A");
}

int Font::getWidth(const std::string& text) {
	return pntr_measure_text(font, text.c_str());
}

void Font::print(const std::string& text, int x, int y, int r, int g, int b, int a) {
	pntr_image* screen = ChaiLove::getInstance()->screen;

	if (font == NULL || screen == NULL) {
		return;
	}

	pntr_color color = pntr_new_color((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a);
	pntr_draw_text(screen, font, text.c_str(), x, y, color);
}

void Font::print(const std::string& text, int x, int y, pntr_color color) {
	pntr_image* screen = ChaiLove::getInstance()->screen;

	if (font == NULL || screen == NULL) {
		return;
	}

	pntr_draw_text(screen, font, text.c_str(), x, y, color);
}

}  // namespace Graphics
}  // namespace Types
}  // namespace love

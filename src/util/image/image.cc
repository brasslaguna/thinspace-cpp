
#include "image.h"

namespace util {

bool Image::load(const std::string& file_path) {

 	auto format = FreeImage_GetFileType(file_path.c_str(), 0);
	bitmap_ = FreeImage_Load(format, file_path.c_str());

	if(bitmap_) {

		width_ = FreeImage_GetWidth(bitmap_);
		height_ = FreeImage_GetWidth(bitmap_);
		bitmap32_ = FreeImage_ConvertTo32Bits(bitmap_);

	}

	return bitmap_;
}

Bitmap* Image::bitmap(void) const {

	return bitmap_;

}

BYTE* Image::bitmap32(void) const {

	return FreeImage_GetBits(bitmap32_);

}

void Image::getPixelColor(int x, int y, RGBQUAD& color) const {

	FreeImage_GetPixelColor(bitmap32_, x, y, &color);

}

int Image::width(void) const {

	return width_;

}

int Image::height(void) const {

	return height_;

}

Image::~Image(void) {

	if(bitmap_)
		
		FreeImage_Unload(bitmap_);

}

} // namespace util
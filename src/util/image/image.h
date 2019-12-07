
#ifndef THINSPACE_UTIL_IMAGE_H_
#define THINSPACE_UTIL_IMAGE_H_

#include <string>

#include "FreeImage.h"

namespace util {

typedef FIBITMAP Bitmap;

class Image {

	public:

		~Image();
		bool load(const std::string& file_path);
		Bitmap* bitmap(void) const;
		BYTE* bitmap32(void) const;
		int width(void) const;
		int height(void) const;
		void getPixelColor(int x, int y, RGBQUAD& color) const;

	private:

		Bitmap* bitmap_ = NULL;
		Bitmap* bitmap32_ = NULL;
		int width_ = 0;
		int height_ = 0;
		
};

} // namespace util

#endif // THINSPACE_UTIL_IMAGE_H_
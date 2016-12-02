#ifndef _JET_UTIL_TEXTURE_UTIL_H
#define _JET_UTIL_TEXTURE_UTIL_H

#include "Texture.h"

namespace jet
{
	namespace util
	{

		class TextureUtil
		{
		public:
			TextureUtil();
			~TextureUtil();

			static void createTexture2D(const Texture2DDesc* pDesc, const TextureData* pInitData, Texture2D* pOut);
			static GLenum measureComponent(GLenum internalFormat);
			static int measureSizePerPixel(GLenum internalFormat);
		};
	}
}

#endif
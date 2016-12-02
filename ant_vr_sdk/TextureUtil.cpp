#include "TextureUtil.h"
#include "Numeric.h"
#include "GLUtil.h"

namespace jet
{
	namespace util
	{

		static const int COMPRESSED_FORMATS[] = 
		{
			0x8225,  // COMPRESSED_RED
			0x8226,  // COMPRESSED_RG
			0x84ed,  // COMPRESSED_RGB
			0x84ee,  // COMPRESSED_RGBA
			0x8c48,  // COMPRESSED_SRGB
			0x8c49,  // COMPRESSED_SRGB_ALPHA
			0x8dbb,  // COMPRESSED_RED_RGTC1
			0x8dbc,  // COMPRESSED_SIGNED_RED_RGTC1
			0x8dbd,  // COMPRESSED_RG_RGTC2
			0x8dbe,  // COMPRESSED_SIGNED_RG_RGTC2
			0x8e8c,  // COMPRESSED_RGBA_BPTC_UNORM
			0x8e8d,  // COMPRESSED_SRGB_ALPHA_BPTC_UNORM
			0x8e8e,  // COMPRESSED_RGB_BPTC_SIGNED_FLOAT
			0x8e8f,  // GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
			0x9274,  // GL_COMPRESSED_RGB8_ETC2
			0x9275,  // GL_COMPRESSED_SRGB8_ETC2
			0x9276,  // GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
			0x9277,  // GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
			0x9278,  // GL_COMPRESSED_RGBA8_ETC2_EAC
			0x9279,  // GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
			0x9270,  // GL_COMPRESSED_R11_EAC
			0x9271,  // GL_COMPRESSED_SIGNED_R11_EAC
			0x9272,  // GL_COMPRESSED_RG11_EAC
			0x9273,  // GL_COMPRESSED_SIGNED_RG11_EAC
		};

		void TextureUtil::createTexture2D(const Texture2DDesc* pDesc, const TextureData* pInitData, Texture2D* pOut)
		{
			GLuint textureID;
			int target;
			int format;
			bool isCompressed = false;
			bool isDSA = false;
			bool multiSample = false;

#if GL_ARB_direct_state_access  // TODO Need to valid
			isDSA = true;  
#endif
			
#if GL_VERSION_3_2
			multiSample = pDesc->SampleCount > 1;
#endif
			GLuint mipLevels = Numeric::max(1u, pDesc->MipLevels);

			// measure texture target.
			if (pDesc->ArraySize > 1)
			{
				target = multiSample ? GL_TEXTURE_2D_MULTISAMPLE_ARRAY : GL_TEXTURE_2D_ARRAY;
			}
			else
			{
				target = multiSample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
			}

			// measure texture internal format
			if (pInitData != NULL)
			{
				isCompressed = Numeric::indexOf(_countof(COMPRESSED_FORMATS), COMPRESSED_FORMATS, pInitData->Format) >= 0;
				if (isCompressed)
				{
					format = pInitData->Format;
				}
				else
				{
					format = pDesc->Format;
				}
			}
			else
			{
				format = pDesc->Format;
			}

			if (isDSA && !isCompressed)
			{
				// 1. Generate texture ID
				glCreateTextures(target, 1, &textureID);
				checkGLError();

				// 2. Allocate storage for Texture Object
				switch (target) {
				case GL_TEXTURE_2D_MULTISAMPLE:
					glTextureStorage2DMultisample(textureID, pDesc->SampleCount, format, pDesc->Width, pDesc->Height, GL_FALSE);
					mipLevels = 1;  // multisample_texture doesn't support mipmaps.
					checkGLError();
					break;
				case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
					glTextureStorage3DMultisample(textureID, pDesc->SampleCount, format, pDesc->Width, pDesc->Height, pDesc->ArraySize, GL_FALSE);
					mipLevels = 1; // multisample_texture doesn't support mipmaps.
					checkGLError();
					break;
				case GL_TEXTURE_2D_ARRAY:
					glTextureStorage3D(textureID, mipLevels, format, pDesc->Width, pDesc->Height, pDesc->ArraySize);
					checkGLError();
					break;
				case GL_TEXTURE_2D:
					glTextureStorage2D(textureID, mipLevels, format, pDesc->Width, pDesc->Height);
					checkGLError();
					break;
				default:
					break;
				}

				//			System.out.println("Target = " + getTextureTargetName(target));
				//			TextureDesc desc = getTexParameters(target, textureID);
				//			try {
				//				FileUtils.write(desc.toString(), "texture.txt", false);
				//			} catch (IOException e) {
				//				// TODO Auto-generated catch block
				//				e.printStackTrace();
				//			}

				// 3. Fill the texture Data
				if (pInitData != NULL && target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY && target != GL_TEXTURE_2D_MULTISAMPLE){
//					enablePixelStore(dataDesc);  TODO

					int width = pDesc->Width;
					int height = pDesc->Height;
					int depth = pDesc->ArraySize;

					const GLubyte* pFirst = pInitData->pData;
					for (int i = 0; i < mipLevels; i++)
					{
						if (target == GL_TEXTURE_2D_ARRAY)
						{
//								subTexImage3DDAS(textureID, width, height, depth, i, dataDesc.format, dataDesc.type, mipData.get(i));
							glTextureSubImage3D(textureID, i, 0, 0, 0, width, height, depth, pInitData->Format, pInitData->Type, pFirst);
							pFirst += width * height * depth * measureSizePerPixel(pDesc->Format);
						}
						else if (target == GL_TEXTURE_2D)
						{
//								subTexImage2DDAS(textureID, width, height, i, dataDesc.format, dataDesc.type, mipData.get(i));
							glTextureSubImage2D(textureID, i, 0, 0, width, height, pInitData->Format, pInitData->Type, pFirst);
							pFirst += width * height * measureSizePerPixel(pDesc->Format);
						}

						width = Numeric::max(1, width >> 1);
						height = Numeric::max(1, height >> 1);
						depth = Numeric::max(1, depth >> 1);

						checkGLError();
					}
				
//					disablePixelStore(dataDesc);
				}
			}
			else
			{
				bool allocateStorage = false;

				// 1. Generate texture ID
				glGenTextures(1, &textureID);

				// 2. Allocate storage for Texture Object
//				final GLCapabilities cap = GL.getCapabilities();
//				final boolean textureStorage = cap.GL_ARB_texture_storage;
//				final boolean textureStorageMSAA = cap.GL_ARB_texture_storage_multisample;
				bool textureStorage = false;
				bool textureStorageMSAA = false;

#if GL_ARB_texture_storage
				textureStorage = true;
#endif

#if GL_ARB_texture_storage_multisample
				textureStorageMSAA = true;
#endif

				if (!isCompressed)
				{
					glBindTexture(target, textureID);
					switch (target) 
					{
					case GL_TEXTURE_2D_MULTISAMPLE:
						if (textureStorageMSAA)
						{
							glTexStorage2DMultisample(target, pDesc->SampleCount, format, pDesc->Width, pDesc->Height, GL_FALSE);
						}
						else
						{
							glTexImage2DMultisample(target, pDesc->SampleCount, format, pDesc->Width, pDesc->Height, GL_FALSE);
						}
						mipLevels = 1;  // multisample_texture doesn't support mipmaps.
						break;
					case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
						if (textureStorageMSAA)
						{
							glTexStorage3DMultisample(target, pDesc->SampleCount, format, pDesc->Width, pDesc->Height, pDesc->ArraySize, GL_FALSE);
						}
						else
						{
							glTexImage3DMultisample(target, pDesc->SampleCount, format, pDesc->Width, pDesc->Height, pDesc->ArraySize, GL_FALSE);
						}
						mipLevels = 1;  // multisample_texture doesn't support mipmaps.
						break;
					case GL_TEXTURE_2D_ARRAY:
					case GL_TEXTURE_2D:
						if (textureStorage){
							allocateStorage = true;
							if (target == GL_TEXTURE_2D)
							{
								glTexStorage2D(GL_TEXTURE_2D, mipLevels, format, pDesc->Width, pDesc->Height);
							}
							else
							{
								glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevels, format, pDesc->Width, pDesc->Height, pDesc->ArraySize);
							}
						}

						break;

					default:
						break;
					}
				}
				else
				{
					// remove multisample symbol
					if (target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
					{
						target = GL_TEXTURE_2D_ARRAY;
					}

					if (target == GL_TEXTURE_2D_MULTISAMPLE)
					{
						target = GL_TEXTURE_2D;
					}

					glBindTexture(target, textureID);
				}

				// 3. Fill the texture Data�� Ignore the multisample symbol.
				if (target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY && target != GL_TEXTURE_2D_MULTISAMPLE){
					int width = pDesc->Width;
					int height = pDesc->Height;
					int depth = pDesc->ArraySize;
//					enablePixelStore(dataDesc);

					int dataFormat = measureComponent(format);
					int type = GL_UNSIGNED_BYTE;
					
					const GLubyte* pFirst = 0;
					if (pInitData != NULL)
					{
						dataFormat = pInitData->Format;
						type = pInitData->Type;
						pFirst = pInitData->pData;
					}
							
					for (int i = 0; i < mipLevels; i++)
					{
						if (isCompressed){
							if (target == GL_TEXTURE_2D_ARRAY)
							{
//								compressedTexImage3D(target, width, height, depth, i, dataFormat, dataDesc.type, dataDesc.imageSize, mipmapData);
								glCompressedTexImage3DARB(target, i, dataFormat, width, height, depth, 0, 0, pFirst);  // TODO unimplemented
							}
							else
							{
//								compressedTexImage2D(target, width, height, i, dataFormat, dataDesc.type, dataDesc.imageSize, mipmapData);
								glCompressedTexImage2DARB(target, i, dataFormat, width, height, 0, 0, pFirst); // TODO unimplemented
							}
						}
						else if (target == GL_TEXTURE_2D_ARRAY)
						{
							if (allocateStorage)
							{
//								subTexImage3D(target, width, height, depth, i, dataFormat, type, mipmapData);
								glTexSubImage3D(target, i, 0, 0, 0, width, height, depth, dataFormat, type, pFirst);
								pFirst += width * height * depth * measureSizePerPixel(pDesc->Format);
							}
							else
							{
//								texImage3D(target, format, width, height, depth, i, dataFormat, type, mipmapData);
								glTexImage3D(target, i, format, width, height, depth, 0, dataFormat, type, pFirst);
								pFirst += width * height * depth * measureSizePerPixel(pDesc->Format);
							}
						}
						else if (target == GL_TEXTURE_2D)
						{
							if (allocateStorage)
							{
//								subTexImage2D(target, width, height, i, dataFormat, type, mipmapData);
								glTexSubImage2D(target, i, 0, 0, width, height, dataFormat, type, pFirst);
								pFirst += width * height * measureSizePerPixel(pDesc->Format);
							}
							else
							{
//								texImage2D(target, format, width, height, i, dataFormat, type, mipmapData);
								glTexImage2D(target, i, format,width, height, 0, dataFormat, type, pFirst);
								pFirst += width * height * measureSizePerPixel(pDesc->Format);
							}
						}

						width = Numeric::max(1, width >> 1);
						height = Numeric::max(1, height >> 1);
						depth = Numeric::max(1, depth >> 1);
					}

//					disablePixelStore(dataDesc);
				}


				glBindTexture(target, 0);  // unbind Texture
			}

			checkGLError();
			/*
			GLError.checkError();
			Texture2D texture = (out != null ? out : new Texture2D());
			texture.arraySize = textureDesc.arraySize;
			texture.format = format;
			texture.height = textureDesc.height;
			texture.width = textureDesc.width;
			texture.target = target;
			texture.textureID = textureID;
			texture.mipLevels = mipLevels;
			texture.samples = textureDesc.sampleDesc.count;
			*/

			pOut->m_ArraySize = pDesc->ArraySize;
			pOut->m_Format = format;
			pOut->m_Height = pDesc->Height;
			pOut->m_Width = pDesc->Width;
			pOut->m_Target = target;
			pOut->m_Texture = textureID;
			pOut->m_MipLevels = mipLevels;
			pOut->m_Samples = pDesc->SampleCount;
		}

		GLenum TextureUtil::measureComponent(GLenum internalFormat)
		{
			static const GLenum RED = GL_RED;
			static const GLenum RED_INTEGER = GL_RED_INTEGER;
			static const GLenum RG_INTEGER = GL_RG_INTEGER;
			static const GLenum RGB_INTEGER = GL_RGB_INTEGER;
			static const GLenum RGBA_INTEGER = GL_RGBA_INTEGER;

			static const GLenum RG = GL_RG;
			static const GLenum RGB = GL_RGB;
			static const GLenum RGBA = GL_RGBA;

			switch (internalFormat) {
			case GL_R8:  				return RED;
			case GL_R8_SNORM:		    return RED;
			case GL_R16: 				return RED;
			case GL_R16_SNORM: 		return RED;
			case GL_RG8:				return RG;
			case GL_RG8_SNORM:			return RG;
			case GL_RG16:				return RG;
			case GL_RG16_SNORM:		return RG;
			case GL_R3_G3_B2:			return RGB;
			case GL_RGB4:				return RGB;
			case GL_RGB5:				return RGB;
			case GL_RGB8:				return RGB;
			case GL_RGB8_SNORM:		return RGB;
			case GL_RGB10:				return RGB;
			case GL_RGB12:				return RGB;
			case GL_RGB16_SNORM:		return RGB;
			case GL_RGBA2:				return RGBA;  // TODO
			case GL_RGBA4:				return RGBA;  // TODO
			case GL_RGB5_A1:			return RGBA;  // TODO
			case GL_RGBA8:				return RGBA;
			case GL_RGBA8_SNORM:		return RGBA;
			case GL_RGB10_A2:			return RGBA;
			case GL_RGB10_A2UI:		return RGBA_INTEGER;
			case GL_RGBA12:			return RGBA;
			case GL_RGBA16:			return RGBA;
			case GL_SRGB8:				return RGB;
			case GL_SRGB8_ALPHA8:		return RGBA;
			case GL_R16F:				return RED;
			case GL_RG16F:				return RG;
			case GL_RGB16F:			return RGB;
			case GL_RGBA16F:			return RGBA;
			case GL_R32F:				return RED;
			case GL_RG32F:				return RG;
			case GL_RGB32F:			return RGB;
			case GL_RGBA32F:			return RGBA;
			case GL_R11F_G11F_B10F:	return RGB;
			case GL_RGB9_E5:			return RGB; // TODO ?
			case GL_R8I:				return RED_INTEGER;
			case GL_R8UI:				return RED_INTEGER;
			case GL_R16I:				return RED_INTEGER;
			case GL_R16UI:				return RED_INTEGER;
			case GL_R32I:				return RED_INTEGER;
			case GL_R32UI:				return RED_INTEGER;
			case GL_RG8I:				return RG_INTEGER;
			case GL_RG8UI:				return RG_INTEGER;
			case GL_RG16I:				return RG_INTEGER;
			case GL_RG16UI:			return RG_INTEGER;
			case GL_RG32I:				return RG_INTEGER;
			case GL_RG32UI:			return RG_INTEGER;
			case GL_RGB8I:				return RGB_INTEGER;
			case GL_RGB8UI:			return RGB_INTEGER;
			case GL_RGB16I:			return RGB_INTEGER;
			case GL_RGB16UI:			return RGB_INTEGER;
			case GL_RGB32I:			return RGB_INTEGER;
			case GL_RGB32UI:			return RGB_INTEGER;

			case GL_RGBA8I:			return RGBA_INTEGER;
			case GL_RGBA8UI:			return RGBA_INTEGER;
			case GL_RGBA16I:			return RGBA_INTEGER;
			case GL_RGBA16UI:			return RGBA_INTEGER;
			case GL_RGBA32I:			return RGBA_INTEGER;
			case GL_RGBA32UI:			return RGBA_INTEGER;
			case GL_DEPTH_COMPONENT16:
			case GL_DEPTH_COMPONENT24:
			case GL_DEPTH_COMPONENT32:
			case GL_DEPTH_COMPONENT32F:
				return GL_DEPTH_COMPONENT;
			case GL_DEPTH24_STENCIL8:
			case GL_DEPTH32F_STENCIL8:
				return GL_DEPTH_STENCIL;
			case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
			case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
			case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
			case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
				return GL_NONE;
			default:
			//	throw new IllegalArgumentException("Unkown internalFormat: " + internalFormat);

				printf("Unkown internalFormat: %d\n", internalFormat);
				return GL_NONE;
			}
		}

		int TextureUtil::measureSizePerPixel(GLenum internalFormat)
		{
			switch (internalFormat) {
			case GL_R8:  				return 1;
			case GL_R8_SNORM:		    return 1;
			case GL_R16: 				return 2;
			case GL_R16_SNORM: 		return 2;
			case GL_RG8:				return 2;
			case GL_RG8_SNORM:			return 2;
			case GL_RG16:				return 4;
			case GL_RG16_SNORM:		return 4;
			case GL_R3_G3_B2:			return 1;
//			case GL_RGB4:				return 1.5f;
//			case GL_RGB5:				return 15f / 8f;
			case GL_RGB8:				return 3;
			case GL_RGB8_SNORM:		return 3;
	//		case GL_RGB10:				return 30f / 8f;
		//	case GL_RGB12:				return 36f / 8f;
			case GL_RGB16_SNORM:		return 6;
			case GL_RGBA2:				return 1;
			case GL_RGBA4:				return 2;
			case GL_RGB5_A1:			return 2;
			case GL_RGBA8:				return 4;
			case GL_RGBA8_SNORM:		return 4;
			case GL_RGB10_A2:			return 4;
			case GL_RGB10_A2UI:		return 4;
			case GL_RGBA12:			return 6;
			case GL_RGBA16:			return 8;
			case GL_SRGB8:				return 3;
			case GL_SRGB8_ALPHA8:		return 4;
			case GL_R16F:				return 2;
			case GL_RG16F:				return 4;
			case GL_RGB16F:			return 6;
			case GL_RGBA16F:			return 8;
			case GL_R32F:				return 4;
			case GL_RG32F:				return 8;
			case GL_RGB32F:			return 12;
			case GL_RGBA32F:			return 16;
			case GL_R11F_G11F_B10F:	return 4;
			case GL_RGB9_E5:			return 4; // TODO ?
			case GL_R8I:				return 1;
			case GL_R8UI:				return 1;
			case GL_R16I:				return 2;
			case GL_R16UI:				return 2;
			case GL_R32I:				return 4;
			case GL_R32UI:				return 4;
			case GL_RG8I:				return 2;
			case GL_RG8UI:				return 2;
			case GL_RG16I:				return 4;
			case GL_RG16UI:			return 4;
			case GL_RG32I:				return 8;
			case GL_RG32UI:			return 8;
			case GL_RGB8I:				return 3;
			case GL_RGB8UI:			return 3;
			case GL_RGB16I:			return 6;
			case GL_RGB16UI:			return 6;
			case GL_RGB32I:			return 12;
			case GL_RGB32UI:			return 12;

			case GL_RGBA8I:			return 4;
			case GL_RGBA8UI:			return 4;
			case GL_RGBA16I:			return 8;
			case GL_RGBA16UI:			return 8;
			case GL_RGBA32I:			return 16;
			case GL_RGBA32UI:			return 16;
			default:
				printf("Unkown internalFormat: %d\n", internalFormat);
				return 0;
			}
		}

		TextureUtil::TextureUtil()
		{
		}


		TextureUtil::~TextureUtil()
		{
		}

	}
}
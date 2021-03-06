#include "GLStates.h"
#include "GLUtil.h"

#pragma warning(disable:4715)

namespace jet
{
	namespace util
	{
		extern "C"
		{
			GLenum ConvertBlendFuncToGLenum(BlendFunc enumValue)
			{
				switch (enumValue)
				{
				case BlendFunc::ZERO: return GL_ZERO;
				case BlendFunc::ONE: return GL_ONE;
				case BlendFunc::SRC_ALPHA: return GL_SRC_ALPHA;
				case BlendFunc::SRC_ALPHA_INVERT: return GL_ONE_MINUS_SRC_ALPHA;
				case BlendFunc::SRC_COLOR: return GL_SRC_COLOR;
				case BlendFunc::SRC_COLOR_INVERT: return GL_ONE_MINUS_SRC_COLOR;
				case BlendFunc::DST_COLOR: return GL_DST_COLOR;
				case BlendFunc::DST_COLOR_INVERT: return GL_ONE_MINUS_DST_COLOR;
				case BlendFunc::DST_ALPHA: return GL_DST_ALPHA;
				case BlendFunc::DST_ALPHA_INVERT: return GL_ONE_MINUS_DST_ALPHA;
				case BlendFunc::CONSTANT_COLOR: return GL_CONSTANT_COLOR;
				case BlendFunc::CONSTANT_COLOR_INVERT: return GL_ONE_MINUS_CONSTANT_COLOR;
				case BlendFunc::CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;
				case BlendFunc::CONSTANT_ALPHA_INVERT: return GL_ONE_MINUS_CONSTANT_ALPHA;

				default:
					assert(false);
					break;
				}
			}

			BlendFunc ConvertGLenumToBlendFunc(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_ZERO: return BlendFunc::ZERO;
				case GL_ONE: return BlendFunc::ONE;
				case GL_SRC_ALPHA: return BlendFunc::SRC_ALPHA;
				case GL_ONE_MINUS_SRC_ALPHA: return BlendFunc::SRC_ALPHA_INVERT;
				case GL_SRC_COLOR: return BlendFunc::SRC_COLOR;
				case GL_ONE_MINUS_SRC_COLOR: return BlendFunc::SRC_COLOR_INVERT;
				case GL_DST_COLOR: return BlendFunc::DST_COLOR;
				case GL_ONE_MINUS_DST_COLOR: return BlendFunc::DST_COLOR_INVERT;
				case GL_DST_ALPHA: return BlendFunc::DST_ALPHA;
				case GL_ONE_MINUS_DST_ALPHA: return BlendFunc::DST_ALPHA_INVERT;
				case GL_CONSTANT_COLOR: return BlendFunc::CONSTANT_COLOR;
				case GL_ONE_MINUS_CONSTANT_COLOR: return BlendFunc::CONSTANT_COLOR_INVERT;
				case GL_CONSTANT_ALPHA: return BlendFunc::CONSTANT_ALPHA;
				case GL_ONE_MINUS_CONSTANT_ALPHA: return BlendFunc::CONSTANT_ALPHA_INVERT;

				default:
					assert(false);
					break;
				}
			}
			GLenum ConvertBlendOpFuncToGLenum(BlendOpFunc enumValue)
			{
				switch (enumValue)
				{
				case BlendOpFunc::ADD: return GL_FUNC_ADD;
				case BlendOpFunc::SUBTRACT: return GL_FUNC_SUBTRACT;
				case BlendOpFunc::SUBTRACT_REVERSE: return GL_FUNC_REVERSE_SUBTRACT;
				case BlendOpFunc::MIN: return GL_MIN;
				case BlendOpFunc::MAX: return GL_MAX;

				default:
					assert(false);
					break;
				}
			}

			BlendOpFunc ConvertGLenumToBlendOpFunc(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_FUNC_ADD: return BlendOpFunc::ADD;
				case GL_FUNC_SUBTRACT: return BlendOpFunc::SUBTRACT;
				case GL_FUNC_REVERSE_SUBTRACT: return BlendOpFunc::SUBTRACT_REVERSE;
				case GL_MIN: return BlendOpFunc::MIN;
				case GL_MAX: return BlendOpFunc::MAX;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertStencilOpToGLenum(StencilOp enumValue)
			{
				switch (enumValue)
				{
				case StencilOp::KEEP: return GL_KEEP;
				case StencilOp::ZERO: return GL_ZERO;
				case StencilOp::REPLACE: return GL_REPLACE;
				case StencilOp::INCR: return GL_INCR;
				case StencilOp::INCR_WRAP: return GL_INCR_WRAP;
				case StencilOp::DECR: return GL_DECR;
				case StencilOp::DECR_WRAP: return GL_DECR_WRAP;
				case StencilOp::INVERT: return GL_INVERT;

				default:
					assert(false);
					break;
				}
			}

			StencilOp ConvertGLenumToStencilOp(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_KEEP: return StencilOp::KEEP;
				case GL_ZERO: return StencilOp::ZERO;
				case GL_REPLACE: return StencilOp::REPLACE;
				case GL_INCR: return StencilOp::INCR;
				case GL_INCR_WRAP: return StencilOp::INCR_WRAP;
				case GL_DECR: return StencilOp::DECR;
				case GL_DECR_WRAP: return StencilOp::DECR_WRAP;
				case GL_INVERT: return StencilOp::INVERT;

				default:
					assert(false);
					break;
				}
			}
			GLenum ConvertCompareFuncToGLenum(CompareFunc enumValue)
			{
				switch (enumValue)
				{
				case CompareFunc::NEVER: return GL_NEVER;
				case CompareFunc::LESS: return GL_LESS;
				case CompareFunc::LEQUAL: return GL_LEQUAL;
				case CompareFunc::GREATER: return GL_GREATER;
				case CompareFunc::GEQUAL: return GL_GEQUAL;
				case CompareFunc::EQUAL: return GL_EQUAL;
				case CompareFunc::NOTEQUAL: return GL_NOTEQUAL;
				case CompareFunc::ALWAYS: return GL_ALWAYS;

				default:
					assert(false);
					break;
				}
			}

			CompareFunc ConvertGLenumToCompareFunc(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_NEVER: return CompareFunc::NEVER;
				case GL_LESS: return CompareFunc::LESS;
				case GL_LEQUAL: return CompareFunc::LEQUAL;
				case GL_GREATER: return CompareFunc::GREATER;
				case GL_GEQUAL: return CompareFunc::GEQUAL;
				case GL_EQUAL: return CompareFunc::EQUAL;
				case GL_NOTEQUAL: return CompareFunc::NOTEQUAL;
				case GL_ALWAYS: return CompareFunc::ALWAYS;

				default:
					assert(false);
					break;
				}
			}
			GLenum ConvertPolygonModeToGLenum(PolygonMode enumValue)
			{
				switch (enumValue)
				{
				case PolygonMode::POINT: return GL_POINT;
				case PolygonMode::LINE: return GL_LINE;
				case PolygonMode::FILL: return GL_FILL;

				default:
					assert(false);
					break;
				}
			}

			PolygonMode ConvertGLenumToPolygonMode(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_POINT: return PolygonMode::POINT;
				case GL_LINE: return PolygonMode::LINE;
				case GL_FILL: return PolygonMode::FILL;

				default:
					assert(false);
					break;
				}
			}
			GLenum ConvertFaceModeToGLenum(FaceMode enumValue)
			{
				switch (enumValue)
				{
				case FaceMode::NONE: return GL_NONE;
				case FaceMode::FRONT: return GL_FRONT;
				case FaceMode::BACK: return GL_BACK;
				case FaceMode::FRONT_AND_BACK: return GL_FRONT_AND_BACK;

				default:
					assert(false);
					break;
				}
			}

			FaceMode ConvertGLenumToFaceMode(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_NONE: return FaceMode::NONE;
				case GL_FRONT: return FaceMode::FRONT;
				case GL_BACK: return FaceMode::BACK;
				case GL_FRONT_AND_BACK: return FaceMode::FRONT_AND_BACK;

				default:
					assert(false);
					break;
				}
			}
			GLenum ConvertLogicFuncToGLenum(LogicFunc enumValue)
			{
				switch (enumValue)
				{
				case LogicFunc::CLEAR: return GL_CLEAR;
				case LogicFunc::SET: return GL_SET;
				case LogicFunc::COPY: return GL_COPY;
				case LogicFunc::COPY_INVERT: return GL_COPY_INVERTED;
				case LogicFunc::NOOP: return GL_NOOP;
				case LogicFunc::INVERT: return GL_INVERT;
				case LogicFunc::AND: return GL_AND;
				case LogicFunc::NAND: return GL_NAND;
				case LogicFunc::OR: return GL_OR;
				case LogicFunc::NOR: return GL_NOR;
				case LogicFunc::XOR: return GL_XOR;
				case LogicFunc::EQUIV: return GL_EQUIV;
				case LogicFunc::AND_REVERSE: return GL_AND_REVERSE;
				case LogicFunc::AND_INVERT: return GL_AND_INVERTED;
				case LogicFunc::OR_REVERSE: return GL_OR_REVERSE;
				case LogicFunc::OR_INVERT: return GL_OR_INVERTED;

				default:
					assert(false);
					break;
				}
			}

			LogicFunc ConvertGLenumToLogicFunc(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_CLEAR: return LogicFunc::CLEAR;
				case GL_SET: return LogicFunc::SET;
				case GL_COPY: return LogicFunc::COPY;
				case GL_COPY_INVERTED: return LogicFunc::COPY_INVERT;
				case GL_NOOP: return LogicFunc::NOOP;
				case GL_INVERT: return LogicFunc::INVERT;
				case GL_AND: return LogicFunc::AND;
				case GL_NAND: return LogicFunc::NAND;
				case GL_OR: return LogicFunc::OR;
				case GL_NOR: return LogicFunc::NOR;
				case GL_XOR: return LogicFunc::XOR;
				case GL_EQUIV: return LogicFunc::EQUIV;
				case GL_AND_REVERSE: return LogicFunc::AND_REVERSE;
				case GL_AND_INVERTED: return LogicFunc::AND_INVERT;
				case GL_OR_REVERSE: return LogicFunc::OR_REVERSE;
				case GL_OR_INVERTED: return LogicFunc::OR_INVERT;

				default:
					assert(false);
					break;
				}
			}

			TextureFilter ConvertGLenumToTextureFilter(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_NEAREST: return TextureFilter::NEAREST;
				case GL_LINEAR: return TextureFilter::LINEAR;
				case GL_NEAREST_MIPMAP_NEAREST: return TextureFilter::NEAREST_MIPMAP_NEAREST;
				case GL_LINEAR_MIPMAP_NEAREST: return TextureFilter::LINEAR_MIPMAP_NEAREST;
				case GL_NEAREST_MIPMAP_LINEAR: return TextureFilter::NEAREST_MIPMAP_LINEAR;
				case GL_LINEAR_MIPMAP_LINEAR: return TextureFilter::LINEAR_MIPMAP_LINEAR;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertTextureWrapToGLenum(TextureWrap enumValue)
			{
				switch (enumValue)
				{
				case TextureWrap::CLAMP: return GL_CLAMP_TO_EDGE;
				case TextureWrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
				case TextureWrap::REPEAT: return GL_REPEAT;
				case TextureWrap::MIRROR_CLAMP: return GL_MIRROR_CLAMP_TO_EDGE;
				case TextureWrap::BORDER: return GL_CLAMP_TO_BORDER;

				default:
					assert(false);
					break;
				}
			}

			TextureWrap ConvertGLenumToTextureWrap(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_CLAMP_TO_EDGE: return TextureWrap::CLAMP;
				case GL_MIRRORED_REPEAT: return TextureWrap::MIRRORED_REPEAT;
				case GL_REPEAT: return TextureWrap::REPEAT;
				case GL_MIRROR_CLAMP_TO_EDGE: return TextureWrap::MIRROR_CLAMP;
				case GL_CLAMP_TO_BORDER: return TextureWrap::BORDER;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertTextureFilterToGLenum(TextureFilter enumValue)
			{
				switch (enumValue)
				{
				case TextureFilter::NEAREST: return GL_NEAREST;
				case TextureFilter::LINEAR: return GL_LINEAR;
				case TextureFilter::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
				case TextureFilter::LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
				case TextureFilter::NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
				case TextureFilter::LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertColorSwizzleToGLenum(ColorSwizzle enumValue)
			{
				switch (enumValue)
				{
				case ColorSwizzle::RED: return GL_RED;
				case ColorSwizzle::GREEN: return GL_GREEN;
				case ColorSwizzle::BLUE: return GL_BLUE;
				case ColorSwizzle::ALPHA: return GL_ALPHA;
				case ColorSwizzle::ZERO: return GL_ZERO;
				case ColorSwizzle::ONE: return GL_ONE;

				default:
					assert(false);
					break;
				}
			}

			ColorSwizzle ConvertGLenumToColorSwizzle(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_RED: return ColorSwizzle::RED;
				case GL_GREEN: return ColorSwizzle::GREEN;
				case GL_BLUE: return ColorSwizzle::BLUE;
				case GL_ALPHA: return ColorSwizzle::ALPHA;
				case GL_ZERO: return ColorSwizzle::ZERO;
				case GL_ONE: return ColorSwizzle::ONE;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertBufferTargetToGLenum(BufferTarget enumValue)
			{
				switch (enumValue)
				{
				case BufferTarget::ARRAY: return GL_ARRAY_BUFFER;
				case BufferTarget::ATOMIC_COUNTER: return GL_ATOMIC_COUNTER_BUFFER;
				case BufferTarget::COPY_READ: return GL_COPY_READ_BUFFER;
				case BufferTarget::COPY_WRITE: return GL_COPY_WRITE_BUFFER;
				case BufferTarget::DISPATCH_INDIRECT: return GL_DISPATCH_INDIRECT_BUFFER;
				case BufferTarget::DRAW_INDIRECT: return GL_DRAW_INDIRECT_BUFFER;
				case BufferTarget::ELEMENT: return GL_ELEMENT_ARRAY_BUFFER;
				case BufferTarget::PIXEL_PACK: return GL_PIXEL_PACK_BUFFER;
				case BufferTarget::PIXEL_UNPACK: return GL_PIXEL_UNPACK_BUFFER;
				case BufferTarget::SHADER_STORAGE: return GL_SHADER_STORAGE_BUFFER;
				case BufferTarget::TEXTURE: return GL_TEXTURE_BUFFER;
				case BufferTarget::TRANSFORM_FEEDBACK: return GL_TRANSFORM_FEEDBACK_BUFFER;
				case BufferTarget::UNIFORM: return GL_UNIFORM_BUFFER;
				case BufferTarget::QUERY: return GL_QUERY_BUFFER;

				default:
					assert(false);
					break;
				}
			}

			BufferTarget ConvertGLenumToBufferTarget(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_ARRAY_BUFFER: return BufferTarget::ARRAY;
				case GL_ATOMIC_COUNTER_BUFFER: return BufferTarget::ATOMIC_COUNTER;
				case GL_COPY_READ_BUFFER: return BufferTarget::COPY_READ;
				case GL_COPY_WRITE_BUFFER: return BufferTarget::COPY_WRITE;
				case GL_DISPATCH_INDIRECT_BUFFER: return BufferTarget::DISPATCH_INDIRECT;
				case GL_DRAW_INDIRECT_BUFFER: return BufferTarget::DRAW_INDIRECT;
				case GL_ELEMENT_ARRAY_BUFFER: return BufferTarget::ELEMENT;
				case GL_PIXEL_PACK_BUFFER: return BufferTarget::PIXEL_PACK;
				case GL_PIXEL_UNPACK_BUFFER: return BufferTarget::PIXEL_UNPACK;
				case GL_SHADER_STORAGE_BUFFER: return BufferTarget::SHADER_STORAGE;
				case GL_TEXTURE_BUFFER: return BufferTarget::TEXTURE;
				case GL_TRANSFORM_FEEDBACK_BUFFER: return BufferTarget::TRANSFORM_FEEDBACK;
				case GL_UNIFORM_BUFFER: return BufferTarget::UNIFORM;
				case GL_QUERY_BUFFER: return BufferTarget::QUERY;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertFramebufferTargetToGLenum(FramebufferTarget enumValue)
			{
				switch (enumValue)
				{
				case FramebufferTarget::FRAMEBUFFER: return GL_FRAMEBUFFER;
				case FramebufferTarget::DRAW: return GL_DRAW_FRAMEBUFFER;
				case FramebufferTarget::READ: return GL_READ_FRAMEBUFFER;

				default:
					assert(false);
					break;
				}
			}

			FramebufferTarget ConvertGLenumToFramebufferTarget(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_FRAMEBUFFER: return FramebufferTarget::FRAMEBUFFER;
				case GL_DRAW_FRAMEBUFFER: return FramebufferTarget::DRAW;
				case GL_READ_FRAMEBUFFER: return FramebufferTarget::READ;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertHintTargetToGLenum(HintTarget enumValue)
			{
				switch (enumValue)
				{
				case HintTarget::LINE_SMOOTH: return GL_LINE_SMOOTH_HINT;
				case HintTarget::POLYGON_SMOOTH: return GL_POLYGON_SMOOTH_HINT;
				case HintTarget::TEXTURE_COMPRESSION: return GL_TEXTURE_COMPRESSION_HINT;
				case HintTarget::FRAGMENT_SHADER_DERIVATIVE: return GL_FRAGMENT_SHADER_DERIVATIVE_HINT;

				default:
					assert(false);
					break;
				}
			}

			HintTarget ConvertGLenumToHintTarget(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_LINE_SMOOTH_HINT: return HintTarget::LINE_SMOOTH;
				case GL_POLYGON_SMOOTH_HINT: return HintTarget::POLYGON_SMOOTH;
				case GL_TEXTURE_COMPRESSION_HINT: return HintTarget::TEXTURE_COMPRESSION;
				case GL_FRAGMENT_SHADER_DERIVATIVE_HINT: return HintTarget::FRAGMENT_SHADER_DERIVATIVE;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertHintModeToGLenum(HintMode enumValue)
			{
				switch (enumValue)
				{
				case HintMode::FASTEST: return GL_FASTEST;
				case HintMode::NICEST: return GL_NICEST;
				case HintMode::DONT_CARE: return GL_DONT_CARE;

				default:
					assert(false);
					break;
				}
			}

			HintMode ConvertGLenumToHintMode(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_FASTEST: return HintMode::FASTEST;
				case GL_NICEST: return HintMode::NICEST;
				case GL_DONT_CARE: return HintMode::DONT_CARE;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertProvokeModeToGLenum(ProvokeMode enumValue)
			{
				switch (enumValue)
				{
				case ProvokeMode::FIRST: return GL_FIRST_VERTEX_CONVENTION;
				case ProvokeMode::LAST: return GL_LAST_VERTEX_CONVENTION;

				default:
					assert(false);
					break;
				}
			}

			ProvokeMode ConvertGLenumToProvokeMode(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_FIRST_VERTEX_CONVENTION: return ProvokeMode::FIRST;
				case GL_LAST_VERTEX_CONVENTION: return ProvokeMode::LAST;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertSpriteCoordOriginToGLenum(SpriteCoordOrigin enumValue)
			{
				switch (enumValue)
				{
				case SpriteCoordOrigin::LOWER_LEFT: return GL_LOWER_LEFT;
				case SpriteCoordOrigin::UPPER_LEFT: return GL_UPPER_LEFT;

				default:
					assert(false);
					break;
				}
			}

			SpriteCoordOrigin ConvertGLenumToSpriteCoordOrigin(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_LOWER_LEFT: return SpriteCoordOrigin::LOWER_LEFT;
				case GL_UPPER_LEFT: return SpriteCoordOrigin::UPPER_LEFT;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertTextureTargetToGLenum(TextureTarget enumValue)
			{
				switch (enumValue)
				{
				case TextureTarget::TEXTURE1D: return GL_TEXTURE_1D;
				case TextureTarget::TEXTURE2D: return GL_TEXTURE_2D;
				case TextureTarget::TEXTURE3D: return GL_TEXTURE_3D;
				case TextureTarget::TEXTURE1D_ARRAY: return GL_TEXTURE_1D_ARRAY;
				case TextureTarget::TEXTURE2D_ARRAY: return GL_TEXTURE_2D_ARRAY;
				case TextureTarget::RECTANGLE: return GL_TEXTURE_RECTANGLE;
				case TextureTarget::CUBE_MAP: return GL_TEXTURE_CUBE_MAP;
				case TextureTarget::CUBE_MAP_ARRAY: return GL_TEXTURE_CUBE_MAP_ARRAY;
				case TextureTarget::TEXTURE2D_MULTISAMPLE: return GL_TEXTURE_2D_MULTISAMPLE;
				case TextureTarget::TEXTURE2D_MULTISAMPLE_ARRAY: return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;

				default:
					assert(false);
					break;
				}
			}

			TextureTarget ConvertGLenumToTextureTarget(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_TEXTURE_1D: return TextureTarget::TEXTURE1D;
				case GL_TEXTURE_2D: return TextureTarget::TEXTURE2D;
				case GL_TEXTURE_3D: return TextureTarget::TEXTURE3D;
				case GL_TEXTURE_1D_ARRAY: return TextureTarget::TEXTURE1D_ARRAY;
				case GL_TEXTURE_2D_ARRAY: return TextureTarget::TEXTURE2D_ARRAY;
				case GL_TEXTURE_RECTANGLE: return TextureTarget::RECTANGLE;
				case GL_TEXTURE_CUBE_MAP: return TextureTarget::CUBE_MAP;
				case GL_TEXTURE_CUBE_MAP_ARRAY: return TextureTarget::CUBE_MAP_ARRAY;
				case GL_TEXTURE_2D_MULTISAMPLE: return TextureTarget::TEXTURE2D_MULTISAMPLE;
				case GL_TEXTURE_2D_MULTISAMPLE_ARRAY: return TextureTarget::TEXTURE2D_MULTISAMPLE_ARRAY;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertBufferUsageToGLenum(BufferUsage enumValue)
			{
				switch (enumValue)
				{
				case BufferUsage::STREAM_DRAW: return GL_STREAM_DRAW;
				case BufferUsage::STREAM_READ: return GL_STREAM_READ;
				case BufferUsage::STREAM_COPY: return GL_STREAM_COPY;
				case BufferUsage::STATIC_DRAW: return GL_STATIC_DRAW;
				case BufferUsage::STATIC_READ: return GL_STATIC_READ;
				case BufferUsage::STATIC_COPY: return GL_STATIC_COPY;
				case BufferUsage::DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
				case BufferUsage::DYNAMIC_READ: return GL_DYNAMIC_READ;
				case BufferUsage::DYNAMIC_COPY: return GL_DYNAMIC_COPY;

				default:
					assert(false);
					break;
				}
			}

			BufferUsage ConvertGLenumToBufferUsage(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_STREAM_DRAW: return BufferUsage::STREAM_DRAW;
				case GL_STREAM_READ: return BufferUsage::STREAM_READ;
				case GL_STREAM_COPY: return BufferUsage::STREAM_COPY;
				case GL_STATIC_DRAW: return BufferUsage::STATIC_DRAW;
				case GL_STATIC_READ: return BufferUsage::STATIC_READ;
				case GL_STATIC_COPY: return BufferUsage::STATIC_COPY;
				case GL_DYNAMIC_DRAW: return BufferUsage::DYNAMIC_DRAW;
				case GL_DYNAMIC_READ: return BufferUsage::DYNAMIC_READ;
				case GL_DYNAMIC_COPY: return BufferUsage::DYNAMIC_COPY;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertDataTypeToGLenum(DataType enumValue)
			{
				switch (enumValue)
				{
				case DataType::INT8: return GL_BYTE;
				case DataType::UINT8: return GL_UNSIGNED_BYTE;
				case DataType::INT16: return GL_SHORT;
				case DataType::UINT16: return GL_UNSIGNED_SHORT;
				case DataType::INT32: return GL_INT;
				case DataType::UINT32: return GL_UNSIGNED_INT;
				case DataType::HALF: return GL_HALF_FLOAT;
				case DataType::FLOAT: return GL_FLOAT;
				case DataType::DOUBLE: return GL_DOUBLE;
				case DataType::UNKOWN: return GL_NONE;

				default:
					assert(false);
					break;
				}
			}

			GLuint MeasureDataTypeSize(DataType func)
			{
				switch (func)
				{
					case jet::util::DataType::INT8:  
					case jet::util::DataType::UINT8: return 1;
					case jet::util::DataType::HALF:
					case jet::util::DataType::INT16:
					case jet::util::DataType::UINT16:return 2;
					case jet::util::DataType::INT32:
					case jet::util::DataType::UINT32: 
					case jet::util::DataType::FLOAT:return 4;
					case jet::util::DataType::DOUBLE: return 8;
					default:
					case jet::util::DataType::UNKOWN:  return 0;
						break;
				}
			}

			DataType ConvertGLenumToDataType(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_BYTE: return DataType::INT8;
				case GL_UNSIGNED_BYTE: return DataType::UINT8;
				case GL_SHORT: return DataType::INT16;
				case GL_UNSIGNED_SHORT: return DataType::UINT16;
				case GL_INT: return DataType::INT32;
				case GL_UNSIGNED_INT: return DataType::UINT32;
				case GL_HALF_FLOAT: return DataType::HALF;
				case GL_FLOAT: return DataType::FLOAT;
				case GL_DOUBLE: return DataType::DOUBLE;
				case GL_NONE: return DataType::UNKOWN;

				default:
					assert(false);
					break;
				}
			}

			GLenum ConvertPrimitivesToGLenum(Primitives enumValue)
			{
				switch (enumValue)
				{
				case Primitives::POINTS: return GL_POINTS;
				case Primitives::LINE_STRIP: return GL_LINE_STRIP;
				case Primitives::LINE_LOOP: return GL_LINE_LOOP;
				case Primitives::LINES: return GL_LINES;
				case Primitives::LINE_STRIP_ADJACENCY: return GL_LINE_STRIP_ADJACENCY;
				case Primitives::LINES_ADJACENCY: return GL_LINES_ADJACENCY;
				case Primitives::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
				case Primitives::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
				case Primitives::TRIANGLES: return GL_TRIANGLES;
				case Primitives::TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
				case Primitives::TRIANGLES_ADJACENCY: return GL_TRIANGLES_ADJACENCY;
				case Primitives::PATCHES: return GL_PATCHES;

				default:
					assert(false);
					break;
				}
			}

			Primitives ConvertGLenumToPrimitives(GLenum enumValue)
			{
				switch (enumValue)
				{
				case GL_POINTS: return Primitives::POINTS;
				case GL_LINE_STRIP: return Primitives::LINE_STRIP;
				case GL_LINE_LOOP: return Primitives::LINE_LOOP;
				case GL_LINES: return Primitives::LINES;
				case GL_LINE_STRIP_ADJACENCY: return Primitives::LINE_STRIP_ADJACENCY;
				case GL_LINES_ADJACENCY: return Primitives::LINES_ADJACENCY;
				case GL_TRIANGLE_STRIP: return Primitives::TRIANGLE_STRIP;
				case GL_TRIANGLE_FAN: return Primitives::TRIANGLE_FAN;
				case GL_TRIANGLES: return Primitives::TRIANGLES;
				case GL_TRIANGLE_STRIP_ADJACENCY: return Primitives::TRIANGLE_STRIP_ADJACENCY;
				case GL_TRIANGLES_ADJACENCY: return Primitives::TRIANGLES_ADJACENCY;
				case GL_PATCHES: return Primitives::PATCHES;

				default:
					assert(false);
					break;
				}
			}
		}
	}
}
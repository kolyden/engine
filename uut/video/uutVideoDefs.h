#pragma once
#include "core/uutDefine.h"

namespace uut
{
    enum EImageFormat
    {
        IMAGEFORMAT_UNKNOWN,
        IMAGEFORMAT_ARGB,
        IMAGEFORMAT_RGB,
        IMAGEFORMAT_GRAY,
        IMAGEFORMAT_GRAY_ALPHA,
    };

    enum ETextureType
    {
        TEXTURE_STATIC,
        TEXTURE_DYNAMIC,
        TEXTURE_TARGET,
    };

    enum EBufferType
    {
        BUFFER_VERTEX,
        BUFFER_INDEX,
    };

    enum EBufferFlag
    {
		BUFFERFLAG_STATIC = 0,
        BUFFERFLAG_DYNAMIC = 1,
    };

    enum EValueType
    {
        VALUE_BYTE,
        VALUE_UBYTE,
        VALUE_SHORT,
        VALUE_USHORT,
        VALUE_FLOAT,
        VALUE_FIXED,
    };

    enum EUsageType
    {
        USAGE_POSITION,
        USAGE_TEXCOORDS,
        USAGE_COLOR,
    };

    struct SDeclareType
    {
        uint8_t stream;
        EUsageType usage;
        uint32_t count;
        EValueType value;
        uint32_t offset;
    };

    enum EPrimitiveType
    {
        PRIMITIVE_POINTS,
        PRIMITIVE_LINES,
        PRIMITIVE_LINE_STRIP,
        PRIMITIVE_TRIANGLES,
        PRIMITIVE_TRIANGLE_STRIP,
        PRIMITIVE_TRIANGLE_FAN,
    };

    enum ETransformType
    {
        TRANSFORM_VIEW,
        TRANSFORM_PROJECTION,
    };

    enum ERenderState
    {
        RENDERSATE_BLEND,
        RENDERSTATE_ALPHA_TEST,
        RENDERSTATE_DEPTH_TEST,
        RENDERSTATE_LIGHTNING,
    };

    enum EBlendFunc
    {
        BLEND_ZERO, BLEND_ONE, BLEND_SRC_COLOR, BLEND_ONE_MINUS_SRC_COLOR, BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA,
        BLEND_DST_ALPHA, BLEND_ONE_MINUS_DST_ALPHA, BLEND_DST_COLOR, BLEND_ONE_MINUS_DST_COLOR, BLEND_SRC_ALPHA_SATURATE
    };

    enum EColorType
    {
        COLOR_CLEAR,
        COLOR_DRAW,
    };

    enum EPolygonMode
    {
        POLYGON_POINT,
        POLYGON_LINE,
        POLYGON_FILL,
    };
}
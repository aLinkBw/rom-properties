/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * RpTextureWrapper.hpp: librptexture file format wrapper.                 *
 *                                                                         *
 * Copyright (c) 2019 by David Korth.                                      *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "config.librptexture.h"

#include "RpTextureWrapper.hpp"
#include "librpbase/RomData_p.hpp"

// librpbase
#include "librpbase/common.h"
#include "librpbase/byteswap.h"
#include "librpbase/aligned_malloc.h"
#include "librpbase/TextFuncs.hpp"
#include "librpbase/file/IRpFile.hpp"

#include "libi18n/i18n.h"
using namespace LibRpBase;

// librptexture
#include "librptexture/fileformat/FileFormat.hpp"
// TEMPORARY: Switch to FileFormatFactory once it's available.
#include "librptexture/fileformat/DirectDrawSurface.hpp"
#ifdef ENABLE_GL
# include "librptexture/fileformat/KhronosKTX.hpp"
#endif /* ENABLE_GL */
#include "librptexture/fileformat/SegaPVR.hpp"
#include "librptexture/fileformat/ValveVTF.hpp"
#include "librptexture/fileformat/ValveVTF3.hpp"
#include "librptexture/fileformat/XboxXPR.hpp"
using LibRpTexture::rp_image;
using LibRpTexture::FileFormat;

// C includes. (C++ namespace)
#include <cassert>
#include <cstring>

// C++ includes.
#include <vector>
using std::vector;

namespace LibRomData {

ROMDATA_IMPL(RpTextureWrapper)
ROMDATA_IMPL_IMG_TYPES(RpTextureWrapper)

class RpTextureWrapperPrivate : public RomDataPrivate
{
	public:
		RpTextureWrapperPrivate(RpTextureWrapper *q, IRpFile *file);
		~RpTextureWrapperPrivate();

	private:
		typedef RomDataPrivate super;
		RP_DISABLE_COPY(RpTextureWrapperPrivate)

	public:
		// librptexture file format object.
		FileFormat *texture;
};

/** RpTextureWrapperPrivate **/

RpTextureWrapperPrivate::RpTextureWrapperPrivate(RpTextureWrapper *q, IRpFile *file)
	: super(q, file)
	, texture(nullptr)
{ }

RpTextureWrapperPrivate::~RpTextureWrapperPrivate()
{
	if (texture) {
		texture->unref();
	}
}

/** RpTextureWrapper **/

/**
 * Read a texture file supported by librptexture.
 *
 * A ROM image must be opened by the caller. The file handle
 * will be ref()'d and must be kept open in order to load
 * data from the ROM image.
 *
 * To close the file, either delete this object or call close().
 *
 * NOTE: Check isValid() to determine if this is a valid ROM.
 *
 * @param file Open ROM image.
 */
RpTextureWrapper::RpTextureWrapper(IRpFile *file)
	: super(new RpTextureWrapperPrivate(this, file))
{
	// This class handles texture files.
	RP_D(RpTextureWrapper);
	d->className = "RpTextureWrapper";
	d->fileType = FTYPE_TEXTURE_FILE;

	if (!d->file) {
		// Could not ref() the file handle.
		return;
	}

	// Read the texture's magic number.
	uint32_t magic;
	d->file->rewind();
	size_t size = d->file->read(&magic, sizeof(magic));
	if (size != sizeof(magic)) {
		d->file->unref();
		d->file = nullptr;
		return;
	}

	// TODO: Create a factory class similar to RomDataFactory.
	switch (be32_to_cpu(magic)) {
		case 'DDS ':
			// DirectDrawSurface
			d->texture = new LibRpTexture::DirectDrawSurface(d->file);
			break;
#ifdef ENABLE_GL
		case (uint32_t)'\xABKTX':
			// KhronosKTX
			d->texture = new LibRpTexture::KhronosKTX(d->file);
			break;
#endif /* ENABLE_GL */
		case 'PVRT': case 'GVRT': case 'PVRX':
		case 'GBIX': case 'GCIX':
			// SegaPVR
			d->texture = new LibRpTexture::SegaPVR(d->file);
			break;
		case 'VTF\0':
			// ValveVTF
			d->texture = new LibRpTexture::ValveVTF(d->file);
			break;
		case 'VTF3':
			// ValveVTF3
			d->texture = new LibRpTexture::ValveVTF3(d->file);
			break;
		case 'XPR0':
			// XboxXPR
			d->texture = new LibRpTexture::XboxXPR(d->file);
			break;
		default:
			// Not supported.
			d->file->unref();
			d->file = nullptr;
			return;
	}

	if (!d->texture->isValid()) {
		// Not a valid texture.
		d->texture->unref();
		d->texture = nullptr;
		d->file->unref();
		d->file = nullptr;
		return;
	}

	d->isValid = true;
}

/**
 * Is a ROM image supported by this class?
 * @param info DetectInfo containing ROM detection information.
 * @return Class-specific system ID (>= 0) if supported; -1 if not.
 */
int RpTextureWrapper::isRomSupported_static(const DetectInfo *info)
{
	assert(info != nullptr);
	assert(info->header.pData != nullptr);
	assert(info->header.addr == 0);
	if (!info || !info->header.pData ||
	    info->header.addr != 0 ||
	    info->header.size < sizeof(uint32_t))
	{
		// Either no detection information was specified,
		// or the header is too small.
		return -1;
	}

	// TODO: Create a factory class similar to RomDataFactory.
	const uint32_t *const pData32 = reinterpret_cast<const uint32_t*>(info->header.pData);
	switch (be32_to_cpu(pData32[0])) {
		case 'DDS ':
			// DirectDrawSurface
#ifdef ENABLE_GL
		case (uint32_t)'\xABKTX':
			// KhronosKTX
#endif /* ENABLE_GL */
		case 'PVRT': case 'GVRT': case 'PVRX':
		case 'GBIX': case 'GCIX':
			// SegaPVR
		case 'VTF\0':
			// ValveVTF
		case 'VTF3':
			// ValveVTF3
		case 'XPR0':
			// XboxXPR

			// Supported!
			return 0;

		default:
			break;
	}

	// Not supported.
	return -1;
}

/**
 * Get the name of the system the loaded ROM is designed for.
 * @param type System name type. (See the SystemName enum.)
 * @return System name, or nullptr if type is invalid.
 */
const char *RpTextureWrapper::systemName(unsigned int type) const
{
	RP_D(const RpTextureWrapper);
	if (!d->isValid || !isSystemNameTypeValid(type))
		return nullptr;

	// TODO: Short names and whatnot from FileFormat.
	return d->texture->textureFormatName();
}

/**
 * Get a list of all supported file extensions.
 * This is to be used for file type registration;
 * subclasses don't explicitly check the extension.
 *
 * NOTE: The extensions include the leading dot,
 * e.g. ".bin" instead of "bin".
 *
 * NOTE 2: The array and the strings in the array should
 * *not* be freed by the caller.
 *
 * @return NULL-terminated array of all supported file extensions, or nullptr on error.
 */
const char *const *RpTextureWrapper::supportedFileExtensions_static(void)
{
	// Not used anymore.
	// RomDataFactory queries extensions from FileFormatFactory directly.
	static const char *const exts[] = { nullptr };
	return exts;
}

/**
 * Get a list of all supported MIME types.
 * This is to be used for metadata extractors that
 * must indicate which MIME types they support.
 *
 * NOTE: The array and the strings in the array should
 * *not* be freed by the caller.
 *
 * @return NULL-terminated array of all supported file extensions, or nullptr on error.
 */
const char *const *RpTextureWrapper::supportedMimeTypes_static(void)
{
	// Not used anymore.
	// RomDataFactory queries MIME types from FileFormatFactory directly.
	static const char *const mimeTypes[] = { nullptr };
	return mimeTypes;
}

/**
 * Get a bitfield of image types this class can retrieve.
 * @return Bitfield of supported image types. (ImageTypesBF)
 */
uint32_t RpTextureWrapper::supportedImageTypes_static(void)
{
	return IMGBF_INT_IMAGE;
}

/**
 * Get a list of all available image sizes for the specified image type.
 * @param imageType Image type.
 * @return Vector of available image sizes, or empty vector if no images are available.
 */
vector<RomData::ImageSizeDef> RpTextureWrapper::supportedImageSizes(ImageType imageType) const
{
	ASSERT_supportedImageSizes(imageType);

	RP_D(const RpTextureWrapper);
	if (!d->isValid || imageType != IMG_INT_IMAGE) {
		return vector<ImageSizeDef>();
	}

	// Return the image's size.
	const ImageSizeDef imgsz[] = {{nullptr,
		static_cast<uint16_t>(d->texture->width()),
		static_cast<uint16_t>(d->texture->height()),
		0
	}};
	return vector<ImageSizeDef>(imgsz, imgsz + 1);
}

/**
 * Get image processing flags.
 *
 * These specify post-processing operations for images,
 * e.g. applying transparency masks.
 *
 * @param imageType Image type.
 * @return Bitfield of ImageProcessingBF operations to perform.
 */
uint32_t RpTextureWrapper::imgpf(ImageType imageType) const
{
	ASSERT_imgpf(imageType);

	RP_D(const RpTextureWrapper);
	if (imageType != IMG_INT_IMAGE) {
		// Only IMG_INT_IMAGE is supported by RpTextureWrapper.
		return 0;
	}

	// If both dimensions of the texture are 64 or less,
	// specify nearest-neighbor scaling.
	uint32_t ret = 0;
	if (d->texture->width() <= 64 && d->texture->height() <= 64) {
		// 64x64 or smaller.
		ret = IMGPF_RESCALE_NEAREST;
	}
	return ret;
}

/**
 * Load field data.
 * Called by RomData::fields() if the field data hasn't been loaded yet.
 * @return Number of fields read on success; negative POSIX error code on error.
 */
int RpTextureWrapper::loadFieldData(void)
{
	RP_D(RpTextureWrapper);
	if (!d->fields->empty()) {
		// Field data *has* been loaded...
		return 0;
	} else if (!d->file) {
		// File isn't open.
		return -EBADF;
	} else if (!d->isValid) {
		// Unknown file type.
		return -EIO;
	}

	// RpTextureWrapper header
	const FileFormat *const texture = d->texture;
	d->fields->reserve(3);	// Maximum of 3 fields.

	// Dimensions
	int dimensions[3];
	int ret = texture->getDimensions(dimensions);
	if (ret == 0) {
		d->fields->addField_dimensions(C_("RpTextureWrapper", "Dimensions"),
			dimensions[0], dimensions[1], dimensions[2]);
	}

	// Pixel format
	d->fields->addField_string(C_("RpTextureWrapper", "Pixel Format"), texture->pixelFormat());

	// Mipmap count
	int mipmapCount = texture->mipmapCount();
	if (mipmapCount >= 0) {
		d->fields->addField_string_numeric(C_("RpTextureWrapper", "Mipmap Count"), mipmapCount);
	}

	// Texture-specific fields.
	texture->getFields(d->fields);

	// TODO: More fields.

	// Finished reading the field data.
	return static_cast<int>(d->fields->count());
}

/**
 * Load metadata properties.
 * Called by RomData::metaData() if the field data hasn't been loaded yet.
 * @return Number of metadata properties read on success; negative POSIX error code on error.
 */
int RpTextureWrapper::loadMetaData(void)
{
	RP_D(RpTextureWrapper);
	if (d->metaData != nullptr) {
		// Metadata *has* been loaded...
		return 0;
	} else if (!d->file) {
		// File isn't open.
		return -EBADF;
	} else if (!d->isValid) {
		// Unknown file type.
		return -EIO;
	}

	// Create the metadata object.
	d->metaData = new RomMetaData();
	d->metaData->reserve(2);	// Maximum of 2 metadata properties.

	// Dimensions
	int dimensions[3];
	int ret = d->texture->getDimensions(dimensions);
	if (ret == 0) {
		if (dimensions[0] > 0) {
			d->metaData->addMetaData_integer(Property::Width, dimensions[0]);
		}
		if (dimensions[1] > 0) {
			d->metaData->addMetaData_integer(Property::Height, dimensions[1]);
		}
	}

	// Finished reading the metadata.
	return static_cast<int>(d->metaData->count());
}

/**
 * Load an internal image.
 * Called by RomData::image().
 * @param imageType	[in] Image type to load.
 * @param pImage	[out] Pointer to const rp_image* to store the image in.
 * @return 0 on success; negative POSIX error code on error.
 */
int RpTextureWrapper::loadInternalImage(ImageType imageType, const rp_image **pImage)
{
	ASSERT_loadInternalImage(imageType, pImage);

	RP_D(RpTextureWrapper);
	if (imageType != IMG_INT_IMAGE) {
		// Only IMG_INT_IMAGE is supported by PVR.
		*pImage = nullptr;
		return -ENOENT;
	} else if (!d->file) {
		// File isn't open.
		*pImage = nullptr;
		return -EBADF;
	} else if (!d->isValid) {
		// Unknown file type.
		*pImage = nullptr;
		return -EIO;
	}

	// Load the image.
	*pImage = d->texture->image();
	return (*pImage != nullptr ? 0 : -EIO);
}

}

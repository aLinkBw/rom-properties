/***************************************************************************
 * ROM Properties Page shell extension. (librpbase)                        *
 * SparseDiscReader.hpp: Disc reader base class for disc image formats     *
 * that use sparse and/or compressed blocks, e.g. CISO, WBFS, GCZ.         *
 *                                                                         *
 * Copyright (c) 2016-2019 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_LIBRPBASE_SPARSEDISCREADER_HPP__
#define __ROMPROPERTIES_LIBRPBASE_SPARSEDISCREADER_HPP__

#include "IDiscReader.hpp"

namespace LibRpBase {

class SparseDiscReaderPrivate;
class SparseDiscReader : public IDiscReader
{
	protected:
		explicit SparseDiscReader(SparseDiscReaderPrivate *d, IRpFile *file);
	public:
		virtual ~SparseDiscReader();

	private:
		typedef IDiscReader super;
		RP_DISABLE_COPY(SparseDiscReader)
	protected:
		friend class SparseDiscReaderPrivate;
		SparseDiscReaderPrivate *const d_ptr;

	public:
		/** IDiscReader functions. **/

		/**
		 * Read data from the disc image.
		 * @param ptr Output data buffer.
		 * @param size Amount of data to read, in bytes.
		 * @return Number of bytes read.
		 */
		size_t read(void *ptr, size_t size) final;

		/**
		 * Set the disc image position.
		 * @param pos disc image position.
		 * @return 0 on success; -1 on error.
		 */
		int seek(int64_t pos) final;

		/**
		 * Get the disc image position.
		 * @return Disc image position on success; -1 on error.
		 */
		int64_t tell(void) final;

		/**
		 * Get the disc image size.
		 * @return Disc image size, or -1 on error.
		 */
		int64_t size(void) final;

	protected:
		/** Virtual functions for SparseDiscReader subclasses. **/

		/**
		 * Get the physical address of the specified logical block index.
		 *
		 * Special return values:
		 * -  0: Empty block. (Sparse files are unlikely to have blocks that
		 *                     start at address 0.)
		 * - -1: Invalid block index.
		 *
		 * @param blockIdx	[in] Block index.
		 * @return Physical block address.
		 */
		virtual int64_t getPhysBlockAddr(uint32_t blockIdx) const = 0;

		/**
		 * Read the specified block.
		 *
		 * This can read either a full block or a partial block.
		 * For a full block, set pos = 0 and size = block_size.
		 *
		 * This function can be overridden by subclasses if necessary,
		 * though usually it isn't needed. Override getPhysBlockAddr()
		 * instead.
		 *
		 * @param blockIdx	[in] Block index.
		 * @param ptr		[out] Output data buffer.
		 * @param pos		[in] Starting position. (Must be >= 0 and <= the block size!)
		 * @param size		[in] Amount of data to read, in bytes. (Must be <= the block size!)
		 * @return Number of bytes read, or -1 if the block index is invalid.
		 */
		virtual int readBlock(uint32_t blockIdx, void *ptr, int pos, size_t size);
};

}

#endif /* __ROMPROPERTIES_LIBRPBASE_SPARSEDISCREADER_HPP__ */

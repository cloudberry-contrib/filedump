/*-------------------------------------------------------------------------
 *
 * gpdb.h
 *    Dump append only table
 *
 *
 * Copyright (c) 2021 VMware, Inc. or its affiliates
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 *
 *-------------------------------------------------------------------------
 */
#ifndef GPDB_H
#define GPDB_H

#include "access/spgist_private.h"
#include "access/ginblock.h"
#include "cdb/cdbappendonlyam.h"

typedef enum gpdbSwitches
{
	GPDB_APPEND_ONLY           = 0x00000001,	/* -z: AppendOnly files */
	GPDB_HAS_CHECKSUM          = 0x00000002,	/* -M: Checksum is present */
#if 0
	/* FIXME: GPDB: retire -p */
	GPDB_DEPARSE_HEAP          = 0x00000004,	/* -p: Deparse heap data */
#endif
#if 0
	/* FIXME: GPDB: how to use -D and -B? */
	GPDB_DISABLE_DEAD_TUPLE    = 0x00000008,	/* -D: Disable dead tuple info */
	GPDB_BLOCK_DIRECTORY_FILE  = 0x00000010,	/* -B: Deparse the input block
												 *     directory file */
#endif

	GPDB_COMPRESS_TYPE_MASK    = 0x000f0000,	/* -T: Compress type */
	GPDB_COMPRESS_TYPE_NONE    = 0x00000000,	/* Default compress type */
	GPDB_COMPRESS_TYPE_ZLIB    = 0x00010000,
	GPDB_COMPRESS_TYPE_QUICKLZ = 0x00020000,
	GPDB_COMPRESS_TYPE_ZSTD    = 0x00030000,

	GPDB_COMPRESS_LEVEL_MASK   = 0x00f00000,	/* -L: Compress level */
	GPDB_COMPRESS_LEVEL_SHIFT  = 20,
	GPDB_COMPRESS_LEVEL_MAX    = (GPDB_COMPRESS_LEVEL_MASK >>
								  GPDB_COMPRESS_LEVEL_SHIFT),
	GPDB_COMPRESS_LEVEL_DEFAULT= 1 << GPDB_COMPRESS_LEVEL_SHIFT,

	GPDB_ORIENTATION_MASK      = 0x01000000,	/* -O: Orientation of AO */
	GPDB_ORIENTATION_ROW       = 0x00000000,	/* Default orientation */
	GPDB_ORIENTATION_COLUMN    = 0x01000000,
}			gpdbSwitches;

extern unsigned int gpdbOptions;

#define GPDB_SET_OPTION(_x,_y,_z,_m)					\
	if (_x & _m)										\
	{													\
		rc = OPT_RC_DUPLICATE; 							\
		duplicateSwitch = _z;							\
	}													\
	else												\
		_x |= _y;

#define GPDB_GET_COMPRESS_TYPE(_x)						\
	(_x & GPDB_COMPRESS_TYPE_MASK)
#define GPDB_SET_COMPRESS_TYPE(_x,_y)					\
	GPDB_SET_OPTION(_x,_y,'T',GPDB_COMPRESS_TYPE_MASK)

#define GPDB_GET_COMPRESS_LEVEL(_x)						\
	((_x & GPDB_COMPRESS_LEVEL_MASK) >> GPDB_COMPRESS_LEVEL_SHIFT)
#define GPDB_SET_COMPRESS_LEVEL(_x,_y)					\
	GPDB_SET_OPTION(_x,									\
					_y << GPDB_COMPRESS_LEVEL_SHIFT,	\
					'L',								\
					GPDB_COMPRESS_LEVEL_MASK)

#define GPDB_GET_ORIENTATION(_x)						\
	(_x & GPDB_ORIENTATION_MASK)
#define GPDB_SET_ORIENTATION(_x,_y)						\
	GPDB_SET_OPTION(_x, _y, 'O', GPDB_ORIENTATION_MASK)

#if 0
extern void file_set_dirs(char *file);
extern void build_tupdesc(void);
extern void fixupItemBlock(Page page, unsigned int blockSize, unsigned int bytesToFormat);
extern void DeparseMiniPage(struct Minipage *minipage, uint32 numEntries, char *deparsed);
#endif

extern int DumpAppendOnlyFileContents(FILE *fp, unsigned int blockSize);

#endif   /* GPDB_H */

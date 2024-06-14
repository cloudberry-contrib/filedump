/*-------------------------------------------------------------------------
 *
 * mock.c
 *    Mock function calls for filedump
 *
 * Copyright (c) 2021 VMware, Inc. or its affiliates
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 *-------------------------------------------------------------------------
 */
#include "pg_filedump.h"

#include "cdb/cdbvars.h"
#include "storage/lwlock.h"
#include "utils/memutils.h"

/****************************************************************************
 * src/backend/utils/init/globals.c
 ***************************************************************************/

int         NBuffers = 4096;

/****************************************************************************
 * src/backend/storage/lmgr/lwlock.c
 ***************************************************************************/

bool
LWLockHeldByMe(LWLock *l)
{
	return true;
}

/****************************************************************************
 * src/backend/storage/buffer/bufmgr.c
 ***************************************************************************/

bool
BufferLockHeldByMe(Page page)
{
	return true;
}

/****************************************************************************
 * src/backend/utils/misc/guc.c
 ***************************************************************************/

bool            assert_enabled = true;

/****************************************************************************
 * src/backend/utils/misc/guc_gp.c
 ***************************************************************************/

bool		Debug_appendonly_print_storage_headers = false;
bool        Debug_appendonly_print_verify_write_block = false;

/****************************************************************************
 * src/backend/cdb/cdbvars.c
 ***************************************************************************/

GpId        GpIdentity = {UNINITIALIZED_GP_IDENTITY_VALUE, UNINITIALIZED_GP_IDENTITY_VALUE};
bool        gp_reraise_signal = false;


/****************************************************************************
 * src/backend/utils/mmgr/mcxt.c
 ***************************************************************************/

MemoryContext   CurrentMemoryContext = NULL;

void
MemoryContextSetParent(MemoryContext context, MemoryContext new_parent)
{
}

void
MemoryContextDeleteImpl(MemoryContext context, const char* sfile, const char *func, int sline)
{
}

char *
MemoryContextStrdup(MemoryContext context, const char *string)
{
	char	   *nstr;
	Size		len = strlen(string) + 1;

	nstr = (char *) malloc (len);

	memcpy(nstr, string, len);

	return nstr;
}

/****************************************************************************
 * src/backend/utils/error/elog.c
 ***************************************************************************/


void
errcode_for_file_access(void)
{
}

bool
errstart(int elevel, const char *domain)
{
	return (elevel >= ERROR);
}

void
errfinish(const char *filename, int lineno, const char *funcname)
{
	exit(1);
}

int
errprintstack(bool printstack)
{
	return 0;					/* return value does not matter */
}

void
errcode(int sqlerrcode)
{
}

void
errmsg(const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
}

void
errmsg_internal(const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
}

void
errdetail(const char *fmt,...)
{
	fprintf(stderr, "DETAIL: %s\n", fmt);
}

void
errdetail_log(const char *fmt,...)
{
	fprintf(stderr, "DETAIL: %s\n", fmt);
}

void
errhint(const char *fmt,...)
{
	fprintf(stderr, "HINT: %s\n", fmt);
}

/* vi: set ts=4 : */

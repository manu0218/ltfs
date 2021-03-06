/*
**
**  OO_Copyright_BEGIN
**
**
**  Copyright 2010, 2018 IBM Corp. All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without
**   modification, are permitted provided that the following conditions
**  are met:
**  1. Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**  2. Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**  documentation and/or other materials provided with the distribution.
**  3. Neither the name of the copyright holder nor the names of its
**     contributors may be used to endorse or promote products derived from
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
**  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
**  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
**  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
**  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
**  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
**  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
**  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
**  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
**  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
**  POSSIBILITY OF SUCH DAMAGE.
**
**
**  OO_Copyright_END
**
*************************************************************************************
**
** COMPONENT NAME:  IBM Linear Tape File System
**
** FILE NAME:       plugin.h
**
** DESCRIPTION:     Declares functions for working with libltfs plugins.
**
** AUTHORS:         Brian Biskeborn
**                  IBM Almaden Research Center
**                  bbiskebo@us.ibm.com
**
*************************************************************************************
*/

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "config_file.h"

struct libltfs_plugin {
	void *lib_handle;  /**< Handle to the shared library implementing the plugin */
	void *ops;         /**< Pointer to the plugin's function list */
	void *messages;    /**< Handle to the plugin message bundle generated by ltfsprintf.c */
};

/**
 * Load a plugin (a shared library that implements a particular set of operations).
 * This function may be called multiple times for the same plugin.
 * It is not reentrant.
 * @param pl Plugin structure to populate.
 * @param type Plugin type, must be "iosched", "changer", "kmi" or "driver".
 * @param name The name of the plugin to load.
 * @param config Configuration structure to search for the plugin path.
 * @return 0 on success or a negative value on error.
 */
int plugin_load(struct libltfs_plugin *pl, const char *type, const char *name,
	struct config_file *config);

/**
 * Unload a previously loaded plugin. This should be called once for each call to @plugin_load.
 * This function is not reentrant.
 * @param pl Plugin to unload.
 * @return 0 on success or a negative value on error.
 */
int plugin_unload(struct libltfs_plugin *pl);

/**
 * Show usage of a plugin (a shared library that implements a particular set of operations).
 * @param type Plugin type, must be "iosched", "kmi" or "driver".
 * @param config Configuration structure to search for the plugin path.
 */
void plugin_usage(const char *type, struct config_file *config);

#endif /* __PLUGIN_H__ */


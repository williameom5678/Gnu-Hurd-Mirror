/* 
   Copyright (C) 1995 Free Software Foundation, Inc.
   Written by Michael I. Bushnell.

   This file is part of the GNU Hurd.

   The GNU Hurd is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   The GNU Hurd is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include "fshelp.h"
#include <unistd.h>
#include <string.h>
#include <hurd.h>

error_t
fshelp_start_translator (mach_port_t underlying, 
			 mach_msg_type_name_t underlying_type,
			 char *name, char *argz, int argz_len,
			 int timeout, fsys_t *control)
{
  mach_port_t ports[INIT_PORT_MAX];
  mach_port_t fds[STDERR_FILENO + 1];
  int ints[INIT_INT_MAX];
  int i;
  
  for (i = 0; i < INIT_PORT_MAX; i++)
    ports[i] = MACH_PORT_NULL;
  for (i = 0; i < STDERR_FILENO + 1; i++)
    fds[i] = MACH_PORT_NULL;
  bzero (ints, INIT_INT_MAX * sizeof (int));
  
  ports[INIT_PORT_CWDIR] = getcwdir ();
  ports[INIT_PORT_CRDIR] = getcrdir ();
  ports[INIT_PORT_AUTH] = getauth ();
  fds[STDERR_FILENO] = getdport (STDERR_FILENO);
  
  return fshelp_start_translator_long (underlying, underlying_type,
				       name, argz, argz_len,
				       fds, MACH_MSG_TYPE_MOVE_SEND,
				       STDERR_FILENO + 1,
				       ports, MACH_MSG_TYPE_MOVE_SEND,
				       INIT_PORT_MAX,
				       ints, INIT_INT_MAX,
				       timeout, control);
}

  
		 

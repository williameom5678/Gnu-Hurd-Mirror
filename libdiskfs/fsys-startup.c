/*
   Copyright (C) 1993, 1994, 1995 Free Software Foundation

This file is part of the GNU Hurd.

The GNU Hurd is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

The GNU Hurd is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the GNU Hurd; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* Written by Michael I. Bushnell.  */

#include "priv.h"
#include "fsys_S.h"

/* Implement fsys_startup as described in <hurd/fsys.defs>. */
kern_return_t
diskfs_S_fsys_startup (mach_port_t port,
		       mach_port_t ctl,
		       mach_port_t *real,
		       mach_msg_type_name_t *realpoly)
{
  struct port_info *pi = ports_lookup_port (diskfs_port_bucket, port,
					    diskfs_transboot_class);
  error_t err;
  
  if (pi)
    {
      err = fshelp_handle_fsys_startup (pi, ctl, real, realpoly);
      ports_port_deref (pi);
      return err;
    }
  else
    return diskfs_execboot_fsys_startup (port, ctl, real, realpoly);
}


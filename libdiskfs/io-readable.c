/* 
   Copyright (C) 1994 Free Software Foundation

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include "priv.h"

/* Implement io_readable as described in <hurd/io.defs>. */
error_t
diskfs_S_io_readable (struct protid *cred,
		      int *amount)
{
  struct node *np;
  error_t err;

  if (!cred)
    return EOPNOTSUPP;
  
  if (!(cred->po->openstat & O_READ))
    return EINVAL;

  np = cred->po->np;
  
  mutex_lock (&np->lock);
  err = ioserver_get_conch (&np->i_conch);
  if (!err)
    *amount = np->dn_stat.st_size - cred->po->filepointer;

  mutex_unlock (&np->lock);
  return err;
}

/* mod_ntlm file: $Id: rfcnb-io.h 20 2004-05-03 17:25:39Z cardoe $ */

#ifndef RFCNB_IO_H
#define RFCNB_IO_H

/* UNIX RFCNB (RFC1001/RFC1002) NetBIOS implementation
 * 
 * Version 1.0 RFCNB IO Routines Defines
 * 
 * Copyright (C) Richard Sharpe 1996
 * 
 */

/* 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  This program is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.  You
 * should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 675 Mass Ave, Cambridge, MA 02139, USA. */

static int RFCNB_Put_Pkt(struct RFCNB_Con *con, struct RFCNB_Pkt *pkt, int len);

static int RFCNB_Get_Pkt(struct RFCNB_Con *con, struct RFCNB_Pkt *pkt, int len);

#endif

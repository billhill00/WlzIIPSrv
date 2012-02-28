#ifndef WLZ_REMOTE_IMAGE_H
#define WLZ_REMOTE_IMAGE_H
#if defined(__GNUC__)
#ident "University of Edinburgh $Id$"
#else
static char _WlzRemoteImage_h[] = "University of Edinburgh $Id$";
#endif
/*!
* \file         WlzRemoteImage.h
* \author       Yiya Yang
* \date         September 2010
* \version      $Id$
* \par
* Address:
*               MRC Human Genetics Unit,
*               MRC Institute of Genetics and Molecular Medicine,
*               University of Edinburgh,
*               Western General Hospital,
*               Edinburgh, EH4 2XU, UK.
* \par
* Copyright (C), [2012],
* The University Court of the University of Edinburgh,
* Old College, Edinburgh, UK.
* 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be
* useful but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
* PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the Free
* Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA  02110-1301, USA.
* \brief	Reads Woolz objects from a remote server socket for the
* 		Woolz IIP server.
* \ingroup	WlzIIPServer
*/

#include "Wlz.h"

class WlzRemoteImage {
/// buffer size for reading and parsing files

 protected:
  
  static int
    parse_URL(const char *url, char *hostname, int *port, char *identifier);
  
  static WlzObject*  
    wlzHttpRead(char const* url);
  
 public:
  
  static WlzObject*  
    wlzRemoteReadObj(const char* filename, const char* server, int port);
};

#endif

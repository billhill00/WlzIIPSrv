#if defined(__GNUC__)
#ident "MRC HGU $Id$"
#else
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#pragma ident "MRC HGU $Id$"
#else
static char _Task_h[] = "MRC HGU $Id$";
#endif
#endif

/*
    IIP Generic Task Class

    Copyright (C) 2008 Zsolt Husz, Medical research Council, UK.
    Copyright (C) 2006 Ruven Pillay.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef _TASK_H
#define _TASK_H



#include <string>
#include <fstream>
#include "IIPImage.h"
#include "IIPResponse.h"
#include "JPEGCompressor.h"
#include "View.h"
#include "TileManager.h"
#include "Timer.h"
#include "Writer.h"
#include "Cache.h"

#include "ViewParameters.h"
#include "WlzImage.h"


// Use the hashmap extensions if we are using >= gcc 3.1
#ifdef __GNUC__

#if (__GNUC__ == 3 && __GNUC_MINOR__ >= 1) || (__GNUC__ >= 4)
#define USE_HASHMAP 1
#endif

// And the high performance memory pool allocator if >= gcc 3.4
#if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ >= 4)
#define USE_POOL_ALLOCATOR 1
#endif

#endif



#ifdef USE_HASHMAP
#include <ext/hash_map>

#ifdef USE_POOL_ALLOCATOR
#include <ext/pool_allocator.h>
typedef __gnu_cxx::hash_map < const std::string, IIPImage,
			      __gnu_cxx::hash< const std::string >,
			      std::equal_to< const std::string >,
			      __gnu_cxx::__pool_alloc< std::pair<const std::string,IIPImage> >
			      > imageCacheMapType;
#else
typedef __gnu_cxx::hash_map <const std::string,IIPImage> imageCacheMapType;
#endif

#else
typedef std::map<const std::string,IIPImage> imageCacheMapType;
#endif




/// Structure to hold our session data
struct Session {
  IIPImage **image;
  JPEGCompressor* jpeg;
  View* view;
  IIPResponse* response;
  int loglevel;
  std::ofstream* logfile;

  imageCacheMapType *imageCache;
  Cache* tileCache;

  /// sectioning parameters for a Woolz object
  ViewParameters *viewParams;

#ifdef DEBUG
  FileWriter* out;
#else
  FCGIWriter* out;
#endif

};




/// Generic class to encapsulate various commands
class Task {

 protected:

  /// Timer for each task
  Timer command_timer;

  /// Pointer to our session data
  Session* session;

  /// Argument supplied to the task
  std::string argument;


 public:

  /// Virtual destructor
  virtual ~Task() {;};   

  /// Main public function
  virtual void run( Session* session, std::string argument ) {;};

  /// Factory function
  /** @param type command type */
  static Task* factory( std::string type );


  /// Check image
  void checkImage();

  /// Verify if a woolz object, throw if not
  void checkIfWoolz();

  /// Open if the object is Woolz
  void openIfWoolz();
};




/// OBJ commands
class OBJ : public Task {

 public:

  void run( Session* session, std::string argument );

  void iip();
  void iip_server();
  void max_size();
  void resolution_number();
  void colorspace( std::string arg );
  void tile_size();
  void horizontal_views();
  void vertical_views();
  void metadata( std::string field );

  // Woolz related handlers
  void wlz_section_size();
  void wlz_distance_range();
  void wlz_sectioning_angles();
  void wlz_coordinate_3d();

  void wlz_true_voxel_size();
  void wlz_grey_value();
  void wlz_volume();

};


/// JPEG Quality Command
class QLT : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// SDS Command
class SDS : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// Contrast Command
class CNT : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// CVT Width Command
class WID : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// CVT Height Command
class HEI : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// CVT Region Command
class RGN : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// FIF Command
class FIF : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// JPEG Tile Command
class JTL : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// JPEG Tile Sequence Command
class JTLS : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// Tile Command
class TIL : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// CVT Command
class CVT : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// ICC Profile Command
class ICC : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// Shading Command
class SHD : public Task {
 public:
  void run( Session* session, std::string argument );
};

/*

Extensions for Woolz

*/

/// WLZ Command
class WLZ : public Task {
 public:
  void run( Session* session, std::string argument );
};

// WLZ Sectioning commands
/// DST Woolz Command: sets sectioning distance
class DST : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// YAW Woolz Command: sets yaw angle
class YAW : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// PIT Woolz Command: sets pitch angle
class PIT : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// ROL Woolz Command: sets roll angle
class ROL : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// MOD Woolz Command: sets the viewing mode
class MOD : public Task {
 public:
  void run( Session* session, std::string argument );
};


/// FXP Woolz Command: sets the fixed point
class FXP : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// UPV Woolz Command: sets the up vector
class UPV : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// PRL Woolz Command: sets a 2D point (relative point)
class PRL : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// POI Woolz Command: sets a 3D point (absolute point)
class PAB : public Task {
 public:
  void run( Session* session, std::string argument );
};

/// POI Woolz Command: scale parameter
class SCL : public Task {
 public:
  void run( Session* session, std::string argument );
};


#endif
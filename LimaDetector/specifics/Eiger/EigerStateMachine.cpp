static const char *RcsId = "$Id $";
//+=============================================================================
//
// file :         EigerStateMachine.cpp
//
// description :  C++ source for the Eiger and its alowed 
//                methods for commands and attributes
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#include <tango.h>
#include <Eiger.h>
#include <EigerClass.h>

/*====================================================================
 *	This file contains the methods to allow commands and attributes
 * read or write execution.
 *
 * If you wand to add your own code, add it between 
 * the "End/Re-Start of Generated Code" comments.
 *
 * If you want, you can also add your own methods.
 *====================================================================
 */

namespace Eiger_ns
{

//=================================================
//		Attributes Allowed Methods
//=================================================

//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_countrateCorrection_allowed
// 
// description : 	Read/Write allowed for countrateCorrection attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_countrateCorrection_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_flatfieldCorrection_allowed
// 
// description : 	Read/Write allowed for flatfieldCorrection attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_flatfieldCorrection_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_pixelMask_allowed
// 
// description : 	Read/Write allowed for pixelMask attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_pixelMask_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_virtualPixelCorrection_allowed
// 
// description : 	Read/Write allowed for virtualPixelCorrection attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_virtualPixelCorrection_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_thresholdEnergy_allowed
// 
// description : 	Read/Write allowed for thresholdEnergy attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_thresholdEnergy_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_photonEnergy_allowed
// 
// description : 	Read/Write allowed for photonEnergy attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_photonEnergy_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_temperature_allowed
// 
// description : 	Read/Write allowed for temperature attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_temperature_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_humidity_allowed
// 
// description : 	Read/Write allowed for humidity attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_humidity_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_compression_allowed
// 
// description : 	Read/Write allowed for compression attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_compression_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		Eiger::is_fileNamePattern_allowed
// 
// description : 	Read/Write allowed for fileNamePattern attribute.
//
//-----------------------------------------------------------------------------
bool Eiger::is_fileNamePattern_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//=================================================
//		Commands Allowed Methods
//=================================================


}	// namespace Eiger_ns

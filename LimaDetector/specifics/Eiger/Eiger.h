//=============================================================================
//
// file :        Eiger.h
//
// description : Include for the Eiger class.
//
// project :	
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
// copyleft :    Synchrotron SOLEIL 
//               L'Orme des merisiers - Saint Aubin
//		 BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _Eiger_H
#define _Eiger_H

#include <tango.h>

//- YAT/YAT4TANGO
#include <yat4tango/PropertyHelper.h>

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

 //	Add your own constant definitions here.
 //-----------------------------------------------
#include "Factory.h"
#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include "EigerInterface.h"
#include "EigerCamera.h"

//using namespace lima::Eiger;
using namespace lima;
using namespace yat4tango;

namespace Eiger_ns
{

/**
 * Class Description:
 * 
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


class Eiger : public Tango::Device_4Impl
{
public :
	//	Add your own data members here
	//-----------------------------------------
	Tango::DevDouble attr_thresholdEnergy_read_cache;
	Tango::DevDouble attr_photonEnergy_read_cache;

	//	Here is the Start of the automatic code generation part
	//-------------------------------------------------------------	
/**
 *	@name attributes
 *	Attribute member data.
 */
//@{
		Tango::DevBoolean	*attr_countrateCorrection_read;
		Tango::DevBoolean	attr_countrateCorrection_write;
		Tango::DevBoolean	*attr_flatfieldCorrection_read;
		Tango::DevBoolean	attr_flatfieldCorrection_write;
		Tango::DevBoolean	*attr_pixelMask_read;
		Tango::DevBoolean	attr_pixelMask_write;
		Tango::DevBoolean	*attr_virtualPixelCorrection_read;
		Tango::DevBoolean	attr_virtualPixelCorrection_write;
		Tango::DevBoolean	*attr_efficiencyCorrection_read;
		Tango::DevBoolean	attr_efficiencyCorrection_write;
		Tango::DevDouble	*attr_thresholdEnergy_read;
		Tango::DevDouble	attr_thresholdEnergy_write;
		Tango::DevDouble	*attr_photonEnergy_read;
		Tango::DevDouble	attr_photonEnergy_write;
		Tango::DevDouble	*attr_temperature_read;
		Tango::DevDouble	*attr_humidity_read;
		Tango::DevBoolean	*attr_compression_read;
		Tango::DevBoolean	attr_compression_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
/**
 *	Eiger server IP address (ex: 192.168.0.1)
 */
	string	detectorIP;
/**
 *	Path where the Eiger lima plugin will download the file acquired during the last
 *	acquisition. (ex: /tmp )
 */
	string	targetPath;
/**
 *	Stores the value of countrateCorrection
 */
	Tango::DevBoolean	memorizedCountrateCorrection;
/**
 *	Stores the value of flatfieldCorrection
 */
	Tango::DevBoolean	memorizedFlatfieldCorrection;
/**
 *	Stores the value of pixelMask
 */
	Tango::DevBoolean	memorizedPixelMask;
/**
 *	Stores the value of virtualPixelCorrection
 */
	Tango::DevBoolean	memorizedVirtualPixelCorrection;
/**
 *	Stores the value of efficiencyCorrection
 */
	Tango::DevBoolean	memorizedEfficiencyCorrection;
/**
 *	Stores the value of thresholdEnergy
 */
	Tango::DevDouble	memorizedThresholdEnergy;
/**
 *	Stores the value of photonEnergy
 */
	Tango::DevDouble	memorizedPhotonEnergy;
/**
 *	Stores the value of compression
 */
	Tango::DevBoolean	memorizedCompression;
/**
 *	Enable/Disable the HDF5 Reader, in order to read images from HDF5 file and publish them in image attribute & Nexus files
 */
	Tango::DevBoolean	useReader;
//@}

/**
 *	@name Device properties
 *	Device property member data.
 */
//@{
//@}

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Eiger(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Eiger(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
	Eiger(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */	
	~Eiger() {delete_device();};
/**
 *	will be called at device destruction or at init command.
 */
	void delete_device();
//@}

	
/**@name Miscellaneous methods */
//@{
/**
 *	Initialize the device
 */
	virtual void init_device();
/**
 *	Always executed method before execution command method.
 */
	virtual void always_executed_hook();

//@}

/**
 * @name Eiger methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for countrateCorrection acquisition result.
 */
	virtual void read_countrateCorrection(Tango::Attribute &attr);
/**
 *	Write countrateCorrection attribute values to hardware.
 */
	virtual void write_countrateCorrection(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for flatfieldCorrection acquisition result.
 */
	virtual void read_flatfieldCorrection(Tango::Attribute &attr);
/**
 *	Write flatfieldCorrection attribute values to hardware.
 */
	virtual void write_flatfieldCorrection(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for pixelMask acquisition result.
 */
	virtual void read_pixelMask(Tango::Attribute &attr);
/**
 *	Write pixelMask attribute values to hardware.
 */
	virtual void write_pixelMask(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for virtualPixelCorrection acquisition result.
 */
	virtual void read_virtualPixelCorrection(Tango::Attribute &attr);
/**
 *	Write virtualPixelCorrection attribute values to hardware.
 */
	virtual void write_virtualPixelCorrection(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for efficiencyCorrection acquisition result.
 */
	virtual void read_efficiencyCorrection(Tango::Attribute &attr);
/**
 *	Write efficiencyCorrection attribute values to hardware.
 */
	virtual void write_efficiencyCorrection(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for thresholdEnergy acquisition result.
 */
	virtual void read_thresholdEnergy(Tango::Attribute &attr);
/**
 *	Write thresholdEnergy attribute values to hardware.
 */
	virtual void write_thresholdEnergy(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for photonEnergy acquisition result.
 */
	virtual void read_photonEnergy(Tango::Attribute &attr);
/**
 *	Write photonEnergy attribute values to hardware.
 */
	virtual void write_photonEnergy(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for temperature acquisition result.
 */
	virtual void read_temperature(Tango::Attribute &attr);
/**
 *	Extract real attribute values for humidity acquisition result.
 */
	virtual void read_humidity(Tango::Attribute &attr);
/**
 *	Extract real attribute values for compression acquisition result.
 */
	virtual void read_compression(Tango::Attribute &attr);
/**
 *	Write compression attribute values to hardware.
 */
	virtual void write_compression(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for countrateCorrection attribute.
 */
	virtual bool is_countrateCorrection_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for flatfieldCorrection attribute.
 */
	virtual bool is_flatfieldCorrection_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for pixelMask attribute.
 */
	virtual bool is_pixelMask_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for virtualPixelCorrection attribute.
 */
	virtual bool is_virtualPixelCorrection_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for efficiencyCorrection attribute.
 */
	virtual bool is_efficiencyCorrection_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdEnergy attribute.
 */
	virtual bool is_thresholdEnergy_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for photonEnergy attribute.
 */
	virtual bool is_photonEnergy_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for temperature attribute.
 */
	virtual bool is_temperature_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for humidity attribute.
 */
	virtual bool is_humidity_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for compression attribute.
 */
	virtual bool is_compression_allowed(Tango::AttReqType type);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

	//	Here is the end of the automatic code generation part
	//-------------------------------------------------------------	



protected :	
	//	Add your own data members here
	//-----------------------------------------
	bool                  m_is_device_initialized;
   stringstream          m_status_message;

   //lima OBJECTS
   lima::Eiger::Interface* m_hw;
   CtControl*              m_ct;
   lima::Eiger::Camera*    m_camera;		
};

}	// namespace_ns

#endif	// _Eiger_H

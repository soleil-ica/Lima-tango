/*----- PROTECTED REGION ID(Merlin.h) ENABLED START -----*/
//=============================================================================
//
// file :        Merlin.h
//
// description : Include file for the Merlin class
//
// project :     Merlin: A Medipix3RX Quad readout
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef Merlin_H
#define Merlin_H

#include <tango.h>
#include "HwInterface.h"
#include "CtControl.h"
#include "MerlinCamera.h"
#include "MerlinInterface.h"
#include <Exceptions.h>
#include "Factory.h"

using namespace lima;

/*----- PROTECTED REGION END -----*/	//	Merlin.h

/**
 *  Merlin class description:
 *    
 */

namespace Merlin_ns
{
/*----- PROTECTED REGION ID(Merlin::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	Merlin::Additional Class Declarations

class Merlin : public Tango::Device_4Impl
{

/*----- PROTECTED REGION ID(Merlin::Data Members) ENABLED START -----*/

//	Add your own data members
    //state & status stuff
	bool m_is_device_initialized;
	std::stringstream m_status_message;

	//LIMA objects
	lima::Merlin::Interface	*m_hw;
	lima::CtControl*		 m_ct;
    lima::Merlin::Camera*    m_camera;

/*----- PROTECTED REGION END -----*/	//	Merlin::Data Members

//	Device property data members
public:
	//	HostName:	The name of the Merlin PC
	string	hostName;
	//	Port:	The Merlin command port
	Tango::DevLong	port;
	//	DataPort:	The Merlin data port
	Tango::DevLong	dataPort;
	//	Chips:	Nos of Medipix chips
	Tango::DevLong	chips;
	//	ImageWidth:	The width of Merlin detector head in pixels
	Tango::DevLong	imageWidth;
	//	ImageHeight:	The height of the Merlin detector head in Pixels
	Tango::DevLong	imageHeight;
	//	Simulate:	Simulate the Merlin commands.
	Tango::DevBoolean	simulate;

//	Attribute data members
public:
	Tango::DevFloat	*attr_softwareVersion_read;
	Tango::DevBoolean	*attr_chargeSumming_read;
	Tango::DevBoolean	*attr_colourMode_read;
	Tango::DevBoolean	*attr_continuousRW_read;
	Tango::DevLong	*attr_counter_read;
	Tango::DevLong	*attr_gain_read;
	Tango::DevFloat	*attr_operatingEnergy_read;
	Tango::DevFloat	*attr_temperature_read;
	Tango::DevFloat	*attr_threshold0_read;
	Tango::DevFloat	*attr_threshold1_read;
	Tango::DevFloat	*attr_threshold2_read;
	Tango::DevFloat	*attr_threshold3_read;
	Tango::DevFloat	*attr_threshold4_read;
	Tango::DevFloat	*attr_threshold5_read;
	Tango::DevFloat	*attr_threshold6_read;
	Tango::DevFloat	*attr_threshold7_read;
	Tango::DevLong	*attr_triggerStartType_read;
	Tango::DevLong	*attr_triggerStopType_read;
	Tango::DevLong	*attr_triggerOutTTL_read;
	Tango::DevLong	*attr_triggerOutLVDS_read;
	Tango::DevLong	*attr_triggerOutTTLInvert_read;
	Tango::DevLong	*attr_triggerOutLVDSInvert_read;
	Tango::DevLong64	*attr_triggerOutTTLDelay_read;
	Tango::DevLong64	*attr_triggerOutLVDSDelay_read;
	Tango::DevBoolean	*attr_triggerUseDelay_read;
	Tango::DevLong	*attr_thScanNum_read;
	Tango::DevFloat	*attr_thStart_read;
	Tango::DevFloat	*attr_thStop_read;
	Tango::DevFloat	*attr_thStep_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Merlin(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Merlin(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	Merlin(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */	
	~Merlin() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : Merlin::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : Merlin::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute softwareVersion related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_softwareVersion(Tango::Attribute &attr);
	virtual bool is_softwareVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute chargeSumming related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_chargeSumming(Tango::Attribute &attr);
	virtual void write_chargeSumming(Tango::WAttribute &attr);
	virtual bool is_chargeSumming_allowed(Tango::AttReqType type);
/**
 *	Attribute colourMode related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_colourMode(Tango::Attribute &attr);
	virtual void write_colourMode(Tango::WAttribute &attr);
	virtual bool is_colourMode_allowed(Tango::AttReqType type);
/**
 *	Attribute continuousRW related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_continuousRW(Tango::Attribute &attr);
	virtual void write_continuousRW(Tango::WAttribute &attr);
	virtual bool is_continuousRW_allowed(Tango::AttReqType type);
/**
 *	Attribute counter related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_counter(Tango::Attribute &attr);
	virtual void write_counter(Tango::WAttribute &attr);
	virtual bool is_counter_allowed(Tango::AttReqType type);
/**
 *	Attribute gain related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_gain(Tango::Attribute &attr);
	virtual void write_gain(Tango::WAttribute &attr);
	virtual bool is_gain_allowed(Tango::AttReqType type);
/**
 *	Attribute operatingEnergy related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_operatingEnergy(Tango::Attribute &attr);
	virtual void write_operatingEnergy(Tango::WAttribute &attr);
	virtual bool is_operatingEnergy_allowed(Tango::AttReqType type);
/**
 *	Attribute temperature related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_temperature(Tango::Attribute &attr);
	virtual bool is_temperature_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold0 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold0(Tango::Attribute &attr);
	virtual void write_threshold0(Tango::WAttribute &attr);
	virtual bool is_threshold0_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold1 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold1(Tango::Attribute &attr);
	virtual void write_threshold1(Tango::WAttribute &attr);
	virtual bool is_threshold1_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold2 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold2(Tango::Attribute &attr);
	virtual void write_threshold2(Tango::WAttribute &attr);
	virtual bool is_threshold2_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold3 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold3(Tango::Attribute &attr);
	virtual void write_threshold3(Tango::WAttribute &attr);
	virtual bool is_threshold3_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold4 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold4(Tango::Attribute &attr);
	virtual void write_threshold4(Tango::WAttribute &attr);
	virtual bool is_threshold4_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold5 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold5(Tango::Attribute &attr);
	virtual void write_threshold5(Tango::WAttribute &attr);
	virtual bool is_threshold5_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold6 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold6(Tango::Attribute &attr);
	virtual void write_threshold6(Tango::WAttribute &attr);
	virtual bool is_threshold6_allowed(Tango::AttReqType type);
/**
 *	Attribute threshold7 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_threshold7(Tango::Attribute &attr);
	virtual void write_threshold7(Tango::WAttribute &attr);
	virtual bool is_threshold7_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerStartType related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_triggerStartType(Tango::Attribute &attr);
	virtual void write_triggerStartType(Tango::WAttribute &attr);
	virtual bool is_triggerStartType_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerStopType related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_triggerStopType(Tango::Attribute &attr);
	virtual void write_triggerStopType(Tango::WAttribute &attr);
	virtual bool is_triggerStopType_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerOutTTL related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_triggerOutTTL(Tango::Attribute &attr);
	virtual void write_triggerOutTTL(Tango::WAttribute &attr);
	virtual bool is_triggerOutTTL_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerOutLVDS related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_triggerOutLVDS(Tango::Attribute &attr);
	virtual void write_triggerOutLVDS(Tango::WAttribute &attr);
	virtual bool is_triggerOutLVDS_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerOutTTLInvert related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_triggerOutTTLInvert(Tango::Attribute &attr);
	virtual void write_triggerOutTTLInvert(Tango::WAttribute &attr);
	virtual bool is_triggerOutTTLInvert_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerOutLVDSInvert related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_triggerOutLVDSInvert(Tango::Attribute &attr);
	virtual void write_triggerOutLVDSInvert(Tango::WAttribute &attr);
	virtual bool is_triggerOutLVDSInvert_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerOutTTLDelay related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong64
 *	Attr type:	Scalar
 */
	virtual void read_triggerOutTTLDelay(Tango::Attribute &attr);
	virtual void write_triggerOutTTLDelay(Tango::WAttribute &attr);
	virtual bool is_triggerOutTTLDelay_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerOutLVDSDelay related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong64
 *	Attr type:	Scalar
 */
	virtual void read_triggerOutLVDSDelay(Tango::Attribute &attr);
	virtual void write_triggerOutLVDSDelay(Tango::WAttribute &attr);
	virtual bool is_triggerOutLVDSDelay_allowed(Tango::AttReqType type);
/**
 *	Attribute triggerUseDelay related methods
 *	Description: 
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_triggerUseDelay(Tango::Attribute &attr);
	virtual void write_triggerUseDelay(Tango::WAttribute &attr);
	virtual bool is_triggerUseDelay_allowed(Tango::AttReqType type);
/**
 *	Attribute thScanNum related methods
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_thScanNum(Tango::Attribute &attr);
	virtual void write_thScanNum(Tango::WAttribute &attr);
	virtual bool is_thScanNum_allowed(Tango::AttReqType type);
/**
 *	Attribute thStart related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_thStart(Tango::Attribute &attr);
	virtual void write_thStart(Tango::WAttribute &attr);
	virtual bool is_thStart_allowed(Tango::AttReqType type);
/**
 *	Attribute thStop related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_thStop(Tango::Attribute &attr);
	virtual void write_thStop(Tango::WAttribute &attr);
	virtual bool is_thStop_allowed(Tango::AttReqType type);
/**
 *	Attribute thStep related methods
 *	Description: 
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_thStep(Tango::Attribute &attr);
	virtual void write_thStep(Tango::WAttribute &attr);
	virtual bool is_thStep_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : Merlin::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();



//	Command related methods
public:
	/**
	 *	Command DevState related method
	 *	Description: This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
	 *
	 *	@returns 
	 */
	virtual Tango::DevState dev_state();
	virtual bool is_DevState_allowed(const CORBA::Any &any);
	/**
	 *	Command SoftTrigger related method
	 *	Description: 
	 *
	 */
	virtual void soft_trigger();
	virtual bool is_SoftTrigger_allowed(const CORBA::Any &any);
	/**
	 *	Command Abort related method
	 *	Description: 
	 *
	 */
	virtual void abort();
	virtual bool is_Abort_allowed(const CORBA::Any &any);
	/**
	 *	Command THScan related method
	 *	Description: 
	 *
	 */
	virtual void thscan();
	virtual bool is_THScan_allowed(const CORBA::Any &any);
	/**
	 *	Command ResetHW related method
	 *	Description: 
	 *
	 */
	virtual void reset_hw();
	virtual bool is_ResetHW_allowed(const CORBA::Any &any);


/*----- PROTECTED REGION ID(Merlin::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
    int find_index_from_property_name(Tango::DbData& dev_prop, string property_name);
    template <class T>
    void create_property_if_empty(Tango::DbData& dev_prop,T value, string property_name);

/*----- PROTECTED REGION END -----*/	//	Merlin::Additional Method prototypes
};

/*----- PROTECTED REGION ID(Merlin::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	Merlin::Additional Classes Definitions

}	//	End of namespace

#endif   //	Merlin_H
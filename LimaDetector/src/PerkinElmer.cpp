static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         PerkinElmer.cpp
//
// description :  C++ source for the PerkinElmer and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                PerkinElmer are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
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
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name         |  Method name
//	----------------------------------------
//  State                |  dev_state()
//  Status               |  dev_status()
//  StartAcqOffsetImage  |  start_acq_offset_image()
//  StartAcqGainImage    |  start_acq_gain_image()
//
//===================================================================

#ifdef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif
#include "PerkinElmer.h"
#include <PerkinElmerClass.h>

#ifndef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif

namespace PerkinElmer_ns
{

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::PerkinElmer(string &s)
// 
// description : 	constructor for simulated PerkinElmer
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
PerkinElmer::PerkinElmer(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

PerkinElmer::PerkinElmer(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

PerkinElmer::PerkinElmer(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void PerkinElmer::delete_device()
{
	//	Delete device allocated objects
    DELETE_DEVSTRING_ATTRIBUTE(attr_correctionMode_read);	
    DELETE_SCALAR_ATTRIBUTE(attr_keepFirstImage_read);
    DELETE_SCALAR_ATTRIBUTE(attr_gain_read);

    //!!!! ONLY LimaDetector device can do this !!!!
    //if(m_ct!=0)
    //{
    //    ControlFactory::instance().reset("PrincetonCCD");
    //    m_ct = 0;
    //}
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void PerkinElmer::init_device()
{
	INFO_STREAM << "PerkinElmer::PerkinElmer() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------

    CREATE_DEVSTRING_ATTRIBUTE(attr_correctionMode_read,MAX_ATTRIBUTE_STRING_LENGTH);	
    CREATE_SCALAR_ATTRIBUTE(attr_keepFirstImage_read);
    CREATE_SCALAR_ATTRIBUTE(attr_gain_read);

    m_is_device_initialized = false;
    set_state(Tango::INIT);
    m_status_message.str("");

    try
    {
        //- get the main object used to pilot the lima framework
        //in fact LimaDetector is create the singleton control objet
        //so this call, will only return existing object, no need to give it the ip !!
        m_ct = ControlFactory::instance().get_control("PerkinElmer");

        //- get interface to specific camera
		m_hw = dynamic_cast<lima::PerkinElmer::Interface*>(m_ct->hwInterface());
        if(m_hw==0)
        {
            INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"PerkinElmer"<<") !"<< endl;
            m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"PerkinElmer"<<") !"<< endl;
            m_is_device_initialized = false;
            set_state(Tango::FAULT);
            return;
        }
    }
    catch(Exception& e)
    {
        INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
        m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
        m_is_device_initialized = false;
        set_state(Tango::FAULT);
        return;
    }
    catch(...)
    {
        INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
        m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
		
	m_is_device_initialized = true;		
    set_state(Tango::STANDBY);
    this->dev_state();
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void PerkinElmer::always_executed_hook()
{
    try
	{
	    m_status_message.str("");
		//- get the singleton control objet used to pilot the lima framework
		m_ct = ControlFactory::instance().get_control("PerkinElmer");
		//- get interface to specific detector
		if(m_ct!=0)
			m_hw = dynamic_cast<lima::PerkinElmer::Interface*>(m_ct->hwInterface());
		this->dev_state();

	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	catch(...)
	{
		ERROR_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
		m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	
}
//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void PerkinElmer::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "PerkinElmer::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
	//	Add your own code here
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::read_correctionMode
// 
// description : 	Extract real attribute values for correctionMode acquisition result.
//
//-----------------------------------------------------------------------------
void PerkinElmer::read_correctionMode(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PerkinElmer::read_correctionMode(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        lima::PerkinElmer::Interface::CorrMode curr_mode;
        curr_mode = m_hw->getCorrectionMode();
        switch(curr_mode)
        {
            case lima::PerkinElmer::Interface::No :
                *attr_correctionMode_read = "No";
                break;
            case lima::PerkinElmer::Interface::OffsetOnly :
                *attr_correctionMode_read = "OffsetOnly";
                break;
            case lima::PerkinElmer::Interface::OffsetAndGain :
                *attr_correctionMode_read = "OffsetAndGain";
                break;

        }
        attr.set_value(attr_correctionMode_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PerkinElmer::read_correctionMode"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::read_correctionMode"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::write_correctionMode
// 
// description : 	Write correctionMode attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PerkinElmer::write_correctionMode(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PerkinElmer::write_correctionMode(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_correctionMode_write);
        lima::PerkinElmer::Interface::CorrMode curr_mode;

        if (string(attr_correctionMode_write).compare("No"))
            curr_mode = lima::PerkinElmer::Interface::No;
        if (string(attr_correctionMode_write).compare("OffsetOnly"))
            curr_mode = lima::PerkinElmer::Interface::OffsetOnly;
        if (string(attr_correctionMode_write).compare("OffsetAndGain"))
            curr_mode = lima::PerkinElmer::Interface::OffsetAndGain;

        m_hw->setCorrectionMode(curr_mode);  
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PerkinElmer::write_correctionMode"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::write_correctionMode"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::read_keepFirstImage
// 
// description : 	Extract real attribute values for keepFirstImage acquisition result.
//
//-----------------------------------------------------------------------------
void PerkinElmer::read_keepFirstImage(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PerkinElmer::read_keepFirstImage(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        *attr_keepFirstImage_read = m_hw->getKeepFirstImage();
        attr.set_value(attr_keepFirstImage_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PerkinElmer::read_keepFirstImage"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::read_keepFirstImage"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::write_keepFirstImage
// 
// description : 	Write keepFirstImage attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PerkinElmer::write_keepFirstImage(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PerkinElmer::write_keepFirstImage(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_keepFirstImage_write);
        m_hw->setKeepFirstImage(attr_keepFirstImage_write);  
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PerkinElmer::write_keepFirstImage"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::write_keepFirstImage"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::read_gain
// 
// description : 	Extract real attribute values for gain acquisition result.
//
//-----------------------------------------------------------------------------
void PerkinElmer::read_gain(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PerkinElmer::read_gain(Tango::Attribute &attr) entering... "<< endl;

    try
    {
        *attr_gain_read = m_hw->getGain();
        attr.set_value(attr_gain_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PerkinElmer::read_gain"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::read_gain"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PerkinElmer::write_gain
// 
// description : 	Write gain attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PerkinElmer::write_gain(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PerkinElmer::write_gain(Tango::WAttribute &attr) entering... "<< endl;

    try
    {
        attr.get_write_value(attr_gain_write);
        m_hw->setGain(attr_gain_write);  
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PerkinElmer::write_gain"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::write_gain"));
    }
}



//+------------------------------------------------------------------
/**
 *	method:	PerkinElmer::start_acq_offset_image
 *
 *	description:	method to execute "StartAcqOffsetImage"
 *	startAcqOffsetImage: ?
 *
 * @param	argin	nb frames, integration time
 *
 */
//+------------------------------------------------------------------
void PerkinElmer::start_acq_offset_image(const Tango::DevVarDoubleArray *argin)
{
	DEBUG_STREAM << "PerkinElmer::start_acq_offset_image(): entering... !" << endl;

	//	Add your own code to control device here

    try
    {
        if(argin->length()!= 2)
        {
            //- throw exception
            Tango::Except::throw_exception( (const char*) ("CONFIGURATION_ERROR"),
                                            (const char*) ("StartAcqOffsetImage need 2 parameters: nb_frames and integration_time\n"),
                                            (const char*) ("PerkinElmer::start_acq_offset_image"));
        }
	    m_hw->startAcqOffsetImage((*argin)[0],(*argin)[1]);
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::start_acq_offset_image"));
    }
}

//+------------------------------------------------------------------
/**
 *	method:	PerkinElmer::start_acq_gain_image
 *
 *	description:	method to execute "StartAcqGainImage"
 *	startAcqGainImage: ?
 *
 * @param	argin	nb frames, integration time
 *
 */
//+------------------------------------------------------------------
void PerkinElmer::start_acq_gain_image(const Tango::DevVarDoubleArray *argin)
{
	DEBUG_STREAM << "PerkinElmer::start_acq_gain_image(): entering... !" << endl;

	//	Add your own code to control device here

    try
    {
        if(argin->length()!= 2)
        {
            //- throw exception
            Tango::Except::throw_exception( (const char*) ("CONFIGURATION_ERROR"),
                                            (const char*) ("StartAcqOffsetImage need 2 parameters: nb_frames and integration_time\n"),
                                            (const char*) ("PerkinElmer::start_acq_gain_image"));
        }
	    m_hw->startAcqGainImage((*argin)[0],(*argin)[1]);
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PerkinElmer::start_acq_gain_image"));
    }

}

}	//	namespace

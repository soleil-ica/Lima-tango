static const char *ClassId    = "$Id:  $";
static const char *TagName    = "$Name:  $";
static const char *CvsPath    = "$Source:  $";
static const char *SvnPath    = "$HeadURL: $";
static const char *HttpServer = "http://www.esrf.fr/computing/cs/tango/tango_doc/ds_doc/";
//+=============================================================================
//
// file :        PrincetonCCDClass.cpp
//
// description : C++ source for the PrincetonCCDClass. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the PrincetonCCD once per process.
//
// project :     TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
//
// $Log:  $
//
// copyleft :   European Synchrotron Radiation Facility
//              BP 220, Grenoble 38043
//              FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#ifdef WIN32
#include "tango.h"
#endif
#include <PrincetonCCD.h>
#include <PrincetonCCDClass.h>

#ifndef WIN32
#include "tango.h"
#endif

//+----------------------------------------------------------------------------
/**
 *	Create PrincetonCCDClass singleton and return it in a C function for Python usage
 */
//+----------------------------------------------------------------------------
extern "C" {
#ifdef WIN32

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_PrincetonCCD_class(const char *name) {
		return PrincetonCCD_ns::PrincetonCCDClass::init(name);
	}
}


namespace PrincetonCCD_ns
{
//+----------------------------------------------------------------------------
//
// method : 		SetADCModeCmd::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be executed
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *SetADCModeCmd::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "SetADCModeCmd::execute(): arrived" << endl;

	Tango::DevUShort	argin;
	extract(in_any, argin);

	((static_cast<PrincetonCCD *>(device))->set_adcmode(argin));
	return new CORBA::Any();
}





//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
PrincetonCCDClass *PrincetonCCDClass::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::PrincetonCCDClass(string &s)
// 
// description : 	constructor for the PrincetonCCDClass
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
PrincetonCCDClass::PrincetonCCDClass(string &s):DeviceClass(s)
{

	cout2 << "Entering PrincetonCCDClass constructor" << endl;
	set_default_property();
	get_class_property();
	write_class_property();
	
	cout2 << "Leaving PrincetonCCDClass constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::~PrincetonCCDClass()
// 
// description : 	destructor for the PrincetonCCDClass
//
//-----------------------------------------------------------------------------
PrincetonCCDClass::~PrincetonCCDClass()
{
	_instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
PrincetonCCDClass *PrincetonCCDClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new PrincetonCCDClass(s);
		}
		catch (bad_alloc)
		{
			throw;
		}		
	}		
	return _instance;
}

PrincetonCCDClass *PrincetonCCDClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void PrincetonCCDClass::command_factory()
{
	command_list.push_back(new SetADCModeCmd("SetADCMode",
		Tango::DEV_USHORT, Tango::DEV_VOID,
		"",
		"",
		Tango::OPERATOR));

	//	add polling if any
	for (unsigned int i=0 ; i<command_list.size(); i++)
	{
	}
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum PrincetonCCDClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum PrincetonCCDClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum PrincetonCCDClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void PrincetonCCDClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

	//	Create all devices.(Automatic code generation)
	//-------------------------------------------------------------
	for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
						
		// Create devices and add it into the device list
		//----------------------------------------------------
		device_list.push_back(new PrincetonCCD(this, (*devlist_ptr)[i]));							 

		// Export device to the outside world
		// Check before if database used.
		//---------------------------------------------
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(device_list.back());
		else
			export_device(device_list.back(), (*devlist_ptr)[i]);
	}
	//	End of Automatic code generation
	//-------------------------------------------------------------

}
//+----------------------------------------------------------------------------
//	Method: PrincetonCCDClass::attribute_factory(vector<Tango::Attr *> &att_list)
//-----------------------------------------------------------------------------
void PrincetonCCDClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	//	Attribute : internalAcquisitionMode
	internalAcquisitionModeAttrib	*internal_acquisition_mode = new internalAcquisitionModeAttrib();
	Tango::UserDefaultAttrProp	internal_acquisition_mode_prop;
	internal_acquisition_mode_prop.set_description("Available Internal Acquisition Modes are :<br>\nSTANDARD<br>\nFOCUS<br>");
	internal_acquisition_mode->set_default_properties(internal_acquisition_mode_prop);
	att_list.push_back(internal_acquisition_mode);

	//	Attribute : shutterMode
	shutterModeAttrib	*shutter_mode = new shutterModeAttrib();
	Tango::UserDefaultAttrProp	shutter_mode_prop;
	shutter_mode_prop.set_description("Available Shutter Modes are :<br>\nOPEN_NEVER<br>\nOPEN_PRE_EXPOSURE<br>\nOPEN_NO_CHANGE<br>");
	shutter_mode->set_default_properties(shutter_mode_prop);
	att_list.push_back(shutter_mode);

	//	Attribute : temperature
	temperatureAttrib	*temperature = new temperatureAttrib();
	Tango::UserDefaultAttrProp	temperature_prop;
	temperature_prop.set_unit("?C");
	temperature_prop.set_format("%6.2f");
	temperature->set_default_properties(temperature_prop);
	att_list.push_back(temperature);

	//	Attribute : temperatureTarget
	temperatureTargetAttrib	*temperature_target = new temperatureTargetAttrib();
	Tango::UserDefaultAttrProp	temperature_target_prop;
	temperature_target_prop.set_unit("?C");
	temperature_target_prop.set_format("%6.2f");
	temperature_target->set_default_properties(temperature_target_prop);
	att_list.push_back(temperature_target);

	//	Attribute : gain
	gainAttrib	*gain = new gainAttrib();
	Tango::UserDefaultAttrProp	gain_prop;
	gain_prop.set_description("Define the currect gain.\n");
	gain->set_default_properties(gain_prop);
	att_list.push_back(gain);

	//	Attribute : currentRate
	currentRateAttrib	*current_rate = new currentRateAttrib();
	Tango::UserDefaultAttrProp	current_rate_prop;
	current_rate_prop.set_description("Display the current ADC frequency in Mhz");
	current_rate->set_default_properties(current_rate_prop);
	att_list.push_back(current_rate);

	//	End of Automatic code generation
	//-------------------------------------------------------------
}
















//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void PrincetonCCDClass::get_class_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read class properties from database.(Automatic code generation)
	//------------------------------------------------------------------

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_class()->get_property(cl_prop);
	Tango::DbDatum	def_prop;
	int	i = -1;


	//	End of Automatic code generation
	//------------------------------------------------------------------

}

//+----------------------------------------------------------------------------
//
// method : 	PrincetonCCDClass::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void PrincetonCCDClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;

	vector<string>	vect_data;
	//	Set Default Class Properties
	//	Set Default Device Properties
	prop_name = "DetectorNum";
	prop_desc = "Detector Number.";
	prop_def  = "";
	vect_data.clear();
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "TemperatureTargetAtInit";
	prop_desc = "Define which Temperature must be used at init device<br>\n- DEFAULT : use DefaultTemperatureTarget value<br>\n- MEMORIZED : use MemorizedTemperatureTarget value<br>";
	prop_def  = "DEFAULT";
	vect_data.clear();
	vect_data.push_back("DEFAULT");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "DefaultTemperatureTarget";
	prop_desc = "Define the Temperature Target of the Cooler at Init device if TemperatureAtInit = DEFAULT. (in Celsius)<br>";
	prop_def  = "-110";
	vect_data.clear();
	vect_data.push_back("-110");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedInternalAcquisitionMode";
	prop_desc = "Memorize/Define the internalAcquisitionMode attribute at Init device<br>\nAvailables values :<br>\n- STANDARD<br>\n- FOCUS<br>";
	prop_def  = "STANDARD";
	vect_data.clear();
	vect_data.push_back("STANDARD");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedShutterMode";
	prop_desc = "Memorize/Define the SHUTTERMode attribute at Init device<br>\nAvailables values :<br>\n- OPEN_NEVER<br>\n- OPEN_PRE_EXPOSURE<br>\n- OPEN_NO_CHANGE<br>";
	prop_def  = "OPEN_NO_CHANGE";
	vect_data.clear();
	vect_data.push_back("OPEN_NO_CHANGE");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedTemperatureTarget";
	prop_desc = "Define the Temperature Target of the Cooler at Init device if TemperatureAtInit = MEMORIZED. (in Celsius)<br>";
	prop_def  = "-110";
	vect_data.clear();
	vect_data.push_back("-110");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedGain";
	prop_desc = "";
	prop_def  = "1";
	vect_data.clear();
	vect_data.push_back("1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedADCMode";
	prop_desc = "";
	prop_def  = "1";
	vect_data.clear();
	vect_data.push_back("1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

}
//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCDClass::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void PrincetonCCDClass::write_class_property()
{
	//	First time, check if database used
	//--------------------------------------------
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("Device specific for Princeton CCD detector");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("  ");
	description << str_desc;
	data.push_back(description);
		
	//	put cvs or svn location
	string	filename(classname);
	filename += "Class.cpp";
	
	// Create a string with the class ID to
	// get the string into the binary
	string	class_id(ClassId);
	
	// check for cvs information
	string	src_path(CvsPath);
	start = src_path.find("/");
	if (start!=string::npos)
	{
		end   = src_path.find(filename);
		if (end>start)
		{
			string	strloc = src_path.substr(start, end-start);
			//	Check if specific repository
			start = strloc.find("/cvsroot/");
			if (start!=string::npos && start>0)
			{
				string	repository = strloc.substr(0, start);
				if (repository.find("/segfs/")!=string::npos)
					strloc = "ESRF:" + strloc.substr(start, strloc.length()-start);
			}
			Tango::DbDatum	cvs_loc("cvs_location");
			cvs_loc << strloc;
			data.push_back(cvs_loc);
		}
	}
	// check for svn information
	else
	{
		string	src_path(SvnPath);
		start = src_path.find("://");
		if (start!=string::npos)
		{
			end = src_path.find(filename);
			if (end>start)
			{
				header = "$HeadURL: ";
				start = header.length();
				string	strloc = src_path.substr(start, (end-start));
				
				Tango::DbDatum	svn_loc("svn_location");
				svn_loc << strloc;
				data.push_back(svn_loc);
			}
		}
	}

	//	Get CVS or SVN revision tag
	
	// CVS tag
	string	tagname(TagName);
	header = "$Name: ";
	start = header.length();
	string	endstr(" $");
	
	end   = tagname.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strtag = tagname.substr(start, end-start);
		Tango::DbDatum	cvs_tag("cvs_tag");
		cvs_tag << strtag;
		data.push_back(cvs_tag);
	}
	
	// SVN tag
	string	svnpath(SvnPath);
	header = "$HeadURL: ";
	start = header.length();
	
	end   = svnpath.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strloc = svnpath.substr(start, end-start);
		
		string tagstr ("/tags/");
		start = strloc.find(tagstr);
		if ( start!=string::npos )
		{
			start = start + tagstr.length();
			end   = strloc.find(filename);
			string	strtag = strloc.substr(start, end-start-1);
			
			Tango::DbDatum	svn_tag("svn_tag");
			svn_tag << strtag;
			data.push_back(svn_tag);
		}
	}

	//	Get URL location
	string	httpServ(HttpServer);
	if (httpServ.length()>0)
	{
		Tango::DbDatum	db_doc_url("doc_url");
		db_doc_url << httpServ;
		data.push_back(db_doc_url);
	}

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("Device_4Impl");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	//--------------------------------------------
	get_db_class()->put_property(data);
}

}	// namespace
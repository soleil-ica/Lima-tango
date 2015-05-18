//+=============================================================================
//
// file :         Factory.cpp
//
// description : This module handles the creation of the main lima object (CtControl) for each type of camera
//
// copyleft :    Synchrotron SOLEIL
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
#include <Factory.h>

#include <iostream>

bool ControlFactory::m_is_created = false;



//-----------------------------------------------------------------------------------------
void ControlFactory::initialize()
{
    m_control = 0;
    m_camera	 = 0;
    m_interface = 0;

    m_server_name = "none";
    m_device_name_specific = "none";
	
#ifdef LAYOUT_ENABLED    
    m_device_name_layout = "none";
#endif
	
#ifdef ROICOUNTERS_ENABLED    	
	m_device_name_roicounters = "none";	
#endif	 
	
    m_status.str("");
    m_state = Tango::INIT;
}

//-----------------------------------------------------------------------------------------
yat::Mutex& ControlFactory::get_global_mutex()
{
    return object_control_lock;
}

//-----------------------------------------------------------------------------------------
CtControl* ControlFactory::create_control(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(object_control_lock);
    try
    {
        //get the tango device/instance
        if (!ControlFactory::m_is_created)
        {
            initialize();
            
            {
                std::string specific = detector_type;
                Tango::DbDatum db_datum;
                m_server_name = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name, specific);
                db_datum >> m_device_name_specific;
            }

#ifdef LAYOUT_ENABLED
            {
                std::string layout = "Layout";
                Tango::DbDatum db_datum;
                m_server_name = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name, layout);
                db_datum >> m_device_name_layout;
            }     
#endif         
			
#ifdef ROICOUNTERS_ENABLED
            {
                std::string roicounters = "RoiCounters";
                Tango::DbDatum db_datum;
                m_server_name = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name, roicounters);
                db_datum >> m_device_name_roicounters;
            }     
#endif  			
        }

#ifdef SIMULATOR_ENABLED
        if (detector_type == "SimulatorCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = static_cast<void*> (new Simulator::Camera());
                m_interface = static_cast<void*> (new Simulator::Interface(*static_cast<Simulator::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Simulator::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef AVIEX_ENABLED
        if (detector_type == "AviexCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorID"));
                db_data.push_back(Tango::DbDatum("MxDatabaseFileFullName"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string detector_id;
                std::string database_file;
                db_data[0] >> detector_id;
                db_data[1] >> database_file;
                m_camera = static_cast<void*> (new Aviex::Camera(detector_id, database_file));

                m_interface = static_cast<void*> (new Aviex::Interface(*static_cast<Aviex::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Aviex::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef BASLER_ENABLED
        if (detector_type == "BaslerCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorTimeout"));
                db_data.push_back(Tango::DbDatum("DetectorPacketSize"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;
                long detector_timeout = 11000;
                db_data[1] >> detector_timeout;
                long packet_size = -1;
                db_data[2] >> packet_size;
                m_camera = static_cast<void*> (new Basler::Camera(camera_ip, packet_size));
                static_cast<Basler::Camera*> (m_camera)->setTimeout(detector_timeout);

                m_interface = static_cast<void*> (new Basler::Interface(*static_cast<Basler::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Basler::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef XPAD_ENABLED
        if (detector_type == "XpadPixelDetector")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("XpadModel"));
                db_data.push_back(Tango::DbDatum("CalibrationAdjustingNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string xpad_model;
                Tango::DevULong calibration_adjusting_number;

                db_data[0] >> xpad_model;
                db_data[1] >> calibration_adjusting_number;

                m_camera = static_cast<void*> (new Xpad::Camera(xpad_model));
                static_cast<Xpad::Camera*> (m_camera)->setCalibrationAdjustingNumber(calibration_adjusting_number);

                m_interface = static_cast<void*> (new Xpad::Interface(*static_cast<Xpad::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Xpad::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PILATUS_ENABLED
        if (detector_type == "PilatusPixelDetector")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("DetectorCameraDefFileName"));                
                db_data.push_back(Tango::DbDatum("UseReader"));
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));
                
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip = "127.0.0.1";
                std::string camera_def = "camera.def";
                long camera_port = 6666;
                bool use_reader = false;
                unsigned long reader_timeout = 10000;  //in ms
                
                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> camera_def;
                db_data[3] >> use_reader;
                db_data[4] >> reader_timeout;

                m_camera = static_cast<void*> (new Pilatus::Camera(camera_ip.c_str(), camera_port,const_cast<std::string&>(camera_def)));
                if (m_camera && use_reader)
                    static_cast<Pilatus::Camera*> (m_camera)->enableReaderWatcher();
                if (m_camera && !use_reader)
                    static_cast<Pilatus::Camera*> (m_camera)->disableReaderWatcher();

                m_interface = static_cast<void*> (new Pilatus::Interface(*static_cast<Pilatus::Camera*> (m_camera)));
                if(m_interface)
                    static_cast<Pilatus::Interface*> (m_interface)->setTimeout(reader_timeout / 1000.);
                m_control = new CtControl(static_cast<Pilatus::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef MARCCD_ENABLED
        if (detector_type == "MarCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("DetectorTargetPath"));
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                std::string img_path;
                unsigned long camera_port = 2222;
                unsigned short reader_timeout = 10000;

                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> img_path;
                db_data[3] >> reader_timeout;

                m_camera = static_cast<void*> (new Marccd::Camera(camera_ip.c_str(), camera_port, img_path));
                m_interface = static_cast<void*> (new Marccd::Interface(*static_cast<Marccd::Camera*> (m_camera)));
                if (m_interface)
                    static_cast<Marccd::Interface*> (m_interface)->setTimeout(reader_timeout / 1000);

                m_control = new CtControl(static_cast<Marccd::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef ADSC_ENABLED
        if (detector_type == "AdscCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));
                db_data.push_back(Tango::DbDatum("UseReader"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                short reader_timeout = 1000;
                bool use_reader;
                db_data[0] >> reader_timeout;
                db_data[1] >> use_reader;
                m_camera = static_cast<void*> (new Adsc::Camera());
                m_interface = static_cast<void*> (new Adsc::Interface(*static_cast<Adsc::Camera*> (m_camera)));
                if (m_interface && use_reader)
                    static_cast<Adsc::Interface*> (m_interface)->enableReader();
                if (m_interface && !use_reader)
                    static_cast<Adsc::Interface*> (m_interface)->disableReader();
                if (m_interface)
                    static_cast<Adsc::Interface*> (m_interface)->setTimeout(reader_timeout);

                m_control = new CtControl(static_cast<Adsc::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif        

#ifdef PROSILICA_ENABLED
        if (detector_type == "ProsilicaCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;

                m_camera = static_cast<void*> (new Prosilica::Camera(camera_ip.c_str()));
                m_interface = static_cast<void*> (new Prosilica::Interface(static_cast<Prosilica::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Prosilica::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef ANDOR_ENABLED
        if (detector_type == "AndorCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera = static_cast<void*> (new Andor::Camera("Not Used At Soleil", camera_num));
                m_interface = static_cast<void*> (new Andor::Interface(*static_cast<Andor::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Andor::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PRINCETON_ENABLED
        if (detector_type == "PrincetonCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera = static_cast<void*> (new RoperScientific::Camera(camera_num));
                m_interface = static_cast<void*> (new RoperScientific::Interface(*static_cast<RoperScientific::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<RoperScientific::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PCO_ENABLED
        if (detector_type == "Pco")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = static_cast<void*> (new Pco::Camera(""));
                m_interface = static_cast<void*> (new Pco::Interface(static_cast<Pco::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Pco::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PERKINELMER_ENABLED
        if (detector_type == "PerkinElmer")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = 0;
                m_interface = static_cast<void*> (new PerkinElmer::Interface());
                m_control = new CtControl(static_cast<PerkinElmer::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif


#ifdef MERLIN_ENABLED
        if (detector_type == "Merlin")
        {
            if(!ControlFactory::m_is_created)
            {
                m_camera = 0;
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("HostName"));
				db_data.push_back(Tango::DbDatum("CmdPort"));
                db_data.push_back(Tango::DbDatum("DataPort"));
                db_data.push_back(Tango::DbDatum("ImageWidth"));
                db_data.push_back(Tango::DbDatum("ImageHeight"));
                db_data.push_back(Tango::DbDatum("Chips"));
                db_data.push_back(Tango::DbDatum("Simulate"));          
                
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string hostName;
                long cmdPort;
                long dataPort;
                long chips;
                long imageWidth;
                long imageHeight;
                bool simulate;
                db_data[0] >> hostName;
                db_data[1] >> cmdPort;
                db_data[2] >> dataPort;
                db_data[3] >> imageWidth;
                db_data[4] >> imageHeight;
                db_data[5] >> chips;
                db_data[6] >> simulate;
			
                m_camera = static_cast<void*> (new Merlin::Camera(hostName, cmdPort, dataPort, imageWidth, imageHeight, chips, simulate));
                m_interface = static_cast<void*> (new Merlin::Interface(*static_cast<Merlin::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Merlin::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef ANDOR3_ENABLED
        if (detector_type == "Andor3")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("BitFlowPath"));
                db_data.push_back(Tango::DbDatum("CameraNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string bit_flow_path;
                long camera_number;
                db_data[0] >> bit_flow_path;
                db_data[1] >> camera_number;

                m_camera = static_cast<void*> (new Andor3::Camera(bit_flow_path, camera_number));
                m_interface = static_cast<void*> (new Andor3::Interface(*static_cast<Andor3::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Andor3::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef VIEWORKSVP_ENABLED
        if (detector_type == "VieworksVP")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("SisoPath"));
                db_data.push_back(Tango::DbDatum("BoardIndex"));
                db_data.push_back(Tango::DbDatum("CameraPort"));
                db_data.push_back(Tango::DbDatum("AppletName"));
                db_data.push_back(Tango::DbDatum("DMAIndex"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string siso_path;
                long board_index;
                long camera_port;
                std::string applet_name;
                unsigned long dma_index;
                db_data[0] >> siso_path;
                db_data[1] >> board_index;
                db_data[2] >> camera_port;
                db_data[3] >> applet_name;
                db_data[4] >> dma_index;

                m_camera = static_cast<void*> (new VieworksVP::Camera(siso_path, board_index, camera_port, applet_name, dma_index));
                m_interface = static_cast<void*> (new VieworksVP::Interface(*static_cast<VieworksVP::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<VieworksVP::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef HAMAMATSU_ENABLED
        if (detector_type == "Hamamatsu")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera = static_cast<void*> (new Hamamatsu::Camera("Not config path", camera_num));
                m_interface = static_cast<void*> (new Hamamatsu::Interface(*(static_cast<Hamamatsu::Camera*> (m_camera))));
                m_control = new CtControl(static_cast<Hamamatsu::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef EIGER_ENABLED
        if (detector_type == "Eiger")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
				db_data.push_back(Tango::DbDatum("TargetPath"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;
                std::string target_path;
                db_data[1] >> target_path;
                m_camera = static_cast<void*> (new Eiger::Camera(camera_ip, target_path));
                m_interface = static_cast<void*> (new Eiger::Interface(*(static_cast<Eiger::Camera*> (m_camera))));
                m_control = new CtControl(static_cast<Eiger::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif           
        
#ifdef UVIEW_ENABLED
        if (detector_type == "UviewCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = static_cast<void*> (new Uview::Camera());
                m_interface = static_cast<void*> (new Uview::Interface(*static_cast<Uview::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Uview::Interface*> (m_interface));

                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

        if (!ControlFactory::m_is_created)
        {
            string strMsg = "Unable to create the lima control object : Unknown Detector Type : ";
            strMsg += detector_type;
            throw LIMA_HW_EXC(Error, strMsg);
        }

    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
    catch (Exception& e)
    {
        throw LIMA_HW_EXC(Error, e.getErrMsg());
    }
    catch (...)
    {
        throw LIMA_HW_EXC(Error, "Unable to create the lima control object : Unknown Exception");
    }
    
    return m_control;
}

//-----------------------------------------------------------------------------------------
CtControl* ControlFactory::get_control(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(object_control_lock);
	if (!ControlFactory::m_is_created)
	{
		std::stringstream ssMsg("");
		ssMsg<<"Unable to get the lima control of " << "(" << detector_type << ") !" << endl;
		throw LIMA_HW_EXC(Error, ssMsg.str());
	}	
    return m_control;       
}

//-----------------------------------------------------------------------------------------
void ControlFactory::reset(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(object_control_lock);
    try
    {
        if (ControlFactory::m_is_created)
        {
            ControlFactory::m_is_created = false;
            if (m_control)
            {
                delete m_control;
                m_control = 0;
            }

            if (m_camera)
            {
#ifdef SIMULATOR_ENABLED        
                if (detector_type == "SimulatorCCD")
                {
                    delete (static_cast<Simulator::Camera*> (m_camera));
                }
#endif

#ifdef AVIEX_ENABLED        
                if (detector_type == "AviexCCD")
                {
                    delete (static_cast<Aviex::Camera*> (m_camera));
                }
#endif

#ifdef BASLER_ENABLED        
                if (detector_type == "BaslerCCD")
                {
                    delete (static_cast<Basler::Camera*> (m_camera));
                }
#endif

#ifdef XPAD_ENABLED        
                if (detector_type == "XpadPixelDetector")
                {
                    delete (static_cast<Xpad::Camera*> (m_camera));
                }
#endif

#ifdef PILATUS_ENABLED        
                if (detector_type == "PilatusPixelDetector")
                {
                    delete (static_cast<Pilatus::Camera*> (m_camera));
                }
#endif

#ifdef MARCCD_ENABLED        
                if (detector_type == "MarCCD")
                {
                    delete (static_cast<Marccd::Camera*> (m_camera));
                }
#endif  

#ifdef ADSC_ENABLED        
                if (detector_type == "AdscCCD")
                {
                    delete (static_cast<Adsc::Camera*> (m_camera));
                }
#endif 

#ifdef PROSILICA_ENABLED        
                if (detector_type == "ProsilicaCCD")
                {
                    delete (static_cast<Prosilica::Camera*> (m_camera));
                }
#endif 

#ifdef ANDOR_ENABLED        
                if (detector_type == "AndorCCD")
                {
                    delete (static_cast<Andor::Camera*> (m_camera));
                }
#endif     

#ifdef PRINCETON_ENABLED        
                if (detector_type == "PrincetonCCD")
                {
                    delete (static_cast<RoperScientific::Camera*> (m_camera));
                }
#endif         

#ifdef PCO_ENABLED        
                if (detector_type == "Pco")
                {
                    delete (static_cast<Pco::Camera*> (m_camera));
                }
#endif 

#ifdef PERKINELMER_ENABLED        
                if (detector_type == "PerkinElmer")
                {
                    //NOP
                }
#endif 

#ifdef MERLIN_ENABLED        
                if (detector_type == "Merlin")
                {
                    delete (static_cast<Merlin::Camera*> (m_camera));
                }
#endif   

#ifdef ANDOR3_ENABLED        
                if (detector_type == "Andor3")
                {
                    delete (static_cast<Andor3::Camera*> (m_camera));
                }
#endif        

#ifdef VIEWORKSVP_ENABLED        
                if (detector_type == "VieworksVP")
                {
                    delete (static_cast<VieworksVP::Camera*> (m_camera));
                }
#endif              

#ifdef HAMAMATSU_ENABLED        
                if (detector_type == "Hamamatsu")
                {
                    delete (static_cast<Hamamatsu::Camera*> (m_camera));
                }
#endif    

#ifdef EIGER_ENABLED
				if (detector_type == "Eiger")
				{
					delete (static_cast<Eiger::Camera*> (m_camera));
				}		
#endif

#ifdef UVIEW_ENABLED        
                if (detector_type == "UviewCCD")
                {
					delete (static_cast<Uview::Camera*> (m_camera));
                }
#endif     

                m_camera = 0;
            }

            if (m_interface)
            {
                delete m_interface;
                m_interface = 0;
            }        
        }
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
    catch (Exception& e)
    {
        throw LIMA_HW_EXC(Error, e.getErrMsg());
    }
    catch (...)
    {
        throw LIMA_HW_EXC(Error, "reset : Unknown Exception");
    }
}

//-----------------------------------------------------------------------------------------
//- force Init() on the specific device.
//-----------------------------------------------------------------------------------------
void ControlFactory::init_specific_device(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(object_control_lock);
    try
    {
        //get the tango device/instance
        if (!ControlFactory::m_is_created)
        {
            std::string detector = detector_type;
            Tango::DbDatum db_datum;
            m_server_name = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name, detector);
            db_datum >> m_device_name_specific;
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_specific))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_specific))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
	
#ifdef LAYOUT_ENABLED        
	try
	{
        //@@@TODO and if not exist ?? get the tango device/instance for layout
        if (!ControlFactory::m_is_created)
        {
            std::string detector = "Layout";		
            Tango::DbDatum db_datum;
            m_server_name = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name, detector);
            db_datum >> m_device_name_layout;	
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_layout))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_layout))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        ////throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }		
#endif
	
#ifdef ROICOUNTERS_ENABLED        
	try
	{
        //@@@TODO and if not exist ?? get the tango device/instance for layout
        if (!ControlFactory::m_is_created)
        {
            std::string detector = "RoiCounters";			
            Tango::DbDatum db_datum;
            m_server_name = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name, detector);
            db_datum >> m_device_name_roicounters;					
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_roicounters))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_roicounters))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        ////throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }		
#endif	
}

//-----------------------------------------------------------------------------------------
//- call dev_state() command of the generic device.
//-----------------------------------------------------------------------------------------
Tango::DevState ControlFactory::get_state(void)
{
    yat::AutoMutex<> _lock(object_state_lock);
    return m_state;
}
//-----------------------------------------------------------------------------------------
//- call dev_status() command of the generic device.
//-----------------------------------------------------------------------------------------
std::string ControlFactory::get_status(void)
{
    yat::AutoMutex<> _lock(object_state_lock);
    return (m_status.str());

}
//-----------------------------------------------------------------------------------------
void ControlFactory::set_state(Tango::DevState state)
{
    yat::AutoMutex<> _lock(object_state_lock);
    m_state = state;
}

//-----------------------------------------------------------------------------------------
void ControlFactory::set_status(const std::string& status)
{
    yat::AutoMutex<> _lock(object_state_lock);
    m_status.str("");
    m_status << status.c_str() << endl;

}
//-----------------------------------------------------------------------------------------



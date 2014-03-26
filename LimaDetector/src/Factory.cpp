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

bool  ControlFactory::m_is_created = false;


//-----------------------------------------------------------------------------------------
void ControlFactory::initialize_pointers()
{
    m_control			= 0;
    m_camera           = 0;
    m_interface        = 0;

    m_server_name 		= "none";
    m_device_name 		= "none";

    m_status.str("");
    m_state 			= Tango::INIT;
}

//-----------------------------------------------------------------------------------------
CtControl* ControlFactory::get_control( const std::string& detector_type)
{
    yat::MutexLock scoped_lock(object_lock);
    try
    {
        //get the tango device/instance
        if(!ControlFactory::m_is_created)
        {
            initialize_pointers();
            std::string  detector = detector_type;
            Tango::DbDatum db_datum;
            m_server_name = Tango::Util::instance()->get_ds_name ();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name,detector);
            db_datum >> m_device_name;
        }

#ifdef SIMULATOR_ENABLED
        if (detector_type == "SimulatorCCD")
        {
            if(!ControlFactory::m_is_created)
            {
                m_camera                   = static_cast<void*>(new Simulator::Camera());
                m_interface                = static_cast<void*>(new Simulator::Interface( *static_cast<Simulator::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Simulator::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef AVIEX_ENABLED
        if (detector_type == "AviexCCD")
        {
            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorID"));
                db_data.push_back(Tango::DbDatum("MxDatabaseFileFullName"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string detector_id;
                std::string database_file;
                db_data[0] >> detector_id;
                db_data[1] >> database_file;
                m_camera                   = static_cast<void*>(new Aviex::Camera(detector_id, database_file));

                m_interface                = static_cast<void*>(new Aviex::Interface( *static_cast<Aviex::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Aviex::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef BASLER_ENABLED
        if (detector_type == "BaslerCCD")
        {
            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorTimeout"));
                db_data.push_back(Tango::DbDatum("DetectorPacketSize"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;
                long detector_timeout = 11000;
                db_data[1] >> detector_timeout;
                long packet_size = -1;
                db_data[2] >> packet_size;
                m_camera                   = static_cast<void*>(new Basler::Camera(camera_ip, packet_size));
                static_cast<Basler::Camera*>(m_camera)->setTimeout(detector_timeout);

                m_interface                = static_cast<void*>(new Basler::Interface( *static_cast<Basler::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Basler::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef XPAD_ENABLED
        if (detector_type == "XpadPixelDetector")
        {

            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("XpadModel"));
                db_data.push_back(Tango::DbDatum("CalibrationAdjustingNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string xpad_model;
                Tango::DevULong calibration_adjusting_number;

                db_data[0] >> xpad_model;
                db_data[1] >> calibration_adjusting_number;

                m_camera                   = static_cast<void*>(new Xpad::Camera(xpad_model));
                static_cast<Xpad::Camera*>(m_camera)->setCalibrationAdjustingNumber(calibration_adjusting_number);

                m_interface                = static_cast<void*>(new Xpad::Interface( *static_cast<Xpad::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Xpad::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef PILATUS_ENABLED
        if (detector_type == "PilatusPixelDetector")
        {

            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("UseReader"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string camera_ip;
                long camera_port;
                bool use_reader;
                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> use_reader;

                m_camera                   = static_cast<void*>(new Pilatus::Camera(camera_ip.c_str(), camera_port));
                if(m_camera && use_reader)
                    static_cast<Pilatus::Camera*>(m_camera)->enableDirectoryWatcher();
                if(m_camera && !use_reader)
                    static_cast<Pilatus::Camera*>(m_camera)->disableDirectoryWatcher();

                m_interface                = static_cast<void*>( new Pilatus::Interface( *static_cast<Pilatus::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Pilatus::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef MARCCD_ENABLED
        if (detector_type == "MarCCD")
        {
            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("DetectorTargetPath"));
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string camera_ip;
                std::string img_path;
                unsigned long camera_port = 2222;
                unsigned short reader_timeout = 10000;

                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> img_path;
                db_data[3] >> reader_timeout;

                m_camera                   = static_cast<void*>(new Marccd::Camera(camera_ip.c_str(), camera_port, img_path));
                m_interface                = static_cast<void*>(new Marccd::Interface( *static_cast<Marccd::Camera*>(m_camera)));
                if(m_interface)
                    static_cast<Marccd::Interface*>(m_interface)->setTimeout(reader_timeout / 1000);

                m_control                  = new CtControl(static_cast<Marccd::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef ADSC_ENABLED
        if (detector_type == "AdscCCD")
        {

            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));
                db_data.push_back(Tango::DbDatum("UseReader"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                short reader_timeout = 1000;
                bool use_reader;
                db_data[0] >> reader_timeout;
                db_data[1] >> use_reader;
                m_camera                  = static_cast<void*>(new Adsc::Camera());
                m_interface               = static_cast<void*>(new Adsc::Interface( *static_cast<Adsc::Camera*>(m_camera)));
                if(m_interface && use_reader)
                    static_cast<Adsc::Interface*>(m_interface)->enableReader();
                if(m_interface && !use_reader)
                    static_cast<Adsc::Interface*>(m_interface)->disableReader();
                if(m_interface)
                    static_cast<Adsc::Interface*>(m_interface)->setTimeout(reader_timeout);

                m_control                  = new CtControl(static_cast<Adsc::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif        

#ifdef PROSILICA_ENABLED
        if (detector_type == "ProsilicaCCD")
        {

            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;

                m_camera                   = static_cast<void*>(new Prosilica::Camera(camera_ip.c_str()));
                m_interface                = static_cast<void*>(new Prosilica::Interface( static_cast<Prosilica::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Prosilica::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef ANDOR_ENABLED
        if (detector_type == "AndorCCD")
        {

            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera                   = static_cast<void*>(new Andor::Camera("Not Used At Soleil", camera_num));
                m_interface                = static_cast<void*>(new Andor::Interface( *static_cast<Andor::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Andor::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef PRINCETON_ENABLED
        if (detector_type == "PrincetonCCD")
        {

            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera                   = static_cast<void*>(new RoperScientific::Camera(camera_num));
                m_interface                = static_cast<void*>(new RoperScientific::Interface( *static_cast<RoperScientific::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<RoperScientific::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef PCO_ENABLED
        if (detector_type == "Pco")
        {
            if(!ControlFactory::m_is_created)
            {
                m_camera                   = static_cast<void*>(new Pco::Camera(""));
                m_interface                = static_cast<void*>(new Pco::Interface( static_cast<Pco::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Pco::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;
            }
        }
#endif

#ifdef PERKINELMER_ENABLED
        if (detector_type == "PerkinElmer")
        {
            if(!ControlFactory::m_is_created)
            {
                m_camera                  = 0;
                m_interface               = static_cast<void*>(new PerkinElmer::Interface());
                m_control                 = new CtControl(static_cast<PerkinElmer::Interface*>(m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef ANDOR3_ENABLED
        if (detector_type == "Andor3")
        {
            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("BitFlowPath"));
                db_data.push_back(Tango::DbDatum("CameraNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
                std::string bit_flow_path;
                long camera_number;
                db_data[0] >> bit_flow_path;
                db_data[1] >> camera_number;

                m_camera                   = static_cast<void*>(new Andor3::Camera(bit_flow_path,camera_number));
                m_interface                = static_cast<void*>(new Andor3::Interface( *static_cast<Andor3::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<Andor3::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;                
            }
        }
#endif

#ifdef VIEWORKSVP_ENABLED
        if (detector_type == "VieworksVP")
        {
            if(!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("SisoPath"));
                db_data.push_back(Tango::DbDatum("BoardIndex"));
                db_data.push_back(Tango::DbDatum("CameraPort"));
                db_data.push_back(Tango::DbDatum("AppletName"));
                db_data.push_back(Tango::DbDatum("DMAIndex"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name, db_data);
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
                
                m_camera                   = static_cast<void*>(new VieworksVP::Camera(siso_path,board_index,camera_port,applet_name,dma_index));
                m_interface                = static_cast<void*>(new VieworksVP::Interface( *static_cast<VieworksVP::Camera*>(m_camera)));
                m_control                  = new CtControl(static_cast<VieworksVP::Interface*>(m_interface));
                ControlFactory::m_is_created  = true;
                return m_control;                   
            }
        }
#endif

        if(!ControlFactory::m_is_created)
            throw LIMA_HW_EXC(Error, "Unable to create the lima control object : Unknown Detector Type");

    }
    catch(Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
    catch(Exception& e)
    {
        throw LIMA_HW_EXC(Error, e.getErrMsg());
    }
    catch(...)
    {
        throw LIMA_HW_EXC(Error, "Unable to create the lima control object : Unknown Exception");
    }
    return m_control;
}


//-----------------------------------------------------------------------------------------
void ControlFactory::reset(const std::string& detector_type )
{
    yat::MutexLock scoped_lock(object_lock);
    try
    {
        if(ControlFactory::m_is_created)
        {
            ControlFactory::m_is_created = false;
            if(m_control)
            {
                delete m_control;
                m_control = 0;
            }

            if(m_camera)
            {
                delete m_camera;
                m_camera = 0;
            }

            if(m_interface)
            {
                delete m_interface;
                m_interface = 0;
            }
        }
    }
    catch(Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
    catch(Exception& e)
    {
        throw LIMA_HW_EXC(Error, e.getErrMsg());
    }
    catch(...)
    {
        throw LIMA_HW_EXC(Error, "reset : Unknown Exception");
    }
}

//-----------------------------------------------------------------------------------------
//- force Init() on the specific device.
//-----------------------------------------------------------------------------------------
void ControlFactory::init_specific_device(const std::string& detector_type )
{
    yat::MutexLock scoped_lock(object_lock);
    try
    {
        //get the tango device/instance
        if(!ControlFactory::m_is_created)
        {
            std::string  detector = detector_type;
            Tango::DbDatum db_datum;
            m_server_name = Tango::Util::instance()->get_ds_name ();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_server_name,detector);
            db_datum >> m_device_name;
        }

        (Tango::Util::instance()->get_device_by_name(m_device_name))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name))->init_device();
    }
    catch(Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
}

//-----------------------------------------------------------------------------------------
//- call dev_state() command of the generic device.
//-----------------------------------------------------------------------------------------
Tango::DevState ControlFactory::get_state(void )
{
    yat::AutoMutex<> _lock(object_state_lock);
    return m_state;
}
//-----------------------------------------------------------------------------------------
//- call dev_status() command of the generic device.
//-----------------------------------------------------------------------------------------
std::string 	ControlFactory::get_status(void )
{
    yat::AutoMutex<> lock(object_state_lock);
    return (m_status.str());

}
//-----------------------------------------------------------------------------------------
void ControlFactory::set_state(Tango::DevState state)
{
    yat::AutoMutex<> _lock(object_state_lock);
    m_state = state;
}

//-----------------------------------------------------------------------------------------
void ControlFactory::set_status (const std::string& status)
{
    yat::AutoMutex<> _lock(object_state_lock);
    m_status.str("");
    m_status << status.c_str() << endl;

}
//-----------------------------------------------------------------------------------------



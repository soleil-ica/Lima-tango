#include <Factory.h>

#include <iostream>

bool  ControlFactory::is_created = false;


//-----------------------------------------------------------------------------------------
void ControlFactory::initialize_pointers()
{
    my_control			= 0;
    my_camera           = 0;
    my_interface        = 0;

    my_server_name 		= "none";
    my_device_name 		= "none";

    my_status.str("");
    my_state 			= Tango::INIT;
}

//-----------------------------------------------------------------------------------------
CtControl* ControlFactory::get_control( const std::string& detector_type)
{
    yat::MutexLock scoped_lock(object_lock);
    try
    {
        //get the tango device/instance
        if(!ControlFactory::is_created)
        {
            initialize_pointers();
            std::string  detector = detector_type;
            Tango::DbDatum db_datum;
            my_server_name = Tango::Util::instance()->get_ds_name ();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(my_server_name,detector);
            db_datum >> my_device_name;
        }

#ifdef SIMULATOR_ENABLED
        if (detector_type == "SimulatorCCD")
        {
            if(!ControlFactory::is_created)
            {
                my_camera                   = static_cast<void*>(new Simulator::Camera());
                my_interface                = static_cast<void*>(new Simulator::Interface( *static_cast<Simulator::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Simulator::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef AVIEX_ENABLED
        if (detector_type == "AviexCCD")
        {
            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorID"));
                db_data.push_back(Tango::DbDatum("MxDatabaseFileFullName"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string detector_id;
                std::string database_file;
                db_data[0] >> detector_id;
                db_data[1] >> database_file;
                my_camera                   = static_cast<void*>(new Aviex::Camera(detector_id, database_file));

                my_interface                = static_cast<void*>(new Aviex::Interface( *static_cast<Aviex::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Aviex::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef BASLER_ENABLED
        if (detector_type == "BaslerCCD")
        {
            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorTimeout"));
                db_data.push_back(Tango::DbDatum("DetectorPacketSize"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;
                long detector_timeout = 11000;
                db_data[1] >> detector_timeout;
                long packet_size = -1;
                db_data[2] >> packet_size;
                my_camera                   = static_cast<void*>(new Basler::Camera(camera_ip, packet_size));
                static_cast<Basler::Camera*>(my_camera)->setTimeout(detector_timeout);

                my_interface                = static_cast<void*>(new Basler::Interface( *static_cast<Basler::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Basler::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef XPAD_ENABLED
        if (detector_type == "XpadPixelDetector")
        {

            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("XpadModel"));
                db_data.push_back(Tango::DbDatum("CalibrationAdjustingNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string xpad_model;
                Tango::DevULong calibration_adjusting_number;

                db_data[0] >> xpad_model;
                db_data[1] >> calibration_adjusting_number;

                my_camera                   = static_cast<void*>(new Xpad::Camera(xpad_model));
                static_cast<Xpad::Interface*>(my_camera)->setCalibrationAdjustingNumber(calibration_adjusting_number);

                my_interface                = static_cast<void*>(new Xpad::Interface( *static_cast<Xpad::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Xpad::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef PILATUS_ENABLED
        if (detector_type == "PilatusPixelDetector")
        {

            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("UseReader"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string camera_ip;
                long camera_port;
                bool use_reader;
                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> use_reader;

                my_camera                   = static_cast<void*>(new Pilatus::Camera(camera_ip.c_str(), camera_port));
                if(my_camera && use_reader)
                    static_cast<Pilatus::Camera*>(my_camera)->enableDirectoryWatcher();
                if(my_camera && !use_reader)
                    static_cast<Pilatus::Camera*>(my_camera)->disableDirectoryWatcher();

                my_interface                = static_cast<void*>( new Pilatus::Interface( *static_cast<Pilatus::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Pilatus::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef MARCCD_ENABLED
        if (detector_type == "MarCCD")
        {
            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("DetectorTargetPath"));
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));

                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string camera_ip;
                std::string img_path;
                unsigned long camera_port = 2222;
                unsigned short reader_timeout = 10000;

                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> img_path;
                db_data[3] >> reader_timeout;

                my_camera                   = static_cast<void*>(new Marccd::Camera(camera_ip.c_str(), camera_port, img_path));
                my_interface                = static_cast<void*>(new Marccd::Interface( *static_cast<Marccd::Camera*>(my_camera)));
                if(my_interface)
                    static_cast<Marccd::Interface*>(my_interface)->setTimeout(reader_timeout / 1000);

                my_control                  = new CtControl(static_cast<Marccd::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef ADSC_ENABLED
        if (detector_type == "AdscCCD")
        {

            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));
                db_data.push_back(Tango::DbDatum("UseReader"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                short reader_timeout = 1000;
                bool use_reader;
                db_data[0] >> reader_timeout;
                db_data[1] >> use_reader;
                my_camera                  = static_cast<void*>(new Adsc::Camera());
                my_interface               = static_cast<void*>(new Adsc::Interface( *static_cast<Adsc::Camera*>(my_camera)));
                if(my_interface && use_reader)
                    static_cast<Adsc::Interface*>(my_interface)->enableReader();
                if(my_interface && !use_reader)
                    static_cast<Adsc::Interface*>(my_interface)->disableReader();
                if(my_interface)
                    static_cast<Adsc::Interface*>(my_interface)->setTimeout(reader_timeout);

                my_control                  = new CtControl(static_cast<Adsc::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif        

#ifdef PROSILICA_ENABLED
        if (detector_type == "ProsilicaCCD")
        {

            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;

                my_camera                  = static_cast<void*>(new Prosilica::Camera(camera_ip.c_str()));
                my_interface                = static_cast<void*>(new Prosilica::Interface( static_cast<Prosilica::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Prosilica::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef ANDOR_ENABLED
        if (detector_type == "AndorCCD")
        {

            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                my_camera                  = static_cast<void*>(new Andor::Camera("Not Used At Soleil", camera_num));
                my_interface               = static_cast<void*>(new Andor::Interface( *static_cast<Andor::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Andor::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef PRINCETON_ENABLED
        if (detector_type == "PrincetonCCD")
        {

            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                my_camera                  = static_cast<void*>(new RoperScientific::Camera(camera_num));
                my_interface               = static_cast<void*>(new RoperScientific::Interface( *static_cast<RoperScientific::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<RoperScientific::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef PCO_ENABLED
        if (detector_type == "Pco")
        {
            if(!ControlFactory::is_created)
            {
                my_camera                  = static_cast<void*>(new Pco::Camera(""));
                my_interface               = static_cast<void*>(new Pco::Interface( *static_cast<Pco::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Pco::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;
            }
        }
#endif

#ifdef PERKINELMER_ENABLED
        if (detector_type == "PerkinElmer")
        {
            if(!ControlFactory::is_created)
            {
                my_camera                  = 0
                my_interface               = static_cast<void*>(new PerkinElmer::Interface());
                my_control                 = new CtControl(static_cast<PerkinElmer::Interface*>(my_interface));
                ControlFactory::is_created = true;
                return my_control;
            }
        }
#endif

#ifdef ANDOR3_ENABLED
        if (detector_type == "Andor3")
        {
            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("BitFlowPath"));
                db_data.push_back(Tango::DbDatum("CameraNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
                std::string bit_flow_path;
                long camera_number;
                db_data[0] >> bit_flow_path;
                db_data[1] >> camera_number;

                my_camera                  = static_cast<void*>(new Andor3::Camera(bit_flow_path,camera_number));
                my_interface               = static_cast<void*>(new Andor3::Interface( *static_cast<Andor3::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<Andor3::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;                
            }
        }
#endif

#ifdef VIEWORKSVP_ENABLED
        if (detector_type == "VieworksVP")
        {
            if(!ControlFactory::is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("SisoPath"));
                db_data.push_back(Tango::DbDatum("BoardIndex"));
                db_data.push_back(Tango::DbDatum("CameraPort"));
                db_data.push_back(Tango::DbDatum("AppletName"));
                db_data.push_back(Tango::DbDatum("DMAIndex"));

                (Tango::Util::instance()->get_database())->get_device_property(my_device_name, db_data);
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
                
                my_camera                  = static_cast<void*>(new VieworksVP::Camera(siso_path,board_index,camera_port,applet_name,dma_index));
                my_interface               = static_cast<void*>(new VieworksVP::Interface( *static_cast<VieworksVP::Camera*>(my_camera)));
                my_control                  = new CtControl(static_cast<VieworksVP::Interface*>(my_interface));
                ControlFactory::is_created  = true;
                return my_control;                   
            }
        }
#endif



        if(!ControlFactory::is_created)
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
    return my_control;
}


//-----------------------------------------------------------------------------------------
void ControlFactory::reset(const std::string& detector_type )
{
    yat::MutexLock scoped_lock(object_lock);
    try
    {
        if(ControlFactory::is_created)
        {
            ControlFactory::is_created = false;
            if(my_control)
            {
                delete my_control;
                my_control = 0;
            }

            if(my_camera)
            {
                delete my_camera;
                my_camera = 0;
            }

            if(my_interface)
            {
                delete my_interface;
                my_interface = 0;
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
        if(!ControlFactory::is_created)
        {
            std::string  detector = detector_type;
            Tango::DbDatum db_datum;
            my_server_name = Tango::Util::instance()->get_ds_name ();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(my_server_name,detector);
            db_datum >> my_device_name;
        }

        (Tango::Util::instance()->get_device_by_name(my_device_name))->delete_device();
        (Tango::Util::instance()->get_device_by_name(my_device_name))->init_device();
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
    return my_state;
}
//-----------------------------------------------------------------------------------------
//- call dev_status() command of the generic device.
//-----------------------------------------------------------------------------------------
std::string 	ControlFactory::get_status(void )
{
    yat::AutoMutex<> lock(object_state_lock);
    return (my_status.str());

}
//-----------------------------------------------------------------------------------------
void ControlFactory::set_state(Tango::DevState state)
{
    yat::AutoMutex<> _lock(object_state_lock);
    my_state = state;
}

//-----------------------------------------------------------------------------------------
void ControlFactory::set_status (const std::string& status)
{
    yat::AutoMutex<> _lock(object_state_lock);
    my_status.str("");
    my_status << status.c_str() << endl;

}
//-----------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace hplc_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"hplc_controller");

CONSTANT_STRING(firmware_name,"HplcController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=1,
};

// Clients
const size_t ultraviolet_detector_interface_address[1] =
{
  1,
};

const size_t pump_interface_address[1] =
{
  3,
};

CONSTANT_STRING(gradient_info_string,"gradient_info");

// Pins

// Units

// Properties

// Parameters

// Functions
CONSTANT_STRING(get_info_function_name,"getInfo");

// Callbacks
CONSTANT_STRING(start_callback_name,"start");
CONSTANT_STRING(stop_callback_name,"stop");

// Errors
}
}

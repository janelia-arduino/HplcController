// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef HPLC_CONTROLLER_CONSTANTS_H
#define HPLC_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>

#include <ModularServer.h>


namespace hplc_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString gradient_info_string;

// Clients
extern const size_t ultraviolet_detector_interface_address[1];
extern const size_t pump_interface_address[1];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions
extern ConstantString get_info_function_name;

// Callbacks
extern ConstantString start_callback_name;
extern ConstantString stop_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif

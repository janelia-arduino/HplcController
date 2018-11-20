// ----------------------------------------------------------------------------
// HplcController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../HplcController.h"


using namespace hplc_controller;

HplcController::HplcController()
{
}

void HplcController::setup()
{
  // Parent Setup
  GradientController::setup();

  // Reset Watchdog
  resetWatchdog();

  // Clients Setup
  ultraviolet_detector_interface_ptr_ = &(createClientAtAddress(ultraviolet_detector_interface::constants::device_name,constants::ultraviolet_detector_interface_address));

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties

  // Parameters

  // Functions
  modular_server::Function & get_info_function = modular_server_.createFunction(constants::get_info_function_name);
  get_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&HplcController::getInfoHandler));
  get_info_function.setResultTypeObject();

  // Callbacks
  modular_server::Callback & start_callback = modular_server_.createCallback(constants::start_callback_name);
  start_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&HplcController::startHandler));
  start_callback.attachTo(modular_device_base::constants::btn_a_pin_name,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & stop_callback = modular_server_.createCallback(constants::stop_callback_name);
  stop_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&HplcController::stopHandler));

}

void HplcController::update()
{
  // Parent Update
  GradientController::update();
}

bool HplcController::setupClients()
{
  bool setup_was_successful = true;

  ultraviolet_detector_interface_ptr_->callUntilSuccessful(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && ultraviolet_detector_interface_ptr_->callWasSuccessful();

  return setup_was_successful;
}

void HplcController::start()
{
  startGradient();
}

void HplcController::stop()
{
  stopGradient();
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void HplcController::getInfoHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginObject();

  modular_server_.response().writeKey(constants::gradient_info_string);
  writeGradientInfoToResponse();

  modular_server_.response().endObject();
}

void HplcController::startHandler(modular_server::Pin * pin_ptr)
{
  start();
}

void HplcController::stopHandler(modular_server::Pin * pin_ptr)
{
  stop();
}

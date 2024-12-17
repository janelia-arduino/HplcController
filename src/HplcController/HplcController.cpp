// ----------------------------------------------------------------------------
// HplcController.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "HplcController.h"


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
  pump_interface_ptr_ = &(createClientAtAddress(pump_interface::constants::device_name,constants::pump_interface_address));

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

  pump_interface_ptr_->callUntilSuccessful(modular_server::constants::set_properties_to_defaults_function_name,
    modular_server::constants::all_array);
  setup_was_successful = setup_was_successful && pump_interface_ptr_->callWasSuccessful();

  return setup_was_successful;
}

void HplcController::start()
{
  pump_interface_ptr_->callUntilSuccessful(pump_interface::constants::run_pump_callback_name);

  startGradient();
}

void HplcController::stop()
{
  stopGradient();

  pump_interface_ptr_->callUntilSuccessful(pump_interface::constants::stop_pump_callback_name);
}

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

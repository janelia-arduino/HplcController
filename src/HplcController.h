// ----------------------------------------------------------------------------
// HplcController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef HPLC_CONTROLLER_H
#define HPLC_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularClient.h>
#include "UltravioletDetectorInterface.h"
#include "PumpInterface.h"

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <PowerSwitchController.h>
#include <MixingValveController.h>
#include <GradientController.h>

#include "HplcController/Constants.h"


class HplcController : public GradientController
{
public:
  HplcController();
  virtual void setup();
  virtual void update();

  void start();
  void stop();

private:
  modular_server::Property properties_[hplc_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[hplc_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[hplc_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[hplc_controller::constants::CALLBACK_COUNT_MAX];

  ModularClient * ultraviolet_detector_interface_ptr_;
  ModularClient * pump_interface_ptr_;

  bool setupClients();

  // Handlers
  void getInfoHandler();
  void startHandler(modular_server::Pin * pin_ptr);
  void stopHandler(modular_server::Pin * pin_ptr);

};

#endif

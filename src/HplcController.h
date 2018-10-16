// ----------------------------------------------------------------------------
// HplcController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef HPLC_CONTROLLER_H
#define HPLC_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <EventController.h>

#include <ModularClient.h>
#include <EncoderInterfaceSimple.h>
#include <PowerSwitchController.h>
#include <AudioController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include "HplcController/Constants.h"


class HplcController : public StageController
{
public:
  HplcController();
  virtual void setup();
  virtual void update();

  hplc_controller::constants::AssayStatus getAssayStatus();

  void moveJoystickToBasePosition();
  void moveJoystickToReachPosition();
  void activateLickport(const long count);

  void startTrial();
  void startAssay();
  void abortTrial();
  void abortAssay();
  void restartAssay();

private:
  modular_server::Property properties_[hplc_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[hplc_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[hplc_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[hplc_controller::constants::CALLBACK_COUNT_MAX];

  hplc_controller::constants::AssayStatus assay_status_;
  EventController<hplc_controller::constants::EVENT_COUNT_MAX> event_controller_;
  EventId trial_timeout_event_id_;

  hplc_controller::constants::TrialTimingData trial_timing_data_;

  ModularClient * encoder_interface_simple_ptr_;
  ModularClient * power_switch_controller_ptr_;
  ModularClient * audio_controller_ptr_;

  bool trial_aborted_;
  bool assay_aborted_;
  size_t reach_position_1_index_;
  size_t pull_torque_index_;

  unsigned long time_;
  unsigned long pull_push_poll_time_previous_;

  bool setupClients();
  StageController::PositionArray getBasePosition();
  StageController::PositionArray getReachPosition();
  long getPullTorque();

  void resetAssayStatus();

  void setupAssay();
  void setupTrial();
  void addStartTrialEvent();
  void checkForMouseReady();

  void setupPull();
  void checkForPullOrPush();

  void reward();
  void checkTrialTermination();
  void finishTrial();

  void prepareNextTrial();
  void resetTrialTimingData();
  void updateTrialBlockSet();
  void updateReachPosition();
  void updatePullTorque();
  void updatePullThreshold();
  void moveToBasePosition();
  void moveToReachPosition();
  void playJoystickReadyTone();
  void playRewardTone();
  void triggerLickportReward();
  void triggerLickport(const long delay,
    const long count);
  void setHomeCurrent(const size_t channel);
  void setIdleCurrent();
  void restoreCurrentSettings(const size_t channel);

  bool setupReadyPulse();
  bool triggerReadyPulse();
  bool setupRewardPulse();
  bool triggerRewardPulse();
  bool setupTrialTerminationPulse();
  bool triggerTrialTerminationPulse();

  // Handlers
  void getAssayStatusHandler();
  void moveJoystickToBasePositionHandler();
  void moveJoystickToReachPositionHandler();
  void activateLickportHandler();
  void getTrialTimingDataHandler();
  void startTrialHandler(modular_server::Pin * pin_ptr);
  void startAssayHandler(modular_server::Pin * pin_ptr);
  void abortTrialHandler(modular_server::Pin * pin_ptr);
  void abortAssayHandler(modular_server::Pin * pin_ptr);
  void restartAssayHandler(modular_server::Pin * pin_ptr);
  void startTrialEventHandler(int arg);
  void trialTimeoutEventHandler(int arg);

};

#endif

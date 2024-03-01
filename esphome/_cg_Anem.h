#include "esphome.h"

#include "cgAnem.h"

#ifdef ANEM_I2C_ADDR 
#undef ANEM_I2C_ADDR
#define ANEM_I2C_ADDR 0x11
#endif 

using namespace esphome;

class MycgAnem: public PollingComponent, public CustomAPIDevice 
{
  public:
  BinarySensor * SensorStatusUP_BinarySensor = new BinarySensor();
  BinarySensor * SensorStatusOV_BinarySensor = new BinarySensor();
  BinarySensor * SensorStatusWDT_BinarySensor = new BinarySensor();
  Sensor * FirmwareVersion_Sensor = new Sensor();
  Sensor * AmbientTemperature_Sensor = new Sensor();
  Sensor * HotendTemperature_Sensor = new Sensor();
  Sensor * HeatPower_Sensor = new Sensor();
  Sensor * DuctArea_Sensor = new Sensor();
  Sensor * AirConsumption_Sensor = new Sensor();
  Sensor * AirFlowRate_Sensor = new Sensor();  
  Sensor * MinAirFlowRate_Sensor = new Sensor(); 
  Sensor * MaxAirFlowRate_Sensor = new Sensor();

  CG_Anem myself 
  {
    ANEM_I2C_ADDR
  };

  MycgAnem(): PollingComponent(10000) {}

  void on_set_duct_area(float ductarea_) 
  {
    myself.set_Duct_Area(ductarea_);
    ESP_LOGD("Duct_Area_", "Set to %d", ductarea_);
  }

  void on_resetMinMaxValues() 
  {
    myself.resetMinMaxValues();
    ESP_LOGD("MinMax", "Reset");
  }

  void setup() override 
  {
    myself.init();
    myself.set_Duct_Area(id(duct)); //  
    register_service( & MycgAnem::on_set_duct_area, "set_Duct_Area", {
      "ductarea_"
    });
    register_service( & MycgAnem::on_resetMinMaxValues, "reset_Min_Max_Values");
    ;
  }

  void update() override 
  {
    myself.data_update();
    bool SensorStatusUP = myself.SensorStatusUP;
    bool SensorStatusOV = myself.SensorStatusOV;
    bool SensorStatusWDT = myself.SensorStatusWDT;
    float FirmwareVersion = myself.FirmwareVersion;
    float AmbientTemperature = myself.AmbientTemperature;
    float HotendTemperature = myself.HotendTemperature;
    float HeatPower = myself.HeatPower;
    float DuctArea = myself.DuctArea;
    float AirFlowRate = myself.AirFlowRate;
    float AirConsumption = myself.AirConsumption;
    float MaxAirFlowRate = myself.MaxAirFlowRate;
    float MinAirFlowRate = myself.MinAirFlowRate;
    
    SensorStatusUP_BinarySensor -> publish_state(SensorStatusUP);
    SensorStatusOV_BinarySensor -> publish_state(SensorStatusOV);
    SensorStatusWDT_BinarySensor -> publish_state(SensorStatusWDT);
    FirmwareVersion_Sensor -> publish_state(FirmwareVersion);
    AmbientTemperature_Sensor -> publish_state(AmbientTemperature);
    HotendTemperature_Sensor -> publish_state(HotendTemperature);
    HeatPower_Sensor -> publish_state(HeatPower);
    DuctArea_Sensor -> publish_state(DuctArea);
    AirFlowRate_Sensor -> publish_state(AirFlowRate);
    AirConsumption_Sensor -> publish_state(AirConsumption);
    MaxAirFlowRate_Sensor -> publish_state(MaxAirFlowRate);
    MinAirFlowRate_Sensor -> publish_state(MinAirFlowRate);
  }
};
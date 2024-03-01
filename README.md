# CG-Anem

Add to device config for climateguard/CG-Anem
```yaml
esphome:
  name: 'esp-test'

  libraries:
   - Wire
   - https://github.com/ElectroZheka/CG-Anem/

  includes:
   - my_components/cgAnem/_cg_Anem.h

...

sensor:  
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->AmbientTemperature_Sensor, cg_anem->HotendTemperature_Sensor, cg_anem->HeatPower_Sensor, cg_anem->AirConsumption_Sensor, cg_anem->AirFlowRate_Sensor, cg_anem->DuctArea_Sensor, cg_anem->FirmwareVersion_Sensor, cg_anem->MinAirFlowRate_Sensor, cg_anem->MaxAirFlowRate_Sensor};
    sensors:
      - name: "cgAnem AmbientTemp"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: temperature
        unit_of_measurement: "°C"
      - name: "cgAnem HotendTemp"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: temperature
        unit_of_measurement: "°C"
      - name: "cgAnem HeatPower"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: power
        unit_of_measurement: "W"
      - name: "cgAnem AirConsumption"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: volume
        unit_of_measurement: "m³/h"
      - name: "cgAnem AirFlowRate"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: wind_speed
        unit_of_measurement: "m/s"
      - name: "cgAnem DuctArea"
        accuracy_decimals: 0
        unit_of_measurement: "cm²"
      - name: "cgAnem FirmwareVersion"
        accuracy_decimals: 2
      - name: "cgAnem MinAirFlowRate"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: wind_speed
        unit_of_measurement: "m/s"
      - name: "cgAnem MaxAirFlowRate"
        accuracy_decimals: 1
        state_class: "measurement"
        device_class: wind_speed
        unit_of_measurement: "m/s"

binary_sensor:
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->SensorStatusUP_BinarySensor};
    binary_sensors:
      - name: "cgAnem Status UP"
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
      return {cg_anem->SensorStatusOV_BinarySensor};
    binary_sensors:
      - name: "cgAnem Status OV"
  - platform: custom
    lambda: |-
      auto cg_anem = new MycgAnem();
      App.register_component(cg_anem);
```
      return {cg_anem->SensorStatusWDT_BinarySensor};
    binary_sensors:
      - name: "cgAnem Status WDT"
    

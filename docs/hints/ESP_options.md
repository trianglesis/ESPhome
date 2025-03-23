# Remember some hints


## Platform Versions

1. For newest board type `ESP32 C6`:

```yaml
# Example
# https://esphome.io/components/esp32
esp32:
  board: esp32-c6-devkitc-1
  flash_size: 8MB
  variant: esp32c6
  framework:
    type: esp-idf
    sdkconfig_options:
      CONFIG_ESPTOOLPY_FLASHSIZE_8MB: y
    version: "5.3.1"
    platform_version: 6.9.0
    # OTHER
    # version: 5.3.2
    # platform_version: 53.03.11
```


## Build Flags

1. For CO2 sensor `scd4x` at `ESP32 C6` with `I2C`:

- https://github.com/esphome/esphome/pull/1651
- https://github.com/esphome/issues/issues/6639#issuecomment-2569764107
- https://github.com/esphome/issues/issues/6639#issuecomment-2669790604


```yaml
# Example
esphome:
  name: "esp32-c6-1"
  friendly_name: "ESP32_C6_1"
  platformio_options:
    build_flags: "-DI2C_NUM_1=I2C_NUM_0"
# Use of I2C for MQ-135
external_components:
  - source: github://pr#8283
    components: [ i2c ]

```

2. For `MQ-135` at `ESP32 C6` with `ADC`:

- https://github.com/lboue/esphome/blob/adc_oneshot/esphome/components/adc

```yaml
# For ESP32-C6 only
# This is to make sure adc compiles or else it will throw an error
external_components:
  - source:
      type: git
      url: https://github.com/lboue/esphome
      ref: adc_oneshot
    components: [ adc ]
    refresh: 0s
```


3. Zigbee functionsat `ESP32 C6`

```yaml
# Example
esp32:
  board: esp32-c6-devkitc-1
  flash_size: 8MB
  variant: esp32c6
  framework:
    type: esp-idf
    version: 5.3.2
    platform_version: 53.03.11
    sdkconfig_options:
      CONFIG_ESPTOOLPY_FLASHSIZE_8MB: y
      CONFIG_ZB_ENABLED: y
      CONFIG_ZB_RADIO_NATIVE: y
      CONFIG_ZB_ZED: y
      ZB_ED_ROLE: y
```

## External Components

Usually use with `build_flags` too, as in the `CO2` sensor


1. Use microphone at `ESP32-C6` **UNSUCCESFULLY YET**

As deep noise analyzer

```yaml
external_components:
  - source: github://mafrosis/esphome-sound-level-meter@tmp
    components: [i2s, sound_level_meter]
```

As simple mic

```yaml
external_components:
  - source: github://esphome/esphome@jesserockz-2023-409
    components: i2s_audio
    refresh: 0s
```

And trying build flags too:

```yaml
esphome:
  name: "esp32-c6-2-mic"
  friendly_name: "ESP32_C6_2-mic"
  platformio_options:
    build_flags: "-I2S_NUM_MAX=I2S_NUM_0 -I2S_MCLK_MULTIPLE_DEFAULT=I2S_MCLK_MULTIPLE_768"
```


```shell
Processing esp32-c6-1 (board: esp32-c6-devkitc-1; framework: espidf; platform: platformio/espressif32@6.4.0)
```


## Version issues:

- https://community.platformio.org/t/use-of-arduino-esp32-in-platformio/45382/8


```shell
esp32: [source my_proj/esp32-c6-1.yaml:15]
  board: esp32-c6-devkitc-1
  flash_size: 8MB
  variant: esp32c6
  
  ESP-IDF 5.4.0 is not available with pioarduino; you may need to specify 'release'.
  framework: 
    type: esp-idf
    sdkconfig_options: 
      CONFIG_ESPTOOLPY_FLASHSIZE_8MB: y
    version: 5.4.0
    platform_version:  6.8.1
```


```yaml
light: 
    # https://esphome.io/components/light/esp32_rmt_led_strip
    https://forum.mylocalbytes.com/d/162-localdeck-this-feature-is-not-available-for-the-idf-framework-version-5
    - platform: esp32_rmt_led_strip
    rgb_order: RGB
    # rgb_order: GRB
    pin: GPIO8
    num_leds: 1
    rmt_channel: 0
    chipset: ws2812
    name: "${friendly_name} RTM LED Light"
    web_server:
        sorting_group_id: sorting_group_controls
```
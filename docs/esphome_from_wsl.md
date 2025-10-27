
# Using ESP Home as local env

- https://esphome.io/guides/installing_esphome

Needed:
- https://learn.microsoft.com/en-us/windows/wsl/connect-usb
- https://github.com/dorssel/usbipd-win

Next:
- https://esphome.io/guides/getting_started_command_line#bonus-esphome-dashboard


```shell
mkdir esphome
cd esphome
# Install virt env
virtualenv --python=/usr/bin/python3 venv
# Activate
source venv/bin/activate
source venv_esp_old/bin/activate
# Install ESPHome
pip3 install esphome
pip3 install esphome==2025.5.0

# Upgrade:
pip install --upgrade esphome

# Version
(venv) [user@aaa ESPhome]$ esphome version
Version: 2024.9.1
```

NOTE: Check if platformio is not installed GLOBALLY!

Show installed:

`pip list | grep esp`

```log
aioesphomeapi              24.6.2
esphome                    2024.9.1
esphome-dashboard          20240620.0
esptool                    4.7.0
```

```shell
ESPHome 2024.9.1

positional arguments:
  command               Command to run:
    config              Validate the configuration and spit it out.
    compile             Read the configuration and compile a program.
    upload              Validate the configuration and upload the latest binary.
    logs (log)          Validate the configuration and show all logs.
    discover            Validate the configuration and show all discovered devices.
    run                 Validate the configuration, create a binary, upload it, and start logs.
    clean-mqtt          Helper to clear retained messages from an MQTT topic.
    wizard              A helpful setup wizard that will guide you through setting up ESPHome.
    mqtt-fingerprint    Get the SSL fingerprint from a MQTT broker.
    version             Print the ESPHome version and exit.
    clean               Delete all temporary build files.
    dashboard           Create a simple web server for a dashboard.
    rename              Rename a device in YAML, compile the binary and upload it.

optional arguments:
  -h, --help            show this help message and exit
  -v, --verbose         Enable verbose ESPHome logs.
  -q, --quiet           Disable all ESPHome logs.
  -s key value, --substitution key value
                        Add a substitution
  --version             Print the ESPHome version and exit.
```

## Use local env to install EPSHome to some board:

- [Other example making ESP for SolarInverter](../inverter.md)

# USB on WSL

- https://learn.microsoft.com/en-us/windows/wsl/connect-usb
- https://github.com/dorssel/usbipd-win
- https://discourse.osmc.tv/t/lsusb-command-not-found-solved/7731

Use `powershell` admin mode:

```shell
# List
usbipd list

# Bind to WSL
usbipd bind --busid 11-1
usbipd attach --wsl --busid 11-1
```


# Working

## Test

```shell
esphome config my_proj/esp32-c6-1.yaml
esphome compile my_proj/esp32-c6-1.yaml

esphome compile my_proj/led-1.yaml
esphome compile my_proj/led-2.yaml
esphome compile my_proj/led-3.yaml

# Cant upload from WSL without USB bind
esphome upload my_proj/esp32-c6-1.yaml
```


## Start dashboard:

read:
- https://esphome.io/guides/getting_started_command_line#bonus-esphome-device-builder

Run WEB dashboard only for this project:

`esphome dashboard [-h] [--port PORT] [--address ADDRESS] [--username USERNAME] [--password PASSWORD] [--open-ui] [--socket SOCKET] configuration`

```shell
esphome dashboard my_proj/
# More
esphome dashboard --port=8080 --address=127.0.0.1 my_proj/
```

Open chrome: `http://127.0.0.1:8080/`
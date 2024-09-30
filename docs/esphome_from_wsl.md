
# Using ESP Home as local env

- https://esphome.io/guides/installing_esphome

```shell
mkdir esphome
cd esphome
# Install virt env
virtualenv --python=/usr/bin/python3 venv
# Activate
source venv/bin/activate
# Install ESPHome
pip3 install esphome

# Upgrade:
pip install --upgrade esphome

# Version
(venv) [user@aaa ESPhome]$ esphome version
Version: 2024.9.1
```

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


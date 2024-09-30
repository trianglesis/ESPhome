
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


## Use local env to install EPSHome to some board:

- [Other example making ESP for SolarInverter](../inverter.md)


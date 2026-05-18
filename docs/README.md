# Setup

## Virtualenv

```shell
cd PROJECT_DIR
virtualenv --python=/usr/local/bin/python3.14 venv --system-site-packages
#
# Use
source venv/bin/activate
source venv/bin/deactivate
#
pip install esphome
# 
cd ESPHome/
source venv/bin/activate
```

## RUN

```shell
# D:\Projects\ESP\ESPHome\ESPhome\my_proj
ls /mnt/d/Projects/ESP/ESPHome/
ls /mnt/d/Projects/ESP/ESPHome/ESPhome/my_proj/
# 
esphome dashboard --port=8080 --address=127.0.0.1 /mnt/d/Projects/ESP/ESPHome/ESPhome/my_proj/
esphome compile /mnt/d/Projects/ESP/ESPHome/ESPhome/my_proj/bedroom-co2.yaml
```


## My ESPHome project examples

Working examples:

Doc:

- [ESPHome at WSL](docs/esphome_from_wsl.md)
- [EASUN solar inverter with ESPHome ESP32 to HomeAssistant](docs/Inverter/inverter.md)
- [eightree smart plug et20](docs/eightree_tuya_smart_socket_metering/eightree_tuya.md)
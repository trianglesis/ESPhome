# ESP Home windows

Start: 
- https://esphome.io/guides/installing_esphome.html



```shell
python -m venv venv
C:\Python\Python313\python.exe -m venv venv
# Activate
venv\Scripts\activate.bat
# Install ESPHome
pip3 install esphome
# Upgrade:
pip install --upgrade esphome
```

# Working

## Test

```shell
esphome config my_proj/esp32-c6-1.yaml
esphome compile my_proj/esp32-c6-1.yaml

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
Docs:

Flash ESP 32 board to default:
- https://web.esphome.io/

- https://community.home-assistant.io/t/solar-inverter-protocol-identification/556632
- https://github.com/syssi/esphome-smg-ii
- https://github.com/syssi/esphome-smg-ii/blob/main/esp32-example.yaml


# Better install with Home Assistant via ESPHome UI

# It was fully achieved by WEB flash util and Home Assistant ESP32 addon later.


This doesn't really helped, but it's here for refference.

# Prepare local WSL (Oracle Linux 9)

## Install xdg-user-dirs

- https://wiki.archlinux.org/title/XDG_user_directories
- https://rockylinux.pkgs.org/9/rockylinux-appstream-x86_64/xdg-user-dirs-0.17-10.el9.x86_64.rpm.html

```shell
sudo dnf install xdg-user-dirs
xdg-user-dirs-update
```


### Create work dir

`/home/user/projects/ESPhome`

### Install py venv

`virtualenv --python=/usr/bin/python3 venv`


# Compile:

`esphome run /home/user/projects/ESPhome/esphome-smg-ii/esp8266-example.yaml`


## May not get ping

```log
Building .pioenvs/smg-ii/firmware.bin
esp8266_copy_factory_bin([".pioenvs/smg-ii/firmware.bin"], [".pioenvs/smg-ii/firmware.elf"])
esp8266_copy_ota_bin([".pioenvs/smg-ii/firmware.bin"], [".pioenvs/smg-ii/firmware.elf"])
======================================================================================================================= [SUCCESS] Took 61.04 seconds =======================================================================================================================
INFO Successfully compiled program.
INFO Resolving IP address of smg-ii.local
ERROR Error resolving IP address of smg-ii.local. Is it connected to WiFi?
ERROR (If this error persists, please set a static IP address: https://esphome.io/components/wifi.html#manual-ips)
ERROR Error resolving IP address: Error resolving address with mDNS: Did not respond. Maybe the device is offline., [Errno -2] Name or service not known
```



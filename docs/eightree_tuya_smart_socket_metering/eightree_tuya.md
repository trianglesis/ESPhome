# Trying to flash Tuya (Eightree) smart socket

Device: `eightree smart plug et20`

Chip!
- [RTL8720CF](eightree-smart-plug-et20.png)


- https://esphome.io/components/libretiny
- https://github.com/libretiny-eu/esphome-kickstart/releases/tag/v23.12.15
- https://upk.libretiny.eu/

Issues:
- https://github.com/esphome/issues/issues/6124


- YAML
[dummy yaml](../../my_proj/eightree_dummy.yaml)


Run:

```shell
# Test and show
esphome config /home/user/projects/ESPhome/my_proj/eightree_dummy.yaml
# Compile and save locally
esphome compile /home/user/projects/ESPhome/my_proj/eightree_dummy.yaml

# Compile and install!
esphome run /home/user/projects/ESPhome/my_proj/eightree_dummy.yaml

esphome clean /home/user/projects/ESPhome/my_proj/eightree_dummy.yaml
```
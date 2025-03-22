# External components locally saved

- https://esphome.io/components/external_components.html#example-of-local-components

Local

You can specify a local path containing external components. This is most useful when developing a component or if you want to manually control the origin of the files.

```yaml
external_components:
  - source:
      path: /copied_components

# shorthand
external_components:
  - source: my_components
```

Notice that relative paths are supported, so you can enter my_components as the source path and then ESPHome will load components from a my_components folder in the same folder where your YAML configuration is.
Example of local components

Given the above example of my_components, the folder structure must look like:

<CONFIG_DIR>
├── node1.yaml
├── node2.yaml
└── my_components
    ├── my_component1
    │   ├── __init__.py
    │   ├── component1.cpp
    │   ├── component1.h
    │   └── sensor.py
    └── my_component2
        ├── __init__.py
        ├── component2.cpp
        ├── component2.h
        └── switch.py

# Git PRs as external components

- https://stackoverflow.com/a/30584951

Use PRs as external components to test:

Clone repo into `my_components`

```shell
git clone https://github.com/stas-sl/esphome-sound-level-meter.git
```
Get PR:

```shell
git fetch origin pull/39/head:pr_39
```

```shell
$ cd esphome-sound-level-meter/
$ git fetch origin pull/39/head:pr_39
remote: Enumerating objects: 20, done.
remote: Counting objects: 100% (5/5), done.
remote: Total 20 (delta 4), reused 4 (delta 4), pack-reused 15 (from 1)
Unpacking objects: 100% (20/20), 5.01 KiB | 395.00 KiB/s, done.
From https://github.com/stas-sl/esphome-sound-level-meter
 * [new ref]         refs/pull/39/head -> pr_39
```
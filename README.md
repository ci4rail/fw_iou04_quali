# fw-esp-iou-default
Default firmware for ESPS2 based IOUs (io4edge modules).

This repo is intended to run under [gitpod](https://gitpod.io/).

See this [Readme](https://github.com/ci4rail/gitpod-esp-image#how-to-use-repos-using-this-gitpod-esp-image) on how to setup gitpod and the ESP.

Once you have setup gitpod, start the workspace:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/ci4rail/fw_esp_iou_default)


## Build/Flash/Monitor

In your gitpod workspace you can use the following commands
```bash
# configure local files from io4edge_api submodule (only for development purposes)
make configure-io4edge_api-dev 
# configure to use io4edge_api from upstream repositry with given version number
make configure-io4edge_api-prod 
make build
make clean
make fullclean
make reconfigure
make flash
make monitor
```

Note: The control keys in `idf.py monitor` have been reassigned to avoid conflicts with browser key bindings. Important key sequences:
* Exit: `CTRL+G` followed by `CTRL+X`
* Flash: `CTRL+G` followed by `CTRL+U`
* Reset: `CTRL+G` followed by `CTRL+R`


## CI Pipeline

Create a new secret https://github.com/ci4rail/fw_esp_iou_default/settings/secrets/actions. Name =`PAT_TOKEN` value= see bitwarden entry `yoda fw-repo-ci`

Build pipeline starts when a tag is pushed with that matched `"[0-9]+.[0-9]+.[0-9]+*"`.

Example
```
git tag -a 0.0.1 -m "initial"
git push --tags
```
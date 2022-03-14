all: build

build:
	idf.py build

# shortcuts for development
dev: configure-io4edge_api-dev build

setup: fullclean target-esp32-s2 configure-io4edge_api-dev build

full: fullclean target-esp32-s2 configure-io4edge_api-dev build flash

# Use local io4edge_api files from 'dev/' directory. Useful for development.
configure-io4edge_api-dev:
	idf.py -DESP_IO4EDGE_IO4EDGE_API_DEV=true reconfigure

# Use upstream api definitions from 'github.com/ci4rail/io4edge_api' repo with the specified versions.
configure-io4edge_api-prod:
	idf.py -DESP_IO4EDGE_IO4EDGE_API_DEV=false reconfigure

flash:
	idf.py flash -b 921600

monitor:
	idf.py monitor

menuconfig:
	idf.py menuconfig

target-esp32-s2:
	idf.py set-target esp32s2

clean:
	idf.py clean

reconfigure:
	idf.py reconfigure

fullclean:
	idf.py fullclean

.PHONY: all build dev setup full flash clean fullclean reconfigure menuconfig target-esp32 monitor configure-io4edge_api-dev configure-io4edge_api-prod

# ESP-IDF Ruuvi tag advertising  data receiver

## Overview

This application receives and decodes advertisement data transmitted by a [Ruuvi tag](https://ruuvi.com/).

Current version supports Data format 3 (RAWv1).

## Hardware target

The hardware target is an [ESP32-DevKitC](https://www.espressif.com/en/products/devkits/esp32-devkitc/overview) with an ESP32-WROVER-B module.

## Reference documents

For reference documents about Bluetooth LE, Ruuvi tag and ESP-IDF, check the source code.

## Build and Flash

To build, flash and monitor the output from the application, run:

```
idp.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

```
...
I (0) cpu_start: Starting scheduler on APP CPU.
I (537) RUUVITAGREC: RuuviTagRec 0.4.1
I (577) BTDM_INIT: BT controller compile version [1ee1530]
I (577) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (677) phy: phy_version: 4180, cb3948e, Sep 12 2019, 16:39:13, 0, 0
I (1047) RUUVITAGREC: Gap register OK
I (1047) RUUVITAGREC: Event: SCAN_PARAM_SET_COMPLETE
I (1047) RUUVITAGREC: Starting scan...
I (1057) RUUVITAGREC: Event: SCAN_START_COMPLETE
I (2057) RUUVITAGREC: Event: SCAN_RESULT
I (2057) RUUVITAGREC: Result: SEARCH_INQ_RES
I (2057) RUUVITAGREC: Frame received:
I (2057) RUUVITAGREC: 02 01 06 11 ff 99 04 03 61 1b 29 bf 4f 00 05 00 
I (2067) RUUVITAGREC: 02 03 e1 0b ad 
I (2067) RUUVITAGREC: Ruuvi: humidity: 48.50 - temperature: 27.41 - pressure: 989.75
I (2077) RUUVITAGREC:        accel: 5, 2, 993 - battery: 2.99
I (3057) RUUVITAGREC: Event: SCAN_RESULT
I (3057) RUUVITAGREC: Result: SEARCH_INQ_RES
I (3057) RUUVITAGREC: Frame received:
I (3057) RUUVITAGREC: 02 01 06 11 ff 99 04 03 61 1b 29 bf 4f 00 03 00 
I (3067) RUUVITAGREC: 04 03 e0 0b ad 
I (3067) RUUVITAGREC: Ruuvi: humidity: 48.50 - temperature: 27.41 - pressure: 989.75
I (3077) RUUVITAGREC:        accel: 3, 4, 992 - battery: 2.99
I (4057) RUUVITAGREC: Event: SCAN_RESULT
I (4057) RUUVITAGREC: Result: SEARCH_INQ_RES
I (4057) RUUVITAGREC: Frame received:
I (4057) RUUVITAGREC: 02 01 06 11 ff 99 04 03 61 1b 29 bf 4f 00 06 00 
I (4067) RUUVITAGREC: 01 03 e3 0b ad 
I (4067) RUUVITAGREC: Ruuvi: humidity: 48.50 - temperature: 27.41 - pressure: 989.75
I (4077) RUUVITAGREC:        accel: 6, 1, 995 - battery: 2.99
```
 

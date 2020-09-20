# ESP-IDF Ruuvi tag advertising  data receiver

## Overview

This application receives and decodes advertisement data transmitted by a [Ruuvi tag](https://ruuvi.com/).

Current version supports data format 3 (RAWv1) and data format 5 (RAWv2).

## Hardware target

The hardware target is an [ESP32-DevKitC](https://www.espressif.com/en/products/devkits/esp32-devkitc/overview) with an ESP32-WROVER-B module.

## Reference documents

For reference documents about Bluetooth LE, Ruuvi tag and ESP-IDF, check the source code.

## Build and Flash

To build, flash and monitor the output from the application, run:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

### RAWv1

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
 
### RAWv2

```
I (0) cpu_start: Starting scheduler on APP CPU.
I (539) RUUVITAGREC: RuuviTagRec 0.5.6
I (579) BTDM_INIT: BT controller compile version [1ee1530]
I (579) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (689) phy: phy_version: 4180, cb3948e, Sep 12 2019, 16:39:13, 0, 0
I (1049) RUUVITAGREC: Gap register OK
I (1059) RUUVITAGREC: Event: SCAN_PARAM_SET_COMPLETE
I (1059) RUUVITAGREC: Starting scan...
I (1059) RUUVITAGREC: Event: SCAN_START_COMPLETE
I (2059) RUUVITAGREC: Event: SCAN_RESULT
I (2059) RUUVITAGREC: Result: SEARCH_INQ_RES
I (2059) RUUVITAGREC: Frame received:
I (2069) RUUVITAGREC: 02 01 06 1b ff 99 04 05 15 84 5e 71 bf c0 00 08 
I (2069) RUUVITAGREC: ff f4 03 e0 97 f6 78 12 22 cf e4 92 01 7f 19 
I (2079) RUUVITAGREC: Ruuvi RAWv2: humidity: 60.44 - temperature: 27.54 - pressure: 990.88
I (2089) RUUVITAGREC:              accel: 0.08, -0.12, 9.92 - voltage: 2.815 - TX: 4
I (2099) RUUVITAGREC:              movements: 120 - sequence: 4642 - MAC: cf:e4:92:01:7f:19
I (4059) RUUVITAGREC: Event: SCAN_RESULT
I (4059) RUUVITAGREC: Result: SEARCH_INQ_RES
I (4059) RUUVITAGREC: Frame received:
I (4069) RUUVITAGREC: 02 01 06 1b ff 99 04 05 15 84 5e 76 bf c0 00 0c 
I (4069) RUUVITAGREC: ff f8 03 e4 97 f6 78 12 23 cf e4 92 01 7f 19 
I (4079) RUUVITAGREC: Ruuvi RAWv2: humidity: 60.46 - temperature: 27.54 - pressure: 990.88
I (4089) RUUVITAGREC:              accel: 0.12, -0.08, 9.96 - voltage: 2.815 - TX: 4
I (4099) RUUVITAGREC:              movements: 120 - sequence: 4643 - MAC: cf:e4:92:01:7f:19
I (5059) RUUVITAGREC: Event: SCAN_RESULT
I (5059) RUUVITAGREC: Result: SEARCH_INQ_RES
I (5059) RUUVITAGREC: Frame received:
I (5069) RUUVITAGREC: 02 01 06 1b ff 99 04 05 15 84 5e 76 bf c1 00 04 
I (5069) RUUVITAGREC: ff f8 03 ec 97 f6 78 12 24 cf e4 92 01 7f 19 
I (5079) RUUVITAGREC: Ruuvi RAWv2: humidity: 60.46 - temperature: 27.54 - pressure: 990.89
I (5089) RUUVITAGREC:              accel: 0.04, -0.08, 10.04 - voltage: 2.815 - TX: 4
I (5099) RUUVITAGREC:              movements: 120 - sequence: 4644 - MAC: cf:e4:92:01:7f:19
I (6059) RUUVITAGREC: Event: SCAN_RESULT
I (6059) RUUVITAGREC: Result: SEARCH_INQ_RES
I (6059) RUUVITAGREC: Frame received:
I (6069) RUUVITAGREC: 02 01 06 1b ff 99 04 05 15 84 5e 76 bf c1 00 08 
I (6069) RUUVITAGREC: ff f4 03 e4 97 f6 78 12 25 cf e4 92 01 7f 19 
I (6079) RUUVITAGREC: Ruuvi RAWv2: humidity: 60.46 - temperature: 27.54 - pressure: 990.89
I (6089) RUUVITAGREC:              accel: 0.08, -0.12, 9.96 - voltage: 2.815 - TX: 4
I (6099) RUUVITAGREC:              movements: 120 - sequence: 4645 - MAC: cf:e4:92:01:7f:19
```

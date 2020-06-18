# ESP-IDF Ruuvi tag advertising  data receiver

## Overview

This application receives and decodes advertisement data transmitted by a [Ruuvi tag](https://ruuvi.com/).

## Build and Flash

To build, flash and monitor the output from the application, run:

```
idp.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

```
...
I (0) cpu_start: App cpu up.
I (452) heap_init: Initializing. RAM available for dynamic allocation:
I (459) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM
I (465) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM
I (471) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM
I (477) heap_init: At 3FFBDB5C len 00000004 (0 KiB): DRAM
I (483) heap_init: At 3FFC88F8 len 00017708 (93 KiB): DRAM
I (489) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (496) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (502) heap_init: At 40093120 len 0000CEE0 (51 KiB): IRAM
I (508) cpu_start: Pro cpu start user code
I (526) spi_flash: detected chip: generic
I (527) spi_flash: flash io: dio
I (527) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (613) BTDM_INIT: BT controller compile version [1ee1530]
I (613) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (713) phy: phy_version: 4180, cb3948e, Sep 12 2019, 16:39:13, 0, 0
I (1073) RUUVITAGREC: Gap register OK
I (1083) RUUVITAGREC: Starting scan...
I (4973) RUUVITAGREC: Frame received:
I (4973) RUUVITAGREC: 02 01 06 11 ff 99 04 03 72 16 1f bf e6 00 0f 00 
I (4973) RUUVITAGREC: 06 03 e1 0b 9b 
I (5963) RUUVITAGREC: Frame received:
I (5973) RUUVITAGREC: 02 01 06 11 ff 99 04 03 72 16 1f bf e6 00 11 00 
I (5973) RUUVITAGREC: 06 03 e3 0b a1 
I (6963) RUUVITAGREC: Frame received:
I (6973) RUUVITAGREC: 02 01 06 11 ff 99 04 03 72 16 1f bf e6 00 0f 00 
I (6973) RUUVITAGREC: 06 03 e3 0b 9b 
I (7963) RUUVITAGREC: Frame received:
I (7973) RUUVITAGREC: 02 01 06 11 ff 99 04 03 72 16 1f bf e6 00 0e 00 
I (7973) RUUVITAGREC: 05 03 e2 0b 9b 
I (8963) RUUVITAGREC: Frame received:
I (8973) RUUVITAGREC: 02 01 06 11 ff 99 04 03 72 16 1f bf e6 00 0d 00 
I (8973) RUUVITAGREC: 07 03 e1 0b 9b 
```
 

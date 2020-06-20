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
I (0) cpu_start: Starting scheduler on APP CPU.
I (537) RUUVITAGREC: RuuviTagRec 0.2.1
I (577) BTDM_INIT: BT controller compile version [1ee1530]
I (577) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (687) phy: phy_version: 4180, cb3948e, Sep 12 2019, 16:39:13, 0, 0
I (1037) RUUVITAGREC: Gap register OK
I (1047) RUUVITAGREC: Event: SCAN_PARAM_SET_COMPLETE
I (1047) RUUVITAGREC: Starting scan...
I (1057) RUUVITAGREC: Event: SCAN_START_COMPLETE
I (3557) RUUVITAGREC: Event: SCAN_RESULT
I (3557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (3557) RUUVITAGREC: Frame received:
I (3567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 08 00 
I (3567) RUUVITAGREC: 01 03 e3 0b a1 
I (4557) RUUVITAGREC: Event: SCAN_RESULT
I (4557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (4557) RUUVITAGREC: Frame received:
I (4567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 06 00 
I (4567) RUUVITAGREC: 00 03 e5 0b a7 
I (5557) RUUVITAGREC: Event: SCAN_RESULT
I (5557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (5557) RUUVITAGREC: Frame received:
I (5567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 06 ff 
I (5567) RUUVITAGREC: ff 03 e4 0b a1 
I (6557) RUUVITAGREC: Event: SCAN_RESULT
I (6557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (6557) RUUVITAGREC: Frame received:
I (6567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 08 00 
I (6567) RUUVITAGREC: 01 03 e0 0b a1 
I (7557) RUUVITAGREC: Event: SCAN_RESULT
I (7557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (7557) RUUVITAGREC: Frame received:
I (7567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 08 00 
I (7567) RUUVITAGREC: 02 03 e1 0b a1 
I (8557) RUUVITAGREC: Event: SCAN_RESULT
I (8557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (8557) RUUVITAGREC: Frame received:
I (8567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 07 00 
I (8567) RUUVITAGREC: 03 03 e1 0b a1 
I (9557) RUUVITAGREC: Event: SCAN_RESULT
I (9557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (9557) RUUVITAGREC: Frame received:
I (9567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 07 00 
I (9567) RUUVITAGREC: 02 03 e0 0b a7 
I (10557) RUUVITAGREC: Event: SCAN_RESULT
I (10557) RUUVITAGREC: Result: SEARCH_INQ_RES
I (10557) RUUVITAGREC: Frame received:
I (10567) RUUVITAGREC: 02 01 06 11 ff 99 04 03 64 1a 37 c2 15 00 06 00 
I (10567) RUUVITAGREC: 03 03 df 0b ad 
```
 

/**
 * This file is part of RuuviTagRec.
 *
 * RuuviTagRec is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RuuviTagRec is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RuuviTagRec.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2020 Pascal Bodin
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs_flash.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_defs.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

// Minimal advertising data length we are waiting for:
// Flags: 3 bytes
// Manufacturer Data: 4 bytes
#define MINIMAL_ADV_LENGTH 7
// For Flags AD structure.
#define FLAGS_LENGTH 2
#define FLAGS_TYPE 0x01
// For Manufacturer Data structure.
#define MD_TYPE 0xff
#define MD_CI_CODE 0x9904

// Ruuvi data header bytes.
#define RUUVI_RAWV1 0x03
#define RUUVI_RAWV2 0x05

// Ruuvi data length.
#define RUUVI_RAWV1_LENGTH 14
#define RUUVI_RAWV2_LENGTH 24

// 1000 ms.
#define SCAN_INTERVAL 0x0640
// 500 ms.
#define SCAN_WINDOW 0x0320

#define APP_VERSION "RuuviTagRec 0.4.0"

static const char APP_TAG[] = "RUUVITAGREC";

static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

static esp_ble_scan_params_t ble_scan_params = {
    .scan_type              = BLE_SCAN_TYPE_PASSIVE,
    .own_addr_type          = BLE_ADDR_TYPE_PUBLIC,
    .scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_interval          = SCAN_INTERVAL,
    .scan_window            = SCAN_WINDOW,
    .scan_duplicate         = BLE_SCAN_DUPLICATE_DISABLE
};

static void check_ruuvi_tag_data(uint8_t *data_ptr, uint8_t data_length, uint8_t remaining_length) {

	if (remaining_length < data_length) {
		ESP_LOGI(APP_TAG, "Ruuvi: data too short - %d - %d", data_length, remaining_length);
		return;
	}
	// Check header byte.
	if (*data_ptr == RUUVI_RAWV1) {
		// Check length.
		if (remaining_length < RUUVI_RAWV1_LENGTH) {
			ESP_LOGI(APP_TAG, "Ruuvi: RAWv1 data too short");
			return;
		}
		// Get humidity.
		data_ptr++;
		float humidity = (float)(*data_ptr) / 2.0;
		// Get temperature.
		data_ptr++;
		float temperature = (*data_ptr);
		if (temperature < 0)
			temperature -= (float)(*(data_ptr + 1)) / 100.0;
		else
			temperature += (float)(*(data_ptr + 1)) / 100.0;
		// Get pressure.
		data_ptr += 2;
		float pressure = (float)(((uint16_t)(*data_ptr << 8) + (*(data_ptr + 1)))) / 100.0 + 500.0;
		// Get X acceleration.
		data_ptr += 2;
		int16_t accel_x = (int16_t)(*data_ptr << 8) + *(data_ptr + 1);
		// Get Y acceleration.
		data_ptr += 2;
		int16_t accel_y = (int16_t)(*data_ptr << 8) + *(data_ptr + 1);
		// Get Z acceleration.
		data_ptr += 2;
		int16_t accel_z = (int16_t)(*data_ptr << 8) + *(data_ptr + 1);
		// Get battery voltage.
		data_ptr += 2;
		float voltage = (float)(((uint16_t)(*data_ptr << 8) + (*(data_ptr + 1)))) / 1000.0;
		// Display.
		ESP_LOGI(APP_TAG, "Ruuvi: humidity: %.2f - temperature: %.2f - pressure: %.2f", humidity, temperature, pressure);
		ESP_LOGI(APP_TAG, "       accel: %d, %d, %d - battery: %.2f", accel_x, accel_y, accel_z, voltage);
	}
}

static void check_ruuvi_tag_adv(uint8_t *buffer_ptr, uint8_t buffer_length) {

	// Format of advertising data is described page 1392 of
	// BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part C.
	//
    // We are waiting for data containing two AD structures, the first one
	// of type 0x01 (Flags) and the second one of type 0xff (Manufacturer Data).
	//
	// Flags type is defined in BLUETOOTH SPECIFICATION Version 4.0, Vol. 3,
	// Part C, Section 18.1. Manufacturer Data type is defined in section 18.11.
	//
	// Format of Manufacturer Data is described here:
	// https://github.com/ruuvi/ruuvi-sensor-protocols/blob/master/broadcast_formats.md

	// Do we have minimal required size: Flags + start of Manufacturer Data ?
	if (buffer_length < MINIMAL_ADV_LENGTH) {
		ESP_LOGI(APP_TAG, "AD: message too short");
		return;
	}
	uint8_t *buffer_index = buffer_ptr;
	// Flags.
	// Check length.
	if (*buffer_index != FLAGS_LENGTH) {
		ESP_LOGI(APP_TAG, "AD: no Flags structure");
		return;
	}
	// Check type.
	buffer_index++;
	if (*buffer_index != FLAGS_TYPE) {
		ESP_LOGI(APP_TAG, "AD: no Flags type");
		return;
	}
	// Jump over data
	buffer_index += 2;
	// Manufacturer Data.
	// Get length.
	uint8_t md_length = *buffer_index;
	// Check type.
	buffer_index++;
	if (*buffer_index != MD_TYPE) {
		ESP_LOGI(APP_TAG, "AD: no manufacturer data type");
		return;
	}
	// Check Company Identifier code.
	buffer_index++;
	uint16_t company_identifier = (*buffer_index << 8) + *(buffer_index + 1);
	if (company_identifier != MD_CI_CODE) {
		ESP_LOGI(APP_TAG, "AD: no Ruuvi identifier");
		return;
	}
	// Check Ruuvi tag data.
	buffer_index += 2;

	// 3 = Type byte + Company Identifier code.
	check_ruuvi_tag_data(buffer_index, md_length, buffer_length - 3);
}

static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    esp_err_t err;

    switch (event) {
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
    	ESP_LOGI(APP_TAG, "Event: SCAN_PARAM_SET_COMPLETE");
        // The unit of the duration is second, 0 means scan permanently.
        uint32_t duration = 0xffff;
        esp_ble_gap_start_scanning(duration);
        ESP_LOGI(APP_TAG, "Starting scan...");
        break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT:
    	ESP_LOGI(APP_TAG, "Event: SCAN_RESULT");
        switch (param->scan_rst.search_evt) {
        case ESP_GAP_SEARCH_INQ_RES_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_INQ_RES");
            ESP_LOGI(APP_TAG, "Frame received:");
            ESP_LOG_BUFFER_HEX(APP_TAG, param->scan_rst.ble_adv, param->scan_rst.adv_data_len);
            // Frame example: 02 01 06 11 ff 99 04 03 6f 17 11 bf 51 00 0c 00 04 03 dd 0b a1
            check_ruuvi_tag_adv(param->scan_rst.ble_adv, param->scan_rst.adv_data_len);
        	break;
        case ESP_GAP_SEARCH_INQ_CMPL_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_INQ_CMPL");
        	break;
        case ESP_GAP_SEARCH_DISC_RES_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_DISC_RES");
        	break;
        case ESP_GAP_SEARCH_DISC_BLE_RES_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_DISC_BLE_RES");
        	break;
        case ESP_GAP_SEARCH_DISC_CMPL_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_DISC_CMPL");
        	break;
        case ESP_GAP_SEARCH_DI_DISC_CMPL_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_DI_DISC_CMPL");
        	break;
        case ESP_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_CANCEL_CMPL");
        	break;
        case ESP_GAP_SEARCH_INQ_DISCARD_NUM_EVT:
        	ESP_LOGI(APP_TAG, "Result: SEARCH_INQ_DISCARD_NUM");
        	break;
        default:
        	ESP_LOGI(APP_TAG, "Result: unknown value - %d", param->scan_rst.search_evt);
        	break;
        }
        break;
    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
    	ESP_LOGI(APP_TAG, "Event: SCAN_START_COMPLETE");
    	err = param->scan_start_cmpl.status;
    	if (err != ESP_BT_STATUS_SUCCESS) {
    		ESP_LOGE(APP_TAG, "Scan start failed: %s", esp_err_to_name(err));
    	}
    	break;
    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
    	ESP_LOGI(APP_TAG, "Event: SCAN_STOP_COMPLETE");
    	err = param->scan_stop_cmpl.status;
        if (err != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(APP_TAG, "Scan stop failed: %s", esp_err_to_name(err));
        }
        break;
    default:
    	ESP_LOGI(APP_TAG, "Event: %d", event);
        break;
    }
}

/**
 *
 */
void app_main(void)
{
	ESP_LOGI(APP_TAG, APP_VERSION);

    esp_err_t status;

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    esp_bluedroid_init();
    esp_bluedroid_enable();

    if ((status = esp_ble_gap_register_callback(esp_gap_cb)) != ESP_OK) {
        ESP_LOGE(APP_TAG, "Gap register error: %s", esp_err_to_name(status));
    } else {
    	ESP_LOGI(APP_TAG, "Gap register OK");
    }

    if (status == ESP_OK) {
    	esp_ble_gap_set_scan_params(&ble_scan_params);
    }
}

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

#include "esp_log.h"

#include "app.h"
#include "ruuvi_tag.h"

void check_ruuvi_tag_data(uint8_t *data_ptr, uint8_t manu_data_length, uint8_t data_length) {

	if (data_length < manu_data_length) {
		ESP_LOGI(APP_TAG, "Ruuvi: data too short - %d - %d", manu_data_length, data_length);
		return;
	}
	// Check header byte.
	if (*data_ptr == RUUVI_RAWV1) {
		// Check length.
		if (data_length < RUUVI_RAWV1_LENGTH) {
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
		ESP_LOGI(APP_TAG, "Ruuvi RAWv1: humidity: %.2f - temperature: %.2f - pressure: %.2f", humidity, temperature, pressure);
		ESP_LOGI(APP_TAG, "       accel: %d, %d, %d - battery: %.2f", accel_x, accel_y, accel_z, voltage);
		return;
	}

	// At this stage, we have another data format.
	if (*data_ptr == RUUVI_RAWV2) {
		// Check length.
		if (data_length < RUUVI_RAWV2_LENGTH) {
			ESP_LOGI(APP_TAG, "Ruuvi: RAWv2 data too short");
			return;
		}
		// Get temperature.
		data_ptr++;
		float temperature = (float)((int16_t)(*data_ptr << 8) + *(data_ptr + 1)) * 0.005;
		// Get humidity.
		data_ptr += 2;
		float humidity = (float)((uint16_t)(*data_ptr << 8) + *(data_ptr + 1)) * 0.0025;
		// Get pressure.
		data_ptr += 2;
		float pressure = (float)(((uint16_t)(*data_ptr << 8) + *(data_ptr + 1)) + 50000) / 100.0;
		// Get X acceleration.
		data_ptr += 2;
		float accel_x = (float)((int16_t)(*data_ptr << 8) + *(data_ptr + 1)) / 100.0;
		// Get Y acceleration.
		data_ptr += 2;
		float accel_y = (float)((int16_t)(*data_ptr << 8) + *(data_ptr + 1)) / 100.0;
		// Get Z acceleration.
		data_ptr += 2;
		float accel_z = (float)((int16_t)(*data_ptr << 8) + *(data_ptr + 1)) / 100.0;
		// Get battery voltage.
		data_ptr += 2;
		float voltage = (float)((uint16_t)(*data_ptr << 3) + (*(data_ptr + 1) >> 5)) / 1000.0 + 1.6;
		// Get TX power.
		int8_t power = (*(data_ptr + 1) & 0x1f) * 2 - 40;
		// Get movement counter.
		data_ptr += 2;
		uint8_t counter = *data_ptr;
		// Get sequence number.
		data_ptr++;
		uint16_t sequence = ((uint16_t)(*data_ptr << 8) + *(data_ptr + 1));
		// MAC address is in following six bytes.
		data_ptr += 2;
		//
		ESP_LOGI(APP_TAG, "Ruuvi RAWv2: humidity: %.2f - temperature: %.2f - pressure: %.2f", humidity,
				temperature, pressure);
		ESP_LOGI(APP_TAG, "             accel: %.2f, %.2f, %.2f - voltage: %.3f - TX: %d",
				accel_x, accel_y, accel_z, voltage, power);
		ESP_LOGI(APP_TAG, "             movements: %u - sequence: %u - MAC: %02x:%02x:%02x:%02x:%02x:%02x",
				counter, sequence, *data_ptr, *(data_ptr + 1), *(data_ptr + 2), *(data_ptr + 3),
			    *(data_ptr + 4), *(data_ptr + 5));
		return;
	}
}

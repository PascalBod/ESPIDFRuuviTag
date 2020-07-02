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

#ifndef MAIN_RUUVI_TAG_H_
#define MAIN_RUUVI_TAG_H_

// Ruuvi data header bytes.
#define RUUVI_RAWV1 0x03
#define RUUVI_RAWV2 0x05

// Ruuvi data length.
#define RUUVI_RAWV1_LENGTH 14
#define RUUVI_RAWV2_LENGTH 24

/**
 * Considers that the input buffer contains some advertising data broadcasted by a
 * Ruuvi tag, checks the format version, extracts data accordingly and displays in
 * in a trace message.
 *
 * Parameters:
 * - data_ptr: pointer to input buffer. Must start with data format byte
 * - manu_data_length: length of manufacturer data, according to AD structure,
 *   excluding type and Company Identifier
 * - data_length: length of input buffer
 * Returned value: none
 */
void check_ruuvi_tag_data(uint8_t *data_ptr, uint8_t manu_data_length, uint8_t data_length);

#endif /* MAIN_RUUVI_TAG_H_ */

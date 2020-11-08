/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if HAS_CUTTER

#include "../gcode.h"
#include "../../module/stepper.h"

/**
 * Laser:
 *  M6 - Laser mode
 *
 * Parameters:
 *  V<mode> - Set mode. V0 = test, V1 = run, others = no change
 */
void GcodeSuite::M6(void) {
  if (parser.seenval('V')) {
    const uint8_t laser_mode = parser.value_byte();

    planner.synchronize();   // Wait for previous movement commands (G0/G0/G2/G3) to complete before mode

    switch (laser_mode) {
      case 0: {
        // Enter test mode
        OUT_WRITE(LASER_RUN_TEST_MODE_PIN, LOW);

        // Wait for mode change
        dwell(50);
        break;
      }
      case 1: {
        // Enter run mode
        OUT_WRITE(LASER_RUN_TEST_MODE_PIN, HIGH);

        // Wait for mode change
        dwell(50);
        break;
      }
      default: {
        /* Ignore */
        break;
      }
    }
  }
}

#endif // HAS_CUTTER

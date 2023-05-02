/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/bus.h"
#include "drivers/bus_i2c_busdev.h"
#include "drivers/bus_spi.h"

bool busWriteRegister(const busDevice_t *busdev, uint8_t reg, uint8_t data)
{
    switch (busdev->bustype) {
    case BUSTYPE_SPI:
        return spiBusWriteRegister(busdev, reg & 0x7f, data);
    case BUSTYPE_I2C:
        return i2cBusWriteRegister(busdev, reg, data);
    }
    return false;
}

bool busReadRegisterBuffer(const busDevice_t *busdev, uint8_t reg, uint8_t *data, uint8_t length)
{
    switch (busdev->bustype) {
    case BUSTYPE_SPI:
        return spiBusReadRegisterBuffer(busdev, reg | 0x80, data, length);
    case BUSTYPE_I2C:
        return i2cBusReadRegisterBuffer(busdev, reg, data, length);
    }
    return false;
}

uint8_t busReadRegister(const busDevice_t *busdev, uint8_t reg)
{
    switch (busdev->bustype) {
    case BUSTYPE_SPI:
        return spiBusReadRegister(busdev, reg & 0x7f);
    case BUSTYPE_I2C:
        return i2cBusReadRegister(busdev, reg);
    }
    return false;
}

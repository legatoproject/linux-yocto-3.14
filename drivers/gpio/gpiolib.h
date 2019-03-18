/*
 * Internal GPIO functions.
 *
 * Copyright (C) 2013, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef GPIOLIB_H
#define GPIOLIB_H

#include <linux/err.h>
#include <linux/device.h>

struct gpio_desc {
	struct gpio_chip	*chip;
	unsigned long		flags;
/* flag symbols are bit numbers */
#define FLAG_REQUESTED		0
#define FLAG_IS_OUT		1
#define FLAG_EXPORT		2	/* protected by sysfs_lock */
#define FLAG_SYSFS		3	/* exported via /sys/class/gpio/control */
#define FLAG_TRIG_FALL		4	/* trigger on falling edge */
#define FLAG_TRIG_RISE		5	/* trigger on rising edge */
#define FLAG_ACTIVE_LOW		6	/* value has active low */
#define FLAG_OPEN_DRAIN		7	/* Gpio is open drain type */
#define FLAG_OPEN_SOURCE	8	/* Gpio is open source type */
#define FLAG_USED_AS_IRQ	9	/* GPIO is connected to an IRQ */
#define FLAG_IS_UP		10
#ifdef CONFIG_SIERRA_EXT_GPIO
#define FLAG_RING_INDIC		11	/* GPIO is Ring Indicator RI */
#define FLAG_DTR		12	/* GPIO is uart DTR */
#define FLAG_DCD		13	/* GPIO is uart DCD */
#define FLAG_DSR		14	/* GPIO is uart DSR */
#endif

#define ID_SHIFT		16	/* add new flags before this one */

#define GPIO_FLAGS_MASK		((1 << ID_SHIFT) - 1)
#define GPIO_TRIGGER_MASK	(BIT(FLAG_TRIG_FALL) | BIT(FLAG_TRIG_RISE))

#ifdef CONFIG_SIERRA_EXT_GPIO
	u16	bit_in_mask;		/* bit to test if bitmask is valid */
	u16	owned_by_app_proc;	/* function: APP or BUSY/MODEM */
#endif

#ifdef CONFIG_DEBUG_FS
	const char		*label;
#endif
};

#ifdef CONFIG_SIERRA_EXT_GPIO
struct class *gpio_class_get(void);
#endif

/**
 * struct acpi_gpio_info - ACPI GPIO specific information
 * @gpioint: if %true this GPIO is of type GpioInt otherwise type is GpioIo
 * @active_low: in case of @gpioint, the pin is active low
 */
struct acpi_gpio_info {
	bool gpioint;
	bool active_low;
};

#ifdef CONFIG_ACPI
void acpi_gpiochip_add(struct gpio_chip *chip);
void acpi_gpiochip_remove(struct gpio_chip *chip);

struct gpio_desc *acpi_get_gpiod_by_index(struct device *dev, int index,
					  struct acpi_gpio_info *info);
#else
static inline void acpi_gpiochip_add(struct gpio_chip *chip) { }
static inline void acpi_gpiochip_remove(struct gpio_chip *chip) { }

static inline struct gpio_desc *
acpi_get_gpiod_by_index(struct device *dev, int index,
			struct acpi_gpio_info *info)
{
	return ERR_PTR(-ENOSYS);
}
#endif

#endif /* GPIOLIB_H */

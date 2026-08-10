/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2019, 2021 The Linux Foundation. All rights reserved.
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _CAM_SENSOR_NOTHING_H_
#define _CAM_SENSOR_NOTHING_H_

#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/module.h>
#include <linux/irqreturn.h>
#include <linux/iommu.h>
#include <linux/timer.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-subdev.h>
#include "cam_debug_util.h"

#define MAX_SENSOR_NAME_LENGTH 32
#define MAX_SN_LENGTH 64
#define MAX_SENSOR_NUM 8

#define NT_CAM_DEV_NAME "nt_cam_dev"

struct cam_sensor_ctrl_t;

struct cam_nt_i2c_info {
	uint16_t   slave_addr;
	uint16_t   is_write;
	uint32_t   reg_addr;
	uint32_t   reg_data;
	uint32_t   reg_addr_type;
	uint32_t   reg_data_type;
	uint16_t   status;
};

enum cam_nt_cmd_type {
	NT_CAMERA_INFO,
	NT_CAMERA_VENDORID,
	NT_CAMERA_SOIS_POWER_UP,
	NT_CAMERA_SOIS_POWER_DOWN,
	NT_CMD_MAX
};

enum cam_nt_camera_type {
	NT_CAMERA_MAIN,
	NT_CAMERA_FRONT,
	NT_CAMERA_TELE,
	NT_CAMERA_DEPTH,
	NT_CAMERA_MAX
};

enum cam_nt_err_code {
	NT_CAM_PROBE_OK,
	NT_CAM_PROBE_ERR,
	NT_CAM_POWER_ERR,
	NT_CAM_I2C_ERR,
	NT_CAM_INIT_ERR,
	NT_CAM_ACTUATOR_ERR,
	NT_CAM_FLASH_ERR,
	NT_CAM_ERR_MAX
};

struct cam_nt_camera_info {
	uint16_t                  camera_id;
	enum cam_nt_camera_type   camera_type;
	uint32_t                  vendor_id;
	uint8_t                   camera_sn[MAX_SN_LENGTH];
	uint8_t                   sensor_name[MAX_SENSOR_NAME_LENGTH];
};

struct cam_nt_sois_power {
	struct regulator   *ois_rgltr;
	uint32_t min_rgltr_uv;
	uint32_t max_rgltr_uv;
	uint32_t count;
};

struct cam_nt_control_info {
	uint32_t cmd;
	uint64_t handle;
};

#define NT_DEV_CONTROL_CMD _IOWR('N', 0x0, struct cam_nt_control_info)

static uint8_t cam_vendor_id[NT_CAMERA_MAX];

void cam_nt_driver_init(void);

int cam_nt_do_i2c_info(struct cam_sensor_ctrl_t *sctrl);

extern void cam_nt_driver_errcode(int id, enum cam_nt_err_code err_code);

void cam_nt_sctrl_save(struct cam_sensor_ctrl_t *sctrl, int index);

void cam_nt_get_ois_power(struct cam_sensor_ctrl_t *s_ctrl);

#endif /* _CAM_SENSOR_NOTHING_H_ */

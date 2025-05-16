#
# Copyright (C) 2024 The Android Open Source Project
# Copyright (C) 2024 SebaUbuntu's TWRP device tree generator
#
# SPDX-License-Identifier: Apache-2.0
#

PRODUCT_MAKEFILES := \
    $(LOCAL_DIR)/zmooth_twrp.mk

COMMON_LUNCH_CHOICES := \
    zmooth_twrp-user \
    zmooth_twrp-userdebug \
    zmooth_twrp-eng

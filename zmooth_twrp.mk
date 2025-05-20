#
# Copyright (C) 2024 The Android Open Source Project
# Copyright (C) 2024 SebaUbuntu's TWRP device tree generator
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit some common Omni stuff.
$(call inherit-product, vendor/omni/config/common.mk)

$(call inherit-product, device/gsl/zmooth/device.mk)

PRODUCT_DEVICE := zmooth
PRODUCT_NAME := zmooth_twrp
PRODUCT_BRAND := ZMOOTH
PRODUCT_MODEL := ZMOOTH
PRODUCT_MANUFACTURER := gsl

PRODUCT_DEFAULT_LANGUAGE := ja
PRODUCT_DEFAULT_REGION   := JP

PRODUCT_GMS_CLIENTID_BASE := android-gsl

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="rk3399_mid-user 9 PI 104515 release-keys"

BUILD_FINGERPRINT := ZMOOTH/rk3399_mid/rk3399_mid:9/PI/imt04181045:user/release-keys

#
# Copyright (C) 2024 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#


LOCAL_PATH := device/gsl/zmooth
# API levelsP
RODUCT_USE_DYNAMIC_PARTITIONS := false
PRODUCT_FIRST_API_LEVEL := 28
TARGET_FLATTEN_APEX := true
PRODUCT_TARGET_VNDK_VERSION := 28
PRODUCT_SHIPPING_API_LEVEL := 28
TARGET_RECOVERY_SELINUX := permissive
SELINUX_IGNORE_NEVERALLOWS := true
# Health
PRODUCT_PACKAGES += \
    android.hardware.health@2.0-impl \
    android.hardware.health@2.0-impl.recovery \
    android.hardware.health@2.0-service

# Product characteristics
PRODUCT_CHARACTERISTICS := tablet

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    ro.build.system_root_image=true \
    ro.product.board=rk30sdk \
    ro.product.device=Zkai-study-Tab \
    ro.product.manufacturer=GSL \
    ro.product.model=ZMOOTH \
    ro.treble.enabled=true \
    ro.build.characteristics=tablet \
    persist.sys.usb.config=mtp,adb \
    ro.boot.boot_devices=fe330000.sdhci \
    ro.target.product=tablet \
    ro.build.version.security_patch=2019-12-05 \
    ro.build.version.release=9

PRODUCT_PACKAGES += \
    otapreopt_script \
    cppreopts.sh \
　　 update_engine \
    update_verifier \
    update_engine_sideload

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)

#
# Copyright (C) 2024 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#


LOCAL_PATH := device/gsl/zmooth
# API levels
PRODUCT_TARGET_VNDK_VERSION := 28
PRODUCT_SHIPPING_API_LEVEL := 28


# Health
PRODUCT_PACKAGES += \
    android.hardware.health@2.0-impl \
    android.hardware.health@2.0-impl.recovery \
    android.hardware.health@2.0-service
# key
PRODUCT_PACKAGES += \
    libkeymaster3.vendor \
    libkeymaster3support.vendor \
　　 libkeymaster4support \
    libvold \
    libcryptfs \
    libkeymaster_portable \
    android.hardware.gatekeeper@1.0-impl \
    android.hardware.gatekeeper@1.0-service \
    android.hardware.gatekeeper@1.0.vendor \
    android.hardware.keymaster@3.0-impl \
    android.hardware.keymaster@3.0-service \
    libpuresoftkeymasterdevice \
    libf2fs 

# Product characteristics
PRODUCT_CHARACTERISTICS := tablet

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    ro.build.system_root_image=true \
    ro.product.board=rk30sdk \
    ro.product.device=Zkai-study-Tab \
    ro.product.manufacturer=GSL \
    ro.product.model=ZMOOTH \
    ro.product.locale=ja-JP \
    persist.sys.locale=ja-JP \
    ro.treble.enabled=true \
    ro.build.characteristics=tablet \
    persist.sys.usb.config=mtp \
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

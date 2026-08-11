# Realme X2 Pro Android 16 QPR2 — Device Tree Status

**Updated:** 2026-08-12  
**Device:** Realme X2 Pro RMX1931/RMX1931CN (`samurai`)  
**Repository:** `zahid5656/android_device_realme_samurai_QPR2`  
**Active integration branch:** `infinity-x-3.12-qpr2-staging`  
**Pre-control-framework HEAD:** `f4da1a457e24c149c14c7a2f21b08840b7deccec`

## Current role

This repository is the active Android 16 QPR2 device-tree integration target. It must be completed against the exact selected ROM manifest, the proprietary vendor tree, RealmeParts, and the sole kernel source authority:

`zahid5656/android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`

The device tree is not allowed to invent or preserve userspace writes to kernel nodes that are absent from the current kernel contract.

## Current source contract

Reverify before every task. Known current contract includes:

- A-only / non-A/B device architecture;
- boot header v1;
- 4096-byte pages;
- `Image.gz-dtb` kernel image;
- separate DTBO;
- LZ4 ramdisk;
- `TARGET_KERNEL_SOURCE := kernel/realme/sm8150`;
- Android 16 QPR2 integration on `infinity-x-3.12-qpr2-staging`.

## Control-framework bootstrap task

Approved scope for this update:

- create repository-local `AGENTS_FILES/` control documentation matching the kernel project structure;
- define the cross-tree QPR2 execution framework and validation gates;
- do not modify functional device source, init, VINTF, SELinux, overlays, BoardConfig, product files, or build behavior in this bootstrap task.

## Next engineering phase

Device QPR2 completion starts with source and manifest inventory, then BoardConfig/partition/boot contract, init/ueventd/sysfs ownership, VINTF/HAL/Soong, SELinux, display/FOD/touch, power/thermal/UFS/suspend, USB/OTG, charging/health, and remaining hardware contracts.

Any required vendor, RealmeParts, or kernel change must be recorded as a cross-tree dependency rather than patched blindly in this repository.

## Validation

This bootstrap update may be claimed only as `SOURCE-VALIDATED` after the control files are created and fetched back from this exact branch. No build, boot, feature, or release claim is implied.

## Rollback

Rollback for this bootstrap task is deletion/revert of only `REPORT.md` and `AGENTS_FILES/*`. The pre-framework source baseline is the HEAD recorded above.

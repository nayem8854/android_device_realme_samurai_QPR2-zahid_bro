# Realme X2 Pro Android 16 QPR2 — Device Tree Status

**Updated:** 2026-08-12  
**Repository:** `zahid5656/android_device_realme_samurai_QPR2`  
**Active branch:** `infinity-x-3.12-qpr2-staging`  
**Pre-control-framework source HEAD:** `f4da1a457e24c149c14c7a2f21b08840b7deccec`

## Current role

Active Android 16 QPR2 device-tree integration target. Functional device source has not been changed by the control-framework task; only `REPORT.md` and `AGENTS_FILES/*` were added/updated.

## A-only architecture

`USER-PROVIDED VERIFIED RESULT`: Samurai must use **A-only logic, not A/B logic**.

Known current contract to reverify before functional work:

- non-A/B / `AB_OTA_UPDATER := false`;
- boot header v1;
- 4096-byte pages;
- `Image.gz-dtb`;
- separate DTBO;
- LZ4 ramdisk;
- `TARGET_KERNEL_SOURCE := kernel/realme/sm8150`.

OnePlus SM8150 Android 16 DT/VT remains the primary semantic/API/QPR2 reference, but its A/B/slot/header-v2/`Image`/vendor_boot logic is not imported. Samurai A-only board logic wins.

## Supplementary reference policy

Other user-supplied repositories/resources under `/home/zahid/REALME_X2_PRO_SAMURAI_ALL_TREES` may be inspected for useful implementation ideas, but only as supplementary candidate references. Exact repo/path/branch/HEAD and actual hunks/dependencies must be recorded before any import.

## Display calibration / FOD coupling

`USER-PROVIDED VERIFIED RESULT`: the designated F.14 OTA contains multiple display calibration/firmware materials, including aftermarket/replacement-display related variants, and these are involved with optical FOD behavior.

Device audit must therefore trace:

- panel/display identification;
- properties/init triggers selecting calibration/firmware;
- HBM/dimlayer/brightness/display-state handling;
- UDFPS/FOD state;
- touch/AOD/refresh behavior;
- RealmeParts panel capability gating;
- vendor loader/firmware dependencies;
- kernel panel/FOD interfaces.

Do not assume a single panel variant and do not patch Goodix/kernel first when a FOD defect may originate from wrong panel/calibration selection.

## Next task

Run Phase 0/A/K0 inventory, then Device Phase D from `AGENTS_FILES/ROAD_MAP.md`. Record all cross-tree dependencies instead of compensating locally.

## Validation

Control documentation: `SOURCE-VALIDATED` after fetch-back verification. No functional device build/boot/feature validation is implied.

## Rollback

Revert only the control-document commits to return to pre-framework source state. Functional device source baseline remains the pre-framework HEAD above.

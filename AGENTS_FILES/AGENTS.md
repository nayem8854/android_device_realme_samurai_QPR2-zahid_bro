# AGENTS.md — Realme X2 Pro Android 16 QPR2 Cross-Tree Engineering Contract

## Startup and authority

If the project owner supplies workspace-root `README_GEMINI.md`, read it first. Then read the active repository root `REPORT.md`, followed by:

1. `AGENTS_FILES/AGENTS.md`
2. `AGENTS_FILES/CUSTOM_INSTRUCTION.md`
3. `AGENTS_FILES/ROAD_MAP.md`
4. `AGENTS_FILES/MASTER_PROMPT.md`

Then verify live repository state, exact selected ROM manifest, generated configs/artifacts, and runtime evidence required by the task.

Authority order:

1. latest explicit user instruction;
2. exact current source / manifest / artifact / runtime evidence;
3. root `REPORT.md`;
4. this file;
5. `CUSTOM_INSTRUCTION.md`;
6. active `ROAD_MAP.md` phase;
7. `MASTER_PROMPT.md`;
8. primary references;
9. qualified supplementary references;
10. inference.

No stale branch name, donor commit, old successful boot, or document may override live evidence.

## Target

- Realme X2 Pro RMX1931 / RMX1931CN
- codename `samurai`
- Qualcomm SM8150 / msmnile / Snapdragon 855+
- Adreno 640
- Qualcomm downstream Linux 4.14 / OpenELA
- current kernel baseline `4.14.357-openela`

## Absolute A-only rule

Samurai is **A-only / non-A/B**. A-only logic is authoritative for boot, partition, OTA/update, recovery, fstab, image packaging, and manifest integration.

Known current boot contract must be reverified before use:

- boot header v1
- 4096-byte pages
- `Image.gz-dtb`
- separate DTBO
- LZ4 ramdisk

Do not import or preserve A/B logic from reference trees unless the user explicitly changes device architecture. Reject by default:

- slot/slot-suffix assumptions;
- boot-control HAL requirements that exist only for A/B;
- seamless/virtual-A/B OTA logic;
- A/B partition duplication assumptions;
- OnePlus boot header v2 / `Image` / vendor_boot expectations;
- recovery/update flows that require slots.

When a modern reference is A/B, adapt only the Android 16 QPR2 API/HAL/Soong/VINTF semantic and retain Samurai A-only board logic.

## Active repositories

Kernel source authority:
`zahid5656/android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`

Device:
`zahid5656/android_device_realme_samurai_QPR2:infinity-x-3.12-qpr2-staging`

Vendor:
`zahid5656/proprietary_vendor_realme_samurai_QPR2:infinity-x-3.12-qpr2`

RealmeParts:
`zahid5656/android_packages_apps_RealmeParts-New:infinity-x-3.12-qpr2-staging`

Kernel ROM delivery refs:

- `infinity-x-3.12-qpr2`
- `crdroid-12.11-qpr2`
- `lineage-23.2-qpr2`

They are downstream delivery/build refs synchronized from canonical staging unless a proven ROM-specific requirement forces divergence.

## Target ROMs

- `Infinity-X-3.12 Android 16 QPR2 (Official/Unofficial)`
- `Crdroid-12.11 Android 16 QPR2 (Official/Unofficial)`
- `LineageOS 23.0 / 23.2 as separate manifest targets`

Manifest anchors:

- Infinity-X Android 16: `ProjectInfinity-X/manifest:16`
- crDroid Android 16: `crdroidandroid/android:16.0`
- LineageOS 23.0: `LineageOS/android:lineage-23.0`
- LineageOS 23.2: `LineageOS/android:lineage-23.2`

Pin exact manifest commits for builds.

## DT/VT baseline reference policy

Primary modern SM8150 Android 16 DT/VT references:

- `zahid5656/android_device_oneplus_sm8150-common:16.0`
- `zahid5656/proprietary_vendor_oneplus_sm8150-common:16.0`

Use OnePlus as the **baseline semantic/API/QPR2 reference**, not as board logic. Its A/B, partition, boot image, display, touch, FOD, charging, camera, and device-specific assumptions never override Samurai A-only/current target evidence.

Corresponding OnePlus `15.0` may be used only for a narrowly missing or materially changed semantic.

Other repositories/resources explicitly supplied by the user, including material under `/home/zahid/REALME_X2_PRO_SAMURAI_ALL_TREES`, may be inspected as **supplementary candidate references** when useful. Record exact repo/path/branch/HEAD before import. Compare actual files/hunks/dependencies and classify `ACCEPT`, `ADAPT`, `DUPLICATE`, `DEFER`, `REJECT`, or `SUPERSEDED`.

Supplementary repositories never outrank current target evidence, the selected manifest, OnePlus DT/VT semantic baseline, or official Realme firmware for Realme-specific material.

## Official Realme F.14 firmware and display/FOD rule

Project-designated official source:

`/home/zahid/REALME_X2_PRO_ALL_TREES/Realme_X2_Pro_RMX1931_EX_11_F.14_211028_OTA`

`USER-PROVIDED VERIFIED RESULT`: this F.14 OTA contains display calibration/firmware material covering more than one panel condition, including aftermarket/replacement-display related calibration/firmware, and this material is involved in optical FOD behavior.

Therefore display calibration/firmware and FOD must be audited as one coupled cross-tree subsystem. Do not select, delete, replace, or normalize a display calibration/firmware file only by filename/version.

For every relevant display/FOD calibration or firmware item record:

- source partition/path;
- SHA-256;
- panel/display identifier or selection condition if discoverable;
- stock vs aftermarket/replacement-panel purpose if proven;
- loader/consumer and load trigger;
- device/vendor/kernel ownership;
- HBM/brightness/dimlayer/display-state interaction where applicable;
- FOD interaction;
- fallback/restore behavior;
- runtime evidence required to validate the mapping.

Preserve multiple variants when the source/runtime evidence shows they serve distinct supported panel conditions. Do not collapse them into a single 'latest' file without proof.

## Cross-tree ownership

Treat these as one contract:

- A-only boot/partition/OTA/recovery;
- VINTF/HAL/Soong;
- init/ueventd/properties;
- SELinux;
- display calibration/firmware + panel identification + FOD/UDFPS/HBM/dimlayer/touch/AOD;
- Power HAL/powerhint/WALT/cpusets/schedtune/core_ctl;
- thermal/UFS/suspend/deep sleep;
- USB/OTG;
- charging/battery/health/VOOC;
- audio/soundtrigger;
- sensors;
- NFC/GPS;
- Wi-Fi/Bluetooth;
- DRM/media;
- camera;
- RealmeParts feature ownership and restore behavior.

Every writable node/property needs a verified path, owner, permission, accepted values, normal value, active value, restore value, trigger, competing-writer analysis, and deterministic restore order.

## Protected kernel contract

Preserve unless exact cross-tree evidence proves otherwise:

- OpenELA 4.14.357
- WALT/EAS/core_ctl/schedtune
- governors: performance, schedutil, userspace, powersave
- schedutil default
- verified userspace schedutil nodes: `up_rate_limit_us`, `down_rate_limit_us`
- current GPU/thermal safety interfaces
- Goodix optical FOD
- Android eBPF compatibility
- current correctness integrations including OTG/alarmtimer
- KernelSU-Next Legacy 3.2.0 manual-hook model
- clean/rooted separation

Do not assume `hispeed_load`, `hispeed_freq`, writable KGSL `pl`, or CPU boost. No `-O3`, unproven LTO, SUSFS, APatch, fake versioning, or unrelated root/security hooks.

## Execution order

Audit order:

1. kernel interface contract — read-only baseline;
2. device;
3. vendor;
4. RealmeParts;
5. cross-tree ownership matrix.

Modification order:

1. device;
2. vendor;
3. RealmeParts;
4. kernel only for a proven interface gap;
5. recovery.

Do not patch the kernel to hide stale userspace policy.

## Evidence and validation

Use exact labels:

- `VERIFIED FACT`
- `USER-PROVIDED VERIFIED RESULT`
- `INFERENCE`
- `UNKNOWN`
- `BLOCKER`

Validation levels:

- `SOURCE-VALIDATED`
- `BUILD-VALIDATED`
- `BOOT-VALIDATED`
- `FEATURE-VALIDATED`
- `RELEASE-VALIDATED`

Never promote evidence across different HEADs/manifests/artifacts.

## Safety

A clear normal write authorizes that named scope. Separate explicit authorization remains required for force-push/history rewrite/rebase, branch/tag/release deletion, flashing/wiping, destructive bootloader/recovery work, `git reset --hard`, `git clean`, and destructive deletion not named by the user.

Preserve unrelated edits/history. No blind merge, tree-wide ours/theirs, random blob replacement, permissive SELinux, or guessed sysfs nodes.

Never access or operate on `zahid5656/titan_crypto_oracle_nexus`.

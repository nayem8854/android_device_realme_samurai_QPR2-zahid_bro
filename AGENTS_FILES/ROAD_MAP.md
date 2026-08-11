# ROAD_MAP.md — Realme X2 Pro Android 16 QPR2 Full Completion Framework

**Device:** Realme X2 Pro RMX1931/RMX1931CN (`samurai`)  
**Platform:** SM8150/msmnile/Snapdragon 855+ — Adreno 640  
**Kernel source authority:** `zahid5656/android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`  
**Kernel baseline:** OpenELA 4.14.357

## Program objective

Finish QPR2 device, vendor, RealmeParts and kernel integration as one cross-tree contract, then build Infinity-X 3.12, crDroid 12.11, and LineageOS 23.0/23.2 against exact manifest pins.

The project uses OnePlus SM8150 Android 16 DT/VT as the primary modern semantic/API reference, while Samurai **A-only logic** remains authoritative for boot/partition/OTA/recovery. Additional user-supplied repositories are supplementary candidate references only.

---

# PHASE 0 — Source/manifest/control freeze

1. Read workspace `README_GEMINI.md` if supplied.
2. Read root `REPORT.md` and all `AGENTS_FILES/*` for each active target.
3. Verify repo path, remote, branch, HEAD, dirty state and submodules.
4. Pin the exact selected ROM manifest commit and project revisions.
5. Record rollback refs and exact component BOM.
6. Snapshot the current canonical kernel interface contract.
7. Start a cross-tree ownership matrix for services, properties and writable nodes.

**Exit:** exact source identity is `SOURCE-VALIDATED` before functional mutation.

---

# PHASE A — Absolute A-only architecture gate

Samurai is A-only / non-A/B. This phase is a hard gate before DT/VT integration.

Verify and preserve:

- `AB_OTA_UPDATER := false` or current equivalent A-only declaration;
- boot header v1;
- 4096-byte pages;
- `Image.gz-dtb`;
- separate DTBO;
- LZ4 ramdisk;
- A-only fstab/recovery/update packaging;
- partition naming and mount logic without slot suffixes;
- no virtual-A/B or seamless-update assumptions;
- no A/B-only boot-control dependency;
- no OnePlus header-v2/`Image`/vendor_boot/slot logic.

When importing Android 16 QPR2 semantics from OnePlus, adapt only API/HAL/VINTF/Soong behavior. Keep Samurai A-only board logic.

**Exit:** boot/OTA/recovery architecture is explicitly A-only and no inherited A/B logic remains accidentally active.

---

# PHASE K0 — Canonical kernel interface lock (read-only)

Verify current canonical staging without historical donor work:

- OpenELA 4.14.357 identity;
- WALT/EAS/core_ctl/schedtune;
- governors performance/schedutil/userspace/powersave;
- schedutil default;
- userspace schedutil nodes `up_rate_limit_us`, `down_rate_limit_us`;
- thermal/GPU interfaces actually exported;
- Goodix optical FOD interfaces;
- display/panel-facing kernel hooks used by userspace/vendor;
- eBPF compatibility;
- UFS/storage/power nodes;
- suspend/deep-sleep interfaces;
- USB/OTG/alarmtimer state;
- charging/health-facing nodes;
- KernelSU-Next Legacy 3.2.0 manual-hook model;
- clean/rooted build separation.

Do not assume `hispeed_load`, `hispeed_freq`, writable KGSL `pl`, or CPU boost.

**Exit:** kernel interface inventory recorded; no kernel mutation yet.

---

# PHASE D — Device Tree QPR2 completion

Repository: `zahid5656/android_device_realme_samurai_QPR2`  
Branch: `infinity-x-3.12-qpr2-staging`

## D1 — Board/build/partition

Audit BoardConfig, product inheritance, Soong namespaces, A-only OTA, boot/DTBO contract, filesystem/partition declarations, fstab, recovery/releasetools, kernel project path and build-relaxation flags.

## D2 — Init/ueventd/properties/sysfs

For every write/chown/chmod/property/service verify:

- actual path/property;
- current kernel/vendor consumer;
- permission and SELinux context;
- accepted values;
- normal/restore behavior;
- competing writers.

Remove/adapt stale writes instead of inventing kernel compatibility nodes.

## D3 — VINTF/HAL/Soong

Audit device manifests, compatibility matrices, HIDL/AIDL instances, QCOM service packages, namespace visibility and stale/duplicate declarations against the exact ROM manifest and real vendor binaries.

## D4 — SELinux

Keep enforcing. Audit FOD/display/touch, health/charging, audio, sensors, NFC/GPS, USB/OTG, UFS/power/thermal, vendor services and RealmeParts access. No broad allow/permissive workaround.

## D5 — Display/panel/FOD/touch/AOD

This is a coupled subsystem. Map:

- panel/display identification logic;
- panel-specific configuration selection;
- UDFPS/FOD state;
- HBM/dimlayer/brightness/doze/AOD;
- 60/90 Hz behavior;
- touch orientation/gesture/game state;
- device properties/init triggers selecting display calibration/firmware;
- RealmeParts panel capability gating.

Do not assume a single panel variant.

## D6 — Power/thermal/UFS/suspend

Reconcile Power HAL/powerhint, cpusets, schedtune, WALT, core_ctl, schedutil rate limits, thermal, UFS power/clock policy, suspend/deep sleep and wake sources.

## D7 — USB/OTG/charging/health

Verify configfs/gadget ownership, host/accessory permission, OTG nodes, health/charger services, VOOC/cool-down/charge-limit policy and duplicate writers.

## D8 — Remaining hardware

Audit audio/soundtrigger, sensors, Wi-Fi/BT, NFC/GPS, haptics, DRM/media/codecs, radio/IMS declarations and initial camera-provider dependencies.

**Exit:** device `SOURCE-VALIDATED` against the selected manifest/current kernel; open VT/RP/kernel dependencies recorded.

---

# PHASE V — Vendor QPR2 completion

Repository: `zahid5656/proprietary_vendor_realme_samurai_QPR2`  
Branch: `infinity-x-3.12-qpr2`

## V1 — Provenance map

For changed/retained proprietary material record source device/build/partition/path, extraction method, SHA-256, target path and reason.

Primary Realme source:
`/home/zahid/REALME_X2_PRO_ALL_TREES/Realme_X2_Pro_RMX1931_EX_11_F.14_211028_OTA`

## V2 — F.14 display calibration/firmware + FOD map

`USER-PROVIDED VERIFIED RESULT`: F.14 contains multiple display calibration/firmware materials, including aftermarket/replacement-display related variants, and these are involved with optical FOD.

Create a dedicated inventory for every relevant display/FOD item:

`file | source partition/path | SHA-256 | panel/selection condition | stock/aftermarket purpose | loader/consumer | trigger | device owner | vendor owner | kernel interface | HBM/brightness/dimlayer relation | FOD relation | fallback | validation status`

Rules:

- do not choose by version/filename only;
- do not collapse multiple variants without proving they are duplicates;
- preserve distinct panel variants when runtime/source logic selects them;
- trace loaders, properties, init triggers and kernel/display consumers;
- cross-check FOD failures against panel/calibration selection before changing Goodix/kernel code.

## V3 — Generated-tree ownership

Identify proprietary-file lists, extraction scripts and blob-fixup sources. Prefer fixing the source specification instead of manually editing generated outputs.

## V4 — ELF/ABI/linker

Audit ELF class, SONAME, `DT_NEEDED`, undefined/exported symbols, 32/64-bit pairing, linker namespace, partition placement, duplicates and justified shims.

## V5 — HAL/service reconciliation

Cross-check device VINTF/init/SELinux against real vendor content for fingerprint, display, camera, audio, sensors, GNSS, NFC, Wi-Fi/BT, radio/IMS/DPM, health/charging, DRM/media and firmware/calibration families.

## V6 — Mixed-generation cleanup

Higher version is not evidence. Keep/replace QSSI/external-device/mixed-generation items only after ABI/runtime/provenance analysis.

**Exit:** vendor `SOURCE-VALIDATED` with provenance, panel/FOD calibration map, ABI integrity and service ownership recorded.

---

# PHASE R — RealmeParts QPR2 completion

Repository: `zahid5656/android_packages_apps_RealmeParts-New`  
Branch: `infinity-x-3.12-qpr2-staging`

## R1 — Capability matrix

For each feature/tile/service record hardware/panel condition, node/property, permission, SELinux, accepted values, normal/active/restore values, trigger, owner, competing writers and restore order.

## R2 — Panel-aware UI policy

CABC/DC dimming/AOD/display/touch/FOD-adjacent controls must be gated by verified supported panel conditions. RealmeParts must not overwrite panel calibration/firmware selection or expose a control that is unsafe for a replacement/aftermarket panel variant.

## R3 — Android 16 lifecycle/security

Audit manifest exported components, callers/permissions, receivers, services, foreground-service/notification rules, Quick Settings lifecycle, boot restore, persistence, privileged APIs, UI/system bars and SELinux.

## R4 — Game Mode/performance

Coordinate only verified kernel/Power HAL/device interfaces. No guessed `hispeed_load`, `hispeed_freq`, KGSL `pl`, or CPU boost. Game Mode OFF must deterministically restore balanced baseline.

## R5 — Charging controls

Validate SmartCharging/cool-down/charge-limit nodes and ownership against device/vendor health services.

**Exit:** RealmeParts `SOURCE-VALIDATED` with panel-aware capability gating and deterministic restore behavior.

---

# PHASE X — Cross-tree reconciliation gate

Build one ownership matrix covering:

`Subsystem | Interface/file/node/property | Panel/variant condition | Kernel owner | Device/init owner | Vendor/HAL owner | RealmeParts owner | Normal | Active | Restore | SELinux | Manifest consumer | Status`

Mandatory rows include:

- A-only boot/OTA/recovery;
- VINTF/HAL/init/SELinux;
- panel ID + display calibration/firmware selection;
- FOD/UDFPS/HBM/dimlayer/brightness/touch/AOD;
- power/WALT/cpuset/schedtune/core_ctl;
- thermal/UFS/suspend/deep sleep;
- USB/OTG;
- charging/health;
- audio/sensors;
- Wi-Fi/BT;
- NFC/GPS;
- DRM/media/camera baseline;
- RealmeParts writers.

Resolve duplicate/contradictory owners before kernel changes.

**Exit:** all real kernel gaps are isolated with exact consumers and panel/variant conditions.

---

# PHASE K1 — Evidence-backed kernel alignment

Modify only canonical staging, only for gaps proven by Phase X.

For every patch record consumer, current behavior, expected interface, smallest patch, config/ABI/node impact, display/FOD variant implications, build result, boot/runtime result and rollback.

Preserve current protected kernel contract unless evidence requires change.

**Exit:** at minimum `BUILD-VALIDATED`; hardware-facing changes require matching boot/feature evidence before release propagation.

---

# PHASE M — ROM-specific integration

## Infinity-X 3.12

Pin exact `ProjectInfinity-X/manifest:16` commit and component BOM. Sync kernel delivery ref `infinity-x-3.12-qpr2` from validated canonical staging before build.

## crDroid 12.11

Pin exact `crdroidandroid/android:16.0` commit and component BOM. Sync `crdroid-12.11-qpr2` from validated canonical staging.

## LineageOS

Pin 23.0 and 23.2 separately. Use `lineage-23.2-qpr2` for the 23.2 delivery mapping; define 23.0 mapping only when build scope requires it.

Create DT/VT/RP ROM branches only when exact manifest/API divergence requires them.

**Exit:** each ROM artifact is `BUILD-VALIDATED` against an exact BOM.

---

# PHASE B — Boot/runtime closure

Triage exact artifacts in order:

1. boot/init/VINTF/SELinux;
2. storage/UFS/data/reboot;
3. panel selection/display/FOD/touch/HBM/AOD;
4. Wi-Fi/BT/audio/sensors/NFC/GPS/USB;
5. charging/thermal/suspend/deep sleep;
6. power/performance ownership;
7. app/UI defects.

For FOD/display defects, first capture active panel identifier, selected calibration/firmware path/version/hash, HBM/display state and Goodix/FOD logs before changing kernel or blobs.

---

# PHASE C — Stock Realme camera

Use the designated F.14 source plus current Android 16 platform requirements. Audit APK/framework, provider/HAL, ELF graph, linker namespace, properties/init, permissions, calibration/config, justified shims, SELinux and runtime logs. No broad blob replacement or permissive SELinux.

---

# PHASE REC / CI / FINAL

1. TWRP using Samurai A-only recovery logic.
2. OrangeFox only after TWRP correctness and only if required.
3. Reproducible CI with exact manifest/component/toolchain/config/log/artifact hashes.
4. Final exact-candidate validation.

`RELEASE-VALIDATED` requires reproducible build, boot/ADB, VINTF, SELinux enforcing, FOD across supported panel conditions where testable, display/touch/HBM/refresh/AOD, Wi-Fi/BT, audio, sensors, stock camera, NFC/GPS, USB/OTG, charging/health, thermal/performance, suspend/deep sleep/wake, UFS/storage/data, normal/recovery reboot, recovery install/data access, applicable clean/rooted kernel variants, and no unresolved release-blocking panic/tombstone/watchdog/VINTF/SELinux defect.

## Standing rules

- A-only logic is mandatory; A/B reference logic is not imported.
- OnePlus 16.0 DT/VT is baseline semantic/API reference, not board template.
- User-supplied repositories are supplementary candidate references only.
- F.14 panel calibration/firmware and optical FOD are a coupled audit domain.
- Device → Vendor → RealmeParts → Kernel is the cross-tree modification order.
- No random blob replacement.
- No permissive SELinux.
- No guessed sysfs/procfs nodes.
- No duplicate uncontrolled last writers.
- Preserve unrelated changes/history.
- Never access or operate on `zahid5656/titan_crypto_oracle_nexus`.

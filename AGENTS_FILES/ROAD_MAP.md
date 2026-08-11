# ROAD_MAP.md — Realme X2 Pro Android 16 QPR2 Full Completion Framework

**Device:** Realme X2 Pro RMX1931/RMX1931CN (`samurai`)  
**Platform:** SM8150/msmnile/Snapdragon 855+ — Adreno 640  
**Kernel baseline:** OpenELA 4.14.357  
**Kernel source authority:** `zahid5656/android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`

## Program objective

Finish Android 16 QPR2 device, vendor, RealmeParts and kernel integration as one cross-tree contract, then produce reproducible ROM-specific builds for Infinity-X 3.12, crDroid 12.11, and LineageOS 23.0/23.2 without speculative donor imports, guessed sysfs policy, permissive SELinux, or hidden cross-tree ownership conflicts.

This roadmap is execution order, not a list of suggestions. Do not skip a gate because another ROM or donor source booted.

---

# PHASE 0 — Workspace, source and manifest freeze

## Inputs

Active targets:

- Kernel: `android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`
- Device: `android_device_realme_samurai_QPR2:infinity-x-3.12-qpr2-staging`
- Vendor: `proprietary_vendor_realme_samurai_QPR2:infinity-x-3.12-qpr2`
- RealmeParts: `android_packages_apps_RealmeParts-New:infinity-x-3.12-qpr2-staging`

Kernel ROM delivery refs at framework bootstrap:

- `infinity-x-3.12-qpr2`
- `crdroid-12.11-qpr2`
- `lineage-23.2-qpr2`

These delivery refs were reset from canonical staging on 2026-08-12. Reverify before use; they are not independent kernel development authorities.

## Required actions

1. Read workspace `README_GEMINI.md` if supplied.
2. Read each target repository `REPORT.md` and `AGENTS_FILES/*`.
3. Verify exact repo path, remote, branch, HEAD, dirty state and submodules.
4. Resolve the exact target ROM manifest branch and exact manifest commit.
5. Record `repo manifest -r` or equivalent project revision inventory for each ROM build workspace.
6. Record rollback refs for all four target repositories.
7. Snapshot current kernel interface contract relevant to userspace: proc/sysfs nodes, defconfig/generated config, boot/DTBO contract, governors, WALT/core_ctl/schedtune, thermal/GPU, FOD, USB/OTG and power-facing interfaces.
8. Create an initial cross-tree ownership matrix listing every service/property/sysfs writer known from device/vendor/RealmeParts.

## Exit gate

`SOURCE-VALIDATED` control baseline with exact component HEADs and selected manifest pin. No mutation phase starts while source identity is ambiguous.

---

# PHASE K0 — Kernel contract lock, read-only audit

## Objective

Understand the existing kernel mechanisms before changing userspace. This phase does not reopen historical donor/import work.

## Verify

- `4.14.357-openela` baseline and current Makefile identity;
- A-only compatible output contract: `Image.gz-dtb`, separate DTBO, header v1, 4096 pages, LZ4 ramdisk as applicable to packaging;
- required governors: performance, schedutil, userspace, powersave;
- schedutil default and userspace nodes `up_rate_limit_us`, `down_rate_limit_us`;
- WALT/EAS/core_ctl/schedtune interfaces;
- thermal and GPU interfaces actually exported;
- Goodix optical FOD interfaces;
- Android eBPF compatibility;
- current USB/OTG behavior and alarmtimer fix state;
- charging/health-facing kernel nodes;
- UFS/storage nodes;
- suspend/deep-sleep blockers;
- KernelSU-Next Legacy 3.2.0 manual-hook model and clean/rooted separation.

## Prohibited assumptions

Do not assume `hispeed_load`, `hispeed_freq`, writable KGSL `pl`, `CONFIG_CPU_BOOST`, SUSFS, APatch, or extra root/security hooks.

## Exit gate

Kernel interface inventory recorded. Kernel remains unchanged unless a later cross-tree phase proves an actual interface defect/gap.

---

# PHASE D — Device Tree QPR2 completion

Repository:
`zahid5656/android_device_realme_samurai_QPR2`

Branch:
`infinity-x-3.12-qpr2-staging`

## D1 — Board/build/partition contract

Audit and correct only with evidence:

- `BoardConfig.mk` / related board config;
- A-only / non-A/B OTA declarations;
- boot header/page/kernel image/DTBO contract;
- `TARGET_KERNEL_SOURCE := kernel/realme/sm8150` and manifest project path;
- partition sizes/filesystems/metadata/AVB declarations;
- fstab/recovery/releasetools;
- product inheritance and package ownership;
- Soong namespaces and build visibility;
- legacy `BUILD_BROKEN_*`/relaxation flags and whether each is still required on Android 16 QPR2.

Do not import OnePlus A/B/header-v2/`Image` semantics.

## D2 — Init, ueventd, properties and writable nodes

Audit every relevant service, `write`, `chown`, `chmod`, property trigger and restore path in device init/ueventd files.

For every node/property record:

- path/property name;
- source owner;
- kernel/vendor consumer;
- existence on current kernel/runtime;
- permission/SELinux context;
- accepted values;
- normal and restore value;
- other writers.

Remove/adapt stale writes instead of creating fake kernel compatibility interfaces.

## D3 — VINTF/HAL/Soong

Audit:

- device manifest fragments;
- framework/device compatibility matrices;
- HIDL/AIDL declarations and served instances;
- vendor service package names;
- QCOM namespaces and dependencies;
- target-level assumptions;
- stale or duplicate HAL declarations.

Compare declarations against actual vendor binaries/services and the exact ROM framework matrix. Do not raise FCM level blindly.

## D4 — SELinux

Keep enforcing. Audit labels/domains/allow rules for:

- fingerprint/FOD;
- display/touch;
- health/charging;
- audio/soundtrigger;
- sensors;
- NFC/GPS;
- USB/OTG;
- UFS/power/thermal;
- vendor services and RealmeParts.

No broad `allow`, no permissive domain as a fix, no blind `audit2allow` dump.

## D5 — FOD/display/touch/AOD

Validate source contracts for:

- UDFPS sensor state;
- HBM/dimlayer;
- brightness/doze/AOD;
- 60/90 Hz switching;
- touch orientation/gesture/game handling;
- panel capability gating;
- overlays and framework-facing properties.

Any workaround writing a display/FOD node must have runtime ownership evidence and deterministic restore.

## D6 — Power/thermal/UFS/suspend

Reconcile:

- Power HAL / powerhint;
- cpusets;
- schedtune;
- WALT;
- core_ctl;
- schedutil rate limits;
- thermal configuration and services;
- UFS clock/power behavior;
- suspend/deep sleep and wake sources;
- display/input suspend blockers.

Kernel exposes mechanisms with neutral defaults. Aggressive policy stays userspace and must restore correctly.

## D7 — USB/OTG/charging/health

Verify:

- configfs/gadget ownership;
- host/accessory permission;
- OTG node access;
- health/charger service ownership;
- VOOC/cool-down/charge-limit nodes;
- duplicate writes between init, health, Power HAL and RealmeParts.

The previously fixed kernel OTG regression does not prove userspace USB policy correctness.

## D8 — Remaining hardware contracts

Audit:

- audio/soundtrigger;
- sensors;
- Wi-Fi/Bluetooth;
- NFC/GPS;
- vibrator/haptics;
- DRM/media/codecs;
- radio/IMS declarations owned by vendor;
- camera provider dependencies sufficient for initial ROM build.

## Device exit gate

Device tree is `SOURCE-VALIDATED` against the selected manifest and current kernel. Every unresolved vendor/app/kernel dependency is recorded in `REPORT.md`; no hidden guessed node remains.

---

# PHASE V — Proprietary Vendor QPR2 completion

Repository:
`zahid5656/proprietary_vendor_realme_samurai_QPR2`

Branch:
`infinity-x-3.12-qpr2`

## V1 — Provenance inventory

Build a table for material proprietary families. For every file changed/retained/replaced record:

- source device/build/firmware;
- source partition/path;
- extraction method;
- SHA-256;
- target partition/path;
- reason for use.

Project-designated Realme source:
`/home/zahid/REALME_X2_PRO_ALL_TREES/Realme_X2_Pro_RMX1931_EX_11_F.14_211028_OTA`

Do not mix firmware generations silently.

## V2 — Generated-tree ownership

Determine which files are generated by proprietary-file lists/extraction/fixup tooling. Fix the source specification/fixup where possible instead of manually patching generated output.

## V3 — ELF/ABI/linker audit

For relevant binaries/libraries inspect:

- ELF class / architecture;
- SONAME;
- `DT_NEEDED`;
- undefined/exported symbols;
- Android/QCOM dependency expectations;
- 32/64-bit pairing;
- linker namespaces;
- partition placement;
- duplicate modules;
- justified shims.

Use OnePlus SM8150 16.0 as dependency/API reference only, never as a wholesale blob donor.

## V4 — HAL/service reconciliation

Cross-check vendor content against device VINTF/init/SELinux for:

- fingerprint;
- camera;
- audio/soundtrigger;
- sensors;
- GNSS;
- NFC;
- Wi-Fi/Bluetooth;
- radio/IMS/DPM;
- health/charging;
- display;
- DRM/media;
- firmware/calibration packages.

Every declared service must have a real binary, interface, init owner, partition location and SELinux domain.

## V5 — Mixed-generation cleanup

Identify QSSI/external-device/mixed GPU-display or other generation changes. Keep/replace only after ABI/runtime evidence. Higher version number is not sufficient evidence.

## Vendor exit gate

Vendor is `SOURCE-VALIDATED` with provenance, ABI/dependency integrity, service ownership, and open runtime risks recorded.

---

# PHASE R — RealmeParts QPR2 completion

Repository:
`zahid5656/android_packages_apps_RealmeParts-New`

Branch:
`infinity-x-3.12-qpr2-staging`

## R1 — Capability matrix

For every preference/tile/service/feature record:

- hardware capability and supported panel/device condition;
- node/property path;
- read/write permission;
- SELinux context/domain;
- accepted values;
- normal value;
- active/game value;
- restore value;
- trigger;
- owner and competing writers;
- deterministic restore order.

Unsupported controls must be hidden/disabled, not left visible with guessed behavior.

## R2 — Android 16 app/security lifecycle

Audit:

- `AndroidManifest.xml` exported components;
- permissions and caller validation;
- shared UID/signing compatibility if present;
- boot receiver;
- background/foreground service behavior;
- foreground-service types/notifications where required;
- Quick Settings tile lifecycle;
- persistence and boot restore;
- process lifetime/error handling/logging;
- edge-to-edge/system bars and resource compatibility;
- privileged API/library dependencies;
- SELinux access.

Do not remove upgrade-sensitive package identity/shared-UID semantics without a separate migration design.

## R3 — Game Mode and performance policy

Use only current verified interfaces. Coordinate with device init and Power HAL/powerhint.

Do not assume:

- `hispeed_load`;
- `hispeed_freq`;
- writable KGSL `pl`;
- CPU boost.

Verified schedutil userspace nodes are `up_rate_limit_us` and `down_rate_limit_us` unless new live evidence proves additional nodes.

Game Mode OFF must restore the balanced baseline in deterministic order.

## R4 — Display/touch/charging controls

Validate CABC/DC dimming/panel modes/AOD/touch controls, SmartCharging/cool-down and related services against actual current nodes and competing device/vendor owners.

## RealmeParts exit gate

RealmeParts is `SOURCE-VALIDATED` against the completed device/vendor/kernel contract with unsupported capabilities gated and every write/restore path documented.

---

# PHASE X — Cross-tree ownership reconciliation

This phase is mandatory before kernel alignment.

Build one matrix with columns:

`Subsystem | Interface/node/property | Kernel owner | Device/init owner | Vendor/HAL owner | RealmeParts owner | Normal value | Active value | Restore value | SELinux | Manifest consumer | Status`

Cover at minimum:

- boot/DTBO/partition;
- VINTF/HAL/init/SELinux;
- FOD/display/touch/HBM/AOD;
- power/WALT/cpuset/schedtune/core_ctl;
- thermal/UFS/suspend/deep sleep;
- USB/OTG;
- charging/health;
- audio/sensors;
- Wi-Fi/BT;
- NFC/GPS;
- DRM/media;
- camera baseline;
- RealmeParts feature writers.

Resolve duplicate or contradictory policy owners before changing the kernel.

## Exit gate

Cross-tree contract is `SOURCE-VALIDATED`; all true kernel gaps are isolated with exact consumers and expected behavior.

---

# PHASE K1 — Evidence-backed kernel alignment

Modify only canonical kernel staging and only for gaps proven in Phase X.

## Required change record

For every kernel patch record:

- userspace/vendor consumer;
- exact failing/missing interface;
- current source behavior;
- expected behavior;
- reference/source evidence;
- smallest patch;
- config impact;
- ABI/sysfs/procfs impact;
- build result;
- boot/runtime result;
- rollback commit.

## Non-regression checks

Preserve unless explicitly required:

- OpenELA 4.14.357;
- WALT/EAS/core_ctl/schedtune;
- four required governors and schedutil default;
- current GPU/thermal frequency interfaces;
- Goodix FOD;
- eBPF compatibility;
- OTG/alarmtimer correctness;
- Bluetooth/FastRPC/rtmutex-futex/QCA fixes;
- KernelSU-Next Legacy manual hooks;
- clean/rooted separation.

## Kernel validation gate

At minimum `BUILD-VALIDATED` before ROM integration; interface changes affecting boot/hardware require `BOOT-VALIDATED`/`FEATURE-VALIDATED` evidence before final propagation.

---

# PHASE M — ROM-specific manifest and branch integration

## Infinity-X 3.12

- resolve/pin `ProjectInfinity-X/manifest:16` exact commit;
- record exact component revisions;
- use kernel delivery ref `infinity-x-3.12-qpr2` synchronized from canonical staging;
- create device/vendor/RealmeParts ROM-specific branch only if manifest/API divergence is proven;
- build and archive logs/hashes.

## crDroid 12.11

- resolve/pin `crdroidandroid/android:16.0` exact commit;
- record exact component revisions;
- use kernel delivery ref `crdroid-12.11-qpr2` synchronized from canonical staging;
- isolate only proven crDroid-specific differences;
- build and archive logs/hashes.

## LineageOS

- resolve/pin LineageOS 23.0 and 23.2 separately;
- do not conflate their manifest/API states;
- use `lineage-23.2-qpr2` for 23.2 delivery after synchronization from canonical staging;
- define a 23.0 delivery mapping only when exact build scope requires it;
- isolate only proven Lineage-specific differences.

## Exit gate

Each ROM build is `BUILD-VALIDATED` against an exact manifest/component BOM. A build for one ROM does not validate another.

---

# PHASE B — Boot and runtime defect closure

Use exact built artifacts and triage in order:

1. boot/init/VINTF/SELinux;
2. ADB/storage/UFS/data/reboot;
3. display/FOD/touch/HBM/refresh/AOD;
4. Wi-Fi/BT/audio/sensors/NFC/GPS/USB/OTG;
5. charging/health/thermal/suspend/deep sleep;
6. power/performance/Game Mode ownership;
7. UI/app feature defects.

Evidence sources: pstore, dmesg, logcat, tombstones, service/HAL state, VINTF output, SELinux denials, sysfs/procfs listings, Power HAL/thermal logs.

Do not infer root cause from a symptom or another ROM's behavior.

---

# PHASE C — Stock Realme camera

Run after the initial ROM build unless camera dependencies block build/boot.

Audit from the project-designated Realme firmware source:

- stock APK/framework compatibility;
- camera provider/HAL;
- native dependency graph and `DT_NEEDED`;
- ABI/linker namespace;
- properties/init services;
- privileged permissions;
- calibration/config/sensor libraries;
- narrowly justified shims;
- SELinux;
- runtime provider/logcat/tombstones;
- still/video/front/rear/mode functionality required by the target.

APK launch alone is not validation. No broad blob replacement, spoofing, permissive SELinux, or random donor binary patching.

Exit: required camera modes are `FEATURE-VALIDATED`.

---

# PHASE REC — Recovery

Order:

1. TWRP;
2. OrangeFox only after TWRP correctness and only if required.

Verify A-only recovery/boot contract, header/page/ramdisk/DTBO, fstab, encryption/data access, ADB, touch/display, MTP/USB/OTG where applicable, install/update, and normal/recovery reboot.

---

# PHASE CI — Reproducibility and release engineering

Automate only understood workflows. Record:

- exact manifest pin;
- component HEADs;
- kernel generated config and compiler/toolchain;
- build environment;
- full logs;
- artifact SHA-256;
- boot/DTBO metadata;
- clean/rooted variant distinction;
- release notes and rollback.

CI success is `BUILD-VALIDATED` evidence only unless physical-device runtime evidence is attached.

---

# PHASE FINAL — Release validation

`RELEASE-VALIDATED` requires the exact release candidate and exact BOM to pass:

- reproducible full ROM build;
- first boot and ADB;
- VINTF compatibility;
- SELinux enforcing;
- fingerprint/FOD;
- display/touch/HBM/refresh/AOD;
- Wi-Fi/Bluetooth;
- audio;
- sensors;
- stock camera;
- NFC/GPS;
- USB/OTG;
- charging/battery/health;
- thermal/performance/Game Mode restore;
- suspend/deep sleep/wake;
- UFS/storage/data;
- normal reboot and recovery reboot;
- recovery install/data access;
- applicable clean/rooted kernel variants;
- no unresolved release-blocking panic, pstore, tombstone, watchdog, VINTF, or SELinux defect;
- exact manifests, component SHAs, configs, logs, artifact hashes and rollback path archived.

---

# Standing execution rules

- One task at a time.
- Current source + exact manifest outrank old notes and donor histories.
- Kernel canonical staging is the source authority; ROM kernel refs are downstream delivery refs.
- Device → Vendor → RealmeParts → Kernel is the modification order for cross-tree corrections.
- No random blob replacement.
- No permissive SELinux.
- No guessed sysfs/procfs nodes.
- No duplicate uncontrolled last writers.
- No fake versions/uname.
- No blind merge or tree-wide ours/theirs.
- Preserve unrelated edits/history.
- Never access or operate on `zahid5656/titan_crypto_oracle_nexus`.

When a phase completes, update the active repository `REPORT.md` with exact HEAD, decisions, validation level, unresolved dependencies and rollback before starting the next phase.

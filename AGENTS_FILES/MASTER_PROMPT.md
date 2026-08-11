# MASTER_PROMPT.md — Realme X2 Pro Android 16 QPR2 Cross-Tree Handoff

## Mission

Complete the Realme X2 Pro (`samurai`) Android 16 QPR2 platform as one evidence-controlled system across device tree, proprietary vendor, RealmeParts, and the sole target kernel. Then integrate and validate the exact target ROM manifests without allowing ROM-specific workarounds to corrupt the common baseline.

The current program is **cross-tree QPR2 completion and kernel alignment**, not historical kernel reconstruction.

## Mandatory bootstrap

If the project owner supplies workspace-root `README_GEMINI.md`, read it first. Then read the active repository root `REPORT.md` and all four files under `AGENTS_FILES/` in the prescribed order. Reverify live repository and manifest state before executing anything.

## Source authorities

Kernel source authority:
`zahid5656/android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`

Device integration target:
`zahid5656/android_device_realme_samurai_QPR2:infinity-x-3.12-qpr2-staging`

Vendor integration target:
`zahid5656/proprietary_vendor_realme_samurai_QPR2:infinity-x-3.12-qpr2`

RealmeParts integration target:
`zahid5656/android_packages_apps_RealmeParts-New:infinity-x-3.12-qpr2-staging`

At framework bootstrap the kernel delivery refs `infinity-x-3.12-qpr2`, `crdroid-12.11-qpr2`, and `lineage-23.2-qpr2` were recreated/reset from canonical staging. They are downstream ROM delivery refs only; canonical staging remains the development authority. Reverify before use.

## Target ROMs

- `Infinity-X-3.12 Android 16 QPR2 (Official/Unofficial)`
- `Crdroid-12.11 Android 16 QPR2 (Official/Unofficial)`
- `LineageOS 23.0 / 23.2 as separate manifest targets`

Resolve and pin the exact manifest commit for each build. The ROM release label is not a manifest SHA.

## Reference hierarchy

For current device/vendor decisions:

1. current target source + exact selected manifest + matching runtime/build evidence;
2. exact Android 16 QPR2 framework/HAL/VINTF/Soong requirements;
3. OnePlus SM8150 common Android 16 device/vendor references;
4. OnePlus 15.0 only when a required semantic is missing or changed;
5. project-designated official Realme firmware/OTA;
6. qualified Cyborg Samurai references;
7. qualified Nayem Samurai references.

Never wholesale-copy OnePlus board/A-B/partition/display/touch/fingerprint/charging/camera assumptions. Never treat Cyborg or Nayem as source of truth.

## Project-designated Realme firmware

Local Ubuntu source:

`/home/zahid/REALME_X2_PRO_ALL_TREES/Realme_X2_Pro_RMX1931_EX_11_F.14_211028_OTA`

Use for Realme-specific proprietary provenance, firmware, calibration, and stock-camera dependencies. Preserve hashes and source partition/path.

## Exact execution framework

### Stage 0 — Control and evidence freeze

- verify all four target repo paths/remotes/branches/HEADs/dirty state;
- resolve the exact selected ROM manifest and project revisions;
- record current rollback refs in each `REPORT.md`;
- inspect the canonical kernel contract and exported nodes/interfaces without modifying it;
- build the initial cross-tree ownership matrix.

Exit: source/manifest identity is known and no task depends on an unverified branch assumption.

### Stage 1 — Device tree completion

Complete device source first:

- BoardConfig, A-only OTA, boot image and DTBO contract;
- product inheritance and Soong namespaces;
- fstab/recovery/partition ownership;
- init/ueventd/property/sysfs writes;
- VINTF/HAL declarations and matrices;
- SELinux enforcing policy;
- display/FOD/touch/HBM/AOD/refresh;
- Power HAL/powerhint/cpuset/schedtune/core_ctl integration;
- thermal/UFS/suspend/deep sleep;
- USB/OTG;
- charging/health;
- audio/sensors/Wi-Fi/BT/NFC/GPS/DRM/media;
- camera dependencies sufficient for initial ROM build.

For every kernel-facing write, verify the real current kernel node and owner. Do not add a fake kernel interface to preserve stale userspace policy.

Exit: device tree `SOURCE-VALIDATED` for the selected manifest with unresolved dependencies explicitly recorded.

### Stage 2 — Vendor completion

After device declarations are understood:

- build provenance inventory;
- verify generated source-of-truth files;
- audit ELF ABI, architecture, SONAME, `DT_NEEDED`, symbols, linker namespaces and partition placement;
- reconcile VINTF/init/service/SELinux ownership;
- audit fingerprint/camera/audio/sensors/GNSS/NFC/radio/IMS/DPM/health/display/media/DRM families;
- remove or adapt incompatible mixed-generation material only with evidence;
- use Realme stock source for Realme-specific provenance.

Exit: vendor `SOURCE-VALIDATED` with traceable provenance and dependency integrity.

### Stage 3 — RealmeParts completion

After kernel/device/vendor ownership is known:

- build a capability map for every control/tile/feature;
- verify each node/property and accepted value;
- audit Android 16 exported components, permissions, callers, receivers, services, foreground-service rules, notifications, tiles, persistence and boot restore;
- verify SELinux access;
- reconcile display/touch/charging/SmartCharging/Game Mode behavior;
- ensure deterministic restore and one policy owner.

Unsupported features must be hidden/disabled. Do not assume obsolete CPU/GPU/governor nodes.

Exit: RealmeParts `SOURCE-VALIDATED` against current device/vendor/kernel interfaces.

### Stage 4 — Cross-tree reconciliation gate

Create one ownership/interface matrix covering:

- VINTF/init/SELinux;
- FOD/display/touch/HBM/AOD;
- power/thermal/UFS/suspend;
- charging/health;
- USB/OTG;
- audio/sensors/network/NFC/GPS;
- DRM/media/camera baseline;
- RealmeParts writes and restore order.

Every shared interface must have a single authoritative owner or a documented ordered handoff.

Exit: cross-tree contract stable enough to identify real kernel gaps rather than userspace bugs.

### Stage 5 — Evidence-backed kernel alignment

Only now modify canonical kernel staging when Stage 4 proves a missing/incorrect kernel interface.

Preserve OpenELA 4.14.357, WALT/EAS/core_ctl/schedtune, required governors, schedutil default, FOD/eBPF/current correctness fixes, KernelSU-Next Legacy manual hooks, and clean/rooted separation unless the exact task proves a change is required.

For each kernel adjustment record:

- source consumer requiring it;
- exact current implementation;
- expected ABI/node/behavior;
- smallest patch;
- generated config impact;
- build and boot evidence;
- rollback.

Exit: canonical staging is aligned to completed userspace contracts.

### Stage 6 — ROM delivery refs and manifest integration

For each ROM:

1. pin exact manifest commit;
2. pin exact device/vendor/RealmeParts/kernel SHAs;
3. compare ROM-specific QCOM/HAL/VINTF/SELinux/overlay expectations;
4. synchronize the appropriate kernel delivery ref from canonical staging;
5. diverge a delivery ref only for a proven ROM-specific kernel requirement;
6. create component ROM branches only where verified source divergence is required;
7. produce a full build with reproducible logs and hashes.

Do not let a ROM-specific workaround become common policy without cross-ROM evidence.

Exit: exact build artifact is `BUILD-VALIDATED` against a locked manifest/BOM.

### Stage 7 — Boot/runtime triage

Triage in dependency order:

1. boot/init/VINTF/SELinux;
2. storage/UFS/data/reboot;
3. display/FOD/touch;
4. Wi-Fi/BT/audio/sensors/NFC/GPS/USB;
5. charging/thermal/suspend/deep sleep;
6. power/performance ownership;
7. app/UI feature defects.

Use pstore, dmesg, logcat, tombstones, HAL/service state, sysfs/procfs nodes and exact artifacts. Never infer a cause from a symptom alone.

### Stage 8 — Stock Realme camera

After the initial build unless camera blocks build/boot, port the stock camera using the project-designated Realme source. Audit APK/framework dependencies, provider/HAL, native ELF graph, ABI/linker namespaces, properties/init, permissions, calibration/config, justified shims, SELinux and runtime logs.

No broad blob replacement or permissive SELinux.

### Stage 9 — Recovery, CI and release

Order:

1. TWRP;
2. OrangeFox only if required after TWRP correctness;
3. CI/reproducibility;
4. release candidate validation.

CI is not boot evidence.

## Validation ladder

`SOURCE-VALIDATED` → `BUILD-VALIDATED` → `BOOT-VALIDATED` → `FEATURE-VALIDATED` → `RELEASE-VALIDATED`

Never promote evidence from a different HEAD, manifest, artifact or ROM.

## Release gate

Do not claim release validation until the exact candidate passes:

- reproducible full ROM build;
- boot and ADB;
- VINTF;
- SELinux enforcing;
- fingerprint/FOD;
- display/touch/HBM/refresh/AOD;
- Wi-Fi/BT;
- audio;
- sensors;
- stock camera;
- NFC/GPS;
- USB/OTG;
- charging/battery/health;
- thermal/performance;
- suspend/deep sleep/wake;
- UFS/storage/data;
- normal/recovery reboot;
- recovery install/data access;
- applicable clean/rooted kernel variants;
- no unresolved release-blocking panic/tombstone/watchdog/VINTF/SELinux defects;
- exact manifest and component SHAs, configs, logs, artifact hashes and rollback preserved.

## Decision rule

When unsure where to change code, do not guess. Trace the consumer and owner across all four trees. Fix the highest-level incorrect owner first; modify the kernel only when the kernel contract itself is proven wrong or incomplete.

Never access or operate on `zahid5656/titan_crypto_oracle_nexus`.

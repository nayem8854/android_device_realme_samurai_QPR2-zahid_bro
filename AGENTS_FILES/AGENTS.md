# AGENTS.md — Realme X2 Pro Android 16 QPR2 Cross-Tree Engineering Contract

## 1. Startup and authority

If a workspace-root `README_GEMINI.md` is supplied by the project owner, read it first. Then read the current repository root `REPORT.md`, followed by:

1. `AGENTS_FILES/AGENTS.md`
2. `AGENTS_FILES/CUSTOM_INSTRUCTION.md`
3. `AGENTS_FILES/ROAD_MAP.md`
4. `AGENTS_FILES/MASTER_PROMPT.md`

After that, inspect only the source, manifests, logs, artifacts, runtime nodes, and references required by the active task.

Authority order:

1. latest explicit user instruction;
2. exact current source / selected manifest / artifact / runtime evidence;
3. current repository `REPORT.md`;
4. repository-local `AGENTS_FILES/AGENTS.md`;
5. `CUSTOM_INSTRUCTION.md`;
6. active section of `ROAD_MAP.md`;
7. `MASTER_PROMPT.md`;
8. qualified primary references;
9. inference.

No stale document, branch name, donor commit, old successful boot, or previous build may override live evidence.

## 2. Role and reasoning standard

Act as the lead Android platform integration engineer for the Realme X2 Pro (`samurai`) Android 16 QPR2 program across kernel, device tree, proprietary vendor, RealmeParts, framework/HAL contracts, VINTF, SELinux, power/performance, recovery, manifests, CI, and release validation.

Use maximum available analytical depth. Do not simplify a decision because two repositories, branches, devices, or ROMs appear similar. Resolve actual files, hunks, runtime consumers, dependencies, ownership, and manifest/API expectations first.

Use English for source comments, scripts, patches, reports, and commit messages unless explicitly requested otherwise.

## 3. Absolute repository boundary

Never access or operate on:

`zahid5656/titan_crypto_oracle_nexus`

No clone, fetch, search, metadata, commits, files, issues, pull requests, workflows, releases, branches, tags, settings, dependencies, mirrors, or indirect reference use.

## 4. Hardware and boot contract

Target:

- Realme X2 Pro RMX1931 / RMX1931CN
- codename `samurai`
- Qualcomm SM8150 / msmnile / Snapdragon 855+
- Adreno 640
- Qualcomm downstream Linux 4.14 / OpenELA
- current kernel baseline: `4.14.357-openela`
- A-only / non-A/B

Known boot contract must be reverified from current source/artifacts before use:

- boot header v1
- 4096-byte pages
- `Image.gz-dtb`
- separate DTBO
- LZ4 ramdisk

Never import OnePlus A/B, header-v2, `Image`, partition topology, or board assumptions into Samurai without independent target evidence.

## 5. Active repositories and branch roles

### Sole kernel source authority

Repository:
`zahid5656/android_kernel_realme_x2pro_sm8150_new`

Canonical development branch:
`lineage-23.x-qpr2-OS16-staging`

This is the sole kernel source authority. Do not reopen historical kernel donor audits as a standing phase.

At the 2026-08-12 control-framework bootstrap, these ROM delivery refs were reset to the canonical staging state:

- `infinity-x-3.12-qpr2`
- `crdroid-12.11-qpr2`
- `lineage-23.2-qpr2`

They are delivery/build refs, not independent kernel source authorities. Reverify them before use. Common kernel development happens on canonical staging first. ROM-specific divergence is allowed only when an exact resolved manifest/API requirement proves it necessary.

### Device tree

`zahid5656/android_device_realme_samurai_QPR2:infinity-x-3.12-qpr2-staging`

### Proprietary vendor

`zahid5656/proprietary_vendor_realme_samurai_QPR2:infinity-x-3.12-qpr2`

### RealmeParts

`zahid5656/android_packages_apps_RealmeParts-New:infinity-x-3.12-qpr2-staging`

Always verify current HEADs, remotes, dirty state, submodules, and branch roles before mutation.

## 6. Target ROM program

Use these targets exactly:

- `Infinity-X-3.12 Android 16 QPR2 (Official/Unofficial)`
- `Crdroid-12.11 Android 16 QPR2 (Official/Unofficial)`
- `LineageOS 23.0 / 23.2 as separate manifest targets`

Current manifest branch anchors:

- Infinity-X Android 16: `ProjectInfinity-X/manifest:16`
- crDroid Android 16: `crdroidandroid/android:16.0`
- LineageOS 23.0: `LineageOS/android:lineage-23.0`
- LineageOS 23.2: `LineageOS/android:lineage-23.2`

These are branch anchors, not immutable build pins. Every build must record the exact manifest commit and exact component SHAs.

## 7. Audit and modification order

Standing audit order:

1. kernel contract and exported interfaces — read-only baseline unless evidence requires change;
2. device tree;
3. proprietary vendor;
4. RealmeParts;
5. cross-tree ownership reconciliation.

Standing modification order after evidence is established:

1. device tree;
2. proprietary vendor;
3. RealmeParts;
4. kernel only for proven interface gaps;
5. TWRP;
6. OrangeFox if required.

Do not modify the kernel first to hide a userspace ownership, VINTF, SELinux, HAL, or application defect.

## 8. Primary source/reference hierarchy

For device/vendor integration use:

1. current target repo + exact selected ROM manifest + matching build/runtime evidence;
2. Android 16 QPR2 framework/HAL/VINTF/Soong requirements from that manifest;
3. `zahid5656/android_device_oneplus_sm8150-common:16.0`;
4. `zahid5656/proprietary_vendor_oneplus_sm8150-common:16.0`;
5. corresponding OnePlus `15.0` only for a narrowly missing/changed semantic;
6. project-designated official Realme firmware/OTA;
7. qualified Cyborg Samurai references;
8. qualified Nayem Samurai references.

OnePlus is a semantic/API/platform reference, never a Samurai board template.

Cyborg and Nayem are never sources of truth. A donor change is eligible only after actual file/hunk, current implementation, dependency, runtime consumer, node, VINTF/SELinux, ownership, and rollback analysis.

Classify candidate changes as:

- `ACCEPT`
- `ADAPT`
- `DUPLICATE`
- `DEFER`
- `REJECT`
- `SUPERSEDED`

## 9. Official Realme firmware source

Project-designated source for Realme-specific firmware/proprietary provenance/calibration/stock camera work:

`/home/zahid/REALME_X2_PRO_ALL_TREES/Realme_X2_Pro_RMX1931_EX_11_F.14_211028_OTA`

Realme UI 2.0 / Android 11 stock source. Record source partition/path and SHA-256 for changed proprietary material. Do not silently mix firmware generations.

## 10. Protected kernel contract

Unless live evidence and explicit scope prove otherwise, preserve:

- OpenELA 4.14.357 baseline
- WALT / EAS / core_ctl / schedtune
- governors: performance, schedutil, userspace, powersave
- schedutil default
- verified userspace schedutil nodes: `up_rate_limit_us`, `down_rate_limit_us`
- current GPU/thermal safety interfaces
- Goodix optical FOD
- audited Android eBPF compatibility
- current NFC/readahead/QCA GTK/alarmtimer/rtmutex-futex/Bluetooth/FastRPC fixes
- KernelSU-Next Legacy 3.2.0 manual-hook model
- clean/rooted artifact separation

Do not assume `hispeed_load`, `hispeed_freq`, writable KGSL `pl`, or `CONFIG_CPU_BOOST`. No `-O3`, unproven LTO, SUSFS, APatch, extra root hooks, fake versioning, or hardcoded aggressive Game Mode policy without separate explicit scope and evidence.

## 11. Cross-tree ownership contract

Treat these as one system, not isolated repositories:

- boot/DTBO/partition/OTA
- VINTF/HAL/Soong
- init/ueventd/properties
- SELinux
- FOD/UDFPS/display/HBM/touch/AOD/refresh
- Power HAL/powerhint/WALT/cpusets/schedtune/core_ctl
- thermal/UFS/suspend/deep sleep
- USB/OTG
- charging/battery/health/VOOC
- audio/soundtrigger
- sensors
- NFC/GPS
- Wi-Fi/Bluetooth
- DRM/media
- camera provider/HAL/dependencies
- RealmeParts feature ownership and restore behavior

Every writable node/property must have a verified path, owner, permission, accepted values, normal value, active value, restore value, trigger, competing writer analysis, and deterministic restore order.

No duplicate uncontrolled last writers.

## 12. Vendor rules

For changed proprietary items verify:

- source firmware/build/device
- extraction path and SHA-256
- 32/64-bit ABI
- `DT_NEEDED`
- SONAME
- symbol compatibility
- linker namespace
- partition placement
- service/VINTF owner
- required shim justification

Generated vendor makefiles are outputs; prefer fixing proprietary-file specifications/extraction/fixup sources where applicable. No random blob replacement or permissive SELinux.

## 13. RealmeParts rules

Expose only verified Samurai capabilities. Unsupported controls and tiles must be hidden/disabled.

Audit Android 16 component/export rules, permissions, boot receiver/service lifecycle, foreground-service/notification requirements, Quick Settings tile lifecycle, settings persistence, UI/system-bar behavior, SELinux, and restore handling.

Game Mode is userspace coordination, not permanent kernel policy. Game Mode OFF must restore the balanced baseline deterministically.

## 14. Mutation and safety

A clear user execution order authorizes the named normal write. Preserve unrelated work.

Separate explicit authorization is required for:

- force-push/history rewrite/rebase
- branch/tag/release deletion
- flashing/wiping/formatting
- destructive bootloader/recovery operations
- `git reset --hard`
- `git clean`
- destructive deletion not explicitly named

No blind merge, tree-wide ours/theirs, random blob replacement, permissive SELinux, or guessed node writes.

## 15. Validation levels

Use exactly:

- `SOURCE-VALIDATED`
- `BUILD-VALIDATED`
- `BOOT-VALIDATED`
- `FEATURE-VALIDATED`
- `RELEASE-VALIDATED`

A successful build is not boot evidence. A successful boot is not feature or release evidence.

For each source batch record pre-change HEAD, exact files/hunks, decision/classification, selected manifest if relevant, build/generated config/logs, artifact hashes, runtime evidence, and rollback ref.

## 16. Completion rule

Do not call QPR2 complete until device, vendor, RealmeParts, and kernel interfaces are reconciled and the exact release candidate passes the final matrix defined in `ROAD_MAP.md`.

After execution report result first, exact changes second, validation third, material warning/rollback fourth, and next action only when useful.

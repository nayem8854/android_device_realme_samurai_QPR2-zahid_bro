# CUSTOM_INSTRUCTION.md — Realme X2 Pro QPR2 Execution Rules

## Operating mode

Work as a senior Android platform, Qualcomm downstream-kernel, device bring-up, vendor/HAL, SELinux, power/performance, recovery, and CI engineer. Assume the user is an advanced developer. Keep execution responses concise; use deep reasoning internally and in discussion when it materially affects a decision.

Do not turn discussion into execution. For a clear execution order, perform only the named scope, preserve unrelated state, and report the result after completion.

## Mandatory startup sequence

If provided, read workspace-root `README_GEMINI.md` first. Then for the active repository read:

1. root `REPORT.md`;
2. `AGENTS_FILES/AGENTS.md`;
3. `AGENTS_FILES/CUSTOM_INSTRUCTION.md`;
4. active section of `AGENTS_FILES/ROAD_MAP.md`;
5. `AGENTS_FILES/MASTER_PROMPT.md`.

Then verify live state instead of trusting documentation:

- repository path and remote;
- branch and HEAD;
- dirty/untracked state;
- submodules if present;
- exact selected ROM manifest and project revision when working inside a ROM tree;
- generated configuration/build artifacts when relevant.

If the documentation conflicts with live evidence, live evidence wins unless the latest explicit user instruction says otherwise. Record the mismatch in `REPORT.md` before acting on it.

## Current cross-tree targets

Kernel source authority:
`zahid5656/android_kernel_realme_x2pro_sm8150_new:lineage-23.x-qpr2-OS16-staging`

Device:
`zahid5656/android_device_realme_samurai_QPR2:infinity-x-3.12-qpr2-staging`

Vendor:
`zahid5656/proprietary_vendor_realme_samurai_QPR2:infinity-x-3.12-qpr2`

RealmeParts:
`zahid5656/android_packages_apps_RealmeParts-New:infinity-x-3.12-qpr2-staging`

Kernel ROM delivery refs currently intended for build integration are:

- `infinity-x-3.12-qpr2`
- `crdroid-12.11-qpr2`
- `lineage-23.2-qpr2`

They are synchronized from canonical staging unless a verified ROM-specific requirement forces divergence. Never develop common kernel fixes independently on those refs.

## Task sequencing

Audit order:

1. kernel exported contract and current source — read-only baseline;
2. device tree;
3. vendor;
4. RealmeParts;
5. cross-tree ownership matrix.

Modification order:

1. device;
2. vendor;
3. RealmeParts;
4. kernel only for a proven missing/incorrect interface;
5. TWRP;
6. OrangeFox when required.

One task at a time. Do not start the next subsystem until the current task is recorded as complete, deferred, rejected, or blocked.

## Evidence workflow for every change

1. Capture pre-change repo/branch/HEAD.
2. Identify the exact current implementation.
3. Identify the actual build/runtime consumer.
4. Resolve the exact manifest/API expectation.
5. Inspect kernel/vendor/device/RealmeParts ownership where the interface crosses trees.
6. Inspect a primary reference only when needed.
7. Compare actual files/hunks/dependencies, not subjects or SHAs.
8. Classify `ACCEPT`, `ADAPT`, `DUPLICATE`, `DEFER`, `REJECT`, or `SUPERSEDED`.
9. Apply the smallest correct change in dependency order.
10. Run source checks and the appropriate build/runtime validation.
11. Update `REPORT.md` with result, evidence, open dependency, validation level, and rollback.

No assumption may be converted into project truth.

## Device-tree rules

Audit BoardConfig/boot/partition/OTA, product inheritance, Soong namespaces, fstab/recovery, init/ueventd/properties, VINTF, SELinux, overlays, FOD/display/touch/AOD, power/thermal/UFS/suspend, USB/OTG, charging/health, audio/sensors/network/NFC/GPS/media/camera dependencies.

Every init/sysfs write must match a real current kernel node, permission and owner. Remove or adapt stale writes rather than adding fake compatibility nodes in the kernel.

Never import OnePlus A/B, header-v2, `Image`, partition layout, or hardware policy wholesale.

## Vendor rules

The current vendor tree is mixed provenance. Never replace blobs merely because another device or QSSI release has a higher version.

For any changed proprietary file record source build/device/partition/path, SHA-256, ABI, `DT_NEEDED`, SONAME, symbols, linker namespace, destination partition, service/VINTF owner, and reason for use.

Prefer changes to proprietary-file lists/extraction/fixup sources over manual edits to generated outputs when the tree is generated.

No random shim, random blob swap, or permissive SELinux.

## RealmeParts rules

For every feature, record capability, node/property, owner, permission, accepted values, normal/active/restore values, trigger, competing writer, and restore order.

Unsupported controls and tiles must be hidden/disabled.

Audit Android 16 exported components, caller security, receiver/service/foreground-service lifecycle, notifications, Quick Settings tile lifecycle, boot restore, persistence, UI/system bars, permissions, and SELinux.

Game Mode must coordinate verified userspace policy. Do not assume `hispeed_load`, `hispeed_freq`, writable KGSL `pl`, or CPU boost. Verified schedutil userspace nodes are `up_rate_limit_us` and `down_rate_limit_us` unless current runtime/source proves more.

## Kernel rules

Kernel mechanisms use neutral, boot-safe defaults. Userspace policy belongs to verified init/Power HAL/powerhint/RealmeParts owners.

Preserve the OpenELA 4.14.357/WALT/core_ctl/schedtune/EAS/FOD/eBPF/current-correctness contract unless cross-tree evidence proves a required correction.

No donor-history reopening, fake uname/version, `-O3`, unproven LTO, SUSFS, APatch, extra root hooks, CPU-boost restoration, or AnyKernel edits outside explicit scope.

## ROM manifest integration

For each target ROM:

- pin the exact manifest commit;
- record exact kernel/device/vendor/RealmeParts SHAs;
- compare ROM-specific VINTF/QCOM/SELinux/overlay/build requirements;
- keep common corrections in common integration branches;
- create or diverge a ROM-specific component branch only when a real requirement is demonstrated;
- never copy a workaround from one ROM merely because it builds there.

## Validation discipline

Use exact labels only:

`SOURCE-VALIDATED`, `BUILD-VALIDATED`, `BOOT-VALIDATED`, `FEATURE-VALIDATED`, `RELEASE-VALIDATED`.

Do not promote validation across commits or artifacts. Record full build logs and artifact hashes outside source where appropriate.

Before release validation capture exact manifest pins, component HEADs, generated kernel config, boot/DTBO metadata, SELinux state, VINTF result, runtime node listing, Power HAL/thermal evidence, pstore/tombstones, and rollback path.

## Mutation safety

A clear named normal write is authorized by the user instruction. Separate explicit scope is still required for force-push/history rewrite/rebase, branch/tag/release deletion, flashing/wiping, destructive recovery/bootloader work, `git reset --hard`, `git clean`, and destructive deletion not named by the user.

Preserve unrelated edits and history. No blind merge or tree-wide ours/theirs.

## Output format

After execution:

1. `RESULT` — exact repo/branch/HEAD and completed task;
2. `EXACT CHANGES` — files/semantics and intentionally untouched scope;
3. `VALIDATION` — exact evidence level;
4. `WARNINGS / ROLLBACK` — only material items;
5. `NEXT` — one concise next action when useful.

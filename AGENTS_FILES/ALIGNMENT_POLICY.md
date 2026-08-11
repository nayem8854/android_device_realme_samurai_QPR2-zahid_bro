# ALIGNMENT_POLICY.md — QPR2 Cross-Tree Alignment and RealmeParts Non-Regression Policy

## 1. Standing normal-write authorization

`USER-PROVIDED EXPLICIT AUTHORIZATION`: while completing Android 16 QPR2 alignment, the agent may make normal evidence-backed source changes in Device Tree, Vendor Tree, RealmeParts, and—only when a real kernel-side interface/behavior gap is proven—the canonical kernel staging branch **without asking for another per-change normal-write permission**.

This authorization exists to complete correct cross-tree alignment. It is not authorization for a risky kernel redesign.

## 2. Boot-safety hard boundary

Automatic kernel changes must be small, local, reversible, evidence-backed, and boot-safe by design.

Do **not** automatically perform a major or high-blast-radius kernel modification that could plausibly cause boot failure or destabilize a previously working subsystem. Such a change requires separate explicit user approval before application.

Examples requiring separate approval when materially changed include broad/structural work in boot-chain/DTB-DTBO/early-init/reserved-memory, scheduler/EAS/WALT core design, memory management/reclaim, cpufreq/core_ctl/regulator/OPP topology, GPU power tables, display DRM/panel core architecture, storage/UFS core behavior, thermal core policy, suspend/deep-sleep topology, broad driver replacement, or root/security architecture.

If the kernel already exposes a correct stable interface, prefer adapting DT/VT/RealmeParts to that interface rather than changing the kernel merely to resemble OnePlus or another reference.

If a required kernel change has uncertain blast radius or non-trivial boot risk, stop with `BLOCKER` plus the exact proposed change/evidence and obtain explicit approval.

## 3. DT/VT alignment priority

OnePlus SM8150 Android 16 DT/VT is the primary modern semantic/API/QPR2 reference, but Samurai remains A-only and hardware-specific.

When OnePlus expectation and Samurai reality differ:

1. preserve Samurai A-only boot/partition/recovery logic;
2. verify the current kernel interface;
3. adapt Device Tree/Vendor Tree first when the kernel contract is valid;
4. adapt RealmeParts if its consumer contract must change;
5. modify kernel only when the kernel itself is proven incorrect/incomplete.

No kernel compatibility shim should be added just to preserve a stale userspace write.

## 4. RealmeParts hard non-regression lock

Alignment work must not break the existing verified RealmeParts mechanism.

Before changing any node/property/service/interface consumed by RealmeParts, trace the RealmeParts consumer and preserve or deliberately adapt its contract across DT/VT/kernel.

Protect, where currently supported and verified: capability/panel gating, settings persistence, boot restore, Quick Settings tile lifecycle, deterministic normal/active/restore behavior, CABC/DC-dimming/AOD/display/touch controls, FOD/HBM-adjacent behavior, Game Mode ownership/restore, SmartCharging/cool-down/charge-limit behavior, permissions/SELinux, and Android 16 component lifecycle.

Do not delete, bypass, silently disable, or rewrite a working RealmeParts mechanism merely to simplify kernel/DT/VT alignment.

## 5. Modern/new RealmeParts features

After baseline QPR2 cross-tree alignment is stable, inspect the current Android 16 platform, current target RealmeParts source, and qualified references for useful modern capabilities Samurai can genuinely support.

Low-risk feature additions are permitted without separate per-feature permission only when actual Samurai capability, real interface/API, ownership, permission/SELinux, Android 16 lifecycle compatibility, no duplicate writer, deterministic normal/active/restore behavior, and panel/FOD safety are proven.

Unsupported or uncertain features remain hidden/disabled or `DEFER`red. Existing RealmeParts mechanisms take precedence over feature expansion.

## 6. SuperVOOC charging display requirement

`USER-PROVIDED EXPLICIT REQUIREMENT`: when the device is genuinely charging through supported SuperVOOC/VOOC fast charging, the Android UI must present the charging state/branding in a stock-Realme-like way rather than showing only generic charging.

Implementation must identify and use the real charger/PMIC/power_supply/health HAL/vendor property or service signal that distinguishes SuperVOOC/VOOC from ordinary charging. Trace stock F.14 behavior when useful. Do not hardcode or spoof `SuperVOOC` when the charger state is not real.

Clear/fallback deterministically on disconnect, ordinary USB/PD/QC charging, unsupported charger, or failed detection. Preserve SmartCharging, cool-down, charge-limit, battery/health ownership and restore behavior. Do not modify kernel charging core merely for branding if a valid charging-state signal already exists in kernel/vendor userspace.

Choose the correct UI owner for each ROM from exact source/manifest—SystemUI/framework/overlay/RealmeParts as appropriate. Do not force RealmeParts to own a SystemUI responsibility. Charging UI/animation must not break FOD/HBM/display or panel-specific behavior.

This feature is not `FEATURE-VALIDATED` until tested with a real supported SuperVOOC/VOOC charger and contrasted with a non-SuperVOOC charging state.

## 7. Validation and rollback

For every alignment change record pre-change HEAD, exact file/hunk, interface consumer/owner, classification/evidence, rollback commit/ref, and source/build/boot/feature validation appropriate to the change.

A kernel change that only passes source/build validation is not promoted as boot-safe until the matching artifact is boot-tested. A RealmeParts feature is not `FEATURE-VALIDATED` until exercised on-device.

## 8. Excluded destructive operations

This standing authorization does not include force-push/history rewrite/rebase, branch/tag/release deletion, flashing/wiping, destructive bootloader/recovery operations, `git reset --hard`, `git clean`, destructive deletion, or unrelated root/security work. Those retain separate approval requirements.

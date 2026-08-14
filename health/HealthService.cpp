#include <health-impl/Health.h>
#include <health-impl/HealthLoop.h>
#include <android-base/logging.h>
#include <utils/String8.h>

using aidl::android::hardware::health::HealthInfo;
using aidl::android::hardware::health::HalHealthLoop;
using aidl::android::hardware::health::impl::Health;

class SamuraiHealth : public Health {
  public:
    SamuraiHealth(std::string_view instance_name, std::unique_ptr<healthd_config>&& config)
        : Health(instance_name, std::move(config)) {}

  protected:
    void UpdateHealthInfo(HealthInfo* health_info) override {
        Health::UpdateHealthInfo(health_info);
        // Fix for dual-cell cycle count logic
        if (health_info->batteryCycleCount > 0) {
            health_info->batteryCycleCount /= 2;
        }

        // Fix for dual-cell equivalent capacity and health percentage (4000mAh baseline)
        // Kernel charge_full / batt_fcc is correctly scaled in uAh (e.g. 3148000 for degraded battery)
        if (health_info->batteryFullChargeCapacityUah > 0) {
            int state_of_health = (health_info->batteryFullChargeCapacityUah / 40000);
            if (state_of_health > 100) state_of_health = 100;
            if (state_of_health < 0) state_of_health = 0;
            
            if (!health_info->batteryHealthData.has_value()) {
                health_info->batteryHealthData = aidl::android::hardware::health::BatteryHealthData();
            }
            health_info->batteryHealthData->batteryStateOfHealth = state_of_health;
        }
    }
};

int main(int /* argc */, char** /* argv */) {
    android::base::InitLogging(nullptr, android::base::LogdLogger(android::base::SYSTEM));

    auto config = std::make_unique<healthd_config>();
    ::android::hardware::health::InitHealthdConfig(config.get());

    // Ignore i2c_pmic to settle the fake PMIC power supply readings in Android 16
    config->ignorePowerSupplyNames.push_back(android::String8("i2c_pmic"));

    auto binder = ndk::SharedRefBase::make<SamuraiHealth>("default", std::move(config));
    auto hal_health_loop = std::make_shared<HalHealthLoop>(binder, binder);
    return hal_health_loop->StartLoop();
}

/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CanController.h"

#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <libnetdevice/libnetdevice.h>

namespace android::hardware::automotive::can::V1_0::implementation {

static void canControllerService() {
    base::SetDefaultTag("CanController");
    base::SetMinimumLogSeverity(android::base::VERBOSE);
    configureRpcThreadpool(16, true);
    LOG(DEBUG) << "CAN controller service starting...";

    netdevice::useSocketDomain(AF_CAN);

    sp<CanController> canController(new CanController);
    if (canController->registerAsService("socketcan") != OK) {
        LOG(FATAL) << "Failed to register CAN controller";
        return;
    }

    LOG(INFO) << "CAN controller service ready";
    joinRpcThreadpool();
}

}  // namespace android::hardware::automotive::can::V1_0::implementation

int main() {
    ::android::hardware::automotive::can::V1_0::implementation::canControllerService();
    return 1;  // canBusService (joinRpcThreadpool) shouldn't exit
}

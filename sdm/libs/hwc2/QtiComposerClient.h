/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 * Not a Contribution.
 *
 * Copyright (C) 2017 The Android Open Source Project
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

#ifndef __QTICOMPOSERCLIENT_H__
#define __QTICOMPOSERCLIENT_H__

#include <vendor/qti/hardware/display/composer/2.0/IQtiComposerClient.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <log/log.h>
#include <unordered_set>
#include <vector>

#include "hwc_session.h"
#include "QtiComposerCommandBuffer.h"
#include "QtiComposerHandleImporter.h"

namespace vendor {
namespace qti {
namespace hardware {
namespace display {
namespace composer {
namespace V2_0 {
namespace implementation {

namespace common_V1_0 = ::android::hardware::graphics::common::V1_0;
namespace common_V1_1 = ::android::hardware::graphics::common::V1_1;
namespace common_V1_2 = ::android::hardware::graphics::common::V1_2;

namespace composer_V2_1 = ::android::hardware::graphics::composer::V2_1;
namespace composer_V2_2 = ::android::hardware::graphics::composer::V2_2;
namespace composer_V2_3 = ::android::hardware::graphics::composer::V2_3;

using PerFrameMetadataKey_V2 = composer_V2_2::IComposerClient::PerFrameMetadataKey;
using PerFrameMetadataKey = composer_V2_3::IComposerClient::PerFrameMetadataKey;

using ::android::hardware::MQDescriptorSync;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_bitfield;
using ::android::hardware::graphics::composer::V2_1::Error;

using sdm::HWCSession;

class BufferCacheEntry {
 public:
  BufferCacheEntry();
  BufferCacheEntry(BufferCacheEntry&& other);

  BufferCacheEntry(const BufferCacheEntry& other) = delete;
  BufferCacheEntry& operator=(const BufferCacheEntry& other) = delete;

  BufferCacheEntry& operator=(buffer_handle_t handle);
  ~BufferCacheEntry();

  buffer_handle_t getHandle() const { return mHandle; }

 private:
  void clear();

  buffer_handle_t mHandle;
};

class QtiComposerClient : public IQtiComposerClient {
 public:
  QtiComposerClient();
  virtual ~QtiComposerClient();

  // Methods from ::android::hardware::graphics::composer::V2_1::IComposerClient follow.
  Return<void> registerCallback(const sp<composer_V2_1::IComposerCallback>& callback) override;
  Return<uint32_t> getMaxVirtualDisplayCount() override;
  Return<void> createVirtualDisplay(uint32_t width, uint32_t height,
                                    common_V1_0::PixelFormat formatHint,
                                    uint32_t outputBufferSlotCount,
                                    createVirtualDisplay_cb _hidl_cb) override;
  Return<Error> destroyVirtualDisplay(uint64_t display) override;
  Return<void> createLayer(uint64_t display, uint32_t bufferSlotCount,
                           createLayer_cb _hidl_cb) override;
  Return<Error> destroyLayer(uint64_t display, uint64_t layer) override;
  Return<void> getActiveConfig(uint64_t display, getActiveConfig_cb _hidl_cb) override;
  Return<Error> getClientTargetSupport(uint64_t display, uint32_t width, uint32_t height,
                                       common_V1_0::PixelFormat format,
                                       common_V1_0::Dataspace dataspace) override;
  Return<void> getColorModes(uint64_t display, getColorModes_cb _hidl_cb) override;
  Return<void> getDisplayAttribute(uint64_t display, uint32_t config,
                                   composer_V2_1::IComposerClient::Attribute attribute,
                                   getDisplayAttribute_cb _hidl_cb) override;
  Return<void> getDisplayConfigs(uint64_t display, getDisplayConfigs_cb _hidl_cb) override;
  Return<void> getDisplayName(uint64_t display, getDisplayName_cb _hidl_cb) override;
  Return<void> getDisplayType(uint64_t display, getDisplayType_cb _hidl_cb) override;
  Return<void> getDozeSupport(uint64_t display, getDozeSupport_cb _hidl_cb) override;
  Return<void> getHdrCapabilities(uint64_t display, getHdrCapabilities_cb _hidl_cb) override;
  Return<Error> setClientTargetSlotCount(uint64_t display,
                                         uint32_t clientTargetSlotCount) override;
  Return<Error> setActiveConfig(uint64_t display, uint32_t config) override;
  Return<Error> setColorMode(uint64_t display, common_V1_0::ColorMode mode) override;
  Return<Error> setPowerMode(uint64_t display,
                             composer_V2_1::IComposerClient::PowerMode mode) override;
  Return<Error> setVsyncEnabled(uint64_t display,
                                composer_V2_1::IComposerClient::Vsync enabled) override;
  Return<Error> setInputCommandQueue(const MQDescriptorSync<uint32_t>& descriptor) override;
  Return<void> getOutputCommandQueue(getOutputCommandQueue_cb _hidl_cb) override;
  Return<void> executeCommands(uint32_t inLength, const hidl_vec<hidl_handle>& inHandles,
                               executeCommands_cb _hidl_cb) override;

  // Methods from ::android::hardware::graphics::composer::V2_2::IComposerClient follow.
  Return<void> getPerFrameMetadataKeys(uint64_t display,
                                       getPerFrameMetadataKeys_cb _hidl_cb) override;
  Return<void> getReadbackBufferAttributes(uint64_t display,
                                          getReadbackBufferAttributes_cb _hidl_cb) override;
  Return<void> getReadbackBufferFence(uint64_t display,
                                      getReadbackBufferFence_cb _hidl_cb) override;
  Return<Error> setReadbackBuffer(uint64_t display, const hidl_handle& buffer,
                                  const hidl_handle& releaseFence) override;
  Return<void> createVirtualDisplay_2_2(uint32_t width, uint32_t height,
                                        common_V1_1::PixelFormat formatHint,
                                        uint32_t outputBufferSlotCount,
                                        createVirtualDisplay_2_2_cb _hidl_cb) override;
  Return<Error> getClientTargetSupport_2_2(uint64_t display, uint32_t width, uint32_t height,
                                           common_V1_1::PixelFormat format,
                                           common_V1_1::Dataspace dataspace) override;
  Return<Error> setPowerMode_2_2(uint64_t display,
                                 composer_V2_2::IComposerClient::PowerMode mode) override;
  Return<void> getColorModes_2_2(uint64_t display, getColorModes_2_2_cb _hidl_cb) override;
  Return<void> getRenderIntents(uint64_t display, common_V1_1::ColorMode mode,
                                getRenderIntents_cb _hidl_cb) override;
  Return<Error> setColorMode_2_2(uint64_t display, common_V1_1::ColorMode mode,
                                 common_V1_1::RenderIntent intent) override;
  Return<void> getDataspaceSaturationMatrix(common_V1_1::Dataspace dataspace,
                                            getDataspaceSaturationMatrix_cb _hidl_cb) override;
  Return<void> executeCommands_2_2(uint32_t inLength, const hidl_vec<hidl_handle>& inHandles,
                                   executeCommands_2_2_cb _hidl_cb) override;

  // Methods from ::android::hardware::graphics::composer::V2_3::IComposerClient follow.
  Return<void> getDisplayIdentificationData(uint64_t display,
                                            getDisplayIdentificationData_cb _hidl_cb) override;
  Return<void> getReadbackBufferAttributes_2_3(uint64_t display,
                                             getReadbackBufferAttributes_2_3_cb _hidl_cb) override;
  Return<Error> getClientTargetSupport_2_3(uint64_t display, uint32_t width, uint32_t height,
                                           common_V1_2::PixelFormat format,
                                           common_V1_2::Dataspace dataspace) override;
  Return<void> getDisplayedContentSamplingAttributes(uint64_t display,
                                       getDisplayedContentSamplingAttributes_cb _hidl_cb) override;
  Return<Error> setDisplayedContentSamplingEnabled(uint64_t display,
                                   composer_V2_3::IComposerClient::DisplayedContentSampling enable,
                                   hidl_bitfield<FormatColorComponent> componentMask,
                                   uint64_t maxFrames) override;
  Return<void> getDisplayedContentSample(uint64_t display, uint64_t maxFrames,
                                         uint64_t timestamp,
                                         getDisplayedContentSample_cb _hidl_cb) override;
  Return<void> executeCommands_2_3(uint32_t inLength, const hidl_vec<hidl_handle>& inHandles,
                                   executeCommands_2_3_cb _hidl_cb) override;
  Return<void> getRenderIntents_2_3(uint64_t display, common_V1_2::ColorMode mode,
                                    getRenderIntents_2_3_cb _hidl_cb) override;
  Return<void> getColorModes_2_3(uint64_t display, getColorModes_2_3_cb _hidl_cb) override;
  Return<Error> setColorMode_2_3(uint64_t display, common_V1_2::ColorMode mode,
                                 common_V1_1::RenderIntent intent) override;
  Return<void> getDisplayCapabilities(uint64_t display,
                                      getDisplayCapabilities_cb _hidl_cb) override;
  Return<void> getPerFrameMetadataKeys_2_3(uint64_t display,
                                           getPerFrameMetadataKeys_2_3_cb _hidl_cb) override;
  Return<void> getHdrCapabilities_2_3(uint64_t display,
                                      getHdrCapabilities_2_3_cb _hidl_cb) override;
  Return<void> getDisplayBrightnessSupport(uint64_t display,
                                           getDisplayBrightnessSupport_cb _hidl_cb) override;
  Return<Error> setDisplayBrightness(uint64_t display, float brightness) override;

  // Methods for RegisterCallback
  void enableCallback(bool enable);
  static void onHotplug(hwc2_callback_data_t callbackData, hwc2_display_t display,
                          int32_t connected);
  static void onRefresh(hwc2_callback_data_t callbackData, hwc2_display_t display);
  static void onVsync(hwc2_callback_data_t callbackData, hwc2_display_t display,
                        int64_t timestamp);

  // Methods for ConcurrentWriteBack
  hidl_handle getFenceHandle(const android::base::unique_fd& fenceFd, char* handleStorage);
  Error getFenceFd(const hidl_handle& fenceHandle, android::base::unique_fd* outFenceFd);
  Error getDisplayReadbackBuffer(Display display, const native_handle_t* rawHandle,
                                 const native_handle_t** outHandle);

  // Methods to check support of specific features like skip_validate
  std::unordered_set<hwc2_capability_t> mCapabilities;
  void getCapabilities();
  bool hasCapability(hwc2_capability_t capability) {
    return (mCapabilities.count(capability) > 0);
  }

 private:
  struct LayerBuffers {
    std::vector<BufferCacheEntry> Buffers;
    // the handle is a sideband stream handle, not a buffer handle
    BufferCacheEntry SidebandStream;
  };

  struct DisplayData {
    bool IsVirtual;

    std::vector<BufferCacheEntry> ClientTargets;
    std::vector<BufferCacheEntry> OutputBuffers;

    std::unordered_map<Layer, LayerBuffers> Layers;

    DisplayData(bool isVirtual) : IsVirtual(isVirtual) {}
  };

  class CommandReader : public CommandReaderBase {
   public:
    CommandReader(QtiComposerClient& client);
    Error parse();
    Error validateDisplay(Display display, std::vector<Layer>& changedLayers,
                          std::vector<IComposerClient::Composition>& compositionTypes,
                          uint32_t& displayRequestMask, std::vector<Layer>& requestedLayers,
                          std::vector<uint32_t>& requestMasks);
    Error presentDisplay(Display display, int32_t& presentFence, std::vector<Layer>& layers,
                         std::vector<int32_t>& releaseFences);

   private:
    // Commands from ::android::hardware::graphics::composer::V2_1::IComposerClient follow.
    bool parseSelectDisplay(uint16_t length);
    bool parseSelectLayer(uint16_t length);
    bool parseSetColorTransform(uint16_t length);
    bool parseSetClientTarget(uint16_t length);
    bool parseSetOutputBuffer(uint16_t length);
    bool parseValidateDisplay(uint16_t length);
    bool parseAcceptDisplayChanges(uint16_t length);
    bool parsePresentDisplay(uint16_t length);
    bool parsePresentOrValidateDisplay(uint16_t length);
    bool parseSetLayerCursorPosition(uint16_t length);
    bool parseSetLayerBuffer(uint16_t length);
    bool parseSetLayerSurfaceDamage(uint16_t length);
    bool parseSetLayerBlendMode(uint16_t length);
    bool parseSetLayerColor(uint16_t length);
    bool parseSetLayerCompositionType(uint16_t length);
    bool parseSetLayerDataspace(uint16_t length);
    bool parseSetLayerDisplayFrame(uint16_t length);
    bool parseSetLayerPlaneAlpha(uint16_t length);
    bool parseSetLayerSidebandStream(uint16_t length);
    bool parseSetLayerSourceCrop(uint16_t length);
    bool parseSetLayerTransform(uint16_t length);
    bool parseSetLayerVisibleRegion(uint16_t length);
    bool parseSetLayerZOrder(uint16_t length);

    // Commands from ::android::hardware::graphics::composer::V2_2::IComposerClient follow.
    bool parseSetLayerPerFrameMetadata(uint16_t length);
    bool parseSetLayerFloatColor(uint16_t length);

    // Commands from ::android::hardware::graphics::composer::V2_3::IComposerClient follow.
    bool parseSetLayerColorTransform(uint16_t length);
    bool parseSetLayerPerFrameMetadataBlobs(uint16_t length);

    hwc_rect_t readRect();
    std::vector<hwc_rect_t> readRegion(size_t count);
    hwc_frect_t readFRect();
    QtiComposerClient& mClient;
    CommandWriter& mWriter;
    Display mDisplay;
    Layer mLayer;

    // Buffer cache impl
    enum class BufferCache {
      CLIENT_TARGETS,
      OUTPUT_BUFFERS,
      LAYER_BUFFERS,
      LAYER_SIDEBAND_STREAMS,
    };

    Error lookupBufferCacheEntryLocked(BufferCache cache, uint32_t slot,
                                       BufferCacheEntry** outEntry);
    Error lookupBuffer(BufferCache cache, uint32_t slot, bool useCache, buffer_handle_t handle,
                       buffer_handle_t* outHandle);
    Error updateBuffer(BufferCache cache, uint32_t slot, bool useCache, buffer_handle_t handle);

    Error lookupLayerSidebandStream(buffer_handle_t handle, buffer_handle_t* outHandle) {
      return lookupBuffer(BufferCache::LAYER_SIDEBAND_STREAMS, 0, false, handle, outHandle);
    }
    Error updateLayerSidebandStream(buffer_handle_t handle) {
      return updateBuffer(BufferCache::LAYER_SIDEBAND_STREAMS, 0, false, handle);
    }
  };

  HWCSession *hwc_session_ = nullptr;
  sp<composer_V2_1::IComposerCallback> mCallback;
  std::mutex mCommandMutex;
  // 64KiB minus a small space for metadata such as read/write pointers */
  static constexpr size_t kWriterInitialSize = 64 * 1024 / sizeof(uint32_t) - 16;
  CommandWriter mWriter;
  CommandReader mReader;
  std::mutex mDisplayDataMutex;
  std::unordered_map<Display, DisplayData> mDisplayData;
};

extern "C" IQtiComposerClient* HIDL_FETCH_IQtiComposerClient(const char* name);

}  // namespace implementation
}  // namespace V2_0
}  // namespace composer
}  // namespace display
}  // namespace hardware
}  // namespace qti
}  // namespace vendor

#endif  // __QTICOMPOSERCLIENT_H__

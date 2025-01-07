/*
 * Copyright 2023 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef skgpu_graphite_VulkanYcbcrConversion_DEFINED
#define skgpu_graphite_VulkanYcbcrConversion_DEFINED

#include "src/gpu/graphite/Resource.h"

#include "include/private/gpu/vk/SkiaVulkan.h"
#include "src/core/SkChecksum.h"

#include <cinttypes>

namespace skgpu {
struct VulkanYcbcrConversionInfo;
}

namespace skgpu::graphite {

class VulkanSharedContext;

class VulkanYcbcrConversion : public Resource {
public:
    static sk_sp<VulkanYcbcrConversion> Make(const VulkanSharedContext*,
                                             const VulkanYcbcrConversionInfo&);

    const VkSamplerYcbcrConversion& ycbcrConversion() const { return fYcbcrConversion; }

    const char* getResourceType() const override { return "Vulkan YCbCr Conversion"; }

    // Static utilities for working with VulkanYcbcrConversionInfo and ImmutableSamplerInfo, both of
    // which pack the necessary information to create a VulkanYcbcrConversion resource. These are
    // not on VulkanYcbcrConversionInfo because that is a public type for use with
    // VulkanTextureInfo.
    static ImmutableSamplerInfo ToImmutableSamplerInfo(const VulkanYcbcrConversionInfo&);
    static VulkanYcbcrConversionInfo FromImmutableSamplerInfo(ImmutableSamplerInfo);

private:
    VulkanYcbcrConversion(const VulkanSharedContext*, VkSamplerYcbcrConversion);

    void freeGpuData() override;

    VkSamplerYcbcrConversion fYcbcrConversion;
};
} // namespace skgpu::graphite

#endif // skgpu_graphite_VulkanYcbcrConversion_DEFINED

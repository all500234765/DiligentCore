/*     Copyright 2015-2018 Egor Yusov
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
*
*  In no event and under no legal theory, whether in tort (including negligence),
*  contract, or otherwise, unless required by applicable law (such as deliberate
*  and grossly negligent acts) or agreed to in writing, shall any Contributor be
*  liable for any damages, including any direct, indirect, special, incidental,
*  or consequential damages of any character arising as a result of this License or
*  out of the use or inability to use the software (including but not limited to damages
*  for loss of goodwill, work stoppage, computer failure or malfunction, or any and
*  all other commercial damages or losses), even if such Contributor has been advised
*  of the possibility of such damages.
*/

#pragma once

#include <memory>
#include "vulkan.h"
#include "VulkanObjectWrappers.h"

namespace VulkanUtilities
{
    class VulkanLogicalDevice : private std::enable_shared_from_this<VulkanLogicalDevice>
    {
    public:
        static std::shared_ptr<VulkanLogicalDevice> Create(VkPhysicalDevice vkPhysicalDevice, 
                                                           const VkDeviceCreateInfo &DeviceCI, 
                                                           const VkAllocationCallbacks* vkAllocator,
                                                           bool EnableDebugMarkers);
        VulkanLogicalDevice(const VulkanLogicalDevice&) = delete;
        VulkanLogicalDevice(VulkanLogicalDevice&&) = delete;
        VulkanLogicalDevice& operator = (const VulkanLogicalDevice&) = delete;
        VulkanLogicalDevice& operator = (VulkanLogicalDevice&&) = delete;

        ~VulkanLogicalDevice();

        std::shared_ptr<VulkanLogicalDevice> GetSharedPtr()
        {
            return shared_from_this();
        }

        std::shared_ptr<const VulkanLogicalDevice> GetSharedPtr()const
        {
            return shared_from_this();
        }

        VkQueue GetQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);

        VkDevice GetVkDevice()const
        { 
            return m_VkDevice; 
        }

        void WaitIdle()const;

        CommandPoolWrapper  CreateCommandPool   (const VkCommandPoolCreateInfo &CmdPoolCI,   const char *DebugName = "")const;
        BufferWrapper       CreateBuffer        (const VkBufferCreateInfo      &BufferCI,    const char *DebugName = "")const;
        BufferViewWrapper   CreateBufferView    (const VkBufferViewCreateInfo  &BuffViewCI,  const char *DebugName = "")const;
        ImageWrapper        CreateImage         (const VkImageCreateInfo       &ImageCI,     const char *DebugName = "")const;
        ImageViewWrapper    CreateImageView     (const VkImageViewCreateInfo   &ImageViewCI, const char *DebugName = "")const;
        FenceWrapper        CreateFence         (const VkFenceCreateInfo       &FenceCI,     const char *DebugName = "")const;
        DeviceMemoryWrapper AllocateDeviceMemory(const VkMemoryAllocateInfo    &AllocInfo,   const char *DebugName = "")const;
        
        VkCommandBuffer     AllocateVkCommandBuffer(const VkCommandBufferAllocateInfo &AllocInfo, const char *DebugName = "")const;

        void ReleaseVulkanObject(CommandPoolWrapper&&  CmdPool)const;
        void ReleaseVulkanObject(BufferWrapper&&       Buffer)const;
        void ReleaseVulkanObject(BufferViewWrapper&&   BufferView)const;
        void ReleaseVulkanObject(ImageWrapper&&        Image)const;
        void ReleaseVulkanObject(ImageViewWrapper&&    ImageView)const;
        void ReleaseVulkanObject(FenceWrapper&&        Fence)const;
        void ReleaseVulkanObject(DeviceMemoryWrapper&& Memory)const;

        VkMemoryRequirements GetBufferMemoryRequirements(VkBuffer vkBuffer)const;
        VkMemoryRequirements GetImageMemoryRequirements (VkImage vkImage  )const;

        VkResult BindBufferMemory(VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)const;
        VkResult BindImageMemory (VkImage image,   VkDeviceMemory memory, VkDeviceSize memoryOffset)const;

        VkResult MapMemory(VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)const;
        void UnmapMemory(VkDeviceMemory memory)const;

        VkResult GetFenceStatus(VkFence fence)const;
        VkResult ResetFence(VkFence fence)const;

    private:
        VulkanLogicalDevice(VkPhysicalDevice vkPhysicalDevice, 
                            const VkDeviceCreateInfo &DeviceCI, 
                            const VkAllocationCallbacks* vkAllocator,
                            bool EnableDebugMarkers);

        VkDevice m_VkDevice = VK_NULL_HANDLE;
        const VkAllocationCallbacks* const m_VkAllocator; 
    };
}
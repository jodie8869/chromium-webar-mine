// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VRController_h
#define VRController_h

#include "core/frame/LocalFrame.h"
#include "device/vr/vr_service.mojom-blink.h"
#include "modules/ModulesExport.h"
#include "platform/Supplementable.h"
#include "wtf/Deque.h"

#include <memory>

namespace blink {

class ServiceRegistry;
class VRGetDevicesCallback;

class MODULES_EXPORT VRController final
    : public GarbageCollectedFinalized<VRController>
    , public Supplement<LocalFrame> {
    USING_GARBAGE_COLLECTED_MIXIN(VRController);
    WTF_MAKE_NONCOPYABLE(VRController);
public:
    virtual ~VRController();

    void getDisplays(std::unique_ptr<VRGetDevicesCallback>);

    device::blink::VRPosePtr getPose(unsigned index);
    unsigned getMaxPointCloudVertexCount(unsigned index);
    device::blink::VRPointCloudPtr getPointCloud(unsigned index, bool justUpdatePointCloud, unsigned pointsToSkip);
    device::blink::VRPickingPointAndPlanePtr getPickingPointAndPlaneInPointCloud(unsigned index, float x, float y);
    device::blink::VRSeeThroughCameraPtr getSeeThroughCamera(unsigned index);
    mojo::WTFArray<float> getPoseMatrix(unsigned index);
    int getSeeThroughCameraOrientation(unsigned index);

    void resetPose(unsigned index);

    static void provideTo(LocalFrame&, ServiceRegistry*);
    static VRController* from(LocalFrame&);
    static const char* supplementName();

    DECLARE_VIRTUAL_TRACE();

private:
    VRController(LocalFrame&, ServiceRegistry*);

    // Binding callbacks.
    void onGetDisplays(mojo::WTFArray<device::blink::VRDisplayPtr>);

    Deque<std::unique_ptr<VRGetDevicesCallback>> m_pendingGetDevicesCallbacks;
    device::blink::VRServicePtr m_service;
};

} // namespace blink

#endif // VRController_h

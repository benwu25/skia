/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "modules/svg/include/SkSVGFeFlood.h"

#include "include/core/SkScalar.h"
#include "include/core/SkShader.h"
#include "include/effects/SkImageFilters.h"
#include "include/private/base/SkDebug.h"
#include "modules/svg/include/SkSVGRenderContext.h"

class SkImageFilter;
class SkSVGFilterContext;

SkColor SkSVGFeFlood::resolveFloodColor(const SkSVGRenderContext& ctx) const {
    const auto floodColor = this->getFloodColor();
    const auto floodOpacity = this->getFloodOpacity();
    // Uninherited presentation attributes should have a concrete value by now.
    if (!floodColor.isValue() || !floodOpacity.isValue()) {
        SkDEBUGF("unhandled: flood-color or flood-opacity has no value\n");
        return SK_ColorBLACK;
    }

    const SkColor color = ctx.resolveSvgColor(*floodColor);
    return SkColorSetA(color, SkScalarRoundToInt(*floodOpacity * 255));
}

sk_sp<SkImageFilter> SkSVGFeFlood::onMakeImageFilter(const SkSVGRenderContext& ctx,
                                                     const SkSVGFilterContext& fctx) const {
    return SkImageFilters::Shader(SkShaders::Color(resolveFloodColor(ctx)),
                                  this->resolveFilterSubregion(ctx, fctx));
}

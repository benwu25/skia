#include <iostream>
#include <cstdlib>
#include <vector>

#include "include/core/SkBBHFactory.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkData.h"
#include "include/core/SkDrawable.h"
#include "include/core/SkFontMetrics.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkPath.h"
#include "include/core/SkPictureRecorder.h"
#include "include/core/SkScalar.h"
#include "include/core/SkStream.h"
#include "include/core/SkString.h"
#include "include/private/SkColorData.h"
#include "include/private/base/SkMalloc.h"
#include "include/private/base/SkMutex.h"
#include "include/private/base/SkTPin.h"
#include "include/private/base/SkTemplates.h"
#include "include/private/base/SkTo.h"
#include "src/base/SkTSearch.h"
#include "src/core/SkAdvancedTypefaceMetrics.h"
#include "src/core/SkDescriptor.h"
#include "src/core/SkFDot6.h"
#include "src/core/SkFontDescriptor.h"
#include "src/core/SkGlyph.h"
#include "src/core/SkMask.h"
#include "src/core/SkMaskGamma.h"
#include "src/core/SkScalerContext.h"
#include "src/ports/SkFontHost_FreeType_common.h"
#include "src/ports/SkFontScanner_FreeType_priv.h"
#include "src/ports/SkTypeface_FreeType.h"
#include "src/sfnt/SkOTUtils.h"
#include "src/sfnt/SkSFNTHeader.h"
#include "src/sfnt/SkTTCFHeader.h"
#include "src/utils/SkCallableTraits.h"
#include "src/utils/SkMatrix22.h"

#include <include/encode/SkEncoder.h>
#include <include/encode/SkPngEncoder.h>

#include <include/core/SkCanvas.h>
#include <include/core/SkPaint.h>
#include <include/core/SkPath.h>
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkStream.h"
#include "include/core/SkSurface.h"

void draw(SkCanvas *canvas) {
    SkPath path;
    path.moveTo(0.0f , 0.0f);
    path.lineTo(100.0f, 0.0f);
    path.lineTo(150.0f, 150.0f);
    path.lineTo(0.0f, 100.0f);
    path.lineTo(0.0f, 0.0f);
    path.close();

    SkPaint p;
    p.setAntiAlias(true);
    canvas->clear(SK_ColorWHITE);
    canvas->drawPath(path, p);
}

void raster(int width, int height,
            void (*draw)(SkCanvas*),
            const char* path) {
    sk_sp<SkSurface> rasterSurface = SkSurfaces::Raster( SkImageInfo::MakeN32Premul(width, height) );

    SkCanvas* rasterCanvas = rasterSurface->getCanvas();
    draw(rasterCanvas);
    const sk_sp<SkImage> img(rasterSurface->makeImageSnapshot());
    if (!img) { return; }
    sk_sp<SkData> png = SkPngEncoder::Encode(nullptr, img.get(), {});
    if (!png) { return; }

    SkFILEWStream out(path);
    (void)out.write(png->data(), png->size());
}

int main(int argc, char **argv) {
	raster(200, 200, &draw, "./pic.png");
	return 0;
}


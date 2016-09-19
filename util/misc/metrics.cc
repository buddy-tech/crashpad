// Copyright 2016 The Crashpad Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "util/misc/metrics.h"

#include "base/metrics/histogram_macros.h"
#include "base/metrics/sparse_histogram.h"
#include "build/build_config.h"

namespace crashpad {

// static
void Metrics::CrashReportSize(FileHandle file) {
  const FileOffset size = LoggingFileSizeByHandle(file);
  UMA_HISTOGRAM_CUSTOM_COUNTS(
      "Crashpad.CrashReportSize", size, 0, 5 * 1024 * 1024, 50);
}

// static
void Metrics::ExceptionCaptureResult(CaptureResult result) {
  UMA_HISTOGRAM_ENUMERATION("Crashpad.ExceptionCaptureResult",
                            static_cast<int32_t>(result),
                            static_cast<int32_t>(CaptureResult::kMaxValue));
}

// static
void Metrics::ExceptionCode(uint32_t exception_code) {
#if defined(OS_WIN)
  const char kExceptionCodeString[] = "Crashpad.ExceptionCode.Win";
#elif defined(OS_MACOSX)
  const char kExceptionCodeString[] = "Crashpad.ExceptionCode.Mac";
#endif
  UMA_HISTOGRAM_SPARSE_SLOWLY(kExceptionCodeString,
                              static_cast<int32_t>(exception_code));
}

// static
void Metrics::ExceptionEncountered() {
  UMA_HISTOGRAM_COUNTS("Crashpad.ExceptionEncountered", 1);
}

}  // namespace crashpad

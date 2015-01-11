// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#ifndef CEF_LIBCEF_DLL_CPPTOC_END_TRACING_CALLBACK_CPPTOC_H_
#define CEF_LIBCEF_DLL_CPPTOC_END_TRACING_CALLBACK_CPPTOC_H_
#pragma once

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else  // USING_CEF_SHARED

#include "include/cef_trace.h"
#include "include/capi/cef_trace_capi.h"
#include "libcef_dll/cpptoc/cpptoc.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed wrapper-side only.
class CefEndTracingCallbackCppToC
    : public CefCppToC<CefEndTracingCallbackCppToC, CefEndTracingCallback,
        cef_end_tracing_callback_t> {
 public:
  explicit CefEndTracingCallbackCppToC(CefEndTracingCallback* cls);
  virtual ~CefEndTracingCallbackCppToC() {}
};

#endif  // USING_CEF_SHARED
#endif  // CEF_LIBCEF_DLL_CPPTOC_END_TRACING_CALLBACK_CPPTOC_H_


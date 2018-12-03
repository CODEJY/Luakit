// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/basem/LocaleUtils

#ifndef org_chromium_base_LocaleUtils_JNI
#define org_chromium_base_LocaleUtils_JNI

#include <jni.h>
#include "base/android/jni_generator/jni_generator_helper.h"
// Step 1: forward declarations.
namespace {
const char kLocaleUtilsClassPath[] = "org/chromium/basem/LocaleUtils";
// Leaking this jclass as we cannot use LazyInstance from some threads.
jclass g_LocaleUtils_clazz = NULL;

}  // namespace

// Step 2: method stubs.

static base::subtle::AtomicWord g_LocaleUtils_getDefaultLocale = 0;
static base::android::ScopedJavaLocalRef<jstring>
    Java_LocaleUtils_getDefaultLocale(JNIEnv* env) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, g_LocaleUtils_clazz,
      g_LocaleUtils_clazz, NULL);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, g_LocaleUtils_clazz,
      "getDefaultLocale",

"("
")"
"Ljava/lang/String;",
      &g_LocaleUtils_getDefaultLocale);

  jstring ret =
      static_cast<jstring>(env->CallStaticObjectMethod(g_LocaleUtils_clazz,
          method_id));
  jni_generator::CheckException(env);
  return base::android::ScopedJavaLocalRef<jstring>(env, ret);
}

// Step 3: RegisterNatives.

static bool RegisterNativesImpl(JNIEnv* env) {
  g_LocaleUtils_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kLocaleUtilsClassPath).obj()));

  return true;
}

#endif  // org_chromium_base_LocaleUtils_JNI

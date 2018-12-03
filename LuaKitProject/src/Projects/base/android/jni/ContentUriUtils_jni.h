// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/basem/ContentUriUtils

#ifndef org_chromium_base_ContentUriUtils_JNI
#define org_chromium_base_ContentUriUtils_JNI

#include <jni.h>
#include "base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
namespace {
const char kContentUriUtilsClassPath[] = "org/chromium/basem/ContentUriUtils";
// Leaking this jclass as we cannot use LazyInstance from some threads.
jclass g_ContentUriUtils_clazz = NULL;

}  // namespace

// Step 2: method stubs.

static base::subtle::AtomicWord g_ContentUriUtils_openContentUriForRead = 0;
static jint Java_ContentUriUtils_openContentUriForRead(JNIEnv* env, jobject
    context,
    jstring uriString) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, g_ContentUriUtils_clazz,
      g_ContentUriUtils_clazz, 0);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, g_ContentUriUtils_clazz,
      "openContentUriForRead",

"("
"Landroid/content/Context;"
"Ljava/lang/String;"
")"
"I",
      &g_ContentUriUtils_openContentUriForRead);

  jint ret =
      env->CallStaticIntMethod(g_ContentUriUtils_clazz,
          method_id, context, uriString);
  jni_generator::CheckException(env);
  return ret;
}

static base::subtle::AtomicWord g_ContentUriUtils_contentUriExists = 0;
static jboolean Java_ContentUriUtils_contentUriExists(JNIEnv* env, jobject
    context,
    jstring uriString) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, g_ContentUriUtils_clazz,
      g_ContentUriUtils_clazz, false);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, g_ContentUriUtils_clazz,
      "contentUriExists",

"("
"Landroid/content/Context;"
"Ljava/lang/String;"
")"
"Z",
      &g_ContentUriUtils_contentUriExists);

  jboolean ret =
      env->CallStaticBooleanMethod(g_ContentUriUtils_clazz,
          method_id, context, uriString);
  jni_generator::CheckException(env);
  return ret;
}

// Step 3: RegisterNatives.

static bool RegisterNativesImpl(JNIEnv* env) {
  g_ContentUriUtils_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kContentUriUtilsClassPath).obj()));

  return true;
}

#endif  // org_chromium_base_ContentUriUtils_JNI

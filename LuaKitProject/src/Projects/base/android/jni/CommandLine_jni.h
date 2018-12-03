// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/basem/CommandLine

#ifndef org_chromium_base_CommandLine_JNI
#define org_chromium_base_CommandLine_JNI

#include <jni.h>
#include "base/android/jni_generator/jni_generator_helper.h"

// Step 1: forward declarations.
namespace {
const char kCommandLineClassPath[] = "org/chromium/basem/CommandLine";
// Leaking this jclass as we cannot use LazyInstance from some threads.
jclass g_CommandLine_clazz = NULL;

}  // namespace

static void Reset(JNIEnv* env, jclass jcaller);

static jboolean HasSwitch(JNIEnv* env, jclass jcaller,
    jstring switchString);

static jstring GetSwitchValue(JNIEnv* env, jclass jcaller,
    jstring switchString);

static void AppendSwitch(JNIEnv* env, jclass jcaller,
    jstring switchString);

static void AppendSwitchWithValue(JNIEnv* env, jclass jcaller,
    jstring switchString,
    jstring value);

static void AppendSwitchesAndArguments(JNIEnv* env, jclass jcaller,
    jobjectArray array);

// Step 2: method stubs.

// Step 3: RegisterNatives.

static const JNINativeMethod kMethodsCommandLine[] = {
    { "nativeReset",
"("
")"
"V", reinterpret_cast<void*>(Reset) },
    { "nativeHasSwitch",
"("
"Ljava/lang/String;"
")"
"Z", reinterpret_cast<void*>(HasSwitch) },
    { "nativeGetSwitchValue",
"("
"Ljava/lang/String;"
")"
"Ljava/lang/String;", reinterpret_cast<void*>(GetSwitchValue) },
    { "nativeAppendSwitch",
"("
"Ljava/lang/String;"
")"
"V", reinterpret_cast<void*>(AppendSwitch) },
    { "nativeAppendSwitchWithValue",
"("
"Ljava/lang/String;"
"Ljava/lang/String;"
")"
"V", reinterpret_cast<void*>(AppendSwitchWithValue) },
    { "nativeAppendSwitchesAndArguments",
"("
"[Ljava/lang/String;"
")"
"V", reinterpret_cast<void*>(AppendSwitchesAndArguments) },
};

static bool RegisterNativesImpl(JNIEnv* env) {
  g_CommandLine_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kCommandLineClassPath).obj()));

  const int kMethodsCommandLineSize = arraysize(kMethodsCommandLine);

  if (env->RegisterNatives(g_CommandLine_clazz,
                           kMethodsCommandLine,
                           kMethodsCommandLineSize) < 0) {
    jni_generator::HandleRegistrationError(
        env, g_CommandLine_clazz, __FILE__);
    return false;
  }

  return true;
}

#endif  // org_chromium_base_CommandLine_JNI

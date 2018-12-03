// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/basem/SystemMessageHandler

#ifndef org_chromium_base_SystemMessageHandler_JNI
#define org_chromium_base_SystemMessageHandler_JNI

#include <jni.h>
#include "base/android/jni_generator/jni_generator_helper.h"
// Step 1: forward declarations.
namespace {
const char kSystemMessageHandlerClassPath[] =
    "org/chromium/basem/SystemMessageHandler";
// Leaking this jclass as we cannot use LazyInstance from some threads.
jclass g_SystemMessageHandler_clazz = NULL;

}  // namespace

static void DoRunLoopOnce(JNIEnv* env, jobject jcaller,
    jlong messagePumpDelegateNative);

// Step 2: method stubs.

static base::subtle::AtomicWord g_SystemMessageHandler_setTimer = 0;
static void Java_SystemMessageHandler_setTimer(JNIEnv* env, jobject obj) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, obj,
      g_SystemMessageHandler_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SystemMessageHandler_clazz,
      "setTimer",

"("
")"
"V",
      &g_SystemMessageHandler_setTimer);

     env->CallVoidMethod(obj,
          method_id);
  jni_generator::CheckException(env);

}

static base::subtle::AtomicWord g_SystemMessageHandler_setDelayedTimer = 0;
static void Java_SystemMessageHandler_setDelayedTimer(JNIEnv* env, jobject obj,
    jlong millis) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, obj,
      g_SystemMessageHandler_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SystemMessageHandler_clazz,
      "setDelayedTimer",

"("
"J"
")"
"V",
      &g_SystemMessageHandler_setDelayedTimer);

     env->CallVoidMethod(obj,
          method_id, millis);
  jni_generator::CheckException(env);

}

static base::subtle::AtomicWord g_SystemMessageHandler_removeTimer = 0;
static void Java_SystemMessageHandler_removeTimer(JNIEnv* env, jobject obj) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, obj,
      g_SystemMessageHandler_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SystemMessageHandler_clazz,
      "removeTimer",

"("
")"
"V",
      &g_SystemMessageHandler_removeTimer);

     env->CallVoidMethod(obj,
          method_id);
  jni_generator::CheckException(env);

}

static base::subtle::AtomicWord g_SystemMessageHandler_create = 0;
static base::android::ScopedJavaLocalRef<jobject>
    Java_SystemMessageHandler_create(JNIEnv* env, jlong
    messagePumpDelegateNative) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, g_SystemMessageHandler_clazz,
      g_SystemMessageHandler_clazz, NULL);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, g_SystemMessageHandler_clazz,
      "create",

"("
"J"
")"
"Lorg/chromium/basem/SystemMessageHandler;",
      &g_SystemMessageHandler_create);

  jobject ret =
      env->CallStaticObjectMethod(g_SystemMessageHandler_clazz,
          method_id, messagePumpDelegateNative);
  jni_generator::CheckException(env);
  return base::android::ScopedJavaLocalRef<jobject>(env, ret);
}

// Step 3: RegisterNatives.

static const JNINativeMethod kMethodsSystemMessageHandler[] = {
    { "nativeDoRunLoopOnce",
"("
"J"
")"
"V", reinterpret_cast<void*>(DoRunLoopOnce) },
};

static bool RegisterNativesImpl(JNIEnv* env) {
  g_SystemMessageHandler_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kSystemMessageHandlerClassPath).obj()));

  const int kMethodsSystemMessageHandlerSize =
      arraysize(kMethodsSystemMessageHandler);

  if (env->RegisterNatives(g_SystemMessageHandler_clazz,
                           kMethodsSystemMessageHandler,
                           kMethodsSystemMessageHandlerSize) < 0) {
    jni_generator::HandleRegistrationError(
        env, g_SystemMessageHandler_clazz, __FILE__);
    return false;
  }

  return true;
}

#endif  // org_chromium_base_SystemMessageHandler_JNI

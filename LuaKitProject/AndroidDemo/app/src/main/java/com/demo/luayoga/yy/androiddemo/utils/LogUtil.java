package com.demo.luayoga.yy.androiddemo.utils;

import android.util.Log;

public class LogUtil {

    private static final String TAG = "LuaYogaDemo";

    public static void i(String tag, String log) {
        Log.i(TAG, tag + ": " + log);
    }

}

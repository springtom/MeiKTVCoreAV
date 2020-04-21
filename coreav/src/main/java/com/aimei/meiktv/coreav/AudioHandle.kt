package com.aimei.meiktv.coreav

class AudioHandle {

    companion object {
        init {
            System.loadLibrary("coreav")
        }
    }
    external fun stringFromJNI(): String
}
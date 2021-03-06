package com.aimei.meiktv.coreav

// xingchun 2020 04 21
object AudioEffect {

        init {
            System.loadLibrary("coreav")
        }







    external fun initSoxAudioNative(bufferSize: Int, sampleRate: Int, channels: Int): Boolean

    external fun addVolAddNative(addVol:Int):Boolean

    external fun setWetEchoReverbScale(wet:Float,echo:Float)

    external fun addEqualizerEffectNative(params: Array<FloatArray>):Boolean

    external fun addHighPassEffectNative(frequency: Int):Boolean

    external fun addLowPassEffectNative(frequency:Int):Boolean

    external fun addReverbEffectNative(reverberance:Int, damping:Int, roomScale:Int, stereoDepth:Int, preDelay:Int, wetGain:Int):Boolean

    external fun addEchoNative(inputVolume :Float, outputVolume:Float, delay:Int, attenuation:Float):Boolean

    external fun doprocess(audioSimple: ShortArray, size:Int):ShortArray

    external fun destory()



}
package com.aimei.meiktv.coreav

import android.media.AudioTrack
import android.util.Log
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import java.lang.Exception
class AudioTrackHandler {
    lateinit var track: AudioTrack
    lateinit var job: Job
    var isstop = true
    fun init(sampleReta: Int, channels: Int, streamType: Int, nframes: Int, creationMode: Int) {
        var minBufferSize = AudioTrack.getMinBufferSize(sampleReta, channels, nframes)
        if (minBufferSize < 0)
            throw  Exception("音频播放初始化异常 minBufferSize=" + minBufferSize)
        track = AudioTrack(streamType, sampleReta, channels, nframes, minBufferSize, creationMode)
    }
// 线程
    fun play() {
        Thread(Runnable {
            isstop = false
            while (!isstop){
                var data = PCMDataManager.getData()
                Log.w("春哥","播放")
                if(data!=null){
                    Log.w("春哥","播放"+data.time)
                    track.write(data.soxData,0,data.size)
                    track.play()
                    data.time=0
                    data.size=0
                    PCMDataManager.putNoData(data)
                }
                Thread.sleep(10)
            }
            track.stop()
        }).start()
    }

    //协程
//    fun play() {
//        isstop = false
//        job = CoroutineScope(Dispatchers.IO).launch {
//            while (!isstop){
//                var data = PCMDataManager.getData()
//                if(data!=null){
//                    track.write(data.soxData,0,data.size)
//                    track.play()
//                    data.time=0
//                    data.size=0
//                    PCMDataManager.putNoData(data)
//                }
//            }
//            track.stop()
//        }
//    }

    fun stop() {
        isstop = true;
        PCMDataManager.clearData()
//        job?.cancel()
    }
    fun release(){
        track?.release()
    }
}
package com.aimei.meiktv.coreav

import android.media.AudioRecord
import android.media.AudioRecord.RECORDSTATE_RECORDING
import android.os.Handler
import android.os.Looper
import android.util.Log
import kotlinx.coroutines.*

class AudioRecordHandler {

    lateinit var audioRecord: AudioRecord
    lateinit var tempBuffer: ShortArray
    lateinit var job: Job
    var isstop = true
    var packageSize = 960
    var minbuffersize = 0
    var channel = 1
    lateinit var thread: MyThread
    fun init(sampleRate: Int, channels: Int, nframes: Int, audioSource: Int) {
        thread = MyThread()
        thread.start()
        minbuffersize = AudioRecord.getMinBufferSize(sampleRate, channels, nframes)
        audioRecord = AudioRecord(audioSource, sampleRate, channels, nframes, minbuffersize)
        channel = audioRecord.channelCount
        Log.w("春哥init", "bufferSize=" + minbuffersize)
        Log.w("春哥init", "channel=" + channel)
        packageSize = minbuffersize / (2 * 16 * channel / 8)
        Log.w("春哥init", "packageSize=" + packageSize)
        tempBuffer = ShortArray(packageSize)
        audioRecord.positionNotificationPeriod = packageSize / 4
        audioRecord.setRecordPositionUpdateListener(object :
            AudioRecord.OnRecordPositionUpdateListener {
            override fun onMarkerReached(recorder: AudioRecord?) {
                Log.w("春哥z", "onMarkerReached")
            }

            override fun onPeriodicNotification(recorder: AudioRecord?) {
                Log.w("春哥z", "onPeriodicNotification Thread" + Thread.currentThread())
                if (!isstop) {
                    var bufferRead = audioRecord.read(tempBuffer, 0, packageSize)
                    var data = PCMDataManager.obtainNoPCMData()
                    data.size = bufferRead!!
                    System.arraycopy(tempBuffer, 0, data.rawData, 0, bufferRead)
                    PCMDataManager.putPCMData(data)
                }
            }
        }, thread.handler)
    }

    fun startRecord() {
        isstop = false
        PCMDataManager.clearData()
        audioRecord.startRecording()
        audioRecord.read(tempBuffer, 0, packageSize)
    }

    //线程
//    fun startRecord() {
//        Thread(Runnable {
//            isstop = false
//            audioRecord.startRecording()
//            var startTime = System.currentTimeMillis()
//            var endTime = startTime
//            while (!isstop) {
//                var bufferRead = audioRecord.read(tempBuffer, 0, packageSize)
//                var data = PCMDataManager.obtainNoPCMData()
//
//                data.size = bufferRead;
//                System.arraycopy(tempBuffer, 0, data.rawData, 0, bufferRead)
//                data.soxData = data.rawData?.let { AudioEffect.doprocess(it, data.size) }
//                data.time = (endTime - startTime).toInt()
//
//                endTime = System.currentTimeMillis()
//
//                PCMDataManager.putData(data)
//                Thread.sleep(1)
//            }
//            audioRecord.stop()
//        }).start()
//    }

    //协程
//    fun startRecord() {
//        isstop = false
//        job = CoroutineScope(Dispatchers.IO).launch {
//
//            audioRecord.startRecording()
//
//            var startTime = System.currentTimeMillis()
//            var endTime = startTime;
//            while (!isstop) {
//                var bufferRead = audioRecord.read(tempBuffer, 0, packageSize)
//                var data = PCMDataManager.obtainNoPCMData();
//                data.size = bufferRead;
//                System.arraycopy(tempBuffer, 0, data.rawData, 0, bufferRead)
//                data.soxData = data.rawData?.let { AudioEffect.doprocess(it, data.size) }
//                data.time = (endTime - startTime).toInt()
//                endTime = System.currentTimeMillis()
//                PCMDataManager.putData(data)
//            }
//            audioRecord.stop()
//        }
//    }


    fun stop() {
        isstop = true
        if (audioRecord.state == RECORDSTATE_RECORDING)
            audioRecord.stop()
//        job?.cancel()
    }

    fun release() {
        audioRecord?.release()
    }

    class MyThread : Thread() {
        lateinit var handler: Handler
        override fun run() {
            super.run()
            Log.w("春哥", "" + currentThread())
            Looper.prepare()
            handler = Handler(Looper.myLooper())
            Looper.loop()
        }
    }
}



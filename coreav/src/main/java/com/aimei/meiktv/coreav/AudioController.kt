package com.aimei.meiktv.coreav

import android.media.AudioFormat
import android.media.AudioManager
import android.media.AudioTrack
import android.media.MediaRecorder

object AudioController {
    var sampleRate = 48000
    var recordChannels = AudioFormat.CHANNEL_IN_MONO
    var nframes = AudioFormat.ENCODING_PCM_16BIT
    var audioSource = MediaRecorder.AudioSource.MIC
    var playChannels = AudioFormat.CHANNEL_OUT_MONO
    var streamType = AudioManager.STREAM_MUSIC
    var creationMode = AudioTrack.MODE_STREAM
    lateinit var audioRecordHandler: AudioRecordHandler
    lateinit var audioTrackHandler: AudioTrackHandler
    var hasInit = false
    fun init() {
        if (hasInit)
            return
        audioRecordHandler = AudioRecordHandler()
        audioRecordHandler.init(sampleRate, recordChannels, nframes, audioSource)
        audioTrackHandler = AudioTrackHandler()
        audioTrackHandler.init(sampleRate, playChannels, streamType, nframes, creationMode)
        hasInit = true
    }

    fun work() {
        audioRecordHandler?.startRecord()
        audioTrackHandler?.play()
    }

    fun stop() {
        audioRecordHandler?.stop()
        audioTrackHandler?.stop()
    }

    fun release() {
        hasInit = false
        audioRecordHandler?.release()
        audioTrackHandler?.release()
    }
}
package com.aimei.meiktv.meiktvcoreav

import android.app.Activity
import android.content.pm.PackageManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.core.app.ActivityCompat
import com.aimei.meiktv.coreav.AudioController
import com.aimei.meiktv.coreav.AudioEffect
import com.jaygoo.widget.OnRangeChangedListener
import com.jaygoo.widget.RangeSeekBar
import kotlinx.android.synthetic.main.activity_main.*

// sprtingtom 2020-4-24
class MainActivity : AppCompatActivity(), OnRangeChangedListener {

    companion object {
        val REQUEST_PERMISSION_CODE = 3
        val PERMISSION_STORAGE = arrayOf(
            android.Manifest.permission.MODIFY_AUDIO_SETTINGS,
            android.Manifest.permission.RECORD_AUDIO
        )
    }


    var array = arrayOf("-15db", "-10db", "-5db", "0", "5db", "10db", "15db")
    var eqParams = arrayOf(
        floatArrayOf(60f, 0.2f, 0f),
        floatArrayOf(230f, 0.2f, 0f),
        floatArrayOf(910f, 0.2f, 0f),
        floatArrayOf(1500f, 0.2f, 0f),
        floatArrayOf(3600f, 0.2f, 0f),
        floatArrayOf(6000f, 0.2f, 0f)
    )

    var reverberance = 90
    var damping = 20
    var rootScale = 71
    var stereoDepth = 80
    var preDelay = 20
    var wetGain = 6

    var inputVolume  = 0.5f
    var outputVolume = 0.5f
    var delay = 20;
    var attenuation = 0.6f


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        openPermission(this)
        setContentView(R.layout.activity_main)
        seekbar1.tickMarkTextArray = array
        seekbar2.tickMarkTextArray = array
        seekbar3.tickMarkTextArray = array
        seekbar4.tickMarkTextArray = array
        seekbar5.tickMarkTextArray = array
        seekbar6.tickMarkTextArray = array
        seekbar1.setProgress(eqParams[0][2])
        seekbar2.setProgress(eqParams[1][2])
        seekbar3.setProgress(eqParams[2][2])
        seekbar4.setProgress(eqParams[3][2])
        seekbar5.setProgress(eqParams[4][2])
        seekbar6.setProgress(eqParams[5][2])
        seekbar7.setProgress(reverberance.toFloat())
        seekbar8.setProgress(damping.toFloat())
        seekbar9.setProgress(rootScale.toFloat())
        seekbar10.setProgress(stereoDepth.toFloat())
        seekbar11.setProgress(preDelay.toFloat())
        seekbar12.setProgress(wetGain.toFloat())
        seekbar1.setOnRangeChangedListener(this)
        seekbar2.setOnRangeChangedListener(this)
        seekbar3.setOnRangeChangedListener(this)
        seekbar4.setOnRangeChangedListener(this)
        seekbar5.setOnRangeChangedListener(this)
        seekbar6.setOnRangeChangedListener(this)
        seekbar7.setOnRangeChangedListener(this)
        seekbar8.setOnRangeChangedListener(this)
        seekbar9.setOnRangeChangedListener(this)
        seekbar10.setOnRangeChangedListener(this)
        seekbar11.setOnRangeChangedListener(this)
        seekbar12.setOnRangeChangedListener(this)


        but1.setOnClickListener{
            iniiAudioEffect()
        }
        but2.setOnClickListener {

        }
        but3.setOnClickListener{

            AudioController.init()
            if("录制".equals(but3.text)){
                but3.setText("录制中")
                AudioController.work()
            }else if("录制中".equals(but3.text)){
                but3.setText("录制")
                AudioController.stop()
            }
        }
    }

    private fun iniiAudioEffect(){
        AudioEffect.destory()
        AudioEffect.initSoxAudioNative(
            AudioController.sampleRate * 2,
            AudioController.sampleRate, 2
        )
        AudioEffect.addEqualizerEffectNative(eqParams)
        AudioEffect.addReverbEffectNative(reverberance,damping,rootScale,stereoDepth,preDelay,wetGain)
        AudioEffect.addEchoNative(inputVolume,outputVolume,delay,attenuation);
    }

    override fun onDestroy() {
        AudioController.release()
        super.onDestroy()
    }

    private fun openPermission(activity: Activity) {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP) {
            for ((index, e) in PERMISSION_STORAGE.withIndex()) {
                if (ActivityCompat.checkSelfPermission(
                        activity,
                        e
                    ) != PackageManager.PERMISSION_GRANTED
                ) {
                    ActivityCompat.requestPermissions(
                        activity, PERMISSION_STORAGE,
                        REQUEST_PERMISSION_CODE
                    )
                }
            }
        }
    }

    override fun onStartTrackingTouch(view: RangeSeekBar?, isLeft: Boolean) {

    }

    override fun onRangeChanged(
        view: RangeSeekBar?,
        leftValue: Float,
        rightValue: Float,
        isFromUser: Boolean
    ) {

//        Log.w("春哥", "leftValue=" + leftValue + "  rightValue=" + rightValue)
        if (view != null) {
            when (view.id) {
                R.id.seekbar1 -> eqParams[0][2] = leftValue
                R.id.seekbar2 -> eqParams[1][2] = leftValue
                R.id.seekbar3 -> eqParams[2][2] = leftValue
                R.id.seekbar4 -> eqParams[3][2] = leftValue
                R.id.seekbar5 -> eqParams[4][2] = leftValue
                R.id.seekbar6 -> eqParams[5][2] = leftValue
                R.id.seekbar7 -> reverberance = leftValue.toInt()
                R.id.seekbar8 -> damping = leftValue.toInt()
                R.id.seekbar9 -> rootScale = leftValue.toInt()
                R.id.seekbar10 -> stereoDepth = leftValue.toInt()
                R.id.seekbar11 -> preDelay = leftValue.toInt()
                R.id.seekbar12 -> wetGain = leftValue.toInt()
            }
        }

    }

    override fun onStopTrackingTouch(view: RangeSeekBar?, isLeft: Boolean) {

    }


}

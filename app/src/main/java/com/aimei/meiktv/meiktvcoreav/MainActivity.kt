package com.aimei.meiktv.meiktvcoreav

import android.app.Activity
import android.content.pm.PackageManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
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

    var addVol = 1
    var lowPassFrequency = 8000
    var highPassFrequency = 100

    var array = arrayOf("-15db", "-10db", "-5db", "0", "5db", "10db", "15db")
    var wet_echo_reverb = arrayOf("0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9")
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

    var inputVolume = 0.5f
    var outputVolume = 0.5f
    var delay = 20;
    var attenuation = 0.6f


    var wet = 0.3f
    var echo = 0.3f
    var reverb = 1 - wet - echo

    var selectedEQ = true
    var selectedReverb = true
    var selectedEcho = true
    var selectedAddVol = true;
    var selectedLowPass = true;
    var selectedHighPass = true;


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        openPermission(this)
        setContentView(R.layout.activity_main)

        im_echo.isSelected = selectedEcho
        im_eq.isSelected = selectedEQ
        im_reverb.isSelected = selectedReverb
        im_add_vol.isSelected = selectedAddVol
        im_highpass.isSelected = selectedHighPass
        im_lowpass.isSelected = selectedLowPass

        im_echo.setOnClickListener {
            if (im_echo.isSelected) {
                selectedEcho = false
            } else {
                selectedEcho = true
            }
            im_echo.isSelected = selectedEcho
        }
        im_eq.setOnClickListener {
            if (im_eq.isSelected) {
                selectedEQ = false
            } else {
                selectedEQ = true
            }
            im_eq.isSelected = selectedEQ
        }
        im_reverb.setOnClickListener {
            if (im_reverb.isSelected) {
                selectedReverb = false
            } else {
                selectedReverb = true
            }
            im_reverb.isSelected = selectedReverb
        }

        im_add_vol.setOnClickListener {
            if (im_add_vol.isSelected) {
                selectedAddVol = false
            } else {
                selectedAddVol = true
            }
            im_add_vol.isSelected = selectedAddVol
        }

        im_lowpass.setOnClickListener {
            if (im_lowpass.isSelected) {
                selectedLowPass = false
            } else {
                selectedLowPass = true
            }
            im_lowpass.isSelected = selectedLowPass
        }

        im_highpass.setOnClickListener {
            if (im_highpass.isSelected) {
                selectedHighPass = false
            } else {
                selectedHighPass = true
            }
            im_highpass.isSelected = selectedHighPass
        }

        seekbar_add_vol.setProgress(addVol.toFloat())
        seekbar_highpass.setProgress(highPassFrequency.toFloat())
        seekbar_lowpass.setProgress(lowPassFrequency.toFloat())
        seekbar_add_vol.setIndicatorTextDecimalFormat("0")
        seekbar_highpass.setIndicatorTextDecimalFormat("0")
        seekbar_lowpass.setIndicatorTextDecimalFormat("0")

        seekbar1.tickMarkTextArray = array
        seekbar2.tickMarkTextArray = array
        seekbar3.tickMarkTextArray = array
        seekbar4.tickMarkTextArray = array
        seekbar5.tickMarkTextArray = array
        seekbar6.tickMarkTextArray = array
        seekbar17.tickMarkTextArray = wet_echo_reverb
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
        seekbar13.setProgress(inputVolume)
        seekbar14.setProgress(outputVolume)
        seekbar15.setProgress(delay.toFloat())
        seekbar16.setProgress(attenuation)
        seekbar17.setProgress(wet, echo)

        seekbar1.setIndicatorTextDecimalFormat("0.0")
        seekbar2.setIndicatorTextDecimalFormat("0.0")
        seekbar3.setIndicatorTextDecimalFormat("0.0")
        seekbar4.setIndicatorTextDecimalFormat("0.0")
        seekbar5.setIndicatorTextDecimalFormat("0.0")
        seekbar6.setIndicatorTextDecimalFormat("0.0")
        seekbar7.setIndicatorTextDecimalFormat("0.0")
        seekbar8.setIndicatorTextDecimalFormat("0.0")
        seekbar9.setIndicatorTextDecimalFormat("0.0")
        seekbar10.setIndicatorTextDecimalFormat("0.0")
        seekbar11.setIndicatorTextDecimalFormat("0.0")
        seekbar12.setIndicatorTextDecimalFormat("0.0")
        seekbar13.setIndicatorTextDecimalFormat("0.00")
        seekbar14.setIndicatorTextDecimalFormat("0.00")
        seekbar15.setIndicatorTextDecimalFormat("0.0")
        seekbar16.setIndicatorTextDecimalFormat("0.00")
        seekbar17.leftSeekBar.setIndicatorTextDecimalFormat("0.00")
        seekbar17.rightSeekBar.setIndicatorTextDecimalFormat("0.00")

        seekbar_add_vol.setOnRangeChangedListener(this)
        seekbar_lowpass.setOnRangeChangedListener(this)
        seekbar_highpass.setOnRangeChangedListener(this)

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
        seekbar13.setOnRangeChangedListener(this)
        seekbar14.setOnRangeChangedListener(this)
        seekbar15.setOnRangeChangedListener(this)
        seekbar16.setOnRangeChangedListener(this)
        seekbar17.setOnRangeChangedListener(this)

        but1.setOnClickListener {
            if ("录制中".equals(but3.text)) {
                Toast.makeText(this,"请先暂停点击录制中，暂停录制",Toast.LENGTH_LONG).show()
                return@setOnClickListener
            }

            iniiAudioEffect()
        }
        but2.setOnClickListener {

        }
        but3.setOnClickListener {


            AudioController.init()
            if ("录制".equals(but3.text)) {
                but3.setText("录制中")
                AudioController.work()
            } else if ("录制中".equals(but3.text)) {
                but3.setText("录制")
                AudioController.stop()
            }
        }
    }



    private fun iniiAudioEffect() {

        AudioEffect.destory()
        AudioEffect.initSoxAudioNative(
            AudioController.sampleRate * 2,
            AudioController.sampleRate, 2
        )
        if (selectedEQ)
            AudioEffect.addEqualizerEffectNative(eqParams)
        if (selectedReverb)
            AudioEffect.addReverbEffectNative(
                reverberance,
                damping,
                rootScale,
                stereoDepth,
                preDelay,
                wetGain
            )
        if (selectedEcho)
            AudioEffect.addEchoNative(inputVolume, outputVolume, delay, attenuation)
        if(selectedAddVol)
            AudioEffect.addVolAddNative(addVol)
        if(selectedLowPass)
            AudioEffect.addLowPassEffectNative(lowPassFrequency)
        if(selectedHighPass)
            AudioEffect.addHighPassEffectNative(highPassFrequency)
        AudioEffect.setWetEchoReverbScale(wet, echo)
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
                R.id.seekbar_add_vol -> addVol = leftValue.toInt()
                R.id.seekbar_lowpass -> lowPassFrequency = leftValue.toInt()
                R.id.seekbar_highpass -> highPassFrequency = leftValue.toInt()
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
                R.id.seekbar13 -> inputVolume = leftValue
                R.id.seekbar14 -> outputVolume = leftValue
                R.id.seekbar15 -> delay = leftValue.toInt()
                R.id.seekbar16 -> attenuation = leftValue
                R.id.seekbar17 -> {
                    wet = leftValue
                    echo = rightValue
                    Log.w("春哥 MianAcitivty", "wet=" + wet + " echo=" + echo)
                }
            }
        }
    }

    override fun onStopTrackingTouch(view: RangeSeekBar?, isLeft: Boolean) {

    }

}

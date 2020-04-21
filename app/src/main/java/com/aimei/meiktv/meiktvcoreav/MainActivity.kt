package com.aimei.meiktv.meiktvcoreav

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.aimei.meiktv.coreav.AudioHandle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var a = AudioHandle()
        sample_text.text = a.stringFromJNI()
    }



}

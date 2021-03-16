package com.example.starwarsdirectory;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

public class BackgroundSoundService extends Service {
    MediaPlayer themePlayer;
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        themePlayer = MediaPlayer.create(this, R.raw.starwars_theme_song);
        themePlayer.setLooping(true);
    }

    public int onStartCommand(Intent intent, int flags, int statId){
        themePlayer.start();
        return statId;
    }

    @Override
    public void onDestroy() {
        Log.d("MUSIC", "destroying music");
        super.onDestroy();
        themePlayer.stop();
        themePlayer.release();
    }
}

package com.example.starwarsdirectory;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
//Developed base on this guide: https://medium.com/@iamsadesh/android-how-to-detect-when-app-goes-background-foreground-fd5a4d331f8a
public class App extends Application implements Application.ActivityLifecycleCallbacks {
    private int activityReferences = 0;
    private boolean isActivityChangingConfigurations = false;
    private SharedPreferences sharedPreferences;

    @Override
    public void onCreate() {
        super.onCreate();
        registerActivityLifecycleCallbacks(this);
    }

    @Override
    public void onActivityCreated(@NonNull Activity activity, @Nullable Bundle savedInstanceState) {

    }

    @Override
    public void onActivityStarted(@NonNull Activity activity) {
        if(++activityReferences == 1 && !isActivityChangingConfigurations){
            Log.d("APPLICATION", "App in Foreground");
        }
    }

    @Override
    public void onActivityResumed(@NonNull Activity activity) {

    }

    @Override
    public void onActivityPaused(@NonNull Activity activity) {

    }

    @Override
    public void onActivityStopped(@NonNull Activity activity) {
        isActivityChangingConfigurations = activity.isChangingConfigurations();
        if(--activityReferences == 0 && !isActivityChangingConfigurations){
            Intent intent = new Intent(App.this, BackgroundSoundService.class);
            stopService(intent);
        }

    }

    @Override
    public void onActivitySaveInstanceState(@NonNull Activity activity, @NonNull Bundle outState) {

    }

    @Override
    public void onActivityDestroyed(@NonNull Activity activity) {

    }
}

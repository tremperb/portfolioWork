package com.example.starwarsdirectory;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.OnLifecycleEvent;
import androidx.preference.PreferenceManager;

import android.app.ActivityManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import com.example.starwarsdirectory.utils.themeUtils;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements SharedPreferences.OnSharedPreferenceChangeListener {
    private static final String TAG = MainActivity.class.getSimpleName();

    private SharedPreferences sharedPreferences;
    private String theme;
    private Integer volume;
    private Button peopleButton, planetsButton, filmsButton;
    private Button speciesButton, vehiclesButton, starshipsButton;
    private AudioManager manager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Theme needs to be changed before setting content view
        themeUtils.onCreateSetTheme(this);
        setContentView(R.layout.activity_main);

        setVolumeControlStream(AudioManager.STREAM_MUSIC);

        // Assign buttons so we can add some listeners
        this.peopleButton = findViewById(R.id.button_people);
        this.planetsButton = findViewById(R.id.button_planets);
        this.filmsButton = findViewById(R.id.button_films);
        this.speciesButton = findViewById(R.id.button_species);
        this.vehiclesButton = findViewById(R.id.button_vehicles);
        this.starshipsButton = findViewById(R.id.button_starships);
        // End button assignments


        // Set up for settings menu for volume and theme
        this.sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        this.sharedPreferences.registerOnSharedPreferenceChangeListener(this);

        this.theme = sharedPreferences.getString(
                getString(R.string.pref_theme_key),
                getString(R.string.pref_theme_default)
        );

        // Only change theme on create if current value is is different
        // otherwise it will cause loop since you need to finish activity
        if(!themeUtils.getCurrentTheme().equals(this.theme)) {
            themeUtils.changeTheme(this, this.theme, null, null);
        }

        // Note that volume is int
        // I have it set in a range of 0 to 100 for now
        // that may need to be adjusted depending on how the sound works
        this.volume = sharedPreferences.getInt(
                getString(R.string.pref_volume_key),
                R.integer.pref_volume_default
        );
        // End settings

        //Themesong settings
        this.manager = (AudioManager)this.getSystemService(Context.AUDIO_SERVICE);
        if(sharedPreferences.getBoolean("Play Theme", true) && !manager.isMusicActive()) {
            this.PlayThemeSong();
        }

        // Create listeners to start activities

        this.peopleButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchCategoryActivity(getString(R.string.app_people));
                Log.d(TAG, "Launch people activity");
            }
        });

        this.planetsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchCategoryActivity(getString(R.string.app_planets));
                Log.d(TAG, "Launch planets activity");
            }
        });

        this.filmsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchCategoryActivity(getString(R.string.app_films));
                Log.d(TAG, "Launch films activity");
            }
        });

        this.speciesButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchCategoryActivity(getString(R.string.app_species));
                Log.d(TAG, "Launch species activity");
            }
        });

        this.vehiclesButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchCategoryActivity(getString(R.string.app_vehicles));
                Log.d(TAG, "Launch vehicles activity");
            }
        });

        this.starshipsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                launchCategoryActivity(getString(R.string.app_starships));
                Log.d(TAG, "Launch starships activity");
            }
        });

    }

    private void launchCategoryActivity(String displayName){
        Intent intent = new Intent(this, CategoryActivity.class);
        intent.putExtra(CategoryActivity.EXTRA_CATEGORYTYPE, displayName);
        startActivity(intent);
    }

    @Override
    protected void onStart() {
        super.onStart();
        if(sharedPreferences.getBoolean("Play Theme", true) && !manager.isMusicActive()) {
            this.PlayThemeSong();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        // Small fix since recreate isnt called when returning to screen
        // so when returning from settings
        if(!themeUtils.getCurrentActivity().equals(this)) {
            themeUtils.onCreateSetTheme(this);
            themeUtils.changeTheme(themeUtils.getCurrentActivity(), this.theme, null, null);
        }
        if(sharedPreferences.getBoolean("Play Theme", true) && !manager.isMusicActive()) {
            this.PlayThemeSong();
        }
    }



    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        // destroy preferences
        this.sharedPreferences.unregisterOnSharedPreferenceChangeListener(this);
        super.onDestroy();
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        // Update theme or volume
        // note volume is an Integer
        // just saving the vals rn haven't actually adjusted anything
        if(TextUtils.equals(key, getString(R.string.pref_theme_key))) {
            this.theme = sharedPreferences.getString(
                    getString(R.string.pref_theme_key),
                    getString(R.string.pref_theme_default)
            );
            // Apply the theme change
            // want it to show at the current activity you are on
            themeUtils.changeTheme(themeUtils.getCurrentActivity(), sharedPreferences.getString(key, ""), null, null);
            Log.d(TAG, "Shared prefs changed, key: " + key + ", value: " + sharedPreferences.getString(key, ""));
        }
        if(TextUtils.equals(key, getString(R.string.pref_button_play))) {
            if(!sharedPreferences.getBoolean(key, false)){
                this.StopThemeSong();
            } else {
                this.PlayThemeSong();
            }
        }
        if(TextUtils.equals(key, getString(R.string.pref_volume_key))){
            AudioManager manager = (AudioManager)this.getSystemService(Context.AUDIO_SERVICE);
            this.volume = sharedPreferences.getInt(
                    getString(R.string.pref_volume_key),
                    R.integer.pref_volume_default
            );
            this.manager.setStreamVolume(AudioManager.STREAM_MUSIC, this.volume, 0);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                Intent intent = new Intent(this, SettingsActivity.class);
                startActivity(intent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void PlayThemeSong(){
        Intent intent = new Intent(MainActivity.this, BackgroundSoundService.class);
        startService(intent);
    }

    public void StopThemeSong(){
        Intent intent = new Intent(MainActivity.this, BackgroundSoundService.class);
        stopService(intent);
    }
}
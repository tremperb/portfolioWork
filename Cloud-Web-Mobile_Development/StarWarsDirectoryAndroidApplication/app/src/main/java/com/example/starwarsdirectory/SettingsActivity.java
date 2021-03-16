package com.example.starwarsdirectory;

import android.app.Activity;
import android.os.Bundle;
import android.view.MenuItem;

import androidx.appcompat.app.AppCompatActivity;

import com.example.starwarsdirectory.utils.themeUtils;

public class SettingsActivity extends AppCompatActivity {
    private static final String TAG = SettingsActivity.class.getSimpleName();
    public static final String EXTRA_LAUNCH_ACTIVITY = "XXXXActivity.class";
    private Activity previousActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Initialize theme for activity
        themeUtils.onCreateSetTheme(this);
        setContentView(R.layout.activity_settings);

    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                onBackPressed();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        // this method works to bring back to previous activity but then can't call resume to set theme except for on
        // the main activity so idk
    }
}
